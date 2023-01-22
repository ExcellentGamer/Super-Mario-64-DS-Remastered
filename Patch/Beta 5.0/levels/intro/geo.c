#include <ultra64.h>
#include "sm64.h"
#include "geo_commands.h"

#include "game/level_geo.h"
#include "game/geo_misc.h"
#include "game/camera.h"
#include "game/moving_texture.h"
#include "game/screen_transition.h"
#include "game/paintings.h"
#include "menu/debug_level_select.h"
#include "menu/intro_geo.h"

#include "make_const_nonconst.h"

#include "levels/intro/header.h"

// DS Background
const GeoLayout dsbg_geo[] = {
   GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_ASM(0, geo_exec_dsbg_start_screen),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM_WITH_FUNC(45, 100, 12800, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(1, 0, 2000, 6000, 0, 0, 0, geo_camera_main),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// DS Background 2
const GeoLayout ds_goddard_geo[] = {
   GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_ASM(0, geo_exec_ds_goddard_start_screen),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM_WITH_FUNC(45, 100, 12800, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(1, 0, 2000, 6000, 0, 0, 0, geo_camera_main),
            GEO_ASM(2, geo_draw_mario_head_goddard),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E00035C
const GeoLayout intro_geo_00035C[] = {
   GEO_NODE_SCREEN_AREA(0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_ASM(0, geo_intro_backdrop),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM(45, 128, 16384),
         GEO_OPEN_NODE(),
            GEO_ASM(2, geo_draw_mario_head_goddard),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E0003B8
const GeoLayout intro_geo_0003B8[] = {
   GEO_NODE_SCREEN_AREA(0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_ASM(0, geo_game_over_tile),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM(45, 128, 16384),
         GEO_OPEN_NODE(),
            GEO_ASM(3, geo_draw_mario_head_goddard),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E000414
const GeoLayout intro_geo_000414[] = {
   GEO_NODE_SCREEN_AREA(0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_ASM(0, geo_intro_backdrop),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM(45, 128, 16384),
         GEO_OPEN_NODE(),
            GEO_CAMERA(0, 0, 0, 1200, 0, 0, 0, 0x00000000),
            GEO_OPEN_NODE(),
               GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -230, 300, 0, debug_level_select_dl_07000858),
               GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -120, 300, 0, debug_level_select_dl_07001100),
               GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE,  -20, 300, 0, debug_level_select_dl_07001BA0),
               GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE,  100, 300, 0, debug_level_select_dl_070025F0),
               GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE,  250, 300, 0, debug_level_select_dl_07003258),
               GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, -310, 100, 0, debug_level_select_dl_07003DB8),
               GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE,  -90, 100, 0, debug_level_select_dl_070048C8),
               GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE,   60, 100, 0, debug_level_select_dl_07005558),
               GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE,  180, 100, 0, debug_level_select_dl_070059F8),
               GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE,  300, 100, 0, debug_level_select_dl_070063B0),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

