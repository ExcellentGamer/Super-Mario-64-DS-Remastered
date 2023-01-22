#ifndef DYNOS_H
#define DYNOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <dirent.h>
#include <SDL2/SDL.h>
#ifdef __cplusplus
#include <new>
#include <utility>
#include <string>
extern "C" {
#endif
#include "config.h"
#include "audio_defines.h"
#include "pc/configfile.h"
#include "pc/fs/fs.h"
#undef STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#ifdef __cplusplus
}
#endif

#define DYNOS_VERSION           "1.1.alpha"
#define DYNOS_EXE_FOLDER        sys_exe_path()
#define DYNOS_USER_FOLDER       sys_user_path()
#define DYNOS_RES_FOLDER        "dynos"
#define DYNOS_GFX_FOLDER        DYNOS_RES_FOLDER "/gfx"
#define DYNOS_AUDIO_FOLDER      DYNOS_RES_FOLDER "/audio"
#define DYNOS_PACKS_FOLDER      DYNOS_RES_FOLDER "/packs"
#define DYNOS_CONFIG_FILENAME   "DynOS." DYNOS_VERSION ".config.txt"
#define DYNOS_AT_STARTUP        __attribute__((constructor))
#define DYNOS_AT_EXIT           __attribute__((destructor))
#define EXPAND(...)             __VA_ARGS__

#endif