#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wpointer-sign"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#ifndef _LANGUAGE_C
#define _LANGUAGE_C
#endif

#ifndef TARGET_SWITCH
#define GLEW_STATIC
# include <GL/glew.h>
#endif

#include <PR/gbi.h>

#include "config.h"

#include "gfx_pc.h"
#include "gfx_cc.h"
#include "gfx_window_manager_api.h"
#include "gfx_rendering_api.h"
#include "gfx_screen_config.h"

#include "../platform.h"
#include "../configfile.h"
#include "../fs/fs.h"
#include "../cheats.h"

#define SUPPORT_CHECK(x) assert(x)

// SCALE_M_N: upscale/downscale M-bit integer to N-bit
#define SCALE_5_8(VAL_) (((VAL_) * 0xFF) / 0x1F)
#define SCALE_8_5(VAL_) ((((VAL_) + 4) * 0x1F) / 0xFF)
#define SCALE_4_8(VAL_) ((VAL_) * 0x11)
#define SCALE_8_4(VAL_) ((VAL_) / 0x11)
#define SCALE_3_8(VAL_) ((VAL_) * 0x24)
#define SCALE_8_3(VAL_) ((VAL_) / 0x24)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define HALF_SCREEN_WIDTH (SCREEN_WIDTH / 2)
#define HALF_SCREEN_HEIGHT (SCREEN_HEIGHT / 2)

#define RATIO_X (gfx_current_dimensions.width / (2.0f * HALF_SCREEN_WIDTH))
#define RATIO_Y (gfx_current_dimensions.height / (2.0f * HALF_SCREEN_HEIGHT))

#ifdef GFX_MAX_BUFFERED
#define MAX_BUFFERED GFX_MAX_BUFFERED
#else
#define MAX_BUFFERED 256
#endif

#define MAX_LIGHTS 2
#define MAX_VERTICES 64

# define MAX_CACHED_TEXTURES 4096 // for preloading purposes
# define HASH_SHIFT 0

#define HASHMAP_LEN (MAX_CACHED_TEXTURES * 2)
#define HASH_MASK (HASHMAP_LEN - 1)

struct RGBA {
    uint8_t r, g, b, a;
};

struct XYWidthHeight {
    uint16_t x, y, width, height;
};

struct LoadedVertex {
    float x, y, z, w;
#ifdef GFX_OUTPUT_NORMALS_TO_VBO
    float nx, ny, nz;
#endif
    float u, v;
    struct RGBA color;
#ifndef GFX_SEPARATE_PROJECTIONS
    uint8_t clip_rej;
#endif
};

struct TextureHashmapNode {
    struct TextureHashmapNode *next;
    
    const uint8_t *texture_addr;
    uint8_t fmt, siz;
    
    uint32_t texture_id;
    uint8_t cms, cmt;
    bool linear_filter;
};
static struct {
    struct TextureHashmapNode *hashmap[HASHMAP_LEN];
    struct TextureHashmapNode pool[MAX_CACHED_TEXTURES];
    uint32_t pool_pos;
} gfx_texture_cache;

struct ColorCombiner {
    uint32_t cc_id;
    struct ShaderProgram *prg;
    uint8_t shader_input_mapping[2][4];
};

static struct ColorCombiner color_combiner_pool[64];
static uint8_t color_combiner_pool_size;

static struct RSP {
    float modelview_matrix_stack[11][4][4];
    uint8_t modelview_matrix_stack_size;
    
    float MP_matrix[4][4];
    float P_matrix[4][4];
    
    Light_t current_lights[MAX_LIGHTS + 1];
    float current_lights_coeffs[MAX_LIGHTS][3];
    float current_lookat_coeffs[2][3]; // lookat_x, lookat_y
    uint8_t current_num_lights; // includes ambient light
    bool lights_changed;
    
    uint32_t geometry_mode;
    int16_t fog_mul, fog_offset;
    
    struct {
        // U0.16
        uint16_t s, t;
    } texture_scaling_factor;
    
    struct LoadedVertex loaded_vertices[MAX_VERTICES + 4];
} rsp;

static struct RDP {
    const uint8_t *palette;
    struct {
        const uint8_t *addr;
        uint8_t siz;
        uint8_t tile_number;
    } texture_to_load;
    struct {
        const uint8_t *addr;
        uint32_t size_bytes;
    } loaded_texture[2];
    struct {
        uint8_t fmt;
        uint8_t siz;
        uint8_t cms, cmt;
        uint16_t uls, ult, lrs, lrt; // U10.2
        uint32_t line_size_bytes;
    } texture_tile;
    bool textures_changed[2];
    
    uint32_t other_mode_l, other_mode_h;
    uint32_t combine_mode;
    
    struct RGBA env_color, prim_color, fog_color, fill_color;
    struct XYWidthHeight viewport, scissor;
    bool viewport_or_scissor_changed;
    void *z_buf_address;
    void *color_image_address;
} rdp;

static struct RenderingState {
    bool depth_test;
    bool depth_mask;
    bool decal_mode;
    bool alpha_blend;
    struct XYWidthHeight viewport, scissor;
    struct ShaderProgram *shader_program;
    struct TextureHashmapNode *textures[2];
} rendering_state;

struct GfxDimensions gfx_current_dimensions;

static bool dropped_frame;

static float buf_vbo[MAX_BUFFERED * (26 * 3)]; // 3 vertices in a triangle and 26 floats per vtx
static size_t buf_vbo_len;
static size_t buf_vbo_num_tris;

static struct GfxWindowManagerAPI *gfx_wapi;
static struct GfxRenderingAPI *gfx_rapi;

// 4x4 pink-black checkerboard texture to indicate missing textures
#define MISSING_W 4
#define MISSING_H 4
static const uint8_t missing_texture[MISSING_W * MISSING_H * 4] = {
    0xFF, 0x00, 0xFF, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,  0x00, 0x00, 0x00, 0xFF,  0x00, 0x00, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,  0x00, 0x00, 0x00, 0xFF,  0x00, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x00, 0xFF,  0x00, 0x00, 0x00, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,
    0x00, 0x00, 0x00, 0xFF,  0x00, 0x00, 0x00, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,  0xFF, 0x00, 0xFF, 0xFF,
};

static inline size_t string_hash(const uint8_t *str) {
    size_t h = 0;
    for (const uint8_t *p = str; *p; p++)
        h = 31 * h + *p;
    return h;
}

static unsigned long get_time(void) {
    return 0;
}

#ifdef GFX_SEPARATE_PROJECTIONS

#include "goddard/gd_math.h"

typedef struct {
    float model_matrix[4][4];
    float inv_model_matrix[4][4];
    float extra_model_matrix[4][4];
    float camera_matrix[4][4];
    float modified_camera_matrix[4][4];
    float graph_view_matrix[4][4];
    float graph_inv_view_matrix[4][4];
    float prev_model_matrix[4][4];
    float offset_matrix[4][4];
} Matrices;
    
static struct {
    bool model_matrix_used;
    bool is_ortho;
    bool double_sided;
    bool persp_triangles_drawn;
    bool camera_matrix_set;
    s32 current_uid;
    Matrices mat;
} separate_projections;

void gfx_set_camera_perspective(float fov_degrees, float near_dist, float far_dist, bool can_interpolate) {
    gfx_rapi->set_camera_perspective(fov_degrees, near_dist, far_dist, can_interpolate);
}

void gfx_set_camera_matrix(float mat[4][4]) {
    // Store camera matrix.
    memcpy(separate_projections.mat.camera_matrix, mat, sizeof(float) * 16);
    gfx_rapi->set_camera_matrix(separate_projections.mat.camera_matrix);

    // Since this call comes from the graph node, store it so we can reverse its effect 
    // on the model view matrices later.
    memcpy(separate_projections.mat.graph_view_matrix, mat, sizeof(float) * 16);
    gd_inverse_mat4f(&separate_projections.mat.graph_view_matrix, &separate_projections.mat.graph_inv_view_matrix);

    separate_projections.camera_matrix_set = true;
}

bool is_affine(float mat[4][4]) {
    return (mat[0][3] == 0.0f) && (mat[1][3] == 0.0f) && (mat[2][3] == 0.0f) && (mat[3][3] == 1.0f);
}

void inverse_affine(Mat4f *src, Mat4f *dst) {
    float m10 = (*src)[0][1], m11 = (*src)[1][1], m12 = (*src)[2][1];
    float m20 = (*src)[0][2], m21 = (*src)[1][2], m22 = (*src)[2][2];

    float t00 = m22 * m11 - m21 * m12;
    float t10 = m20 * m12 - m22 * m10;
    float t20 = m21 * m10 - m20 * m11;

    float m00 = (*src)[0][0], m01 = (*src)[1][0], m02 = (*src)[2][0];

    float invDet = 1.0f / (m00 * t00 + m01 * t10 + m02 * t20);

    t00 *= invDet; t10 *= invDet; t20 *= invDet;

    m00 *= invDet; m01 *= invDet; m02 *= invDet;

    float r00 = t00;
    float r01 = m02 * m21 - m01 * m22;
    float r02 = m01 * m12 - m02 * m11;

    float r10 = t10;
    float r11 = m00 * m22 - m02 * m20;
    float r12 = m02 * m10 - m00 * m12;

    float r20 = t20;
    float r21 = m01 * m20 - m00 * m21;
    float r22 = m00 * m11 - m01 * m10;

    float m03 = (*src)[3][0], m13 = (*src)[3][1], m23 = (*src)[3][2];

    float r03 = -(r00 * m03 + r01 * m13 + r02 * m23);
    float r13 = -(r10 * m03 + r11 * m13 + r12 * m23);
    float r23 = -(r20 * m03 + r21 * m13 + r22 * m23);

    (*dst)[0][0] = r00; (*dst)[1][0] = r01; (*dst)[2][0] = r02; (*dst)[3][0] = r03;
    (*dst)[0][1] = r10; (*dst)[1][1] = r11; (*dst)[2][1] = r12; (*dst)[3][1] = r13;
    (*dst)[0][2] = r20; (*dst)[1][2] = r21; (*dst)[2][2] = r22; (*dst)[3][2] = r23;
    (*dst)[0][3] = 0.0f; (*dst)[1][3] = 0.0f; (*dst)[2][3] = 0.0f; (*dst)[3][3] = 1.0f;
}

bool is_identity(float mat[4][4]) {
    return
        mat[0][0] == 1.0f && mat[1][0] == 0.0f && mat[2][0] == 0.0f && mat[3][0] == 0.0f &&
        mat[0][1] == 0.0f && mat[1][1] == 1.0f && mat[2][1] == 0.0f && mat[3][1] == 0.0f &&
        mat[0][2] == 0.0f && mat[1][2] == 0.0f && mat[2][2] == 1.0f && mat[3][2] == 0.0f &&
        mat[0][3] == 0.0f && mat[1][3] == 0.0f && mat[2][3] == 0.0f && mat[3][3] == 1.0f;
}

void transform_loaded_vertex(size_t i, Mat4f *src) {
    struct LoadedVertex *d = &rsp.loaded_vertices[i];
    float x = d->x * (*src)[0][0] + d->y * (*src)[1][0] + d->z * (*src)[2][0] + (*src)[3][0];
    float y = d->x * (*src)[0][1] + d->y * (*src)[1][1] + d->z * (*src)[2][1] + (*src)[3][1];
    float z = d->x * (*src)[0][2] + d->y * (*src)[1][2] + d->z * (*src)[2][2] + (*src)[3][2];
    d->x = x;
    d->y = y;
    d->z = z;

#ifdef GFX_OUTPUT_NORMALS_TO_VBO
    float nx = d->nx * (*src)[0][0] + d->ny * (*src)[1][0] + d->nz * (*src)[2][0];
    float ny = d->nx * (*src)[0][1] + d->ny * (*src)[1][1] + d->nz * (*src)[2][1];
    float nz = d->nx * (*src)[0][2] + d->ny * (*src)[1][2] + d->nz * (*src)[2][2];
    d->nx = nx;
    d->ny = ny;
    d->nz = nz;
#endif
}

#endif

static void gfx_flush(void) {
    if (buf_vbo_len > 0) {
        int num = buf_vbo_num_tris;
        unsigned long t0 = get_time();
#ifndef GFX_SEPARATE_PROJECTIONS
        gfx_rapi->draw_triangles(buf_vbo, buf_vbo_len, buf_vbo_num_tris);
#else
        if (separate_projections.is_ortho) {
            // TODO: An empty UID is passed because the drawing order is not currently preserved properly for 2D instances if it's used.
            // This should ideally be reverted once a way to preserve the drawing order is implemented. However, it's not required to do
            // this until HUD interpolation is supported.
            gfx_rapi->draw_triangles_ortho(buf_vbo, buf_vbo_len, buf_vbo_num_tris, separate_projections.double_sided, 0);
        }
        else {
            gfx_rapi->draw_triangles_persp(buf_vbo, buf_vbo_len, buf_vbo_num_tris, separate_projections.mat.model_matrix, separate_projections.double_sided, separate_projections.current_uid);
            separate_projections.persp_triangles_drawn = true;
        }

        separate_projections.double_sided = false;
#endif
        buf_vbo_len = 0;
        buf_vbo_num_tris = 0;
        unsigned long t1 = get_time();
        /*if (t1 - t0 > 1000) {
            printf("f: %d %d\n", num, (int)(t1 - t0));
        }*/
    }
}

static struct ShaderProgram *gfx_lookup_or_create_shader_program(uint32_t shader_id) {
    struct ShaderProgram *prg = gfx_rapi->lookup_shader(shader_id);
    if (prg == NULL) {
        gfx_rapi->unload_shader(rendering_state.shader_program);
        prg = gfx_rapi->create_and_load_new_shader(shader_id);
        rendering_state.shader_program = prg;
    }
    return prg;
}

static void gfx_generate_cc(struct ColorCombiner *comb, uint32_t cc_id) {
    uint8_t c[2][4];
    uint32_t shader_id = (cc_id >> 24) << 24;
    uint8_t shader_input_mapping[2][4] = {{0}};
    for (int i = 0; i < 4; i++) {
        c[0][i] = (cc_id >> (i * 3)) & 7;
        c[1][i] = (cc_id >> (12 + i * 3)) & 7;
    }
    for (int i = 0; i < 2; i++) {
        if (c[i][0] == c[i][1] || c[i][2] == CC_0) {
            c[i][0] = c[i][1] = c[i][2] = 0;
        }
        uint8_t input_number[8] = {0};
        int next_input_number = SHADER_INPUT_1;
        for (int j = 0; j < 4; j++) {
            int val = 0;
            switch (c[i][j]) {
                case CC_0:
                    break;
                case CC_TEXEL0:
                    val = SHADER_TEXEL0;
                    break;
                case CC_TEXEL1:
                    val = SHADER_TEXEL1;
                    break;
                case CC_TEXEL0A:
                    val = SHADER_TEXEL0A;
                    break;
                case CC_PRIM:
                case CC_SHADE:
                case CC_ENV:
                case CC_LOD:
                    if (input_number[c[i][j]] == 0) {
                        shader_input_mapping[i][next_input_number - 1] = c[i][j];
                        input_number[c[i][j]] = next_input_number++;
                    }
                    val = input_number[c[i][j]];
                    break;
            }
            shader_id |= val << (i * 12 + j * 3);
        }
    }
    comb->cc_id = cc_id;
    comb->prg = gfx_lookup_or_create_shader_program(shader_id);
    memcpy(comb->shader_input_mapping, shader_input_mapping, sizeof(shader_input_mapping));
}

static struct ColorCombiner *gfx_lookup_or_create_color_combiner(uint32_t cc_id) {
    static struct ColorCombiner *prev_combiner;
    if (prev_combiner != NULL && prev_combiner->cc_id == cc_id) {
        return prev_combiner;
    }
    
    for (size_t i = 0; i < color_combiner_pool_size; i++) {
        if (color_combiner_pool[i].cc_id == cc_id) {
            return prev_combiner = &color_combiner_pool[i];
        }
    }
    gfx_flush();
    struct ColorCombiner *comb = &color_combiner_pool[color_combiner_pool_size++];
    gfx_generate_cc(comb, cc_id);
    return prev_combiner = comb;
}

static bool gfx_texture_cache_lookup(int tile, struct TextureHashmapNode **n, const uint8_t *orig_addr, uint32_t fmt, uint32_t siz) {
    size_t hash = string_hash(orig_addr);
    #define CMPADDR(x, y) (x && !sys_strcasecmp((const char *)x, (const char *)y))

    hash = (hash >> HASH_SHIFT) & HASH_MASK;

    struct TextureHashmapNode **node = &gfx_texture_cache.hashmap[hash];
    while (*node != NULL && *node - gfx_texture_cache.pool < gfx_texture_cache.pool_pos) {
        if (CMPADDR((*node)->texture_addr, orig_addr) && (*node)->fmt == fmt && (*node)->siz == siz) {
            gfx_rapi->select_texture(tile, (*node)->texture_id);
            *n = *node;
            return true;
        }
        node = &(*node)->next;
    }
    if (gfx_texture_cache.pool_pos == sizeof(gfx_texture_cache.pool) / sizeof(struct TextureHashmapNode)) {
        // Pool is full. We just invalidate everything and start over.
        gfx_texture_cache.pool_pos = 0;
        node = &gfx_texture_cache.hashmap[hash];
        // puts("Clearing texture cache");
    }
    *node = &gfx_texture_cache.pool[gfx_texture_cache.pool_pos++];
    if ((*node)->texture_addr == NULL) {
#ifdef GFX_REQUIRE_TEXTURE_NAME
        (*node)->texture_id = gfx_rapi->new_texture((const char *)(orig_addr));
#else
        (*node)->texture_id = gfx_rapi->new_texture();
#endif
    }
    gfx_rapi->select_texture(tile, (*node)->texture_id);
    gfx_rapi->set_sampler_parameters(tile, false, 0, 0);
    (*node)->cms = 0;
    (*node)->cmt = 0;
    (*node)->linear_filter = false;
    (*node)->next = NULL;
    (*node)->texture_addr = orig_addr;
    (*node)->fmt = fmt;
    (*node)->siz = siz;
    *n = *node;
    return false;
    #undef CMPADDR
}

static inline void load_texture(const char *fullpath) {
    int w, h;
    u64 imgsize = 0;

    u8 *imgdata = fs_load_file(fullpath, &imgsize);
    if (imgdata) {
#ifndef GFX_UPLOAD_TEXTURE_FILE
        // TODO: implement stbi_callbacks or some shit instead of loading the whole texture
        u8 *data = stbi_load_from_memory(imgdata, imgsize, &w, &h, NULL, 4);
        free(imgdata);
        if (data) {
            gfx_rapi->upload_texture(data, w, h);
            stbi_image_free(data); // don't need this anymore
            return;
        }
#else
        gfx_rapi->upload_texture_file(fullpath, imgdata, imgsize);
        free(imgdata);
        return;
#endif
    }

    fprintf(stderr, "could not load texture: `%s`\n", fullpath);
    // replace with missing texture
    gfx_rapi->upload_texture(missing_texture, MISSING_W, MISSING_H);
}


// this is taken straight from n64graphics
static bool texname_to_texformat(const char *name, u8 *fmt, u8 *siz) {
    static const struct {
        const char *name;
        const u8 format;
        const u8 size;
    } fmt_table[] = {
        { "rgba16", G_IM_FMT_RGBA, G_IM_SIZ_16b },
        { "rgba32", G_IM_FMT_RGBA, G_IM_SIZ_32b },
        { "ia1",    G_IM_FMT_IA,   G_IM_SIZ_8b  }, // uhh
        { "ia4",    G_IM_FMT_IA,   G_IM_SIZ_4b  },
        { "ia8",    G_IM_FMT_IA,   G_IM_SIZ_8b  },
        { "ia16",   G_IM_FMT_IA,   G_IM_SIZ_16b },
        { "i4",     G_IM_FMT_I,    G_IM_SIZ_4b  },
        { "i8",     G_IM_FMT_I,    G_IM_SIZ_8b  },
        { "ci8",    G_IM_FMT_I,    G_IM_SIZ_8b  },
        { "ci16",   G_IM_FMT_I,    G_IM_SIZ_16b },
    };

    char *fstr = strrchr(name, '.');
    if (!fstr) return false; // no format string?
    fstr++;

    for (unsigned i = 0; i < sizeof(fmt_table) / sizeof(fmt_table[0]); ++i) {
        if (!sys_strcasecmp(fstr, fmt_table[i].name)) {
            *fmt = fmt_table[i].format;
            *siz = fmt_table[i].size;
            return true;
        }
    }

    return false;
}

// calls import_texture() on every texture in the res folder
// we can get the format and size from the texture files
// and then cache them using gfx_texture_cache_lookup
static bool preload_texture(void *user, const char *path) {
    // strip off the extension
    char texname[SYS_MAX_PATH];
    strncpy(texname, path, sizeof(texname));
    texname[sizeof(texname)-1] = 0;
    char *dot = strrchr(texname, '.');
    if (dot) *dot = 0;

    // get the format and size from filename
    u8 fmt, siz;
    if (!texname_to_texformat(texname, &fmt, &siz)) {
        fprintf(stderr, "unknown texture format: `%s`, skipping\n", texname);
        return true; // just skip it, might be a stray skybox or something
    }

    char *actualname = texname;
    // strip off the prefix // TODO: make a fs_ function for this shit
    if (!strncmp(FS_TEXTUREDIR "/", actualname, 4)) actualname += 4;
    // this will be stored in the hashtable, so make a copy
    actualname = sys_strdup(actualname);
    assert(actualname);

    struct TextureHashmapNode *n;
    if (!gfx_texture_cache_lookup(0, &n, actualname, fmt, siz))
        load_texture(path); // new texture, load it

    return true;
}

#ifdef GFX_SEPARATE_SKYBOX

#define MAX_SKYBOX_COUNT 10
#define MAX_SKYBOX_EXTENSIONS 2

#define SKYBOX_DIR FS_TEXTUREDIR "/textures/skyboxes/"

const char *skybox_base_paths[MAX_SKYBOX_COUNT] = {
    SKYBOX_DIR "water",
    SKYBOX_DIR "bitfs",
    SKYBOX_DIR "wdw",
    SKYBOX_DIR "cloud_floor",
    SKYBOX_DIR "ccm",
    SKYBOX_DIR "ssl",
    SKYBOX_DIR "bbh",
    SKYBOX_DIR "bidw",
    SKYBOX_DIR "clouds",
    SKYBOX_DIR "bits"
};

const char *skybox_extensions[MAX_SKYBOX_EXTENSIONS] = {
    "dds",
    "png"
};

struct {
    uint32_t textures[MAX_SKYBOX_COUNT];
} skybox;

void gfx_preload_skybox(uint8_t skybox_id) {
    const char *skyboxBasePath = skybox_base_paths[skybox_id];
    skybox.textures[skybox_id] = gfx_rapi->new_texture(skyboxBasePath);
    gfx_rapi->select_texture(0, skybox.textures[skybox_id]);

    // Search for the different file extensions the skybox texture could have.
    char skyboxPath[64];
    for (int e = 0; e < MAX_SKYBOX_EXTENSIONS; e++) {
        snprintf(skyboxPath, 64, "%s.rgba16.%s", skyboxBasePath, skybox_extensions[e]);
        if (fs_is_file(skyboxPath)) {
            load_texture(skyboxPath);
            break;
        }
    }
}

void gfx_init_skybox() {
    // Preload all the skyboxes so there's no stutter when loading the levels.
    for (int i = 0; i < MAX_SKYBOX_COUNT; i++) {
        gfx_preload_skybox(i);
    }
}

void gfx_set_skybox(uint8_t skybox_id, float diffuse_color[3]) {
    gfx_rapi->set_skybox(skybox.textures[skybox_id], diffuse_color);
}

#endif

static void import_texture(int tile) {
    extern s32 dynos_gfx_import_texture(void **output, void *ptr, s32 tile, void *grapi, void **hashmap, void *pool, s32 *poolpos, s32 poolsize);
    if (dynos_gfx_import_texture((void **) &rendering_state.textures[tile], (void *) rdp.loaded_texture[tile].addr, tile, gfx_rapi, (void **) gfx_texture_cache.hashmap, (void *) gfx_texture_cache.pool, (int *) &gfx_texture_cache.pool_pos, MAX_CACHED_TEXTURES)) {
        return;
    }
    uint8_t fmt = rdp.texture_tile.fmt;
    uint8_t siz = rdp.texture_tile.siz;

    if (!rdp.loaded_texture[tile].addr) {
        fprintf(stderr, "NULL texture: tile %d, format %d/%d, size %d\n",
                tile, (int)fmt, (int)siz, (int)rdp.loaded_texture[tile].size_bytes);
        return;
    }

    if (gfx_texture_cache_lookup(tile, &rendering_state.textures[tile], rdp.loaded_texture[tile].addr, fmt, siz)) {
        return;
    }

    // the "texture data" is actually a C string with the path to our texture in it
    // load it from an external image in our data path
    char texname[SYS_MAX_PATH];
    snprintf(texname, sizeof(texname), FS_TEXTUREDIR "/%s.png", (const char*)rdp.loaded_texture[tile].addr);
    load_texture(texname);
}

static void gfx_normalize_vector(float v[3]) {
    float s = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= s;
    v[1] /= s;
    v[2] /= s;
}

static void gfx_transposed_matrix_mul(float res[3], const float a[3], const float b[4][4]) {
    res[0] = a[0] * b[0][0] + a[1] * b[0][1] + a[2] * b[0][2];
    res[1] = a[0] * b[1][0] + a[1] * b[1][1] + a[2] * b[1][2];
    res[2] = a[0] * b[2][0] + a[1] * b[2][1] + a[2] * b[2][2];
}

static void calculate_normal_dir(const Light_t *light, float coeffs[3]) {
    float light_dir[3] = {
        light->dir[0] / 127.0f,
        light->dir[1] / 127.0f,
        light->dir[2] / 127.0f
    };
    gfx_transposed_matrix_mul(coeffs, light_dir, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1]);
    gfx_normalize_vector(coeffs);
}

static void gfx_matrix_mul(float res[4][4], const float a[4][4], const float b[4][4]) {
    float tmp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tmp[i][j] = a[i][0] * b[0][j] +
                        a[i][1] * b[1][j] +
                        a[i][2] * b[2][j] +
                        a[i][3] * b[3][j];
        }
    }
    memcpy(res, tmp, sizeof(tmp));
}

static void gfx_sp_matrix(uint8_t parameters, const int32_t *addr) {
    float matrix[4][4];
#if 0
    // Original code when fixed point matrices were used
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j += 2) {
            int32_t int_part = addr[i * 2 + j / 2];
            uint32_t frac_part = addr[8 + i * 2 + j / 2];
            matrix[i][j] = (int32_t)((int_part & 0xffff0000) | (frac_part >> 16)) / 65536.0f;
            matrix[i][j + 1] = (int32_t)((int_part << 16) | (frac_part & 0xffff)) / 65536.0f;
        }
    }
#else
    memcpy(matrix, addr, sizeof(matrix));
#endif

    if (parameters & G_MTX_PROJECTION) {
        if (parameters & G_MTX_LOAD) {
            if (Cheats.EnableCheats && Cheats.ChaosMode) {
                if ((Cheats.ChaosInvertedScreen >> 0) & 1) {
                    matrix[0][0] *= -1;
                }
                if ((Cheats.ChaosInvertedScreen >> 1) & 1) {
                    matrix[1][1] *= -1;
                }
            }
            memcpy(rsp.P_matrix, matrix, sizeof(matrix));
#ifdef GFX_SEPARATE_PROJECTIONS
            gd_set_identity_mat4(&separate_projections.mat.extra_model_matrix);
            separate_projections.is_ortho = (matrix[3][3] != 0.0f);
#endif
        } else {
            gfx_matrix_mul(rsp.P_matrix, matrix, rsp.P_matrix);

#ifdef GFX_SEPARATE_PROJECTIONS
            // If a view/model matrix (affine) gets pushed into the projection matrix, we multiply and add its effect to
            // the model matrices that get used afterwards.
            //
            // This is used in three separate instances in the game:
            // - Goddard uses it to store the model matrix in the projection matrix, probably due to the dynamic light sources.
            // - When Mario gets hurt an offset is applied to the view matrix.
            // - One of the camera shots when Mario collects a key from Bowser rotates the view matrix.
            //
            // However, an additional condition is checked to know if any triangles have already been drawn as
            // part of the perspective view. This is because parts of the game can add a slight offset to the camera
            // by modifying this matrix without actually affecting the camera matrix that is first used, since the
            // offset is not part of the modelview stack.
            //
            // Effectively, this means the game can use this to either correct a model into position (like the Goddard head),
            // or to move the camera without moving its node. This condition could break at any moment if the game chooses to
            // do something more elaborate, but it avoids having to add a lot of extra logic that would be needed to handle 
            // multiple types of perspectives being rendered in the same frame.
            if (!separate_projections.is_ortho && is_affine(matrix) && !is_identity(matrix)) {
                // Fixes Lakitu camera shake and Bowser key cutscene by adding the offset to the camera matrix.
                if (separate_projections.camera_matrix_set && !separate_projections.persp_triangles_drawn) {
                    gfx_matrix_mul(separate_projections.mat.modified_camera_matrix, separate_projections.mat.camera_matrix, matrix);
                    gfx_rapi->set_camera_matrix(separate_projections.mat.modified_camera_matrix);
                }
                // Fixes Goddard by adding the offset to the model matrix.
                else {
                    gfx_matrix_mul(separate_projections.mat.extra_model_matrix, separate_projections.mat.extra_model_matrix, matrix);
                }
            }
#endif
        }
    } else { // G_MTX_MODELVIEW
        if ((parameters & G_MTX_PUSH) && rsp.modelview_matrix_stack_size < 11) {
            ++rsp.modelview_matrix_stack_size;
            memcpy(rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 2], sizeof(matrix));
        }
        if (parameters & G_MTX_LOAD) {
            memcpy(rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], matrix, sizeof(matrix));
        } else {
            gfx_matrix_mul(rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], matrix, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1]);
        }
        rsp.lights_changed = 1;
    }
    gfx_matrix_mul(rsp.MP_matrix, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], rsp.P_matrix);

#ifdef GFX_SEPARATE_PROJECTIONS
    gfx_matrix_mul(separate_projections.mat.model_matrix, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], separate_projections.mat.graph_inv_view_matrix);
    gfx_matrix_mul(separate_projections.mat.model_matrix, separate_projections.mat.model_matrix, separate_projections.mat.extra_model_matrix);
#endif
}

static void gfx_sp_pop_matrix(uint32_t count) {
    while (count--) {
        if (rsp.modelview_matrix_stack_size > 0) {
            --rsp.modelview_matrix_stack_size;
            if (rsp.modelview_matrix_stack_size > 0) {
                gfx_matrix_mul(rsp.MP_matrix, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], rsp.P_matrix);

#ifdef GFX_SEPARATE_PROJECTIONS
                gfx_matrix_mul(separate_projections.mat.model_matrix, rsp.modelview_matrix_stack[rsp.modelview_matrix_stack_size - 1], separate_projections.mat.graph_inv_view_matrix);
                gfx_matrix_mul(separate_projections.mat.model_matrix, separate_projections.mat.model_matrix, separate_projections.mat.extra_model_matrix);
#endif
            }
        }
    }
}

static float gfx_adjust_x_for_aspect_ratio(float x) {
    return x * (4.0f / 3.0f) / ((float)gfx_current_dimensions.width / (float)gfx_current_dimensions.height);
}

static void gfx_sp_vertex(size_t n_vertices, size_t dest_index, const Vtx *vertices) {
#ifdef GFX_SEPARATE_PROJECTIONS
    if (!separate_projections.model_matrix_used) {
        if (dest_index > 0) {
            inverse_affine(&separate_projections.mat.model_matrix, &separate_projections.mat.inv_model_matrix);
            gfx_matrix_mul(separate_projections.mat.offset_matrix, separate_projections.mat.prev_model_matrix, separate_projections.mat.inv_model_matrix);

            for (size_t i = 0; i < dest_index; i++) {
                transform_loaded_vertex(i, &separate_projections.mat.offset_matrix);
            }

            for (size_t i = dest_index + n_vertices; i < MAX_VERTICES; i++) {
                transform_loaded_vertex(i, &separate_projections.mat.offset_matrix);
            }
        }

        memcpy(separate_projections.mat.prev_model_matrix, separate_projections.mat.model_matrix, sizeof(float) * 16);
        separate_projections.model_matrix_used = true;
    }
#endif

    for (size_t i = 0; i < n_vertices; i++, dest_index++) {
        const Vtx_t *v = &vertices[i].v;
        const Vtx_tn *vn = &vertices[i].n;
        struct LoadedVertex *d = &rsp.loaded_vertices[dest_index];
#ifndef GFX_SEPARATE_PROJECTIONS
        float x = v->ob[0] * rsp.MP_matrix[0][0] + v->ob[1] * rsp.MP_matrix[1][0] + v->ob[2] * rsp.MP_matrix[2][0] + rsp.MP_matrix[3][0];
        float y = v->ob[0] * rsp.MP_matrix[0][1] + v->ob[1] * rsp.MP_matrix[1][1] + v->ob[2] * rsp.MP_matrix[2][1] + rsp.MP_matrix[3][1];
        float z = v->ob[0] * rsp.MP_matrix[0][2] + v->ob[1] * rsp.MP_matrix[1][2] + v->ob[2] * rsp.MP_matrix[2][2] + rsp.MP_matrix[3][2];
        float w = v->ob[0] * rsp.MP_matrix[0][3] + v->ob[1] * rsp.MP_matrix[1][3] + v->ob[2] * rsp.MP_matrix[2][3] + rsp.MP_matrix[3][3];
        
        x = gfx_adjust_x_for_aspect_ratio(x);
#else
        float x, y, z, w;
        if (separate_projections.is_ortho) {
            x = v->ob[0] * rsp.MP_matrix[0][0] + v->ob[1] * rsp.MP_matrix[1][0] + v->ob[2] * rsp.MP_matrix[2][0] + rsp.MP_matrix[3][0];
            y = v->ob[0] * rsp.MP_matrix[0][1] + v->ob[1] * rsp.MP_matrix[1][1] + v->ob[2] * rsp.MP_matrix[2][1] + rsp.MP_matrix[3][1];
            z = v->ob[0] * rsp.MP_matrix[0][2] + v->ob[1] * rsp.MP_matrix[1][2] + v->ob[2] * rsp.MP_matrix[2][2] + rsp.MP_matrix[3][2];
            w = v->ob[0] * rsp.MP_matrix[0][3] + v->ob[1] * rsp.MP_matrix[1][3] + v->ob[2] * rsp.MP_matrix[2][3] + rsp.MP_matrix[3][3];
           x = gfx_adjust_x_for_aspect_ratio(x);
        }
        else {
            x = v->ob[0];
            y = v->ob[1];
            z = v->ob[2];
            w = 1.0f;
        }
#endif
        short U = v->tc[0] * rsp.texture_scaling_factor.s >> 16;
        short V = v->tc[1] * rsp.texture_scaling_factor.t >> 16;
        
        if ((rsp.geometry_mode & G_LIGHTING) && !(Cheats.EnableCheats && Cheats.ChaosRainbow)) {
#ifdef GFX_OUTPUT_NORMALS_TO_VBO
            d->nx = vn->n[0] / 127.0f;
            d->ny = vn->n[1] / 127.0f;
            d->nz = vn->n[2] / 127.0f;
#endif
            if (rsp.lights_changed) {
                for (int i = 0; i < rsp.current_num_lights - 1; i++) {
                    calculate_normal_dir(&rsp.current_lights[i], rsp.current_lights_coeffs[i]);
                }
                static const Light_t lookat_x = {{0, 0, 0}, 0, {0, 0, 0}, 0, {127, 0, 0}, 0};
                static const Light_t lookat_y = {{0, 0, 0}, 0, {0, 0, 0}, 0, {0, 127, 0}, 0};
                calculate_normal_dir(&lookat_x, rsp.current_lookat_coeffs[0]);
                calculate_normal_dir(&lookat_y, rsp.current_lookat_coeffs[1]);
                rsp.lights_changed = false;
            }
            
            int r = rsp.current_lights[rsp.current_num_lights - 1].col[0];
            int g = rsp.current_lights[rsp.current_num_lights - 1].col[1];
            int b = rsp.current_lights[rsp.current_num_lights - 1].col[2];
#ifndef GFX_DISABLE_LIGHTING
            for (int i = 0; i < rsp.current_num_lights - 1; i++) {
                float intensity = 0;
                intensity += vn->n[0] * rsp.current_lights_coeffs[i][0];
                intensity += vn->n[1] * rsp.current_lights_coeffs[i][1];
                intensity += vn->n[2] * rsp.current_lights_coeffs[i][2];
                intensity /= 127.0f;
                if (intensity > 0.0f) {
                    r += intensity * rsp.current_lights[i].col[0];
                    g += intensity * rsp.current_lights[i].col[1];
                    b += intensity * rsp.current_lights[i].col[2];
                }
            }
#else
            // Simulated flat lighting with arbitrary value for every light.
            // This can probably be estimated in a more accurate way to get a
            // better color value.
            for (int i = 0; i < rsp.current_num_lights - 1; i++) {
                float intensity = 0.6f;
                r += intensity * rsp.current_lights[i].col[0];
                g += intensity * rsp.current_lights[i].col[1];
                b += intensity * rsp.current_lights[i].col[2];
            }
#endif
            d->color.r = r > 255 ? 255 : r;
            d->color.g = g > 255 ? 255 : g;
            d->color.b = b > 255 ? 255 : b;
            
            if (rsp.geometry_mode & G_TEXTURE_GEN) {
                float dotx = 0, doty = 0;
#ifndef GFX_DISABLE_TEXTURE_GEN
                dotx += vn->n[0] * rsp.current_lookat_coeffs[0][0];
                dotx += vn->n[1] * rsp.current_lookat_coeffs[0][1];
                dotx += vn->n[2] * rsp.current_lookat_coeffs[0][2];
                doty += vn->n[0] * rsp.current_lookat_coeffs[1][0];
                doty += vn->n[1] * rsp.current_lookat_coeffs[1][1];
                doty += vn->n[2] * rsp.current_lookat_coeffs[1][2];
#else
                dotx = vn->n[0];
                doty = vn->n[1];
#endif
                U = (int32_t)((dotx / 127.0f + 1.0f) / 4.0f * rsp.texture_scaling_factor.s);
                V = (int32_t)((doty / 127.0f + 1.0f) / 4.0f * rsp.texture_scaling_factor.t);
            }
        } else {
#ifdef GFX_OUTPUT_NORMALS_TO_VBO
            d->nx = 0.0f;
            d->ny = 0.0f;
            d->nz = 0.0f;
#endif
            d->color.r = v->cn[0];
            d->color.g = v->cn[1];
            d->color.b = v->cn[2];
        }
        
        // Make the whole screen more red, as if the entire world was burning
        if (Cheats.EnableCheats && Cheats.ChaosBowserTime) {
            d->color.g /= 2;
            d->color.b /= 2;
        }
        
        d->u = U;
        d->v = V;
#ifndef GFX_SEPARATE_PROJECTIONS
        // trivial clip rejection
        d->clip_rej = 0;
        if (x < -w) d->clip_rej |= 1;
        if (x > w) d->clip_rej |= 2;
        if (y < -w) d->clip_rej |= 4;
        if (y > w) d->clip_rej |= 8;
        if (z < -w) d->clip_rej |= 16;
        if (z > w) d->clip_rej |= 32;
#endif
        d->x = x;
        d->y = y;
        d->z = z;
        d->w = w;
        
        if (rsp.geometry_mode & G_FOG) {
#ifndef GFX_SEPARATE_FOG
            if (fabsf(w) < 0.001f) {
                // To avoid division by zero
                w = 0.001f;
            }
            
            float winv = 1.0f / w;
            if (winv < 0.0f) {
                winv = 32767.0f;
            }
            
            float fog_z = z * winv * rsp.fog_mul + rsp.fog_offset;
            if (fog_z < 0) fog_z = 0;
            if (fog_z > 255) fog_z = 255;
            d->color.a = fog_z; // Use alpha variable to store fog factor
#else
            d->color.a = 1.0f;
#endif
        } else {
            d->color.a = v->cn[3];
        }
    }
}

static void gfx_sp_tri1(uint8_t vtx1_idx, uint8_t vtx2_idx, uint8_t vtx3_idx) {
#ifdef GFX_SEPARATE_PROJECTIONS
    uint8_t swap = 0;
    switch (rsp.geometry_mode & G_CULL_BOTH) {
        // Ignore this call entirely.
        case G_CULL_BOTH:
            return;
        // Continue as normal.
        case G_CULL_BACK:
            break;
        // Continue as normal.
        case G_CULL_FRONT:
            break;
        // Set the double sided flag, flush if any contents were already processed while the flag was false.
        default:
            if (!separate_projections.double_sided) {
                gfx_flush();
                separate_projections.double_sided = true;
            }
            break;
    }
#endif

    struct LoadedVertex *v1 = &rsp.loaded_vertices[vtx1_idx];
    struct LoadedVertex *v2 = &rsp.loaded_vertices[vtx2_idx];
    struct LoadedVertex *v3 = &rsp.loaded_vertices[vtx3_idx];
    struct LoadedVertex *v_arr[3] = {v1, v2, v3};
    
    //if (rand()%2) return;
#ifndef GFX_SEPARATE_PROJECTIONS
    if (v1->clip_rej & v2->clip_rej & v3->clip_rej) {
        // The whole triangle lies outside the visible area
        return;
    }

    if ((rsp.geometry_mode & G_CULL_BOTH) != 0) {
        float dx1 = v1->x / (v1->w) - v2->x / (v2->w);
        float dy1 = v1->y / (v1->w) - v2->y / (v2->w);
        float dx2 = v3->x / (v3->w) - v2->x / (v2->w);
        float dy2 = v3->y / (v3->w) - v2->y / (v2->w);
        float cross = dx1 * dy2 - dy1 * dx2;
        
        if ((v1->w < 0) ^ (v2->w < 0) ^ (v3->w < 0)) {
            // If one vertex lies behind the eye, negating cross will give the correct result.
            // If all vertices lie behind the eye, the triangle will be rejected anyway.
            cross = -cross;
        }
        
        s32 crossSign;
        if (Cheats.EnableCheats && Cheats.ChaosMode) {
            crossSign = ((((Cheats.ChaosInvertedScreen >> 0) & 1) ^ ((Cheats.ChaosInvertedScreen >> 1) & 1)) ? -1 : +1);
        } else {
            crossSign = +1;
        }
        switch (rsp.geometry_mode & G_CULL_BOTH) {
            case G_CULL_FRONT:
                if (cross * crossSign <= 0) return;
                break;
            case G_CULL_BACK:
                if (cross * crossSign >= 0) return;
                break;
            case G_CULL_BOTH:
                // Why is this even an option?
                return;
        }
    }
#endif
    
    bool depth_test = (rsp.geometry_mode & G_ZBUFFER) == G_ZBUFFER;
    if (depth_test != rendering_state.depth_test) {
        gfx_flush();
        gfx_rapi->set_depth_test(depth_test);
        rendering_state.depth_test = depth_test;
    }
    
    bool z_upd = (rdp.other_mode_l & Z_UPD) == Z_UPD;
    if (z_upd != rendering_state.depth_mask) {
        gfx_flush();
        gfx_rapi->set_depth_mask(z_upd);
        rendering_state.depth_mask = z_upd;
    }
    
    bool zmode_decal = (rdp.other_mode_l & ZMODE_DEC) == ZMODE_DEC;
    if (zmode_decal != rendering_state.decal_mode) {
        gfx_flush();
        gfx_rapi->set_zmode_decal(zmode_decal);
        rendering_state.decal_mode = zmode_decal;
    }
    
    if (rdp.viewport_or_scissor_changed) {
        if (memcmp(&rdp.viewport, &rendering_state.viewport, sizeof(rdp.viewport)) != 0) {
            gfx_flush();
            gfx_rapi->set_viewport(rdp.viewport.x, rdp.viewport.y, rdp.viewport.width, rdp.viewport.height);
            rendering_state.viewport = rdp.viewport;
        }
        if (memcmp(&rdp.scissor, &rendering_state.scissor, sizeof(rdp.scissor)) != 0) {
            gfx_flush();
            gfx_rapi->set_scissor(rdp.scissor.x, rdp.scissor.y, rdp.scissor.width, rdp.scissor.height);
            rendering_state.scissor = rdp.scissor;
        }
        rdp.viewport_or_scissor_changed = false;
    }
    
    uint32_t cc_id = rdp.combine_mode;
    
    bool use_alpha = (rdp.other_mode_l & (G_BL_A_MEM << 18)) == 0;
    bool use_fog = (rdp.other_mode_l >> 30) == G_BL_CLR_FOG;
    bool texture_edge = (rdp.other_mode_l & CVG_X_ALPHA) == CVG_X_ALPHA;
    bool use_noise = (rdp.other_mode_l & G_AC_DITHER) == G_AC_DITHER;
	bool use_coverage = (rdp.other_mode_l & G_AC_COVERAGE) == G_AC_COVERAGE;

#if defined (RAPI_GL) && defined(TRANSPARENCY_GL)
	glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
	glDisable(GL_SAMPLE_ALPHA_TO_ONE);
	if (use_coverage) {
		glDepthMask(GL_TRUE);
        glEnable(GL_MULTISAMPLE);
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		glEnable(GL_SAMPLE_ALPHA_TO_ONE);
	}
#endif

    if (texture_edge) {
        use_alpha = true;
    }
    
    if (use_alpha) cc_id |= SHADER_OPT_ALPHA;
    if (use_fog) cc_id |= SHADER_OPT_FOG;
    if (texture_edge) cc_id |= SHADER_OPT_TEXTURE_EDGE;
    if (use_noise) cc_id |= SHADER_OPT_NOISE;
    
    if (!use_alpha) {
        cc_id &= ~0xfff000;
    }
    
    struct ColorCombiner *comb = gfx_lookup_or_create_color_combiner(cc_id);
    struct ShaderProgram *prg = comb->prg;
    if (prg != rendering_state.shader_program) {
        gfx_flush();
        gfx_rapi->unload_shader(rendering_state.shader_program);
        gfx_rapi->load_shader(prg);
        rendering_state.shader_program = prg;
    }
    if (use_alpha != rendering_state.alpha_blend) {
        gfx_flush();
        gfx_rapi->set_use_alpha(use_alpha);
        rendering_state.alpha_blend = use_alpha;
    }
    uint8_t num_inputs;
    bool used_textures[2];
    gfx_rapi->shader_get_info(prg, &num_inputs, used_textures);
    
    for (int i = 0; i < 2; i++) {
        if (used_textures[i]) {
            if (rdp.textures_changed[i]) {
                gfx_flush();
                import_texture(i);
                rdp.textures_changed[i] = false;
            }
            bool linear_filter = configFiltering && ((rdp.other_mode_h & (3U << G_MDSFT_TEXTFILT)) != G_TF_POINT);
            if (linear_filter != rendering_state.textures[i]->linear_filter || rdp.texture_tile.cms != rendering_state.textures[i]->cms || rdp.texture_tile.cmt != rendering_state.textures[i]->cmt) {
                gfx_flush();
                gfx_rapi->set_sampler_parameters(i, linear_filter, rdp.texture_tile.cms, rdp.texture_tile.cmt);
                rendering_state.textures[i]->linear_filter = linear_filter;
                rendering_state.textures[i]->cms = rdp.texture_tile.cms;
                rendering_state.textures[i]->cmt = rdp.texture_tile.cmt;
            }
        }
    }

#ifdef GFX_SEPARATE_FOG
    if (use_fog) {
        gfx_rapi->set_fog(rdp.fog_color.r, rdp.fog_color.g, rdp.fog_color.b, rsp.fog_mul, rsp.fog_offset);
    }
#endif
    
    bool use_texture = used_textures[0] || used_textures[1];
    uint32_t tex_width = (rdp.texture_tile.lrs - rdp.texture_tile.uls + 4) / 4;
    uint32_t tex_height = (rdp.texture_tile.lrt - rdp.texture_tile.ult + 4) / 4;
    
#ifndef GFX_SEPARATE_PROJECTIONS
    bool z_is_from_0_to_1 = gfx_rapi->z_is_from_0_to_1();    
#else
    bool z_is_from_0_to_1 = separate_projections.is_ortho && gfx_rapi->z_is_from_0_to_1();
#endif
    
    for (int i = 0; i < 3; i++) {
        float z = v_arr[i]->z, w = v_arr[i]->w;
        if (z_is_from_0_to_1) {
            z = (z + w) / 2.0f;
        }
        buf_vbo[buf_vbo_len++] = v_arr[i]->x;
        buf_vbo[buf_vbo_len++] = v_arr[i]->y;
        buf_vbo[buf_vbo_len++] = z;
        buf_vbo[buf_vbo_len++] = w;
#ifdef GFX_OUTPUT_NORMALS_TO_VBO
        buf_vbo[buf_vbo_len++] = v_arr[i]->nx;
        buf_vbo[buf_vbo_len++] = v_arr[i]->ny;
        buf_vbo[buf_vbo_len++] = v_arr[i]->nz;
#endif
        if (use_texture) {
            float u = (v_arr[i]->u - rdp.texture_tile.uls * 8) / 32.0f;
            float v = (v_arr[i]->v - rdp.texture_tile.ult * 8) / 32.0f;
            if ((rdp.other_mode_h & (3U << G_MDSFT_TEXTFILT)) != G_TF_POINT) {
                // Linear filter adds 0.5f to the coordinates
                u += 0.5f;
                v += 0.5f;
            }
            buf_vbo[buf_vbo_len++] = u / tex_width;
            buf_vbo[buf_vbo_len++] = v / tex_height;
        }
#ifndef GFX_SEPARATE_FOG
        if (use_fog) {
            buf_vbo[buf_vbo_len++] = rdp.fog_color.r / 255.0f;
            buf_vbo[buf_vbo_len++] = rdp.fog_color.g / 255.0f;
            buf_vbo[buf_vbo_len++] = rdp.fog_color.b / 255.0f;
            buf_vbo[buf_vbo_len++] = v_arr[i]->color.a / 255.0f; // fog factor (not alpha)
        }
#endif
        for (int j = 0; j < num_inputs; j++) {
            struct RGBA *color;
            struct RGBA tmp;
            for (int k = 0; k < 1 + (use_alpha ? 1 : 0); k++) {
                switch (comb->shader_input_mapping[k][j]) {
                    case CC_PRIM:
                        color = &rdp.prim_color;
                        break;
                    case CC_SHADE:
                        color = &v_arr[i]->color;
                        break;
                    case CC_ENV:
                        color = &rdp.env_color;
                        break;
                    case CC_LOD:
                    {
                        float distance_frac = (v1->w - 3000.0f) / 3000.0f;
                        if (distance_frac < 0.0f) distance_frac = 0.0f;
                        if (distance_frac > 1.0f) distance_frac = 1.0f;
                        tmp.r = tmp.g = tmp.b = tmp.a = distance_frac * 255.0f;
                        color = &tmp;
                        break;
                    }
                    default:
                        memset(&tmp, 0, sizeof(tmp));
                        color = &tmp;
                        break;
                }
                if (k == 0) {
                    buf_vbo[buf_vbo_len++] = color->r / 255.0f;
                    buf_vbo[buf_vbo_len++] = color->g / 255.0f;
                    buf_vbo[buf_vbo_len++] = color->b / 255.0f;
                } else {
                    if (use_fog && color == &v_arr[i]->color) {
                        // Shade alpha is 100% for fog
                        buf_vbo[buf_vbo_len++] = 1.0f;
                    } else {
                        buf_vbo[buf_vbo_len++] = color->a / 255.0f;
                    }
                }
            }
        }
        /*struct RGBA *color = &v_arr[i]->color;
        buf_vbo[buf_vbo_len++] = color->r / 255.0f;
        buf_vbo[buf_vbo_len++] = color->g / 255.0f;
        buf_vbo[buf_vbo_len++] = color->b / 255.0f;
        buf_vbo[buf_vbo_len++] = color->a / 255.0f;*/
    }

    if (++buf_vbo_num_tris == MAX_BUFFERED) {
        gfx_flush();
    }
}

static void gfx_sp_geometry_mode(uint32_t clear, uint32_t set) {
    rsp.geometry_mode &= ~clear;
    rsp.geometry_mode |= set;
}

static void gfx_calc_and_set_viewport(const Vp_t *viewport) {
    // 2 bits fraction
    float width = 2.0f * viewport->vscale[0] / 4.0f;
    float height = 2.0f * viewport->vscale[1] / 4.0f;
    float x = (viewport->vtrans[0] / 4.0f) - width / 2.0f;
    float y = SCREEN_HEIGHT - ((viewport->vtrans[1] / 4.0f) + height / 2.0f);
    
    width *= RATIO_X;
    height *= RATIO_Y;
    x *= RATIO_X;
    y *= RATIO_Y;
    
    rdp.viewport.x = x;
    rdp.viewport.y = y;
    rdp.viewport.width = width;
    rdp.viewport.height = height;
    
    rdp.viewport_or_scissor_changed = true;
}

static void gfx_sp_movemem(uint8_t index, uint8_t offset, const void* data) {
    switch (index) {
        case G_MV_VIEWPORT:
            gfx_calc_and_set_viewport((const Vp_t *) data);
            break;
#if 0
        case G_MV_LOOKATY:
        case G_MV_LOOKATX:
            memcpy(rsp.current_lookat + (index - G_MV_LOOKATY) / 2, data, sizeof(Light_t));
            //rsp.lights_changed = 1;
            break;
#endif
#ifdef F3DEX_GBI_2
        case G_MV_LIGHT: {
            int lightidx = offset / 24 - 2;
            if (lightidx >= 0 && lightidx <= MAX_LIGHTS) { // skip lookat
                // NOTE: reads out of bounds if it is an ambient light
                memcpy(rsp.current_lights + lightidx, data, sizeof(Light_t));
            }
            break;
        }
#else
        case G_MV_L0:
        case G_MV_L1:
        case G_MV_L2:
            // NOTE: reads out of bounds if it is an ambient light
            memcpy(rsp.current_lights + (index - G_MV_L0) / 2, data, sizeof(Light_t));
            break;
#endif
    }
}

static void gfx_sp_moveword(uint8_t index, uint16_t offset, uint32_t data) {
    switch (index) {
        case G_MW_NUMLIGHT:
#ifdef F3DEX_GBI_2
            rsp.current_num_lights = data / 24 + 1; // add ambient light
#else
            // Ambient light is included
            // The 31th bit is a flag that lights should be recalculated
            rsp.current_num_lights = (data - 0x80000000U) / 32;
#endif
            rsp.lights_changed = 1;
            break;
        case G_MW_FOG:
            rsp.fog_mul = (int16_t)(data >> 16);
            rsp.fog_offset = (int16_t)data;
            break;
    }
}

static void gfx_sp_texture(uint16_t sc, uint16_t tc, uint8_t level, uint8_t tile, uint8_t on) {
    rsp.texture_scaling_factor.s = sc;
    rsp.texture_scaling_factor.t = tc;
}

static void gfx_dp_set_scissor(uint32_t mode, uint32_t ulx, uint32_t uly, uint32_t lrx, uint32_t lry) {
    float x = ulx / 4.0f * RATIO_X;
    float y = (SCREEN_HEIGHT - lry / 4.0f) * RATIO_Y;
    float width = (lrx - ulx) / 4.0f * RATIO_X;
    float height = (lry - uly) / 4.0f * RATIO_Y;
    
    rdp.scissor.x = x;
    rdp.scissor.y = y;
    rdp.scissor.width = width;
    rdp.scissor.height = height;
    
    rdp.viewport_or_scissor_changed = true;
}

static void gfx_dp_set_texture_image(uint32_t format, uint32_t size, uint32_t width, const void* addr) {
    rdp.texture_to_load.addr = addr;
    rdp.texture_to_load.siz = size;
}

static void gfx_dp_set_tile(uint8_t fmt, uint32_t siz, uint32_t line, uint32_t tmem, uint8_t tile, uint32_t palette, uint32_t cmt, uint32_t maskt, uint32_t shiftt, uint32_t cms, uint32_t masks, uint32_t shifts) {
    
    if (tile == G_TX_RENDERTILE) {
        SUPPORT_CHECK(palette == 0); // palette should set upper 4 bits of color index in 4b mode
        rdp.texture_tile.fmt = fmt;
        rdp.texture_tile.siz = siz;
        rdp.texture_tile.cms = cms;
        rdp.texture_tile.cmt = cmt;
        rdp.texture_tile.line_size_bytes = line * 8;
        rdp.textures_changed[0] = true;
        rdp.textures_changed[1] = true;
    }
    
    if (tile == G_TX_LOADTILE) {
        rdp.texture_to_load.tile_number = tmem / 256;
    }
}

static void gfx_dp_set_tile_size(uint8_t tile, uint16_t uls, uint16_t ult, uint16_t lrs, uint16_t lrt) {
    if (tile == G_TX_RENDERTILE) {
        rdp.texture_tile.uls = uls;
        rdp.texture_tile.ult = ult;
        rdp.texture_tile.lrs = lrs;
        rdp.texture_tile.lrt = lrt;
        rdp.textures_changed[0] = true;
        rdp.textures_changed[1] = true;
    }
}

static void gfx_dp_load_tlut(uint8_t tile, uint32_t high_index) {
    SUPPORT_CHECK(tile == G_TX_LOADTILE);
    SUPPORT_CHECK(rdp.texture_to_load.siz == G_IM_SIZ_16b);
    rdp.palette = rdp.texture_to_load.addr;
}

static void gfx_dp_load_block(uint8_t tile, uint32_t uls, uint32_t ult, uint32_t lrs, uint32_t dxt) {
    if (tile == 1) return;
    SUPPORT_CHECK(tile == G_TX_LOADTILE);
    SUPPORT_CHECK(uls == 0);
    SUPPORT_CHECK(ult == 0);
    
    // The lrs field rather seems to be number of pixels to load
    uint32_t word_size_shift;
    switch (rdp.texture_to_load.siz) {
        case G_IM_SIZ_4b:
            word_size_shift = 0; // Or -1? It's unused in SM64 anyway.
            break;
        case G_IM_SIZ_8b:
            word_size_shift = 0;
            break;
        case G_IM_SIZ_16b:
            word_size_shift = 1;
            break;
        case G_IM_SIZ_32b:
            word_size_shift = 2;
            break;
    }
    uint32_t size_bytes = (lrs + 1) << word_size_shift;
    rdp.loaded_texture[rdp.texture_to_load.tile_number].size_bytes = size_bytes;
    rdp.loaded_texture[rdp.texture_to_load.tile_number].addr = rdp.texture_to_load.addr;
    
    rdp.textures_changed[rdp.texture_to_load.tile_number] = true;
}

static void gfx_dp_load_tile(uint8_t tile, uint32_t uls, uint32_t ult, uint32_t lrs, uint32_t lrt) {
    if (tile == 1) return;
    SUPPORT_CHECK(tile == G_TX_LOADTILE);
    SUPPORT_CHECK(uls == 0);
    SUPPORT_CHECK(ult == 0);

    uint32_t word_size_shift;
    switch (rdp.texture_to_load.siz) {
        case G_IM_SIZ_4b:
            word_size_shift = 0; // Or -1? It's unused in SM64 anyway.
            break;
        case G_IM_SIZ_8b:
            word_size_shift = 0;
            break;
        case G_IM_SIZ_16b:
            word_size_shift = 1;
            break;
        case G_IM_SIZ_32b:
            word_size_shift = 2;
            break;
    }

    uint32_t size_bytes = (((lrs >> G_TEXTURE_IMAGE_FRAC) + 1) * ((lrt >> G_TEXTURE_IMAGE_FRAC) + 1)) << word_size_shift;
    rdp.loaded_texture[rdp.texture_to_load.tile_number].size_bytes = size_bytes;

    rdp.loaded_texture[rdp.texture_to_load.tile_number].addr = rdp.texture_to_load.addr;
    rdp.texture_tile.uls = uls;
    rdp.texture_tile.ult = ult;
    rdp.texture_tile.lrs = lrs;
    rdp.texture_tile.lrt = lrt;

    rdp.textures_changed[rdp.texture_to_load.tile_number] = true;
}

static uint8_t color_comb_component(uint32_t v) {
    switch (v) {
        case G_CCMUX_TEXEL0:
            return CC_TEXEL0;
        case G_CCMUX_TEXEL1:
            return CC_TEXEL1;
        case G_CCMUX_PRIMITIVE:
            return CC_PRIM;
        case G_CCMUX_SHADE:
            return CC_SHADE;
        case G_CCMUX_ENVIRONMENT:
            return CC_ENV;
        case G_CCMUX_TEXEL0_ALPHA:
            return CC_TEXEL0A;
        case G_CCMUX_LOD_FRACTION:
            return CC_LOD;
        default:
            return CC_0;
    }
}

static inline uint32_t color_comb(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    return color_comb_component(a) |
           (color_comb_component(b) << 3) |
           (color_comb_component(c) << 6) |
           (color_comb_component(d) << 9);
}

static void gfx_dp_set_combine_mode(uint32_t rgb, uint32_t alpha) {
    rdp.combine_mode = rgb | (alpha << 12);
}

static void gfx_dp_set_env_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    rdp.env_color.r = r;
    rdp.env_color.g = g;
    rdp.env_color.b = b;
    rdp.env_color.a = a;
}

static void gfx_dp_set_prim_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    rdp.prim_color.r = r;
    rdp.prim_color.g = g;
    rdp.prim_color.b = b;
    rdp.prim_color.a = a;
}

static void gfx_dp_set_fog_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    rdp.fog_color.r = r;
    rdp.fog_color.g = g;
    rdp.fog_color.b = b;
    rdp.fog_color.a = a;
}

static void gfx_dp_set_fill_color(uint32_t packed_color) {
    uint16_t col16 = (uint16_t)packed_color;
    uint32_t r = col16 >> 11;
    uint32_t g = (col16 >> 6) & 0x1f;
    uint32_t b = (col16 >> 1) & 0x1f;
    uint32_t a = col16 & 1;
    rdp.fill_color.r = SCALE_5_8(r);
    rdp.fill_color.g = SCALE_5_8(g);
    rdp.fill_color.b = SCALE_5_8(b);
    rdp.fill_color.a = a * 255;
}

static void gfx_draw_rectangle(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry) {
#ifdef GFX_SEPARATE_PROJECTIONS
    separate_projections.is_ortho = true;
#endif

    uint32_t saved_other_mode_h = rdp.other_mode_h;
    uint32_t cycle_type = (rdp.other_mode_h & (3U << G_MDSFT_CYCLETYPE));
    
    if (cycle_type == G_CYC_COPY) {
        rdp.other_mode_h = (rdp.other_mode_h & ~(3U << G_MDSFT_TEXTFILT)) | G_TF_POINT;
    }
    
    // U10.2 coordinates
    float ulxf = ulx;
    float ulyf = uly;
    float lrxf = lrx;
    float lryf = lry;
    
    ulxf = ulxf / (4.0f * HALF_SCREEN_WIDTH) - 1.0f;
    ulyf = -(ulyf / (4.0f * HALF_SCREEN_HEIGHT)) + 1.0f;
    lrxf = lrxf / (4.0f * HALF_SCREEN_WIDTH) - 1.0f;
    lryf = -(lryf / (4.0f * HALF_SCREEN_HEIGHT)) + 1.0f;
    
    ulxf = gfx_adjust_x_for_aspect_ratio(ulxf);
    lrxf = gfx_adjust_x_for_aspect_ratio(lrxf);
    
    struct LoadedVertex* ul = &rsp.loaded_vertices[MAX_VERTICES + 0];
    struct LoadedVertex* ll = &rsp.loaded_vertices[MAX_VERTICES + 1];
    struct LoadedVertex* lr = &rsp.loaded_vertices[MAX_VERTICES + 2];
    struct LoadedVertex* ur = &rsp.loaded_vertices[MAX_VERTICES + 3];
    
    ul->x = ulxf;
    ul->y = ulyf;
    ul->z = -1.0f;
    ul->w = 1.0f;
    
    ll->x = ulxf;
    ll->y = lryf;
    ll->z = -1.0f;
    ll->w = 1.0f;
    
    lr->x = lrxf;
    lr->y = lryf;
    lr->z = -1.0f;
    lr->w = 1.0f;
    
    ur->x = lrxf;
    ur->y = ulyf;
    ur->z = -1.0f;
    ur->w = 1.0f;
    
    // The coordinates for texture rectangle shall bypass the viewport setting
    struct XYWidthHeight default_viewport = {0, 0, gfx_current_dimensions.width, gfx_current_dimensions.height};
    struct XYWidthHeight viewport_saved = rdp.viewport;
    uint32_t geometry_mode_saved = rsp.geometry_mode;
    
    rdp.viewport = default_viewport;
    rdp.viewport_or_scissor_changed = true;
    rsp.geometry_mode = 0;
    
    gfx_sp_tri1(MAX_VERTICES + 0, MAX_VERTICES + 1, MAX_VERTICES + 3);
    gfx_sp_tri1(MAX_VERTICES + 1, MAX_VERTICES + 2, MAX_VERTICES + 3);
    
    rsp.geometry_mode = geometry_mode_saved;
    rdp.viewport = viewport_saved;
    rdp.viewport_or_scissor_changed = true;
    
    if (cycle_type == G_CYC_COPY) {
        rdp.other_mode_h = saved_other_mode_h;
    }
}

static void gfx_dp_texture_rectangle(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry, uint8_t tile, int16_t uls, int16_t ult, int16_t dsdx, int16_t dtdy, bool flip) {
    uint32_t saved_combine_mode = rdp.combine_mode;
    if ((rdp.other_mode_h & (3U << G_MDSFT_CYCLETYPE)) == G_CYC_COPY) {
        // Per RDP Command Summary Set Tile's shift s and this dsdx should be set to 4 texels
        // Divide by 4 to get 1 instead
        dsdx >>= 2;
        
        // Color combiner is turned off in copy mode
        gfx_dp_set_combine_mode(color_comb(0, 0, 0, G_CCMUX_TEXEL0), color_comb(0, 0, 0, G_ACMUX_TEXEL0));
        
        // Per documentation one extra pixel is added in this modes to each edge
        lrx += 1 << 2;
        lry += 1 << 2;
    }
    
    // uls and ult are S10.5
    // dsdx and dtdy are S5.10
    // lrx, lry, ulx, uly are U10.2
    // lrs, lrt are S10.5
    if (flip) {
        dsdx = -dsdx;
        dtdy = -dtdy;
    }
    int16_t width = !flip ? lrx - ulx : lry - uly;
    int16_t height = !flip ? lry - uly : lrx - ulx;
    float lrs = ((uls << 7) + dsdx * width) >> 7;
    float lrt = ((ult << 7) + dtdy * height) >> 7;
    
    struct LoadedVertex* ul = &rsp.loaded_vertices[MAX_VERTICES + 0];
    struct LoadedVertex* ll = &rsp.loaded_vertices[MAX_VERTICES + 1];
    struct LoadedVertex* lr = &rsp.loaded_vertices[MAX_VERTICES + 2];
    struct LoadedVertex* ur = &rsp.loaded_vertices[MAX_VERTICES + 3];
    ul->u = uls;
    ul->v = ult;
    lr->u = lrs;
    lr->v = lrt;
    if (!flip) {
        ll->u = uls;
        ll->v = lrt;
        ur->u = lrs;
        ur->v = ult;
    } else {
        ll->u = lrs;
        ll->v = ult;
        ur->u = uls;
        ur->v = lrt;
    }
    
    gfx_draw_rectangle(ulx, uly, lrx, lry);
    rdp.combine_mode = saved_combine_mode;
}

static void gfx_dp_fill_rectangle(int32_t ulx, int32_t uly, int32_t lrx, int32_t lry) {
    if (rdp.color_image_address == rdp.z_buf_address) {
        // Don't clear Z buffer here since we already did it with glClear
        return;
    }
    uint32_t mode = (rdp.other_mode_h & (3U << G_MDSFT_CYCLETYPE));
    
    if (mode == G_CYC_COPY || mode == G_CYC_FILL) {
        // Per documentation one extra pixel is added in this modes to each edge
        lrx += 1 << 2;
        lry += 1 << 2;
    }
    
    for (int i = MAX_VERTICES; i < MAX_VERTICES + 4; i++) {
        struct LoadedVertex* v = &rsp.loaded_vertices[i];
        v->color = rdp.fill_color;
    }
    
    uint32_t saved_combine_mode = rdp.combine_mode;
    gfx_dp_set_combine_mode(color_comb(0, 0, 0, G_CCMUX_SHADE), color_comb(0, 0, 0, G_ACMUX_SHADE));
    gfx_draw_rectangle(ulx, uly, lrx, lry);
    rdp.combine_mode = saved_combine_mode;
}

static void gfx_dp_set_z_image(void *z_buf_address) {
    rdp.z_buf_address = z_buf_address;
}

static void gfx_dp_set_color_image(uint32_t format, uint32_t size, uint32_t width, void* address) {
    rdp.color_image_address = address;
}

static void gfx_sp_set_other_mode(uint32_t shift, uint32_t num_bits, uint64_t mode) {
    uint64_t mask = (((uint64_t)1 << num_bits) - 1) << shift;
    uint64_t om = rdp.other_mode_l | ((uint64_t)rdp.other_mode_h << 32);
    om = (om & ~mask) | mode;
    rdp.other_mode_l = (uint32_t)om;
    rdp.other_mode_h = (uint32_t)(om >> 32);
}

static inline void *seg_addr(uintptr_t w1) {
    return (void *) w1;
}

#define C0(pos, width) ((cmd->words.w0 >> (pos)) & ((1U << width) - 1))
#define C1(pos, width) ((cmd->words.w1 >> (pos)) & ((1U << width) - 1))

static void gfx_run_dl(Gfx* cmd) {
    int dummy = 0;
    for (;;) {
        uint32_t opcode = cmd->words.w0 >> 24;
        
        switch (opcode) {
            // RSP commands:
            case G_MTX:
#ifdef F3DEX_GBI_2
                gfx_sp_matrix(C0(0, 8) ^ G_MTX_PUSH, (const int32_t *) seg_addr(cmd->words.w1));
#else
                gfx_sp_matrix(C0(16, 8), (const int32_t *) seg_addr(cmd->words.w1));
#endif
                break;
            case (uint8_t)G_POPMTX:
#ifdef F3DEX_GBI_2
                gfx_sp_pop_matrix(cmd->words.w1 / 64);
#else
                gfx_sp_pop_matrix(1);
#endif
                break;
            case G_MOVEMEM:
#ifdef F3DEX_GBI_2
                gfx_sp_movemem(C0(0, 8), C0(8, 8) * 8, seg_addr(cmd->words.w1));
#else
                gfx_sp_movemem(C0(16, 8), 0, seg_addr(cmd->words.w1));
#endif
                break;
            case (uint8_t)G_MOVEWORD:
#ifdef F3DEX_GBI_2
                gfx_sp_moveword(C0(16, 8), C0(0, 16), cmd->words.w1);
#else
                gfx_sp_moveword(C0(0, 8), C0(8, 16), cmd->words.w1);
#endif
                break;
            case (uint8_t)G_TEXTURE:
#ifdef F3DEX_GBI_2
                gfx_sp_texture(C1(16, 16), C1(0, 16), C0(11, 3), C0(8, 3), C0(1, 7));
#else
                gfx_sp_texture(C1(16, 16), C1(0, 16), C0(11, 3), C0(8, 3), C0(0, 8));
#endif
                break;
            case G_VTX:
#ifdef F3DEX_GBI_2
                gfx_sp_vertex(C0(12, 8), C0(1, 7) - C0(12, 8), seg_addr(cmd->words.w1));
#elif defined(F3DEX_GBI) || defined(F3DLP_GBI)
                gfx_sp_vertex(C0(10, 6), C0(16, 8) / 2, seg_addr(cmd->words.w1));
#else
                gfx_sp_vertex((C0(0, 16)) / sizeof(Vtx), C0(16, 4), seg_addr(cmd->words.w1));
#endif
                break;
            case G_DL:
                if (C0(16, 1) == 0) {
                    // Push return address
                    gfx_run_dl((Gfx *)seg_addr(cmd->words.w1));
                } else {
                    cmd = (Gfx *)seg_addr(cmd->words.w1);
                    --cmd; // increase after break
                }
                break;
            case (uint8_t)G_ENDDL:
#ifdef GFX_FLUSH_ON_ENDDL
                gfx_flush();
#endif
#ifdef GFX_SEPARATE_PROJECTIONS
                separate_projections.model_matrix_used = false;
#endif
                return;
#ifdef F3DEX_GBI_2
            case G_GEOMETRYMODE:
                gfx_sp_geometry_mode(~C0(0, 24), cmd->words.w1);
                break;
#else
            case (uint8_t)G_SETGEOMETRYMODE:
                gfx_sp_geometry_mode(0, cmd->words.w1);
                break;
            case (uint8_t)G_CLEARGEOMETRYMODE:
                gfx_sp_geometry_mode(cmd->words.w1, 0);
                break;
#endif
            case (uint8_t)G_TRI1:
#ifdef F3DEX_GBI_2
                gfx_sp_tri1(C0(16, 8) / 2, C0(8, 8) / 2, C0(0, 8) / 2);
#elif defined(F3DEX_GBI) || defined(F3DLP_GBI)
                gfx_sp_tri1(C1(16, 8) / 2, C1(8, 8) / 2, C1(0, 8) / 2);
#else
                gfx_sp_tri1(C1(16, 8) / 10, C1(8, 8) / 10, C1(0, 8) / 10);
#endif
                break;
#if defined(F3DEX_GBI) || defined(F3DLP_GBI)
            case (uint8_t)G_TRI2:
                gfx_sp_tri1(C0(16, 8) / 2, C0(8, 8) / 2, C0(0, 8) / 2);
                gfx_sp_tri1(C1(16, 8) / 2, C1(8, 8) / 2, C1(0, 8) / 2);
                break;
#endif
            case (uint8_t)G_SETOTHERMODE_L:
#ifdef F3DEX_GBI_2
                gfx_sp_set_other_mode(31 - C0(8, 8) - C0(0, 8), C0(0, 8) + 1, cmd->words.w1);
#else
                gfx_sp_set_other_mode(C0(8, 8), C0(0, 8), cmd->words.w1);
#endif
                break;
            case (uint8_t)G_SETOTHERMODE_H:
#ifdef F3DEX_GBI_2
                gfx_sp_set_other_mode(63 - C0(8, 8) - C0(0, 8), C0(0, 8) + 1, (uint64_t) cmd->words.w1 << 32);
#else
                gfx_sp_set_other_mode(C0(8, 8) + 32, C0(0, 8), (uint64_t) cmd->words.w1 << 32);
#endif
                break;
            
            // RDP Commands:
            case G_SETTIMG:
                gfx_dp_set_texture_image(C0(21, 3), C0(19, 2), C0(0, 10), seg_addr(cmd->words.w1));
                break;
            case G_LOADBLOCK:
                gfx_dp_load_block(C1(24, 3), C0(12, 12), C0(0, 12), C1(12, 12), C1(0, 12));
                break;
            case G_LOADTILE:
                gfx_dp_load_tile(C1(24, 3), C0(12, 12), C0(0, 12), C1(12, 12), C1(0, 12));
                break;
            case G_SETTILE:
                gfx_dp_set_tile(C0(21, 3), C0(19, 2), C0(9, 9), C0(0, 9), C1(24, 3), C1(20, 4), C1(18, 2), C1(14, 4), C1(10, 4), C1(8, 2), C1(4, 4), C1(0, 4));
                break;
            case G_SETTILESIZE:
                gfx_dp_set_tile_size(C1(24, 3), C0(12, 12), C0(0, 12), C1(12, 12), C1(0, 12));
                break;
            case G_LOADTLUT:
                gfx_dp_load_tlut(C1(24, 3), C1(14, 10));
                break;
            case G_SETENVCOLOR:
                gfx_dp_set_env_color(C1(24, 8), C1(16, 8), C1(8, 8), C1(0, 8));
                break;
            case G_SETPRIMCOLOR:
                gfx_dp_set_prim_color(C1(24, 8), C1(16, 8), C1(8, 8), C1(0, 8));
                break;
            case G_SETFOGCOLOR:
                gfx_dp_set_fog_color(C1(24, 8), C1(16, 8), C1(8, 8), C1(0, 8));
                break;
            case G_SETFILLCOLOR:
                gfx_dp_set_fill_color(cmd->words.w1);
                break;
            case G_SETCOMBINE:
                gfx_dp_set_combine_mode(
                    color_comb(C0(20, 4), C1(28, 4), C0(15, 5), C1(15, 3)),
                    color_comb(C0(12, 3), C1(12, 3), C0(9, 3), C1(9, 3)));
                    /*color_comb(C0(5, 4), C1(24, 4), C0(0, 5), C1(6, 3)),
                    color_comb(C1(21, 3), C1(3, 3), C1(18, 3), C1(0, 3)));*/
                break;
            // G_SETPRIMCOLOR, G_CCMUX_PRIMITIVE, G_ACMUX_PRIMITIVE, is used by Goddard
            // G_CCMUX_TEXEL1, LOD_FRACTION is used in Bowser room 1
            case G_TEXRECT:
            case G_TEXRECTFLIP:
            {
                int32_t lrx, lry, tile, ulx, uly;
                uint32_t uls, ult, dsdx, dtdy;
#ifdef F3DEX_GBI_2E
                lrx = (int32_t)(C0(0, 24) << 8) >> 8;
                lry = (int32_t)(C1(0, 24) << 8) >> 8;
                ++cmd;
                ulx = (int32_t)(C0(0, 24) << 8) >> 8;
                uly = (int32_t)(C1(0, 24) << 8) >> 8;
                ++cmd;
                uls = C0(16, 16);
                ult = C0(0, 16);
                dsdx = C1(16, 16);
                dtdy = C1(0, 16);
#else
                lrx = C0(12, 12);
                lry = C0(0, 12);
                tile = C1(24, 3);
                ulx = C1(12, 12);
                uly = C1(0, 12);
                ++cmd;
                uls = C1(16, 16);
                ult = C1(0, 16);
                ++cmd;
                dsdx = C1(16, 16);
                dtdy = C1(0, 16);
#endif
                gfx_dp_texture_rectangle(ulx, uly, lrx, lry, tile, uls, ult, dsdx, dtdy, opcode == G_TEXRECTFLIP);
                break;
            }
            case G_FILLRECT:
#ifdef F3DEX_GBI_2E
            {
                int32_t lrx, lry, ulx, uly;
                lrx = (int32_t)(C0(0, 24) << 8) >> 8;
                lry = (int32_t)(C1(0, 24) << 8) >> 8;
                ++cmd;
                ulx = (int32_t)(C0(0, 24) << 8) >> 8;
                uly = (int32_t)(C1(0, 24) << 8) >> 8;
                gfx_dp_fill_rectangle(ulx, uly, lrx, lry);
                break;
            }
#else
                gfx_dp_fill_rectangle(C1(12, 12), C1(0, 12), C0(12, 12), C0(0, 12));
                break;
#endif
            case G_SETSCISSOR:
                gfx_dp_set_scissor(C1(24, 2), C0(12, 12), C0(0, 12), C1(12, 12), C1(0, 12));
                break;
            case G_SETZIMG:
                gfx_dp_set_z_image(seg_addr(cmd->words.w1));
                break;
            case G_SETCIMG:
                gfx_dp_set_color_image(C0(21, 3), C0(19, 2), C0(0, 11), seg_addr(cmd->words.w1));
                break;
#ifdef GFX_ENABLE_GRAPH_NODE_MODS
            case G_NOOP: {
                GraphNodeGfxInfo *gfxInfo = (GraphNodeGfxInfo *)(cmd->words.w1);
                if (gfxInfo != NULL) {
                    separate_projections.current_uid = gfxInfo->UID;
                    gfx_rapi->set_graph_node_mod(gfxInfo->graphNodeMod);
                }
                else {
                    separate_projections.current_uid = 0;
                    gfx_rapi->set_graph_node_mod(NULL);
                }
                break;
            }
#endif
        }
        ++cmd;
    }
}

static void gfx_sp_reset() {
    rsp.modelview_matrix_stack_size = 1;
    rsp.current_num_lights = 2;
    rsp.lights_changed = true;
}

void gfx_get_dimensions(uint32_t *width, uint32_t *height) {
    gfx_wapi->get_dimensions(width, height);
}

void gfx_init(struct GfxWindowManagerAPI *wapi, struct GfxRenderingAPI *rapi, const char *window_title) {
    gfx_wapi = wapi;
    gfx_rapi = rapi;
    gfx_wapi->init(window_title);
    gfx_rapi->init();
    
    // Used in the 120 star TAS
    static uint32_t precomp_shaders[] = {
        0x01200200,
        0x00000045,
        0x00000200,
        0x01200a00,
        0x00000a00,
        0x01a00045,
        0x00000551,
        0x01045045,
        0x05a00a00,
        0x01200045,
        0x05045045,
        0x01045a00,
        0x01a00a00,
        0x0000038d,
        0x01081081,
        0x0120038d,
        0x03200045,
        0x03200a00,
        0x01a00a6f,
        0x01141045,
        0x07a00a00,
        0x05200200,
        0x03200200,
        0x09200200,
        0x0920038d,
        0x09200045
    };

    for (size_t i = 0; i < sizeof(precomp_shaders) / sizeof(uint32_t); i++)
        gfx_lookup_or_create_shader_program(precomp_shaders[i]);

#ifdef GFX_SEPARATE_SKYBOX
    gfx_init_skybox();
#endif
}

void gfx_precache_textures(void) {
    // preload all textures
    fs_walk(FS_TEXTUREDIR, preload_texture, NULL, true);
}

struct GfxRenderingAPI *gfx_get_current_rendering_api(void) {
    return gfx_rapi;
}

void gfx_start_frame() {
    gfx_wapi->handle_events();
    gfx_wapi->get_dimensions(&gfx_current_dimensions.width, &gfx_current_dimensions.height);
    if (gfx_current_dimensions.height == 0) {
        // Avoid division by zero
        gfx_current_dimensions.height = 1;
    }
    gfx_current_dimensions.aspect_ratio = (float)gfx_current_dimensions.width / (float)gfx_current_dimensions.height;

#ifdef GFX_SEPARATE_PROJECTIONS
    gd_set_identity_mat4(&separate_projections.mat.extra_model_matrix);
    gd_set_identity_mat4(&separate_projections.mat.camera_matrix);
    gd_set_identity_mat4(&separate_projections.mat.graph_view_matrix);
    gd_set_identity_mat4(&separate_projections.mat.graph_inv_view_matrix);
    gfx_rapi->set_camera_matrix(separate_projections.mat.camera_matrix);

    separate_projections.camera_matrix_set = false;
    separate_projections.is_ortho = false;
    separate_projections.model_matrix_used = false;
    separate_projections.double_sided = false;
    separate_projections.persp_triangles_drawn = false;
#endif
}

void gfx_run(Gfx *commands) {
    gfx_sp_reset();
    
    //puts("New frame");
    
    if (!gfx_wapi->start_frame()) {
        dropped_frame = true;
        return;
    }
    dropped_frame = false;
    
    double t0 = gfx_wapi->get_time();
    gfx_rapi->start_frame();
    gfx_run_dl(commands);
    gfx_flush();
    double t1 = gfx_wapi->get_time();
    //printf("Process %f %f\n", t1, t1 - t0);
    gfx_rapi->end_frame();
    gfx_wapi->swap_buffers_begin();
}

void gfx_end_frame(void) {
    if (!dropped_frame) {
        gfx_rapi->finish_render();
        gfx_wapi->swap_buffers_end();
    }
}

void gfx_shutdown(void) {
    if (gfx_rapi) {
        if (gfx_rapi->shutdown) gfx_rapi->shutdown();
        gfx_rapi = NULL;
    }
    if (gfx_wapi) {
        if (gfx_wapi->shutdown) gfx_wapi->shutdown();
        gfx_wapi = NULL;
    }
}
