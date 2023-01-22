#include "data/r96/r96_c_includes.h"
// Everything that should be initialized at the start of the game must be here
__attribute__((constructor))
static void r96_system_init() {
    //R96_Effect_Init();
    dynos_audio_init();
    dynos_music_stop();
    dynos_music_load_presets_from_dynos_folder("/music.txt", "levels");
    dynos_music_load_presets_from_dynos_folder("/music_other.txt", "jingles");
    dynos_jingle_load_presets_from_dynos_folder("/jingle.txt", "jingles");
    dynos_sound_load_presets_from_dynos_folder("/sfx_mario.txt", "sfx_mario");
    dynos_sound_load_presets_from_dynos_folder("/sfx_mario_peach.txt", "sfx_mario_peach");
    dynos_sound_load_presets_from_dynos_folder("/sfx_luigi.txt", "sfx_luigi");
    dynos_sound_load_presets_from_dynos_folder("/sfx_luigi_peach.txt", "sfx_luigi_peach");
    dynos_sound_load_presets_from_dynos_folder("/sfx_waluigi.txt", "sfx_waluigi");
    dynos_sound_load_presets_from_dynos_folder("/sfx_waluigi_peach.txt", "sfx_waluigi_peach");
    dynos_sound_load_presets_from_dynos_folder("/sfx_yoshi.txt", "sfx_yoshi");
    dynos_sound_load_presets_from_dynos_folder("/sfx_yoshi_peach.txt", "sfx_yoshi_peach");
    dynos_sound_load_presets_from_dynos_folder("/sfx_wario.txt", "sfx_wario");
    dynos_sound_load_presets_from_dynos_folder("/sfx_wario_peach.txt", "sfx_wario_peach");
   //// Levels - Main
   //dynos_music_load_from_r96_folder(R96_LEVEL_GRASS, 187327, 0.75f); //DONE
   //dynos_music_load_from_r96_folder(R96_LEVEL_SPOOKY, 905211, 0.80f); //DONE
   //dynos_music_load_from_r96_folder(R96_LEVEL_KOOPA_ROAD, 156800, 0.70f); //DONE
   //dynos_music_load_from_r96_folder(R96_LEVEL_BOSS_KOOPA, 222451, 0.75f); //DONE
   //dynos_music_load_from_r96_folder(R96_LEVEL_BOSS_KOOPA_FINAL, 1117670, 0.85f); //DONE
   //dynos_music_load_from_r96_folder(R96_LEVEL_INSIDE_CASTLE, 27015, 0.70f); //DONE
   //dynos_music_load_from_r96_folder(R96_LEVEL_SNOW, 138353, 0.70f); //DONE
   //dynos_music_load_from_r96_folder(R96_LEVEL_UNDERGROUND, 1597796, 1.00f); //DONE
   //dynos_music_load_from_r96_folder(R96_LEVEL_WATER, 159158, 0.75f); //DONE
   //dynos_music_load_from_r96_folder(R96_LEVEL_HOT, 619277, 0.75f); //DONE
   //dynos_music_load_from_r96_folder(R96_LEVEL_SLIDE, 126754, 0.65f); //DONE

   //// Other Music - Replaces Main
   //dynos_music_load_from_jingles_folder(R96_EVENT_BOSS_INTRO, 441000, 0.85f); //DONE
   //dynos_music_load_from_jingles_folder(R96_EVENT_BOSS_THEME, 124950, 0.85f); //DONE
   //dynos_music_load_from_jingles_folder(R96_EVENT_CAP_METAL, 180000, 0.70f); //DONE
   //dynos_music_load_from_jingles_folder(R96_EVENT_RACE, 126754, 0.80f); //DONE
   //dynos_music_load_from_jingles_folder(R96_EVENT_POWERUP, 313600, 0.65f); //DONE
   //dynos_music_load_from_jingles_folder(R96_EVENT_GOT_MILK, 1, 0.70f);

   //// Secondary Music - Plays with Main
   //dynos_jingle_load_from_jingles_folder(R96_MENU_FILE_SELECT, 1, 0.65f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_GAME_OVER, 556587, 0.70f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_TITLE_SCREEN, 123070, 0.70f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_ENDLESS_STAIRS, 1, 0.75f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_MERRY_GO_ROUND, 1, 0.75f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_PIRANHA_PLANT, 1, 0.75f); //DONE

   //// Jingles - No loop
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_KEY_COLLECT, 0, 0.75f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_PEACH_ENDING, 0, 0.70f);
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_PEACH_MESSAGE, 0, 0.70f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_RACE_FANFARE, 0, 0.80f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_SOLVE_PUZZLE, 0, 0.80f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_STAR_APPEAR, 0, 0.70f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_STAR_COLLECT, 0, 0.80f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_STAR_FANFARE, 0, 0.70f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_STAR_SELECT, 0, 0.75f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_TOAD_MESSAGE, 0, 0.80f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_KOOPA_MESSAGE, 0, 0.65f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_INTRO, 0, 0.75f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_CREDITS, 0, 0.75f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_LAKITU_MESSAGE, 0, 0.75f); //DONE
   //dynos_jingle_load_from_jingles_folder(R96_EVENT_VICTORY, 0, 0.75f); //DONE

   //// SFX
   //dynos_sound_load_sfx_mario(R96_MARIO_HOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_WAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_YAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_HAHA, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_YAHOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_GRUNT, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_LIFT, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_THROW, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_WHOA, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_PULL_UP, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_ATTACKED, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_OOOF, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_HERE_WE_GO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_YAWNING, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_SNORING_1, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_SNORING_2, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_DOH, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_GAME_OVER, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_HELLO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_PRESS_START_TO_PLAY, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_TWIRL_BOUNCE, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_SNORING_3, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_SO_LONGA_BOWSER, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_IMA_TIRED, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_WAHA, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_YIPPEE, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario(R96_MARIO_SOUND_LETS_A_GO, 0.75f, 0x80);

   //dynos_sound_load_sfx_mario_peach(R96_MARIO_FALLING, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_HOOHOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PANTING, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_DYING, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_ON_FIRE, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_GRUNT_2, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_COUGHING_1, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_ITS_A_ME_MARIO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PUNCH_YAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PUNCH_HOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_MAMA_MIA, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_OKEY_DOKEY, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_DROWNING, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_THANK_YOU_PLAYING_MY_GAME, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PEACH_DEAR_MARIO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PEACH_MARIO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PEACH_POWER_OF_THE_STARS, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PEACH_THANKS_TO_YOU, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PEACH_THANK_YOU_MARIO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PEACH_SOMETHING_SPECIAL, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PEACH_BAKE_A_CAKE, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PEACH_FOR_MARIO, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_SOUND_PEACH_MARIO2, 0.75f, 0x80);
   //dynos_sound_load_sfx_mario_peach(R96_MARIO_PANTING_COLD, 0.75f, 0x80);

   //dynos_sound_load_sfx_luigi(R96_LUIGI_HOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_WAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_YAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_HAHA, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_YAHOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_GRUNT, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_LIFT, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_THROW, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_WHOA, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_PULL_UP, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_ATTACKED, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_OOOF, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_HERE_WE_GO, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_YAWNING, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_SNORING_1, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_SNORING_2, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_DOH, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_GAME_OVER, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_HELLO, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_PRESS_START_TO_PLAY, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_TWIRL_BOUNCE, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_SNORING_3, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_SO_LONGA_BOWSER, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_IMA_TIRED, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_WAHA, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_YIPPEE, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi(R96_LUIGI_SOUND_LETS_A_GO, 0.75f, 0x80);

   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_FALLING, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_HOOHOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PANTING, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_DYING, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_ON_FIRE, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_GRUNT_2, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_COUGHING_1, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_ITS_A_ME_LUIGI, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PUNCH_YAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PUNCH_HOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_MAMA_MIA, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_OKEY_DOKEY, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_DROWNING, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_THANK_YOU_PLAYING_MY_GAME, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PEACH_DEAR_LUIGI, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PEACH_LUIGI, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PEACH_POWER_OF_THE_STARS, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PEACH_THANKS_TO_YOU, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PEACH_THANK_YOU_LUIGI, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PEACH_SOMETHING_SPECIAL, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PEACH_BAKE_A_CAKE, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PEACH_FOR_LUIGI, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_SOUND_PEACH_LUIGI2, 0.75f, 0x80);
   //dynos_sound_load_sfx_luigi_peach(R96_LUIGI_PANTING_COLD, 0.75f, 0x80);

   //dynos_sound_load_sfx_wario(R96_WARIO_HOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_WAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_YAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_HAHA, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_YAHOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_GRUNT, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_LIFT, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_THROW, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_WHOA, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_PULL_UP, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_ATTACKED, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_OOOF, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_HERE_WE_GO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_YAWNING, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_SNORING_1, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_SNORING_2, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_DOH, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_GAME_OVER, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_HELLO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_PRESS_START_TO_PLAY, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_TWIRL_BOUNCE, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_SNORING_3, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_SO_LONGA_BOWSER, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_IMA_TIRED, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_WAHA, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_YIPPEE, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario(R96_WARIO_SOUND_LETS_A_GO, 0.75f, 0x80);

   //dynos_sound_load_sfx_wario_peach(R96_WARIO_FALLING, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_HOOHOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PANTING, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_DYING, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_ON_FIRE, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_GRUNT_2, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_COUGHING_1, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_ITS_A_ME_WARIO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PUNCH_YAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PUNCH_HOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_MAMA_MIA, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_OKEY_DOKEY, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_DROWNING, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_THANK_YOU_PLAYING_MY_GAME, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PEACH_DEAR_WARIO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PEACH_WARIO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PEACH_POWER_OF_THE_STARS, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PEACH_THANKS_TO_YOU, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PEACH_THANK_YOU_WARIO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PEACH_SOMETHING_SPECIAL, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PEACH_BAKE_A_CAKE, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PEACH_FOR_WARIO, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_SOUND_PEACH_WARIO2, 0.75f, 0x80);
   //dynos_sound_load_sfx_wario_peach(R96_WARIO_PANTING_COLD, 0.75f, 0x80);

   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_HOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_WAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_YAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_HAHA, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_YAHOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_GRUNT, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_LIFT, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_THROW, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_WHOA, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_PULL_UP, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_ATTACKED, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_OOOF, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_HERE_WE_GO, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_YAWNING, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_SNORING_1, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_SNORING_2, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_DOH, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_GAME_OVER, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_HELLO, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_PRESS_START_TO_PLAY, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_TWIRL_BOUNCE, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_SNORING_3, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_SO_LONGA_BOWSER, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_IMA_TIRED, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_WAHA, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_YIPPEE, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi(R96_WALUIGI_SOUND_LETS_A_GO, 0.75f, 0x80);

   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_FALLING, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_HOOHOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PANTING, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_DYING, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_ON_FIRE, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_GRUNT_2, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_COUGHING_1, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_ITS_A_ME_WALUIGI, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PUNCH_YAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PUNCH_HOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_MAMA_MIA, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_OKEY_DOKEY, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_DROWNING, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_THANK_YOU_PLAYING_MY_GAME, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PEACH_DEAR_WALUIGI, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PEACH_WALUIGI, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PEACH_POWER_OF_THE_STARS, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PEACH_THANKS_TO_YOU, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PEACH_THANK_YOU_WALUIGI, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PEACH_SOMETHING_SPECIAL, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PEACH_BAKE_A_CAKE, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PEACH_FOR_WALUIGI, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_SOUND_PEACH_WALUIGI2, 0.75f, 0x80);
   //dynos_sound_load_sfx_waluigi_peach(R96_WALUIGI_PANTING_COLD, 0.75f, 0x80);

    //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_HOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_WAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_YAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_HAHA, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_YAHOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_GRUNT, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_LIFT, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_THROW, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_WHOA, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_PULL_UP, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_ATTACKED, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_OOOF, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_HERE_WE_GO, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_YAWNING, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_SNORING_1, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_SNORING_2, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_DOH, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_GAME_OVER, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_HELLO, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_PRESS_START_TO_PLAY, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_TWIRL_BOUNCE, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_SNORING_3, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_SO_LONGA_BOWSER, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_IMA_TIRED, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_WAHA, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_YIPPEE, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds(R96_YOSHI_DS_SOUND_LETS_A_GO, 0.75f, 0x80);

   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_FALLING, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_HOOHOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PANTING, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_DYING, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_ON_FIRE, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_GRUNT_2, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_COUGHING_1, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_ITS_A_ME_YOSHI_DS, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PUNCH_YAH, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PUNCH_HOO, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_MAMA_MIA, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_OKEY_DOKEY, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_DROWNING, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_THANK_YOU_PLAYING_MY_GAME, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PEACH_DEAR_YOSHI_DS, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PEACH_YOSHI_DS, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PEACH_POWER_OF_THE_STARS, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PEACH_THANKS_TO_YOU, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PEACH_THANK_YOU_YOSHI_DS, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PEACH_SOMETHING_SPECIAL, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PEACH_BAKE_A_CAKE, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PEACH_FOR_YOSHI_DS, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_SOUND_PEACH_YOSHI_DS2, 0.75f, 0x80);
   //dynos_sound_load_sfx_yoshi_ds_peach(R96_YOSHI_DS_PANTING_COLD, 0.75f, 0x80);
}
