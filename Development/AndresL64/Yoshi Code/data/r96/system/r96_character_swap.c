#include "r96_system.h"
#include "game/area.h"
#include "include/model_ids.h"
#include "game/mario.h"
#include "game/level_update.h"
#include "include/sm64.h"
#include "audio/data.h"
#include "audio/external.h"
#include "seq_ids.h"
#include "game/hud.h"

void setCharacterModel(s32 characterType){
    s32 type = MODEL_MARIO;
    switch (characterType) {
        case MARIO_DEFAULT:
            type = MODEL_MARIO;
            break;
        case LUIGI:
            type = MODEL_LUIGI;
            break;
        case WARIO:
            type = MODEL_WARIO;
            break;
        case YOSHI:
            type = MODEL_YOSHI_DS;
            break;
    }

    gLoadedGraphNodes[MODEL_PLAYER] = gLoadedGraphNodes[type];
}

s32 getCharacterType(){
    s32 type;
    if(gLoadedGraphNodes[MODEL_PLAYER] == gLoadedGraphNodes[MODEL_MARIO]){
        type = MARIO_DEFAULT;
    }else if(gLoadedGraphNodes[MODEL_PLAYER] == gLoadedGraphNodes[MODEL_LUIGI]){
        type = LUIGI;
    }else if(gLoadedGraphNodes[MODEL_PLAYER] == gLoadedGraphNodes[MODEL_WARIO]){
        type = WARIO;
    }else if(gLoadedGraphNodes[MODEL_PLAYER] == gLoadedGraphNodes[MODEL_YOSHI_DS]){
        type = YOSHI;
    }else{
        type = MARIO_DEFAULT;
    }
    return type;
}

f32 getCharacterMultiplier(){
    f32 mul = 1.0f;
    switch (getCharacterType()) {
        case MARIO_DEFAULT:
        case YOSHI:
            mul = 1.0f;
            break;
        case LUIGI:
            mul = 1.07f;
            break;
        case WARIO:
            mul = 1.0f;
            break;
    }
    return mul;
}

s32 isLuigi(){
    return getCharacterType() == LUIGI;
}

s32 isWario(){
    return getCharacterType() == WARIO;
}

s32 isYoshi(){
    return getCharacterType() == YOSHI;
}

s8 notificationStatus = FALSE;

void triggerLuigiNotification(){
    if(!notificationStatus){
        r96_play_collect_jingle(R96_EVENT_SOLVE_PUZZLE);
        queue_rumble_data(15, 80);
        set_notification_state(TRUE);
        notificationStatus = TRUE;
    }    
}

void set_notification_status(s8 newState){
    notificationStatus = newState;
}
s8 get_notification_status(){
    return notificationStatus;
}
