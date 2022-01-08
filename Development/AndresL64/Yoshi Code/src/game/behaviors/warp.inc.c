// warp.c.inc

void bhv_warp_loop(void) {
    u16 sp6;
    if (o->oTimer == 0) {
        sp6 = (o->oBehParams >> 24) & 0xFF;
        if (sp6 == 0)
            o->hitboxRadius = 50.0f;
        else if (sp6 == 0xFF)
            o->hitboxRadius = 10000.0f;
        else
            o->hitboxRadius = sp6 * 10.0;
        o->hitboxHeight = 50.0f;
    }
    o->oInteractStatus = 0;
}

void bhv_warp_locked_luigi_init() {
    if(gMarioState->numKeys == 10)
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void bhv_warp_unlocked_luigi_init() {
    if(gMarioState->numKeys != 10)
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void bhv_warp_unlocked_wario_init() {
    if(gMarioState->numWarioCoins != 6)
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void bhv_warp_locked_wario_init() {
    if(gMarioState->numWarioCoins == 6)
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void bhv_fading_warp_loop() // identical to the above function except for o->hitboxRadius
{
    u16 sp6;
    if (o->oTimer == 0) {
        sp6 = (o->oBehParams >> 24) & 0xFF;
        if (sp6 == 0)
            o->hitboxRadius = 85.0f;
        else if (sp6 == 0xFF)
            o->hitboxRadius = 10000.0f;
        else
            o->hitboxRadius = sp6 * 10.0;
        o->hitboxHeight = 50.0f;
    }
    o->oInteractStatus = 0;
}
