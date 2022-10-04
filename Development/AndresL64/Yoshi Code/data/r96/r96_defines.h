#ifndef R96_DEFINES_H
#define R96_DEFINES_H

/* Character Swap */
#define MARIO_DEFAULT 0
#define LUIGI 1
#define WARIO 2
#define YOSHI 3

/* Music */
extern const char *R96_LEVEL_BOB;
extern const char *R96_LEVEL_WF;
extern const char *R96_LEVEL_CCM;
extern const char *R96_LEVEL_CCM_SLIDE;
extern const char *R96_LEVEL_JRB_PHASE_1;
extern const char *R96_LEVEL_JRB_PHASE_2;
extern const char *R96_LEVEL_JRB_PHASE_3;
extern const char *R96_LEVEL_JRB_SHIP;
extern const char *R96_LEVEL_BBH_PHASE_1;
extern const char *R96_LEVEL_BBH_PHASE_2;
extern const char *R96_LEVEL_HMC_PHASE_1;
extern const char *R96_LEVEL_HMC_PHASE_2;
extern const char *R96_LEVEL_LLL_OUTSIDE;
extern const char *R96_LEVEL_LLL_VOLCANO;
extern const char *R96_LEVEL_SSL_OUTSIDE;
extern const char *R96_LEVEL_SSL_PYRAMID;
extern const char *R96_LEVEL_SSL_EYEROK;
extern const char *R96_LEVEL_DDD_PHASE_1;
extern const char *R96_LEVEL_DDD_PHASE_2;
extern const char *R96_LEVEL_DDD_PHASE_3;
extern const char *R96_LEVEL_SL_OUTSIDE;
extern const char *R96_LEVEL_SL_IGLOO;
extern const char *R96_LEVEL_WDW_MAIN;
extern const char *R96_LEVEL_WDW_TOWN;
extern const char *R96_LEVEL_TTM_OUTSIDE;
extern const char *R96_LEVEL_TTM_SLIDE;
extern const char *R96_LEVEL_THI_HUGE;
extern const char *R96_LEVEL_THI_TINY;
extern const char *R96_LEVEL_THI_WIGGLER;
extern const char *R96_LEVEL_TTC;
extern const char *R96_LEVEL_RR;
extern const char *R96_LEVEL_BITDW;
extern const char *R96_LEVEL_BITFS;
extern const char *R96_LEVEL_BITS;
extern const char *R96_LEVEL_SA;
extern const char *R96_LEVEL_WMOTR;
extern const char *R96_LEVEL_PSS;
extern const char *R96_LEVEL_COTMC;
extern const char *R96_LEVEL_TOTWC;
extern const char *R96_LEVEL_VCUTM;
extern const char *R96_LEVEL_BOWSER_1;
extern const char *R96_LEVEL_BOWSER_2;
extern const char *R96_LEVEL_BOWSER_3;
extern const char *R96_LEVEL_INSIDE_CASTLE_LOBBY;
extern const char *R96_LEVEL_INSIDE_CASTLE_TIPPY;
extern const char *R96_LEVEL_INSIDE_CASTLE_BASEMENT;
extern const char *R96_LEVEL_CASTLE_GROUNDS;
extern const char *R96_LEVEL_CASTLE_COURTYARD;
extern const char *R96_LEVEL_FOURTH_FLOOR;

/* Jingle */
// loops
extern const char *R96_EVENT_BOSS_INTRO;
extern const char *R96_EVENT_BOSS_THEME;
extern const char *R96_EVENT_ENDLESS_STAIRS;
extern const char *R96_EVENT_MERRY_GO_ROUND;
extern const char *R96_EVENT_CAP_METAL;
extern const char *R96_EVENT_RACE;
extern const char *R96_EVENT_PIRANHA_PLANT;
extern const char *R96_MENU_FILE_SELECT;
extern const char *R96_EVENT_GOT_MILK;
extern const char *R96_EVENT_TITLE_SCREEN;
extern const char *R96_EVENT_CAP_VANISH;
extern const char *R96_EVENT_CAP_WING;
extern const char *R96_EVENT_SHELL;

//no loops
extern const char *R96_EVENT_GAME_OVER;
extern const char *R96_EVENT_KEY_COLLECT;
extern const char *R96_EVENT_PEACH_ENDING;
extern const char *R96_EVENT_PEACH_MESSAGE;
extern const char *R96_EVENT_RACE_FANFARE;
extern const char *R96_EVENT_SOLVE_PUZZLE;
extern const char *R96_EVENT_STAR_APPEAR;
extern const char *R96_EVENT_STAR_COLLECT;
extern const char *R96_EVENT_STAR_FANFARE;
extern const char *R96_EVENT_TOAD_MESSAGE;
extern const char *R96_EVENT_KOOPA_MESSAGE;
extern const char *R96_EVENT_INTRO;
extern const char *R96_EVENT_CREDITS;
extern const char *R96_EVENT_LAKITU_MESSAGE;
extern const char *R96_EVENT_VICTORY;
extern const char *R96_EVENT_STAR_SELECT;
extern const char *R96_EVENT_COLLECTIBLE_GRAB;

/* Sounds */
// sfx_mario
extern const char *R96_MARIO_HOO;
extern const char *R96_MARIO_WAH;
extern const char *R96_MARIO_YAH;
extern const char *R96_MARIO_HAHA;
extern const char *R96_MARIO_YAHOO;
extern const char *R96_MARIO_GRUNT;
extern const char *R96_MARIO_LIFT;
extern const char *R96_MARIO_THROW;
extern const char *R96_MARIO_WHOA;
extern const char *R96_MARIO_PULL_UP;
extern const char *R96_MARIO_ATTACKED;
extern const char *R96_MARIO_OOOF;
extern const char *R96_MARIO_HERE_WE_GO;
extern const char *R96_MARIO_YAWNING;
extern const char *R96_MARIO_SNORING_1;
extern const char *R96_MARIO_SNORING_2;
extern const char *R96_MARIO_DOH;
extern const char *R96_MARIO_GAME_OVER;
extern const char *R96_MARIO_HELLO;
extern const char *R96_MARIO_PRESS_START_TO_PLAY;
extern const char *R96_MARIO_TWIRL_BOUNCE;
extern const char *R96_MARIO_SNORING_3;
extern const char *R96_MARIO_SO_LONGA_BOWSER;
extern const char *R96_MARIO_IMA_TIRED;
extern const char *R96_MARIO_WAHA;
extern const char *R96_MARIO_YIPPEE;
extern const char *R96_MARIO_SOUND_LETS_A_GO;
    
// sfx_mario_peach        
extern const char *R96_MARIO_FALLING;
extern const char *R96_MARIO_HOOHOO;
extern const char *R96_MARIO_PANTING;
extern const char *R96_MARIO_DYING;
extern const char *R96_MARIO_ON_FIRE;
extern const char *R96_MARIO_GRUNT_2;
extern const char *R96_MARIO_COUGHING_1;
extern const char *R96_MARIO_ITS_A_ME_MARIO;
extern const char *R96_MARIO_PUNCH_YAH;
extern const char *R96_MARIO_PUNCH_HOO;
extern const char *R96_MARIO_MAMA_MIA;
extern const char *R96_MARIO_OKEY_DOKEY;
extern const char *R96_MARIO_DROWNING;
extern const char *R96_MARIO_THANK_YOU_PLAYING_MY_GAME;
extern const char *R96_MARIO_PEACH_DEAR_MARIO;
extern const char *R96_MARIO_PEACH_MARIO;
extern const char *R96_MARIO_PEACH_POWER_OF_THE_STARS;
extern const char *R96_MARIO_PEACH_THANKS_TO_YOU;
extern const char *R96_MARIO_PEACH_THANK_YOU_MARIO;
extern const char *R96_MARIO_PEACH_SOMETHING_SPECIAL;
extern const char *R96_MARIO_PEACH_BAKE_A_CAKE;
extern const char *R96_MARIO_PEACH_FOR_MARIO;
extern const char *R96_MARIO_SOUND_PEACH_MARIO2;
extern const char *R96_MARIO_PANTING_COLD;

// sfx_luigi
extern const char *R96_LUIGI_HOO;
extern const char *R96_LUIGI_WAH;
extern const char *R96_LUIGI_YAH;
extern const char *R96_LUIGI_HAHA;
extern const char *R96_LUIGI_YAHOO;
extern const char *R96_LUIGI_GRUNT;
extern const char *R96_LUIGI_LIFT;
extern const char *R96_LUIGI_THROW;
extern const char *R96_LUIGI_WHOA;
extern const char *R96_LUIGI_PULL_UP;
extern const char *R96_LUIGI_ATTACKED;
extern const char *R96_LUIGI_OOOF;
extern const char *R96_LUIGI_HERE_WE_GO;
extern const char *R96_LUIGI_YAWNING;
extern const char *R96_LUIGI_SNORING_1;
extern const char *R96_LUIGI_SNORING_2;
extern const char *R96_LUIGI_DOH;
extern const char *R96_LUIGI_GAME_OVER;
extern const char *R96_LUIGI_HELLO;
extern const char *R96_LUIGI_PRESS_START_TO_PLAY;
extern const char *R96_LUIGI_TWIRL_BOUNCE;
extern const char *R96_LUIGI_SNORING_3;
extern const char *R96_LUIGI_SO_LONGA_BOWSER;
extern const char *R96_LUIGI_IMA_TIRED;
extern const char *R96_LUIGI_WAHA;
extern const char *R96_LUIGI_YIPPEE;
extern const char *R96_LUIGI_SOUND_LETS_A_GO;
    
// sfx_luigi_peach        
extern const char *R96_LUIGI_FALLING;
extern const char *R96_LUIGI_HOOHOO;
extern const char *R96_LUIGI_PANTING;
extern const char *R96_LUIGI_DYING;
extern const char *R96_LUIGI_ON_FIRE;
extern const char *R96_LUIGI_GRUNT_2;
extern const char *R96_LUIGI_COUGHING_1;
extern const char *R96_LUIGI_ITS_A_ME_LUIGI;
extern const char *R96_LUIGI_PUNCH_YAH;
extern const char *R96_LUIGI_PUNCH_HOO;
extern const char *R96_LUIGI_MAMA_MIA;
extern const char *R96_LUIGI_OKEY_DOKEY;
extern const char *R96_LUIGI_DROWNING;
extern const char *R96_LUIGI_THANK_YOU_PLAYING_MY_GAME;
extern const char *R96_LUIGI_PEACH_DEAR_LUIGI;
extern const char *R96_LUIGI_PEACH_LUIGI;
extern const char *R96_LUIGI_PEACH_POWER_OF_THE_STARS;
extern const char *R96_LUIGI_PEACH_THANKS_TO_YOU;
extern const char *R96_LUIGI_PEACH_THANK_YOU_LUIGI;
extern const char *R96_LUIGI_PEACH_SOMETHING_SPECIAL;
extern const char *R96_LUIGI_PEACH_BAKE_A_CAKE;
extern const char *R96_LUIGI_PEACH_FOR_LUIGI;
extern const char *R96_LUIGI_SOUND_PEACH_LUIGI2;
extern const char *R96_LUIGI_PANTING_COLD;

// sfx_wario
extern const char *R96_WARIO_HOO;
extern const char *R96_WARIO_WAH;
extern const char *R96_WARIO_YAH;
extern const char *R96_WARIO_HAHA;
extern const char *R96_WARIO_YAHOO;
extern const char *R96_WARIO_GRUNT;
extern const char *R96_WARIO_LIFT;
extern const char *R96_WARIO_THROW;
extern const char *R96_WARIO_WHOA;
extern const char *R96_WARIO_PULL_UP;
extern const char *R96_WARIO_ATTACKED;
extern const char *R96_WARIO_OOOF;
extern const char *R96_WARIO_HERE_WE_GO;
extern const char *R96_WARIO_YAWNING;
extern const char *R96_WARIO_SNORING_1;
extern const char *R96_WARIO_SNORING_2;
extern const char *R96_WARIO_DOH;
extern const char *R96_WARIO_GAME_OVER;
extern const char *R96_WARIO_HELLO;
extern const char *R96_WARIO_PRESS_START_TO_PLAY;
extern const char *R96_WARIO_TWIRL_BOUNCE;
extern const char *R96_WARIO_SNORING_3;
extern const char *R96_WARIO_SO_LONGA_BOWSER;
extern const char *R96_WARIO_IMA_TIRED;
extern const char *R96_WARIO_WAHA;
extern const char *R96_WARIO_YIPPEE;
extern const char *R96_WARIO_SOUND_LETS_A_GO;
    
// sfx_wario_peach        
extern const char *R96_WARIO_FALLING;
extern const char *R96_WARIO_HOOHOO;
extern const char *R96_WARIO_PANTING;
extern const char *R96_WARIO_DYING;
extern const char *R96_WARIO_ON_FIRE;
extern const char *R96_WARIO_GRUNT_2;
extern const char *R96_WARIO_COUGHING_1;
extern const char *R96_WARIO_ITS_A_ME_WARIO;
extern const char *R96_WARIO_PUNCH_YAH;
extern const char *R96_WARIO_PUNCH_HOO;
extern const char *R96_WARIO_MAMA_MIA;
extern const char *R96_WARIO_OKEY_DOKEY;
extern const char *R96_WARIO_DROWNING;
extern const char *R96_WARIO_THANK_YOU_PLAYING_MY_GAME;
extern const char *R96_WARIO_PEACH_DEAR_WARIO;
extern const char *R96_WARIO_PEACH_WARIO;
extern const char *R96_WARIO_PEACH_POWER_OF_THE_STARS;
extern const char *R96_WARIO_PEACH_THANKS_TO_YOU;
extern const char *R96_WARIO_PEACH_THANK_YOU_WARIO;
extern const char *R96_WARIO_PEACH_SOMETHING_SPECIAL;
extern const char *R96_WARIO_PEACH_BAKE_A_CAKE;
extern const char *R96_WARIO_PEACH_FOR_WARIO;
extern const char *R96_WARIO_SOUND_PEACH_WARIO2;
extern const char *R96_WARIO_PANTING_COLD;

#endif // R96_DEFINES_H
