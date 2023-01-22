/**
 * Behavior for bhvAlphaBooKey and bhvBetaBooKey.
 * They were apparently intended to be a key that would be contained in boos
 * and would fall out, like coins do. There is a model, MODEL_BETA_BOO_KEY, that
 * is loaded in script_func_global_10, which contains boo-themed models used in
 * BBH and the castle courtyard. It is used in a macro preset with bhvAlphaBooKey,
 * which is also grouped near other boo/BBH-related macros. This is evidence that
 * bhvAlphaBooKey was supposed to be a key. bhvBetaBooKey has code similar to
 * bhvAlphaBooKey's for rotation and collection, and functions correctly when
 * spawned as a child of a boo (it checks the death status of the boo to know when
 * to drop, so this is almost definitely what was intended). It appears that
 * bhvAlphaBooKey was abandoned for reasons unknown and replaced with bhvBetaBooKey.
 */

/**
 * Update function for bhvAlphaBooKey.
 * It rotates the key, and deletes it when collected.
 * The code in this function is similar to that found in
 * bhvBetaBooKey code, which implies that these are 2 versions
 * of the same object. It is a less developed version of
 * bhvBetaBooKey, hence the "alpha" moniker.
 */
#include <sys/time.h>
#include "../../../data/r96/r96_c_includes.h"

int modifier = 0;

void validate_key(){
	if(save_file_taken_key(gCurrSaveFileNum - 1, o->oObjectID)){
        cur_obj_become_intangible();
        cur_obj_disable_rendering();
        obj_mark_for_deletion(o);
    }
}

void bhv_key_init(void) {
	o->oPosY += 80;	
	o->oObjectID = (s32) o->oBehParams;    
	validate_key();
}

void bhv_beta_boo_key_loop(void) {
	o->oFaceAngleYaw += 0x700;
    o->oPosY += sin(o->oFaceAngleYaw / (20 * 1000)) * 2;
	if (obj_check_if_collided_with_object(o, gMarioObject)) {
		// Delete the object and spawn sparkles
		obj_mark_for_deletion(o);
		spawn_object(o, MODEL_SPARKLES, bhvGoldenCoinSparkles);
        r96_play_collect_jingle(R96_EVENT_COLLECTIBLE_GRAB, 0.1, 1.0, 1500);
        //cur_obj_play_sound_2(SOUND_OBJ_BIG_PENGUIN_YELL);
		gMarioState->numKeys++;
        save_file_register_key(gCurrSaveFileNum - 1, o->oObjectID);

        if(gMarioState->numKeys >= 10){
            triggerLuigiNotification();
        }		
	}
}

void validate_wario_key(){
	if(save_file_taken_wario_key(gCurrSaveFileNum - 1, o->oObjectID)){
        cur_obj_become_intangible();
        cur_obj_disable_rendering();
        obj_mark_for_deletion(o);
    }
}

void bhv_wario_key_init(void) {
    cur_obj_scale(2.0f);
	o->oObjectID = (s32) o->oBehParams;    
	validate_wario_key();
}

void bhv_wario_key_loop(void) {
	if (obj_check_if_collided_with_object(o, gMarioObject)) {
		// Delete the object and spawn sparkles
		obj_mark_for_deletion(o);
		spawn_object(o, MODEL_SPARKLES, bhvGoldenCoinSparkles);
        r96_play_collect_jingle(R96_EVENT_COLLECTIBLE_GRAB, 0.1, 1.0, 1500);
        //cur_obj_play_sound_2(SOUND_OBJ_BIG_PENGUIN_YELL);
		gMarioState->WarioKey++;
        save_file_register_wario_key(gCurrSaveFileNum - 1, o->oObjectID);

        if(gMarioState->WarioKey >= 1){
            triggerLuigiNotification();
        }		
	}
}
