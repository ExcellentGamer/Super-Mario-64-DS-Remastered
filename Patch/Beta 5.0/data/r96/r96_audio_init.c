#ifndef R96_AUDIO
#define R96_AUDIO

#include "data/r96/r96_c_includes.h"
#include "data/r96/system/r96_system.h"

EffectData R96_EffectData[LEVEL_MAX+1][5];

void R96_Effect_Init() {
{
    R96_EffectData[0][1].name = NULL;
    R96_EffectData[0][1].roomSize = 1.0f/10.0f;
    R96_EffectData[0][1].damping = 0.25f;
    R96_EffectData[0][1].width = 1.0f;
    R96_EffectData[0][1].wetVolume = 0.1f;
    R96_EffectData[0][1].dryVolume = 0.5f;
    R96_EffectData[0][1].mode = 0.0f;
}
    //LEVEL_UNKNOWN_1
{
    R96_EffectData[LEVEL_UNKNOWN_1][0].name = NULL;
    R96_EffectData[LEVEL_UNKNOWN_1][0].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_UNKNOWN_1][0].damping = 0.25f;
    R96_EffectData[LEVEL_UNKNOWN_1][0].width = 1.0f;
    R96_EffectData[LEVEL_UNKNOWN_1][0].wetVolume = 0.1f;
    R96_EffectData[LEVEL_UNKNOWN_1][0].dryVolume = 0.5f;
    R96_EffectData[LEVEL_UNKNOWN_1][0].mode = 0.0f;
}
    //LEVEL_UNKNOWN_2
{
    R96_EffectData[LEVEL_UNKNOWN_2][0].name = NULL;
    R96_EffectData[LEVEL_UNKNOWN_2][0].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_UNKNOWN_2][0].damping = 0.25f;
    R96_EffectData[LEVEL_UNKNOWN_2][0].width = 1.0f;
    R96_EffectData[LEVEL_UNKNOWN_2][0].wetVolume = 0.1f;
    R96_EffectData[LEVEL_UNKNOWN_2][0].dryVolume = 0.5f;
    R96_EffectData[LEVEL_UNKNOWN_2][0].mode = 0.0f;
}
    //LEVEL_UNKNOWN_3
{
    //R96_EffectData[LEVEL_UNKNOWN_3][0].name = NULL;
    R96_EffectData[LEVEL_UNKNOWN_3][0].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_UNKNOWN_3][0].damping = 0.25f;
    R96_EffectData[LEVEL_UNKNOWN_3][0].width = 1.0f;
    R96_EffectData[LEVEL_UNKNOWN_3][0].wetVolume = 0.1f;
    R96_EffectData[LEVEL_UNKNOWN_3][0].dryVolume = 0.5f;
    R96_EffectData[LEVEL_UNKNOWN_3][0].mode = 0.0f;
}
    //LEVEL_BBH
{
    R96_EffectData[LEVEL_BBH][1].name = R96_LEVEL_BBH_PHASE_1;
    R96_EffectData[LEVEL_BBH][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_BBH][1].damping = 0.25f;
    R96_EffectData[LEVEL_BBH][1].width = 1.0f;
    R96_EffectData[LEVEL_BBH][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_BBH][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_BBH][1].mode = 0.0f;

    R96_EffectData[LEVEL_BBH][2].name = R96_LEVEL_BBH_PHASE_2;
    R96_EffectData[LEVEL_BBH][2].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_BBH][2].damping = 0.25f;
    R96_EffectData[LEVEL_BBH][2].width = 1.0f;
    R96_EffectData[LEVEL_BBH][2].wetVolume = 0.1f;
    R96_EffectData[LEVEL_BBH][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_BBH][2].mode = 0.0f;
}
    //LEVEL_CCM
{
    R96_EffectData[LEVEL_CCM][1].name = R96_LEVEL_CCM;
    R96_EffectData[LEVEL_CCM][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_CCM][1].damping = 0.25f;
    R96_EffectData[LEVEL_CCM][1].width = 1.0f;
    R96_EffectData[LEVEL_CCM][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_CCM][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_CCM][1].mode = 0.0f;

    R96_EffectData[LEVEL_CCM][2].name = R96_LEVEL_CCM_SLIDE;
    R96_EffectData[LEVEL_CCM][2].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_CCM][2].damping = 0.25f;
    R96_EffectData[LEVEL_CCM][2].width = 1.0f;
    R96_EffectData[LEVEL_CCM][2].wetVolume = 0.2f;
    R96_EffectData[LEVEL_CCM][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_CCM][2].mode = 0.0f;
}
    //LEVEL_CASTLE
{
    R96_EffectData[LEVEL_CASTLE][1].name = R96_LEVEL_INSIDE_CASTLE_LOBBY;
    R96_EffectData[LEVEL_CASTLE][1].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_CASTLE][1].damping = 0.25f;
    R96_EffectData[LEVEL_CASTLE][1].width = 1.0f;
    R96_EffectData[LEVEL_CASTLE][1].wetVolume = 0.2f;
    R96_EffectData[LEVEL_CASTLE][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_CASTLE][1].mode = 0.0f;

    R96_EffectData[LEVEL_REC_ROOM][1].name = R96_LEVEL_INSIDE_CASTLE_LOBBY;
    R96_EffectData[LEVEL_REC_ROOM][1].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_REC_ROOM][1].damping = 0.25f;
    R96_EffectData[LEVEL_REC_ROOM][1].width = 1.0f;
    R96_EffectData[LEVEL_REC_ROOM][1].wetVolume = 0.2f;
    R96_EffectData[LEVEL_REC_ROOM][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_REC_ROOM][1].mode = 0.0f;

    R96_EffectData[LEVEL_CASTLE][2].name = R96_LEVEL_INSIDE_CASTLE_TIPPY;
    R96_EffectData[LEVEL_CASTLE][2].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_CASTLE][2].damping = 0.25f;
    R96_EffectData[LEVEL_CASTLE][2].width = 1.0f;
    R96_EffectData[LEVEL_CASTLE][2].wetVolume = 0.2f;
    R96_EffectData[LEVEL_CASTLE][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_CASTLE][2].mode = 0.0f;

    R96_EffectData[LEVEL_CASTLE][3].name = R96_LEVEL_INSIDE_CASTLE_BASEMENT;
    R96_EffectData[LEVEL_CASTLE][3].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_CASTLE][3].damping = 0.25f;
    R96_EffectData[LEVEL_CASTLE][3].width = 1.0f;
    R96_EffectData[LEVEL_CASTLE][3].wetVolume = 0.2f;
    R96_EffectData[LEVEL_CASTLE][3].dryVolume = 0.5f;
    R96_EffectData[LEVEL_CASTLE][3].mode = 0.0f;
}
    //LEVEL_HMC
{
    R96_EffectData[LEVEL_HMC][1].name = R96_LEVEL_HMC_PHASE_1;
    R96_EffectData[LEVEL_HMC][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_HMC][1].damping = 0.25f;
    R96_EffectData[LEVEL_HMC][1].width = 1.0f;
    R96_EffectData[LEVEL_HMC][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_HMC][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_HMC][1].mode = 0.0f;

    R96_EffectData[LEVEL_HMC][2].name = R96_LEVEL_HMC_PHASE_2;
    R96_EffectData[LEVEL_HMC][2].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_HMC][2].damping = 0.25f;
    R96_EffectData[LEVEL_HMC][2].width = 1.0f;
    R96_EffectData[LEVEL_HMC][2].wetVolume = 0.1f;
    R96_EffectData[LEVEL_HMC][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_HMC][2].mode = 0.0f;
}
    //LEVEL_SSL
{
    R96_EffectData[LEVEL_SSL][1].name = R96_LEVEL_SSL_OUTSIDE;
    R96_EffectData[LEVEL_SSL][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_SSL][1].damping = 0.25f;
    R96_EffectData[LEVEL_SSL][1].width = 1.0f;
    R96_EffectData[LEVEL_SSL][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_SSL][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_SSL][1].mode = 0.0f;

    R96_EffectData[LEVEL_SSL][2].name = R96_LEVEL_SSL_PYRAMID;
    R96_EffectData[LEVEL_SSL][2].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_SSL][2].damping = 0.25f;
    R96_EffectData[LEVEL_SSL][2].width = 1.0f;
    R96_EffectData[LEVEL_SSL][2].wetVolume = 0.1f;
    R96_EffectData[LEVEL_SSL][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_SSL][2].mode = 0.0f;

    R96_EffectData[LEVEL_SSL][3].name = R96_LEVEL_SSL_EYEROK;
    R96_EffectData[LEVEL_SSL][3].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_SSL][3].damping = 0.25f;
    R96_EffectData[LEVEL_SSL][3].width = 1.0f;
    R96_EffectData[LEVEL_SSL][3].wetVolume = 0.1f;
    R96_EffectData[LEVEL_SSL][3].dryVolume = 0.5f;
    R96_EffectData[LEVEL_SSL][3].mode = 0.0f;
}
    //LEVEL_BOB
{
    R96_EffectData[LEVEL_BOB][1].name = R96_LEVEL_BOB;
    R96_EffectData[LEVEL_BOB][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_BOB][1].damping = 0.25f;
    R96_EffectData[LEVEL_BOB][1].width = 1.0f;
    R96_EffectData[LEVEL_BOB][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_BOB][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_BOB][1].mode = 0.0f;
}
    //LEVEL_SL
{
    R96_EffectData[LEVEL_SL][1].name = R96_LEVEL_SL_OUTSIDE;
    R96_EffectData[LEVEL_SL][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_SL][1].damping = 0.25f;
    R96_EffectData[LEVEL_SL][1].width = 1.0f;
    R96_EffectData[LEVEL_SL][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_SL][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_SL][1].mode = 0.0f;

    R96_EffectData[LEVEL_SL][2].name = R96_LEVEL_SL_IGLOO;
    R96_EffectData[LEVEL_SL][2].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_SL][2].damping = 0.25f;
    R96_EffectData[LEVEL_SL][2].width = 1.0f;
    R96_EffectData[LEVEL_SL][2].wetVolume = 0.1f;
    R96_EffectData[LEVEL_SL][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_SL][2].mode = 0.0f;
}
    //LEVEL_WDW
{
    R96_EffectData[LEVEL_WDW][1].name = R96_LEVEL_WDW_MAIN;
    R96_EffectData[LEVEL_WDW][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_WDW][1].damping = 0.25f;
    R96_EffectData[LEVEL_WDW][1].width = 1.0f;
    R96_EffectData[LEVEL_WDW][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_WDW][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_WDW][1].mode = 0.0f;

    R96_EffectData[LEVEL_WDW][2].name = R96_LEVEL_WDW_TOWN;
    R96_EffectData[LEVEL_WDW][2].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_WDW][2].damping = 0.25f;
    R96_EffectData[LEVEL_WDW][2].width = 1.0f;
    R96_EffectData[LEVEL_WDW][2].wetVolume = 0.1f;
    R96_EffectData[LEVEL_WDW][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_WDW][2].mode = 0.0f;
}
    //LEVEL_JRB
    R96_EffectData[LEVEL_JRB][1].name = R96_LEVEL_JRB_PHASE_1;
    R96_EffectData[LEVEL_JRB][1].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_JRB][1].damping = 0.25f;
    R96_EffectData[LEVEL_JRB][1].width = 1.0f;
    R96_EffectData[LEVEL_JRB][1].wetVolume = 0.2f;
    R96_EffectData[LEVEL_JRB][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_JRB][1].mode = 0.0f;

    R96_EffectData[LEVEL_JRB][2].name = R96_LEVEL_JRB_PHASE_2;
    R96_EffectData[LEVEL_JRB][2].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_JRB][2].damping = 0.25f;
    R96_EffectData[LEVEL_JRB][2].width = 1.0f;
    R96_EffectData[LEVEL_JRB][2].wetVolume = 0.2f;
    R96_EffectData[LEVEL_JRB][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_JRB][2].mode = 0.0f;

    R96_EffectData[LEVEL_JRB][3].name = R96_LEVEL_JRB_PHASE_3;
    R96_EffectData[LEVEL_JRB][3].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_JRB][3].damping = 0.25f;
    R96_EffectData[LEVEL_JRB][3].width = 1.0f;
    R96_EffectData[LEVEL_JRB][3].wetVolume = 0.2f;
    R96_EffectData[LEVEL_JRB][3].dryVolume = 0.5f;
    R96_EffectData[LEVEL_JRB][3].mode = 0.0f;

    R96_EffectData[LEVEL_JRB][4].name = R96_LEVEL_JRB_SHIP;
    R96_EffectData[LEVEL_JRB][4].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_JRB][4].damping = 0.25f;
    R96_EffectData[LEVEL_JRB][4].width = 1.0f;
    R96_EffectData[LEVEL_JRB][4].wetVolume = 0.2f;
    R96_EffectData[LEVEL_JRB][4].dryVolume = 0.5f;
    R96_EffectData[LEVEL_JRB][4].mode = 0.0f;

    //LEVEL_THI
    R96_EffectData[LEVEL_THI][1].name = R96_LEVEL_THI_HUGE;
    R96_EffectData[LEVEL_THI][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_THI][1].damping = 0.25f;
    R96_EffectData[LEVEL_THI][1].width = 1.0f;
    R96_EffectData[LEVEL_THI][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_THI][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_THI][1].mode = 0.0f;

    R96_EffectData[LEVEL_THI][2].name = R96_LEVEL_THI_TINY;
    R96_EffectData[LEVEL_THI][2].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_THI][2].damping = 0.25f;
    R96_EffectData[LEVEL_THI][2].width = 1.0f;
    R96_EffectData[LEVEL_THI][2].wetVolume = 0.1f;
    R96_EffectData[LEVEL_THI][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_THI][2].mode = 0.0f;

    R96_EffectData[LEVEL_THI][3].name = R96_LEVEL_THI_WIGGLER;
    R96_EffectData[LEVEL_THI][3].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_THI][3].damping = 0.25f;
    R96_EffectData[LEVEL_THI][3].width = 1.0f;
    R96_EffectData[LEVEL_THI][3].wetVolume = 0.1f;
    R96_EffectData[LEVEL_THI][3].dryVolume = 0.5f;
    R96_EffectData[LEVEL_THI][3].mode = 0.0f;

    //LEVEL_TTC
    R96_EffectData[LEVEL_TTC][1].name = R96_LEVEL_TTC;
    R96_EffectData[LEVEL_TTC][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_TTC][1].damping = 0.25f;
    R96_EffectData[LEVEL_TTC][1].width = 1.0f;
    R96_EffectData[LEVEL_TTC][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_TTC][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_TTC][1].mode = 0.0f;

    //LEVEL_RR
    R96_EffectData[LEVEL_RR][1].name = R96_LEVEL_TTC;
    R96_EffectData[LEVEL_RR][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_RR][1].damping = 0.25f;
    R96_EffectData[LEVEL_RR][1].width = 1.0f;
    R96_EffectData[LEVEL_RR][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_RR][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_RR][1].mode = 0.0f;

    //LEVEL_CASTLE_GROUNDS
    R96_EffectData[LEVEL_CASTLE_GROUNDS][1].name = R96_LEVEL_CASTLE_GROUNDS;
    R96_EffectData[LEVEL_CASTLE_GROUNDS][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_CASTLE_GROUNDS][1].damping = 0.25f;
    R96_EffectData[LEVEL_CASTLE_GROUNDS][1].width = 1.0f;
    R96_EffectData[LEVEL_CASTLE_GROUNDS][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_CASTLE_GROUNDS][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_CASTLE_GROUNDS][1].mode = 0.0f;

    //LEVEL_BITDW
    R96_EffectData[LEVEL_BITDW][1].name = R96_LEVEL_BITDW;
    R96_EffectData[LEVEL_BITDW][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_BITDW][1].damping = 0.25f;
    R96_EffectData[LEVEL_BITDW][1].width = 1.0f;
    R96_EffectData[LEVEL_BITDW][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_BITDW][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_BITDW][1].mode = 0.0f;

    //LEVEL_VCUTM
    R96_EffectData[LEVEL_VCUTM][1].name = R96_LEVEL_VCUTM;
    R96_EffectData[LEVEL_VCUTM][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_VCUTM][1].damping = 0.25f;
    R96_EffectData[LEVEL_VCUTM][1].width = 1.0f;
    R96_EffectData[LEVEL_VCUTM][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_VCUTM][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_VCUTM][1].mode = 0.0f;

    //LEVEL_BITFS
    R96_EffectData[LEVEL_BITFS][1].name = R96_LEVEL_BITFS;
    R96_EffectData[LEVEL_BITFS][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_BITFS][1].damping = 0.25f;
    R96_EffectData[LEVEL_BITFS][1].width = 1.0f;
    R96_EffectData[LEVEL_BITFS][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_BITFS][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_BITFS][1].mode = 0.0f;

    //LEVEL_SA
    R96_EffectData[LEVEL_SA][1].name = R96_LEVEL_SA;
    R96_EffectData[LEVEL_SA][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_SA][1].damping = 0.25f;
    R96_EffectData[LEVEL_SA][1].width = 1.0f;
    R96_EffectData[LEVEL_SA][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_SA][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_SA][1].mode = 0.0f;

    //LEVEL_BITS
    R96_EffectData[LEVEL_BITS][1].name = R96_LEVEL_BITFS;
    R96_EffectData[LEVEL_BITS][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_BITS][1].damping = 0.25f;
    R96_EffectData[LEVEL_BITS][1].width = 1.0f;
    R96_EffectData[LEVEL_BITS][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_BITS][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_BITS][1].mode = 0.0f;

    //LEVEL_LLL
    R96_EffectData[LEVEL_LLL][1].name = R96_LEVEL_LLL_OUTSIDE;
    R96_EffectData[LEVEL_LLL][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_LLL][1].damping = 0.25f;
    R96_EffectData[LEVEL_LLL][1].width = 1.0f;
    R96_EffectData[LEVEL_LLL][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_LLL][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_LLL][1].mode = 0.0f;

    R96_EffectData[LEVEL_LLL][2].name = R96_LEVEL_LLL_VOLCANO;
    R96_EffectData[LEVEL_LLL][2].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_LLL][2].damping = 0.25f;
    R96_EffectData[LEVEL_LLL][2].width = 1.0f;
    R96_EffectData[LEVEL_LLL][2].wetVolume = 0.1f;
    R96_EffectData[LEVEL_LLL][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_LLL][2].mode = 0.0f;

    //LEVEL_DDD
    R96_EffectData[LEVEL_DDD][1].name = R96_LEVEL_DDD_PHASE_1;
    R96_EffectData[LEVEL_DDD][1].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_DDD][1].damping = 0.25f;
    R96_EffectData[LEVEL_DDD][1].width = 1.0f;
    R96_EffectData[LEVEL_DDD][1].wetVolume = 0.2f;
    R96_EffectData[LEVEL_DDD][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_DDD][1].mode = 0.0f;

    R96_EffectData[LEVEL_DDD][2].name = R96_LEVEL_DDD_PHASE_2;
    R96_EffectData[LEVEL_DDD][2].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_DDD][2].damping = 0.25f;
    R96_EffectData[LEVEL_DDD][2].width = 1.0f;
    R96_EffectData[LEVEL_DDD][2].wetVolume = 0.2f;
    R96_EffectData[LEVEL_DDD][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_DDD][2].mode = 0.0f;

    R96_EffectData[LEVEL_DDD][3].name = R96_LEVEL_DDD_PHASE_3;
    R96_EffectData[LEVEL_DDD][3].roomSize = 1.0f/3.0f;
    R96_EffectData[LEVEL_DDD][3].damping = 0.25f;
    R96_EffectData[LEVEL_DDD][3].width = 1.0f;
    R96_EffectData[LEVEL_DDD][3].wetVolume = 0.2f;
    R96_EffectData[LEVEL_DDD][3].dryVolume = 0.5f;
    R96_EffectData[LEVEL_DDD][3].mode = 0.0f;

    //LEVEL_WF
    R96_EffectData[LEVEL_WF][1].name = R96_LEVEL_WF;
    R96_EffectData[LEVEL_WF][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_WF][1].damping = 0.25f;
    R96_EffectData[LEVEL_WF][1].width = 1.0f;
    R96_EffectData[LEVEL_WF][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_WF][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_WF][1].mode = 0.0f;

    //LEVEL_ENDING
    R96_EffectData[LEVEL_ENDING][1].name = NULL;
    R96_EffectData[LEVEL_ENDING][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_ENDING][1].damping = 0.25f;
    R96_EffectData[LEVEL_ENDING][1].width = 1.0f;
    R96_EffectData[LEVEL_ENDING][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_ENDING][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_ENDING][1].mode = 0.0f;

    //LEVEL_CASTLE_COURTYARD
    R96_EffectData[LEVEL_CASTLE_COURTYARD][1].name = R96_LEVEL_CASTLE_COURTYARD;
    R96_EffectData[LEVEL_CASTLE_COURTYARD][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_CASTLE_COURTYARD][1].damping = 0.25f;
    R96_EffectData[LEVEL_CASTLE_COURTYARD][1].width = 1.0f;
    R96_EffectData[LEVEL_CASTLE_COURTYARD][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_CASTLE_COURTYARD][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_CASTLE_COURTYARD][1].mode = 0.0f;

    //LEVEL_PSS
    R96_EffectData[LEVEL_PSS][1].name = R96_LEVEL_PSS;
    R96_EffectData[LEVEL_PSS][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_PSS][1].damping = 0.25f;
    R96_EffectData[LEVEL_PSS][1].width = 1.0f;
    R96_EffectData[LEVEL_PSS][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_PSS][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_PSS][1].mode = 0.0f;

    //LEVEL_COTMC
    R96_EffectData[LEVEL_COTMC][1].name = R96_LEVEL_COTMC;
    R96_EffectData[LEVEL_COTMC][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_COTMC][1].damping = 0.25f;
    R96_EffectData[LEVEL_COTMC][1].width = 1.0f;
    R96_EffectData[LEVEL_COTMC][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_COTMC][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_COTMC][1].mode = 0.0f;

    //LEVEL_TOTWC
    R96_EffectData[LEVEL_TOTWC][1].name = R96_LEVEL_TOTWC;
    R96_EffectData[LEVEL_TOTWC][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_TOTWC][1].damping = 0.25f;
    R96_EffectData[LEVEL_TOTWC][1].width = 1.0f;
    R96_EffectData[LEVEL_TOTWC][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_TOTWC][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_TOTWC][1].mode = 0.0f;

    //LEVEL_BOWSER_1
    R96_EffectData[LEVEL_BOWSER_1][1].name = R96_LEVEL_BOWSER_1;
    R96_EffectData[LEVEL_BOWSER_1][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_BOWSER_1][1].damping = 0.25f;
    R96_EffectData[LEVEL_BOWSER_1][1].width = 1.0f;
    R96_EffectData[LEVEL_BOWSER_1][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_BOWSER_1][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_BOWSER_1][1].mode = 0.0f;

    //LEVEL_WMOTR
    R96_EffectData[LEVEL_WMOTR][1].name = R96_LEVEL_WMOTR;
    R96_EffectData[LEVEL_WMOTR][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_WMOTR][1].damping = 0.25f;
    R96_EffectData[LEVEL_WMOTR][1].width = 1.0f;
    R96_EffectData[LEVEL_WMOTR][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_WMOTR][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_WMOTR][1].mode = 0.0f;

    //LEVEL_UNKNOWN_32
    R96_EffectData[LEVEL_UNKNOWN_32][1].name = NULL;
    R96_EffectData[LEVEL_UNKNOWN_32][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_UNKNOWN_32][1].damping = 0.25f;
    R96_EffectData[LEVEL_UNKNOWN_32][1].width = 1.0f;
    R96_EffectData[LEVEL_UNKNOWN_32][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_UNKNOWN_32][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_UNKNOWN_32][1].mode = 0.0f;

    //LEVEL_BOWSER_2
    R96_EffectData[LEVEL_BOWSER_2][1].name = R96_LEVEL_BOWSER_2;
    R96_EffectData[LEVEL_BOWSER_2][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_BOWSER_2][1].damping = 0.25f;
    R96_EffectData[LEVEL_BOWSER_2][1].width = 1.0f;
    R96_EffectData[LEVEL_BOWSER_2][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_BOWSER_2][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_BOWSER_2][1].mode = 0.0f;

    //LEVEL_BOWSER_3
    R96_EffectData[LEVEL_BOWSER_3][1].name = R96_LEVEL_BOWSER_3;
    R96_EffectData[LEVEL_BOWSER_3][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_BOWSER_3][1].damping = 0.25f;
    R96_EffectData[LEVEL_BOWSER_3][1].width = 1.0f;
    R96_EffectData[LEVEL_BOWSER_3][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_BOWSER_3][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_BOWSER_3][1].mode = 0.0f;

    //LEVEL_UNKNOWN_35
    R96_EffectData[LEVEL_UNKNOWN_35][1].name = NULL;
    R96_EffectData[LEVEL_UNKNOWN_35][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_UNKNOWN_35][1].damping = 0.25f;
    R96_EffectData[LEVEL_UNKNOWN_35][1].width = 1.0f;
    R96_EffectData[LEVEL_UNKNOWN_35][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_UNKNOWN_35][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_UNKNOWN_35][1].mode = 0.0f;

    //LEVEL_TTM
    R96_EffectData[LEVEL_TTM][1].name = R96_LEVEL_TTM_OUTSIDE;
    R96_EffectData[LEVEL_TTM][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_TTM][1].damping = 0.25f;
    R96_EffectData[LEVEL_TTM][1].width = 1.0f;
    R96_EffectData[LEVEL_TTM][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_TTM][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_TTM][1].mode = 0.0f;

    R96_EffectData[LEVEL_TTM][2].name = R96_LEVEL_TTM_SLIDE;
    R96_EffectData[LEVEL_TTM][2].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_TTM][2].damping = 0.25f;
    R96_EffectData[LEVEL_TTM][2].width = 1.0f;
    R96_EffectData[LEVEL_TTM][2].wetVolume = 0.1f;
    R96_EffectData[LEVEL_TTM][2].dryVolume = 0.5f;
    R96_EffectData[LEVEL_TTM][2].mode = 0.0f;

    R96_EffectData[LEVEL_TTM][3].name = R96_LEVEL_TTM_SLIDE;
    R96_EffectData[LEVEL_TTM][3].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_TTM][3].damping = 0.25f;
    R96_EffectData[LEVEL_TTM][3].width = 1.0f;
    R96_EffectData[LEVEL_TTM][3].wetVolume = 0.1f;
    R96_EffectData[LEVEL_TTM][3].dryVolume = 0.5f;
    R96_EffectData[LEVEL_TTM][3].mode = 0.0f;

    R96_EffectData[LEVEL_TTM][4].name = R96_LEVEL_TTM_SLIDE;
    R96_EffectData[LEVEL_TTM][4].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_TTM][4].damping = 0.25f;
    R96_EffectData[LEVEL_TTM][4].width = 1.0f;
    R96_EffectData[LEVEL_TTM][4].wetVolume = 0.1f;
    R96_EffectData[LEVEL_TTM][4].dryVolume = 0.5f;
    R96_EffectData[LEVEL_TTM][4].mode = 0.0f;

    //LEVEL_UNKNOWN_37
    R96_EffectData[LEVEL_UNKNOWN_37][1].name = NULL;
    R96_EffectData[LEVEL_UNKNOWN_37][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_UNKNOWN_37][1].damping = 0.25f;
    R96_EffectData[LEVEL_UNKNOWN_37][1].width = 1.0f;
    R96_EffectData[LEVEL_UNKNOWN_37][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_UNKNOWN_37][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_UNKNOWN_37][1].mode = 0.0f;

    //LEVEL_UNKNOWN_38
    R96_EffectData[LEVEL_UNKNOWN_38][1].name = NULL;
    R96_EffectData[LEVEL_UNKNOWN_38][1].roomSize = 1.0f/10.0f;
    R96_EffectData[LEVEL_UNKNOWN_38][1].damping = 0.25f;
    R96_EffectData[LEVEL_UNKNOWN_38][1].width = 1.0f;
    R96_EffectData[LEVEL_UNKNOWN_38][1].wetVolume = 0.1f;
    R96_EffectData[LEVEL_UNKNOWN_38][1].dryVolume = 0.5f;
    R96_EffectData[LEVEL_UNKNOWN_38][1].mode = 0.0f;
}
#endif