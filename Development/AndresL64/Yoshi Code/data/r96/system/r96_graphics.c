#include "src/pc/gfx/gfx_rendering_api.h"
#include "src/pc/pc_main.h"
#include "data/r96/r96_c_includes.h"

// Resolution stuff
int internalHeight[] = {
    240,
    480,
    720,
    1080,
    1440,
    360,
    480,
    720,
    900,
    1080,
    1440,
    2160
};

int internalWidth[] = {
    320,
    640,
    960,
    1440,
    1920,
    640,
    848,
    1280,
    1600,
    1920,
    2560,
    3840
};

void internal_resolution() {

    //Windowed
    //configWindow.w = internalWidth[configCustomWindowResolution];
    //configWindow.h = internalHeight[configCustomWindowResolution];

    //Internal
    configInternalResolutionWidth = internalWidth[configCustomInternalResolution];
    configInternalResolutionHeight = internalHeight[configCustomInternalResolution];

    gfx_get_current_rendering_api()->on_resize();
#ifdef WAPI_DXGI
    gfx_dxgi_update_dimensions();
#endif
}