#ifndef R96_C_INCLUDES_H
#define R96_C_INCLUDES_H

/* Include this file only in .c files */

/* include */
#include "data/dynos.c.h"
#include "data/r96/r96_includes.h"
#include "sm64.h"
#include "behavior_data.h"
#include "gfx_dimensions.h"
#include "dialog_ids.h"
#include "model_ids.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* src/game */
#include "game/behavior_actions.h"
#include "game/camera.h"
#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "game/spawn_object.h"
#include "game/spawn_sound.h"
#include "game/game_init.h"
#include "game/level_update.h"
#include "game/interaction.h"
#include "game/ingame_menu.h"
#include "game/mario.h"
#include "game/mario_cheats.h"
#include "game/mario_step.h"
#include "game/print.h"
#include "game/save_file.h"
#include "game/segment2.h"

/* src/engine */
#include "engine/surface_collision.h"
#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"

/* src/audio */
#include "audio/external.h"

/* pc */
#include "pc/cheats.h"
#include "pc/configfile.h"
#include "pc/controller/controller_api.h"

#endif // R96_C_INCLUDES_H
