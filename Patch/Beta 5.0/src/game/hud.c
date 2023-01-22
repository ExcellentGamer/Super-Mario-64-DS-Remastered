#include <stdbool.h>
#include <PR/ultratypes.h>

#include "sm64.h"
#include "actors/common1.h"
#include "gfx_dimensions.h"
#include "game_init.h"
#include "level_update.h"
#include "camera.h"
#include "print.h"
#include "ingame_menu.h"
#include "hud.h"
#include "segment2.h"
#include "area.h"
#include "save_file.h"
#include "print.h"
#include "engine/surface_load.h"
#include "pc/configfile.h"

#ifdef TARGET_SWITCH
#define AVOID_UTYPES
#include "nx/m_nx.h"
#include "nx/m_controller.h"
#endif

/* @file hud.c
 * This file implements HUD rendering and power meter animations.
 * That includes stars, lives, coins, camera status, power meter, timer
 * cannon reticle, and the unused keys.
 **/

struct PowerMeterHUD {
    s8 animation;
    s16 x;
    s16 y;
    f32 unused;
};

struct UnusedHUDStruct {
    u32 unused1;
    u16 unused2;
    u16 unused3;
};

struct CameraHUD {
    s16 status;
};

// Stores health segmented value defined by numHealthWedges
// When the HUD is rendered this value is 8, full health.
static s16 sPowerMeterStoredHealth;

static struct PowerMeterHUD sPowerMeterHUD = {
    POWER_METER_HIDDEN,
    140,
    166,
    1.0,
};

// Power Meter timer that keeps counting when it's visible.
// Gets reset when the health is filled and stops counting
// when the power meter is hidden.
s32 sPowerMeterVisibleTimer = 0;

// Custom left and right snapping functions
s32 get_left(s32 value) {
    if (configForce4by3) {
        return value;
    }
    else {
        return GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(value);
    }
}
s32 get_right(s32 value) {
    if (configForce4by3) {
        return SCREEN_WIDTH-value;
    }
    else {
        return GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(value);
    }
}

static struct UnusedHUDStruct sUnusedHUDValues = { 0x00, 0x0A, 0x00 };

static struct CameraHUD sCameraHUD = { CAM_STATUS_NONE };

void render_hud_rectangle(s16 x1, s16 y1, s16 x2, s16 y2, u8 r, u8 g, u8 b) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetRenderMode(gDisplayListHead++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    gDPSetCycleType(gDisplayListHead++, G_CYC_FILL);
    gDPSetFillColor(gDisplayListHead++, GPACK_RGBA5551(r, g, b, 255));
    gDPFillRectangle(gDisplayListHead++, x1, y1, x2 + 1, y2 + 1);
    gDPPipeSync(gDisplayListHead++);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
}

static u32 sPowerMeterLastRenderTimestamp;
static s16 sPowerMeterLastY;
static Gfx *sPowerMeterDisplayListPos;

void patch_interpolated_hud(void) {
    if (sPowerMeterDisplayListPos != NULL) {
        Mtx *mtx = alloc_display_list(sizeof(Mtx));
        guTranslate(mtx, (f32) sPowerMeterHUD.x, (f32) sPowerMeterHUD.y, 0);
        gSPMatrix(sPowerMeterDisplayListPos, VIRTUAL_TO_PHYSICAL(mtx),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        sPowerMeterDisplayListPos = NULL;
    }
}

/**
 * Renders a rgba16 16x16 glyph texture from a table list.
 */
void render_hud_tex_lut(s32 x, s32 y, u8 *texture) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gSPDisplayList(gDisplayListHead++, &dl_hud_img_load_tex_block);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 15) << 2, (y + 15) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
}

/**
 * Renders a rgba16 8x8 glyph texture from a table list.
 */
void render_hud_small_tex_lut(s32 x, s32 y, u8 *texture) {
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0,
                G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0,
                G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_16b_BYTES));
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 7) << 2, (y + 7) << 2, G_TX_RENDERTILE,
                        0, 0, 4 << 10, 1 << 10);
}

void render_hud_texture(s32 x, s32 y, u32 w, u32 h, u8 *texture) {
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 2, 0, G_TX_RENDERTILE, 0, G_TX_NOMIRROR, 3, G_TX_NOLOD, G_TX_NOMIRROR, 3, G_TX_NOLOD);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, w << G_TEXTURE_IMAGE_FRAC, h << G_TEXTURE_IMAGE_FRAC);
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, texture);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, w * h - 1, CALC_DXT(w, G_IM_SIZ_32b_BYTES));
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + w) << 2, (y + h) << 2, G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

/**
 * Renders power meter health segment texture using a table list.
 */
void render_power_meter_health_segment(s16 numHealthWedges) {
    u8 *(*healthLUT)[];

    healthLUT = segmented_to_virtual(&power_meter_health_segments_lut);

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1,
                       (*healthLUT)[numHealthWedges - 1]);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES));
    gSP1Triangle(gDisplayListHead++, 0, 1, 2, 0);
    gSP1Triangle(gDisplayListHead++, 0, 2, 3, 0);
}

/**
 * Renders power meter display lists.
 * That includes the "POWER" base and the colored health segment textures.
 */
void render_dl_power_meter(s16 numHealthWedges) {
    Mtx *mtx;
    f32 interpolatedY;

    mtx = alloc_display_list(sizeof(Mtx));

    if (mtx == NULL) {
        return;
    }

    if (gGlobalTimer == sPowerMeterLastRenderTimestamp + 1) {
        interpolatedY = (sPowerMeterLastY + sPowerMeterHUD.y) / 2.0f;
    } else {
        interpolatedY = sPowerMeterHUD.y;
    }
    guTranslate(mtx, (f32) sPowerMeterHUD.x, interpolatedY, 0);
    sPowerMeterLastY = sPowerMeterHUD.y;
    sPowerMeterLastRenderTimestamp = gGlobalTimer;
    sPowerMeterDisplayListPos = gDisplayListHead;

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx++),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(gDisplayListHead++, &dl_power_meter_base);

    if (numHealthWedges != 0) {
        gSPDisplayList(gDisplayListHead++, &dl_power_meter_health_segments_begin);
        render_power_meter_health_segment(numHealthWedges);
        gSPDisplayList(gDisplayListHead++, &dl_power_meter_health_segments_end);
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

/**
 * Power meter animation called when there's less than 8 health segments
 * Checks its timer to later change into deemphasizing mode.
 */
void animate_power_meter_emphasized(void) {
    s16 hudDisplayFlags;
    hudDisplayFlags = gHudDisplay.flags;

    if (!(hudDisplayFlags & HUD_DISPLAY_FLAG_EMPHASIZE_POWER)) {
        if (sPowerMeterVisibleTimer == 45.0) {
            sPowerMeterHUD.animation = POWER_METER_DEEMPHASIZING;
        }
    } else {
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Power meter animation called after emphasized mode.
 * Moves power meter y pos speed until it's at 200 to be visible.
 */
static void animate_power_meter_deemphasizing(void) {
    s16 speed = 5;

    if (sPowerMeterHUD.y >= 181) {
        speed = 3;
    }

    if (sPowerMeterHUD.y >= 191) {
        speed = 2;
    }

    if (sPowerMeterHUD.y >= 196) {
        speed = 1;
    }

    sPowerMeterHUD.y += speed;

    if (sPowerMeterHUD.y >= 201) {
        sPowerMeterHUD.y = 200;
        sPowerMeterHUD.animation = POWER_METER_VISIBLE;
    }
}

/**
 * Power meter animation called when there's 8 health segments.
 * Moves power meter y pos quickly until it's at 301 to be hidden.
 */
static void animate_power_meter_hiding(void) {
    sPowerMeterHUD.y += 20;
    if (sPowerMeterHUD.y >= 301) {
        sPowerMeterHUD.animation = POWER_METER_HIDDEN;
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Handles power meter actions depending of the health segments values.
 */
void handle_power_meter_actions(s16 numHealthWedges) {
    // Show power meter if health is not full, less than 8
    if (numHealthWedges < 8 && sPowerMeterStoredHealth == 8 && sPowerMeterHUD.animation == POWER_METER_HIDDEN) {
        sPowerMeterHUD.animation = POWER_METER_EMPHASIZED;
        sPowerMeterHUD.y = 166;
    }

    // Show power meter if health is full, has 8
    if (numHealthWedges == 8 && sPowerMeterStoredHealth == 7) {
        sPowerMeterVisibleTimer = 0;
    }

    // After health is full, hide power meter
    if (numHealthWedges == 8 && sPowerMeterVisibleTimer > 45.0) {
        sPowerMeterHUD.animation = POWER_METER_HIDING;
    }

    // Update to match health value
    sPowerMeterStoredHealth = numHealthWedges;

    // If Mario is swimming, keep power meter visible
    if (gPlayerCameraState->action & ACT_FLAG_SWIMMING) {
        if (sPowerMeterHUD.animation == POWER_METER_HIDDEN
            || sPowerMeterHUD.animation == POWER_METER_EMPHASIZED) {
            sPowerMeterHUD.animation = POWER_METER_DEEMPHASIZING;
            sPowerMeterHUD.y = 166;
        }
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Renders the power meter that shows when Mario is in underwater
 * or has taken damage and has less than 8 health segments.
 * And calls a power meter animation function depending of the value defined.
 */
void render_hud_power_meter(void) {
    s16 shownHealthWedges = gHudDisplay.wedges;

    if (sPowerMeterHUD.animation != POWER_METER_HIDING) {
        handle_power_meter_actions(shownHealthWedges);
    }

    if (sPowerMeterHUD.animation == POWER_METER_HIDDEN) {
        return;
    }

    switch (sPowerMeterHUD.animation) {
        case POWER_METER_EMPHASIZED:
            animate_power_meter_emphasized();
            break;
        case POWER_METER_DEEMPHASIZING:
            animate_power_meter_deemphasizing();
            break;
        case POWER_METER_HIDING:
            animate_power_meter_hiding();
            break;
        default:
            break;
    }

    render_dl_power_meter(shownHealthWedges);

    sPowerMeterVisibleTimer += 1;
}

#ifdef VERSION_JP
#define HUD_TOP_Y 210
#else
#define HUD_TOP_Y 209
#endif

void render_debug_info(void) {
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(22), HUD_TOP_Y - 30, "%d", gMarioState->pos[0]);
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(22), HUD_TOP_Y - 50, "%d", gMarioState->pos[1]);
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(22), HUD_TOP_Y - 70, "%d", gMarioState->pos[2]);
}

/**
 * Renders the amount of lives Mario has.
 */

s32 is_metal_cap(struct MarioState *m){
    return (m->flags & MARIO_METAL_CAP);
}

s32 is_vanish_cap(struct MarioState *m){
    return (m->flags & MARIO_VANISH_CAP);
}

s32 is_wing_cap(struct MarioState *m){
    return (m->flags & MARIO_WING_CAP);
}

s32 is_hatless(struct MarioState *m){
    return !(m->flags & MARIO_CAP_ON_HEAD);
}

void render_hud_mario_lives(void) {
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    if (isLuigi())
        render_hud_tex_lut(get_left(22), 15, "textures/hud/ds_luigi.rgba16"); // Luigi HUD
    else if (isWario())
        render_hud_tex_lut(get_left(22), 15, "textures/hud/ds_wario.rgba16"); // Wario HUD
    else if (isWaluigi())
        render_hud_tex_lut(get_left(22), 15, "textures/hud/ds_luigi.rgba16"); // Luigi HUD
    else if (isYoshi())
        render_hud_tex_lut(get_left(22), 15, "textures/hud/ds_yoshi.rgba16"); // Yoshi HUD
    else
    render_hud_tex_lut(get_left(22), 15, "textures/hud/ds_mario.rgba16"); // Mario HUD
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
    
    print_text(get_left(38), HUD_TOP_Y, "*"); // 'X' glyph
    print_text_fmt_int(get_left(54), HUD_TOP_Y, "%d", gHudDisplay.lives);

	//render_debug_info();
}

void render_red_coins(void) {
    s8 x;
    for (x = 0; x < gRedCoinsCollected; x++) {
        gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
        render_hud_tex_lut(get_left(18) + x * 10, 35, "textures/hud/ds_redcoin.rgba16");
        gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
    }
}


/**
 * Renders the amount of coins collected.
 */
void render_hud_coins(void) {
    print_text(168, HUD_TOP_Y, "+"); // 'Coin' glyph
    print_text(184, HUD_TOP_Y, "*"); // 'X' glyph
    print_text_fmt_int(198, HUD_TOP_Y, "%d", gHudDisplay.coins);
}

#define HUD_STARS_X 78

/**
 * Renders the amount of stars collected.
 * Disables "X" glyph when Mario has 100 stars or more.
 */
void render_hud_stars(void) {
    s8 showX = 0;

    if (gHudFlash == 1 && gGlobalTimer & 0x08) {
        return;
    }

    if (gHudDisplay.stars < 100) {
        showX = 1;
    }

    print_text(get_right(HUD_STARS_X), HUD_TOP_Y, "-"); // 'Star' glyph
    if (showX == 1) {
        print_text(get_right(HUD_STARS_X) + 16, HUD_TOP_Y, "*"); // 'X' glyph
    }
    print_text_fmt_int((showX * 14) + get_right(HUD_STARS_X - 16),
                       HUD_TOP_Y, "%d", gHudDisplay.stars);
}

f32 slideY = 0;
f32 slideTimer = 0;

s32 buttonTimer = 0;

char* normal = "textures/segment2/luigi.rgba16";
char* press = "textures/segment2/luigi_pressed.rgba16";

char* current = "textures/segment2/luigi.rgba16";

s32 currentSwitch = FALSE;

s8 renderNotification = FALSE;

void set_notification_state(s8 newState){
    renderNotification = newState;
}
s8 get_notification_state(){
    return renderNotification;
}

void render_notification(){
    if(renderNotification){
        if(buttonTimer < 15){
            buttonTimer++;
        }else{
            current = (strcmp(current, normal) != 0) ? normal : press;
            buttonTimer= 0;
        }

        if(!currentSwitch){
            if(slideTimer < 100){
                if(slideTimer < 15) slideY += 2;
                slideTimer++;
            }else{
                currentSwitch = TRUE;
            }
        }else{
            if(slideTimer > 0) {
                if(slideTimer > 85) slideY -= 2;
                else renderNotification = FALSE;
                slideTimer--;
            }else {
                currentSwitch = FALSE;
            }
        }

        u32 baseWidth = 845;
        u32 baseHeight = 109;

        f32 newWidth = 16 * baseWidth / baseHeight;

        render_hud_texture((SCREEN_WIDTH / 2) - (newWidth / 2), -28 + slideY, newWidth, 16, current);
    }
}

/**
 * Renders the timer when Mario start sliding in PSS.
 */
void render_hud_timer(void) {
    u8 *(*hudLUT)[58];
    u16 timerValFrames;
    u16 timerMins;
    u16 timerSecs;
    u16 timerFracSecs;

    hudLUT = segmented_to_virtual(&main_hud_lut);
    timerValFrames = gHudDisplay.timer;
    timerMins = timerValFrames / (30 * 60);
    timerSecs = (timerValFrames - (timerMins * 1800)) / 30;

    timerFracSecs = ((timerValFrames - (timerMins * 1800) - (timerSecs * 30)) & 0xFFFF) / 3;
    print_text(get_right(150), 185, "TIME");
    print_text_fmt_int(get_right(91), 185, "%0d", timerMins);
    print_text_fmt_int(get_right(71), 185, "%02d", timerSecs);
    print_text_fmt_int(get_right(37), 185, "%d", timerFracSecs);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(get_right(81), 32, (*hudLUT)[GLYPH_APOSTROPHE]);
    render_hud_tex_lut(get_right(46), 32, (*hudLUT)[GLYPH_DOUBLE_QUOTE]);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

/**
 * Sets HUD status camera value depending of the actions
 * defined in update_camera_status.
 */
void set_hud_camera_status(s16 status) {
    sCameraHUD.status = status;
}

#define HUD_LAKITU_X 54
#define HUD_LAKITU_Y 205

/**
 * Renders camera HUD glyphs using a table list, depending of
 * the camera status called, a defined glyph is rendered.
 */
void render_hud_camera_status(void) {
    u8 *(*cameraLUT)[6];
    cameraLUT = segmented_to_virtual(&main_hud_camera_lut);

    if (sCameraHUD.status == CAM_STATUS_NONE) {
        return;
    }
    if (configEnableCamera == false) {
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(get_right(HUD_LAKITU_X), HUD_LAKITU_Y, (*cameraLUT)[GLYPH_CAM_CAMERA]);

    switch (sCameraHUD.status & CAM_STATUS_MODE_GROUP) {
        case CAM_STATUS_MARIO:
            if(isLuigi()){
                render_hud_tex_lut(get_right(HUD_LAKITU_X) + 16, HUD_LAKITU_Y, "textures/hud/ds_luigi.rgba16");
            }
            if(isWario()){
                render_hud_tex_lut(get_right(HUD_LAKITU_X) + 16, HUD_LAKITU_Y, "textures/hud/ds_wario.rgba16");
            }
            if(isWaluigi()){
                render_hud_tex_lut(get_right(HUD_LAKITU_X) + 16, HUD_LAKITU_Y, "textures/hud/ds_luigi.rgba16");
            }
            if(isYoshi()){
                render_hud_tex_lut(get_right(HUD_LAKITU_X) + 16, HUD_LAKITU_Y, "textures/hud/ds_yoshi.rgba16");
            }
            else if (!isLuigi() && !isWario() && !isWaluigi()){
                render_hud_tex_lut(get_right(HUD_LAKITU_X) + 16, HUD_LAKITU_Y, "textures/hud/ds_mario.rgba16");
            }
            break;
        case CAM_STATUS_LAKITU:
            render_hud_tex_lut(get_right(HUD_LAKITU_X) + 16, HUD_LAKITU_Y, (*cameraLUT)[GLYPH_CAM_LAKITU_HEAD]);
            break;
        case CAM_STATUS_FIXED:
            render_hud_tex_lut(get_right(HUD_LAKITU_X) + 16, HUD_LAKITU_Y, (*cameraLUT)[GLYPH_CAM_FIXED]);
            break;
    }

    switch (sCameraHUD.status & CAM_STATUS_C_MODE_GROUP) {
        case CAM_STATUS_C_DOWN:
            render_hud_small_tex_lut(get_right(HUD_LAKITU_X) + 4, HUD_LAKITU_Y + 16, (*cameraLUT)[GLYPH_CAM_ARROW_DOWN]);
            break;
        case CAM_STATUS_C_UP:
            render_hud_small_tex_lut(get_right(HUD_LAKITU_X) + 4, HUD_LAKITU_Y - 8, (*cameraLUT)[GLYPH_CAM_ARROW_UP]);
            break;
    }
  }
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

#ifdef TARGET_SWITCH
void render_nx_hud(void){
    s16 x = GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(40);
    s16 y = 212;
    s16 w = x + 14;
    s16 h = y + 6;

    render_hud_rectangle(x - 1, y - 1, w + 1, h + 1, 57, 57, 57);
    render_hud_rectangle(w, y + 1, w + 2, y + 6, 57, 57, 57);
    render_hud_rectangle(x, y, w, h, 194, 194, 194);
    render_hud_rectangle(x, y, x + (s16)(14 * getBatteryPercentage()), h, 76, 235, 52);

    x = GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(20);
    y = 207;

    struct NXController controller;

    get_controller_nx(&controller);

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(x, y, controller.icon);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);

}
#endif


/**
 * Render HUD strings using hudDisplayFlags with it's render functions,
 * excluding the cannon reticle which detects a camera preset for it.
 */
void render_hud(void) {
    s16 hudDisplayFlags;

    hudDisplayFlags = gHudDisplay.flags;

    if (hudDisplayFlags == HUD_DISPLAY_NONE) {
        sPowerMeterHUD.animation = POWER_METER_HIDDEN;
        sPowerMeterStoredHealth = 8;
        sPowerMeterVisibleTimer = 0;
    } else {
        create_dl_ortho_matrix();

        if (gCurrentArea != NULL && gCurrentArea->camera->mode == CAMERA_MODE_INSIDE_CANNON) {
            render_hud_cannon_reticle();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_LIVES && configHUD) {
            render_hud_mario_lives();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_COIN_COUNT && configHUD) {
            render_hud_coins();
            render_red_coins();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_STAR_COUNT && configHUD) {
            render_hud_stars();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_CAMERA_AND_POWER && configHUD) {
            render_hud_power_meter();
            render_hud_camera_status();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_TIMER && configHUD) {
            render_hud_timer();
        }

        if( configHUD ) {

        #ifdef TARGET_SWITCH
            if ( configSwitchHud )
                render_nx_hud();
        #endif

        }

        //render_notification();
    }
}
