#include "dynos.cpp.h"
#include <SDL2/SDL.h>
extern "C" {
#include "game/area.h"
#include "r96/r96_miniaudio.h"
#include "r96/system/r96_system.h"
}

//#define AUDIO_FORMAT		AUDIO_S16SYS

#define MA_NO_DEVICE_IO
#define MA_DEBUG_OUTPUT
#define SDL_MAIN_HANDLED
#define AUDIO_BUFFER_SIZE       0x200
#define AUDIO_FORMAT            AUDIO_F32SYS
#define AUDIO_SAMPLES_SFX       32000
#define AUDIO_SAMPLES_MUSIC     44100
#define AUDIO_CHANNELS          2

int R96_SoundCount[LEVEL_MAX+1] = { 0, 0, 0, 0, 3, 3, 4, 3, 
                                   4, 2, 3, 3, 5, 4, 2, 
                                   2, 2, 2, 2, 2, 2, 2, 
                                   3, 4, 2, 0, 2, 2, 2, 
                                   2, 2, 2, 0, 2, 2, 0, 
                                   5, 0, 0, 2 };


void MusicCallBack(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
void SoundCallBack(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

static bool TokenizeBuffer(char *aBuffer, char **aTokens, s32 aTokenMax) {
    bool dq = false;
    for (char *p = NULL; *aBuffer != 0 && aTokenMax > 0; ++aBuffer) {
        u8 c = (u8) *aBuffer;
        if ((c <= 0x20 && !dq) || (c == '\"' && dq)) {
            if (p) {
                *(aTokens++) = p;
                aTokenMax--;
                p = NULL;
            }
            *aBuffer = 0;
            dq = false;
        } else if (c == '\"' && !dq) {
            dq = true;
        } else if (!p) {
            p = aBuffer;
        }
    }
    return (aTokenMax == 0);
}

//
// Audio
//

static ma_engine            AudioEngine[2];
static ma_delay_node        g_delayNode;   /* The echo effect is achieved using a delay node. */
static ma_reverb_node       g_reverbNode[LEVEL_MAX+1][5];        /* The reverb node. */
static ma_device_ex         device[2];
static ma_context_ex        context[2];

#define DELAY_IN_SECONDS    0.2f
#define DECAY               0.25f   /* Volume falloff for each echo. */

void DynOS_Audio_Init() {
    ma_result               result;
    ma_delay_node_config    delayNodeConfig;
    ma_reverb_node_config   reverbNodeConfig[LEVEL_MAX+1][5];
    ma_engine_config        engineConfig[2];
    ma_context_config       contextConfig[2];
    ma_device_config        deviceConfig[2];

    ma_backend backends[] = {
        ma_backend_custom
    };

    // Init SDL2 Audio
    if (!SDL_WasInit(SDL_INIT_AUDIO)) {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
            sys_fatal("DynOS_Sound_GetDevice: Could not init SDL Audio.");
        }
    }

/* Sound Engine and Device */
{
    engineConfig[0] = ma_engine_config_init();
    engineConfig[0].noDevice           = TRUE;
    engineConfig[0].periodSizeInFrames = 256;
    engineConfig[0].channels           = AUDIO_CHANNELS;
    engineConfig[0].sampleRate         = AUDIO_SAMPLES_SFX;

    result = ma_engine_init(&engineConfig[0], &AudioEngine[0]);
    if (result != MA_SUCCESS) {
        sys_fatal("Failed to initialize sound engine.");
    }

    contextConfig[0] = ma_context_config_init();
    contextConfig[0].custom.onContextInit = ma_context_init__custom_loader;

    result = ma_context_init(backends, sizeof(backends)/sizeof(backends[0]), &contextConfig[0], (ma_context*)&context[0]);
    if (result != MA_SUCCESS) {
        sys_fatal("Could not init Context.");
    }

    deviceConfig[0] = ma_device_config_init(ma_device_type_playback);
    deviceConfig[0].playback.format   = ma_format_f32;
    deviceConfig[0].playback.channels = ma_engine_get_channels(&AudioEngine[0]);
    deviceConfig[0].capture.format    = ma_format_f32;
    deviceConfig[0].capture.channels  = ma_engine_get_channels(&AudioEngine[0]);
    deviceConfig[0].sampleRate        = ma_engine_get_sample_rate(&AudioEngine[0]);
    deviceConfig[0].dataCallback      = SoundCallBack;
    deviceConfig[0].pUserData         = NULL;

    result = ma_device_init((ma_context*)&context[0], &deviceConfig[0], (ma_device*)&device[0]);
    if (result != MA_SUCCESS) {
        ma_context_uninit((ma_context*)&context[0]);
        sys_fatal("Failed to initialize device for sound.");
    }

    if (ma_device_start((ma_device*)&device[0]) != MA_SUCCESS) {
        ma_device_uninit((ma_device*)&device[0]);
        ma_context_uninit((ma_context*)&context[0]);
        sys_fatal("Failed to start device for sound.");
    }
}
/* End of Sound Engine and Device */

/* Music Engine and Device */
{
    engineConfig[1] = ma_engine_config_init();
    engineConfig[1].noDevice           = TRUE;
    engineConfig[1].periodSizeInFrames = 256;
    engineConfig[1].channels           = AUDIO_CHANNELS;
    engineConfig[1].sampleRate         = AUDIO_SAMPLES_MUSIC;

    result = ma_engine_init(&engineConfig[1], &AudioEngine[1]);
    if (result != MA_SUCCESS) {
        sys_fatal("Failed to initialize music engine.");
    }

    contextConfig[1] = ma_context_config_init();
    contextConfig[1].custom.onContextInit = ma_context_init__custom_loader;

    result = ma_context_init(backends, sizeof(backends)/sizeof(backends[0]), &contextConfig[1], (ma_context*)&context[1]);
    if (result != MA_SUCCESS) {
        sys_fatal("Could not init Context.");
    }

    deviceConfig[1] = ma_device_config_init(ma_device_type_playback);
    deviceConfig[1].playback.format   = ma_format_f32;
    deviceConfig[1].playback.channels = ma_engine_get_channels(&AudioEngine[1]);
    deviceConfig[1].capture.format    = ma_format_f32;
    deviceConfig[1].capture.channels  = ma_engine_get_channels(&AudioEngine[1]);
    deviceConfig[1].sampleRate        = ma_engine_get_sample_rate(&AudioEngine[1]);
    deviceConfig[1].dataCallback      = MusicCallBack;
    deviceConfig[1].pUserData         = NULL;

    result = ma_device_init((ma_context*)&context[1], &deviceConfig[1], (ma_device*)&device[1]);
    if (result != MA_SUCCESS) {
        ma_context_uninit((ma_context*)&context[1]);
        sys_fatal("Failed to initialize device for music.");
    }

    if (ma_device_start((ma_device*)&device[1]) != MA_SUCCESS) {
        ma_device_uninit((ma_device*)&device[1]);
        ma_context_uninit((ma_context*)&context[1]);
        sys_fatal("Failed to start device for music.");
    }
}
/* End of Music Engine and Device */

    R96_Effect_Init();

    for (int i = 1; i < LEVEL_MAX+1; i++) {
        for (int j = 1; j < R96_SoundCount[i]; j++) {
            reverbNodeConfig[i][j] = ma_reverb_node_config_init(AUDIO_CHANNELS, AUDIO_SAMPLES_SFX, R96_EffectData[i][j].roomSize, R96_EffectData[i][j].damping, R96_EffectData[i][j].width, R96_EffectData[i][j].wetVolume, R96_EffectData[i][j].dryVolume, R96_EffectData[i][j].mode);
            result = ma_reverb_node_init(ma_engine_get_node_graph(&AudioEngine[0]), &reverbNodeConfig[i][j], NULL, &g_reverbNode[i][j]);
            if (result != MA_SUCCESS) {
                sys_fatal("Failed to initialize reverb node.");
            }
            /* Connect the output of the delay node to the input of the endpoint. */
            ma_node_attach_output_bus(&g_reverbNode[i][j], 0, ma_engine_get_endpoint(&AudioEngine[0]), 0);
        }
        if (R96_SoundCount[i] == 0) {
            reverbNodeConfig[i][0] = ma_reverb_node_config_init(AUDIO_CHANNELS, AUDIO_SAMPLES_SFX, R96_EffectData[i][0].roomSize, R96_EffectData[i][0].damping, R96_EffectData[i][0].width, R96_EffectData[i][0].wetVolume, R96_EffectData[i][0].dryVolume, R96_EffectData[i][0].mode);
            result = ma_reverb_node_init(ma_engine_get_node_graph(&AudioEngine[0]), &reverbNodeConfig[i][0], NULL, &g_reverbNode[i][0]);
            if (result != MA_SUCCESS) {
                sys_fatal("Failed to initialize reverb node.");
            }
            /* Connect the output of the delay node to the input of the endpoint. */
            ma_node_attach_output_bus(&g_reverbNode[i][0], 0, ma_engine_get_endpoint(&AudioEngine[0]), 0);
        }
    }


    //delayNodeConfig = ma_delay_node_config_init(MUSIC_CHANNELS, AUDIO_FREQUENCY_32000, (ma_uint32)(AUDIO_FREQUENCY_32000 * DELAY_IN_SECONDS), DECAY);

    /*result = ma_delay_node_init(ma_engine_get_node_graph(&g_engine), &delayNodeConfig, NULL, &g_delayNode);
    if (result != MA_SUCCESS) {
        sys_fatal("Failed to initialize delay node.");
    }
    */
    /* Connect the output of the delay node to the input of the endpoint. */
    //ma_node_attach_output_bus(&g_delayNode, 0, ma_engine_get_endpoint(&g_engine), 0);

}

struct SoundData {
    String mName;
    f32 mVolume;
    u8 mPriority;
    u8 mBank;
    SysPath mFileName;
    ma_sound mAudio;
};

STATIC_STORAGE(Array<SoundData *>, LoadedSounds);
#define sLoadedSounds __LoadedSounds()

STATIC_STORAGE(SoundData *, PlayingSound);
#define sPlayingSound __PlayingSound()


struct MusicData {
    String mName;
    s32 mLoop;
    f32 mVolume;
    SysPath mFileName;
    ma_sound mAudio;
};

STATIC_STORAGE(Array<MusicData *>, LoadedMusics);
#define sLoadedMusics __LoadedMusics()

STATIC_STORAGE(MusicData *, PlayingMusic);
#define sPlayingMusic __PlayingMusic()

STATIC_STORAGE(MusicData *, PreviousMusic);
#define sPreviousMusic __PreviousMusic()

ma_uint64 mCurrentMultiTrack = 0;
bool MultiTrackBool = 0;
bool EndMusic = 0;

struct JingleData {
    String mName;
    u8 *mData;
    s32 mLength;
    s32 mLoop;
    s32 mCurrent;
    f32 mVolume;
    SysPath mFileName;
    ma_sound mAudio;
};

STATIC_STORAGE(Array<JingleData *>, LoadedJingles);
#define sLoadedJingles __LoadedJingles()

STATIC_STORAGE(JingleData *, PlayingJingle);
#define sPlayingJingle __PlayingJingle()

bool EndJingle = 0;

//
// Music
//

void MusicCallBack(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    MA_ASSERT(pDevice->playback.channels == ma_engine_get_channels(&AudioEngine[1]));

    if (pDevice->type == ma_device_type_playback)  {
        ma_engine_read_pcm_frames(&AudioEngine[1], pOutput, frameCount, NULL);
    }

    if (pDevice->type == ma_device_type_duplex) {
        ma_copy_pcm_frames(pOutput, pInput, frameCount, pDevice->playback.format, pDevice->playback.channels);
    }

    if (sPlayingJingle != NULL) {
        f32 _Volume = sPlayingJingle->mVolume * (configMasterVolume / 127.f) * (configMusicVolume / 127.f) * softenJingleVolume * !configMusicMute;
        ma_sound_set_volume(&sPlayingJingle->mAudio, _Volume);
        float _CurrentFadeVolume = ma_sound_get_current_fade_volume(&sPlayingJingle->mAudio);
        if ((_CurrentFadeVolume < 0.09) && EndJingle) {
            ma_sound_stop(&sPlayingJingle->mAudio);
            ma_sound_set_fade_in_milliseconds(&sPlayingJingle->mAudio, 0.1, 0.1, 1);
            EndJingle = 0;
        }
    }
    if (sPlayingMusic != NULL) {
        f32 _Volume = sPlayingMusic->mVolume * (configMasterVolume / 127.f) * (configMusicVolume / 127.f) * softenVolume * !configMusicMute;
        ma_sound_set_volume(&sPlayingMusic->mAudio, _Volume);
        float _CurrentFadeVolume = ma_sound_get_current_fade_volume(&sPlayingMusic->mAudio);
        if ((_CurrentFadeVolume < 0.09) && EndMusic) {
            ma_sound_stop(&sPlayingMusic->mAudio);
            ma_sound_set_fade_in_milliseconds(&sPlayingMusic->mAudio, 0.1, 0.1, 1);
            EndMusic = 0;
        }
        if (sPreviousMusic != NULL && MultiTrackBool) {
            ma_sound_stop(&sPreviousMusic->mAudio);
            sPreviousMusic = sPlayingMusic;
            MultiTrackBool = 0;
        }
    }
}

bool DynOS_Music_Load(const String &aName, const SysPath &aFilename, s32 aLoop, f32 aVolume) {
    if (sLoadedMusics.FindIf([&aName](const MusicData *aMusicData) { return aMusicData->mName == aName; }) != -1) {
        return false;
    }

    MusicData *_MusicData = New<MusicData>();
    _MusicData->mName     = aName;
    _MusicData->mLoop     = aLoop;
    _MusicData->mVolume   = aVolume;
    _MusicData->mFileName = aFilename;
    sLoadedMusics.Add(_MusicData);
    return true;
}

// The file format is a simple txt file
// Each line is something like this:
// [name] [filename] [volume] [loop]
// - name is the internal id used by the music
// - filename (.wav can be omitted)
// - volume ranges from 0 to 127
// - loop can be any positive integer, any negative value acts as no loop
bool DynOS_Music_LoadPresets(const SysPath &aFilename, const SysPath &aFolder) {
    FILE *_File = fopen(aFilename.c_str(), "r");
    if (_File) {
        char _Buffer[1024];
        while (fgets(_Buffer, 1024, _File)) {
            char *_Tokens[4];
            if (TokenizeBuffer(_Buffer, _Tokens, 4)) {
                SysPath _Filename = aFolder + "/" + _Tokens[1];
                if(!access((_Filename + ".wav").c_str(), F_OK )) {
                    _Filename += ".wav";
                }
                else if(!access((_Filename + ".flac").c_str(), F_OK )) {
                    _Filename += ".flac";
                }
                // Does not loop!
                //else if(!access((_Filename + ".mp3").c_str(), F_OK )) {
                //    _Filename += ".mp3";
                //}
                //else if(!access((_Filename + ".ogg").c_str(), F_OK )) {
                //    _Filename += ".ogg";
                //}
                DynOS_Music_Load(_Tokens[0], _Filename, String(_Tokens[3]).ParseInt(), String(_Tokens[2]).ParseInt() / 127.f);
            }
        }
        fclose(_File);
        return true;
    }
    return false;
}

void DynOS_Music_Play(const String& aName, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime) {
    s32 _MusicDataIndex = sLoadedMusics.FindIf([&aName](const MusicData *aMusicData) { return aMusicData->mName == aName; });
    if (_MusicDataIndex == -1) {
        return;
    }

    // Music data
    MusicData *_MusicData = sLoadedMusics[_MusicDataIndex];
    if (!_MusicData) {
        return;
    }

    ma_result result;
    ma_uint64 _TotalLength;
    if (!_MusicData->mAudio.ownsDataSource) {
        result = ma_sound_init_from_file(&AudioEngine[1], _MusicData->mFileName.c_str(), 0, NULL, NULL, &_MusicData->mAudio);
        if (result != MA_SUCCESS) {
            sys_fatal("Failed to initialize music.");
        }
        result = ma_sound_get_length_in_pcm_frames(&_MusicData->mAudio, &_TotalLength);
        if (result != MA_SUCCESS) {
            sys_fatal("Could not get total length.");
        }
        result = ma_sound_set_loop_point_in_pcm_frames(&_MusicData->mAudio, _MusicData->mLoop, _TotalLength);
        if (result != MA_SUCCESS) {
            sys_fatal("Failed to set loop point.");
        }
        ma_sound_set_looping(&_MusicData->mAudio, TRUE);
    }
    sPlayingMusic = _MusicData;
    ma_sound_set_fade_in_milliseconds(&sPlayingMusic->mAudio, aVolumeBegin, aVolumeEnd, aDelaytime);
    ma_sound_start(&sPlayingMusic->mAudio);
}

void DynOS_Music_Multi_Play(const String& aName, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime) {
    s32 _MusicDataIndex = sLoadedMusics.FindIf([&aName](const MusicData *aMusicData) { return aMusicData->mName == aName; });
    if (_MusicDataIndex == -1) {
        return;
    }

    // Music data
    MusicData *_MusicData = sLoadedMusics[_MusicDataIndex];
    if (!_MusicData) {
        return;
    }

    ma_result result;
    ma_uint64 _TotalLength;
    if (!_MusicData->mAudio.ownsDataSource) {
        result = ma_sound_init_from_file(&AudioEngine[1], _MusicData->mFileName.c_str(), MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, NULL, NULL, &_MusicData->mAudio);
        if (result != MA_SUCCESS) {
           sys_fatal("Failed to initialize music.");
        }
        result = ma_sound_get_length_in_pcm_frames(&_MusicData->mAudio, &_TotalLength);
        if (result != MA_SUCCESS) {
            sys_fatal("Could not get total length.");
        }
        result = ma_sound_set_loop_point_in_pcm_frames(&_MusicData->mAudio, _MusicData->mLoop, _TotalLength);
        if (result != MA_SUCCESS) {
            sys_fatal("Failed to set loop point.");
        }
        if (_MusicData->mLoop != 0) {
            ma_sound_set_looping(&_MusicData->mAudio, TRUE);
        }
    }
    if (!ma_sound_is_playing(&_MusicData->mAudio) && sPlayingMusic != NULL)
    {
        sPreviousMusic = sPlayingMusic;
        MultiTrackBool = 1;
        ma_result result;
        result = ma_sound_get_cursor_in_pcm_frames(&sPlayingMusic->mAudio, &mCurrentMultiTrack);
        if (result != MA_SUCCESS) {
            sys_fatal("Could not get cursor.");
        }
    }
    sPlayingMusic = _MusicData;
    ma_sound_seek_to_pcm_frame(&sPlayingMusic->mAudio, mCurrentMultiTrack);
    ma_sound_set_fade_in_milliseconds(&sPlayingMusic->mAudio, aVolumeBegin, aVolumeEnd, aDelaytime);
    ma_sound_start(&sPlayingMusic->mAudio);
}

void DynOS_Music_Stop() {
    mCurrentMultiTrack = 0;
    MultiTrackBool = 0;
    if (sPlayingMusic != NULL) {
        ma_sound_seek_to_pcm_frame(&sPlayingMusic->mAudio, 0);
        ma_sound_stop(&sPlayingMusic->mAudio);
    }
    if (sPreviousMusic != NULL) {
        ma_sound_seek_to_pcm_frame(&sPreviousMusic->mAudio, 0);
        ma_sound_stop(&sPreviousMusic->mAudio);
    }
    sPreviousMusic = NULL;
    sPlayingMusic = NULL;
}

void DynOS_Music_Pause() {
    if (sPlayingMusic != NULL) {
        ma_sound_stop(&sPlayingMusic->mAudio);
    }
}

void DynOS_Music_Resume() {
    if (sPlayingMusic != NULL) {
        ma_sound_start(&sPlayingMusic->mAudio);
    }
}

void DynOS_Music_Fade(bool aEnd, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime) {
    if (sPlayingMusic != NULL) {
        ma_sound_set_fade_in_milliseconds(&sPlayingMusic->mAudio, aVolumeBegin, aVolumeEnd, aDelaytime);
        EndMusic = aEnd;
    }
}

bool DynOS_Music_IsPlaying(const String& aName) {
    if (sPlayingMusic != NULL && sPlayingMusic->mName == aName) {
        return ma_sound_is_playing(&sPlayingMusic->mAudio);
    }
    return 0;
}

//
// Sound
//

void SoundCallBack(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    MA_ASSERT(pDevice->playback.channels == ma_engine_get_channels(&AudioEngine[0]));

    if (pDevice->type == ma_device_type_playback)  {
        ma_engine_read_pcm_frames(&AudioEngine[0], pOutput, frameCount, NULL);
    }

    if (pDevice->type == ma_device_type_duplex) {
        ma_copy_pcm_frames(pOutput, pInput, frameCount, pDevice->playback.format, pDevice->playback.channels);
    }

    if (sPlayingSound != NULL) {
        f32 _Volume = sPlayingSound->mVolume * (configMasterVolume / 127.f) * (configSfxVolume / 127.f) * !configSfxMute;
        ma_sound_set_volume(&sPlayingSound->mAudio, _Volume);
    }
}

bool DynOS_Sound_Load(const String& aName, u8 aBank, const SysPath& aFilename, f32 aVolume, u8 aPriority) {
   if (sLoadedSounds.FindIf([&aName](const SoundData *aSoundData) { return aSoundData->mName == aName; }) != -1) {
       return false;
   }

   SoundData *_SoundData = New<SoundData>();
   _SoundData->mName     = aName;
   _SoundData->mVolume   = aVolume;
   _SoundData->mPriority = aPriority;
   _SoundData->mBank     = aBank;
   _SoundData->mFileName = aFilename;
   sLoadedSounds.Add(_SoundData);
   return true;
}

// The file format is a simple txt file
// Each line is something like this:
// [name] [filename] [volume] [bank] [priority]
// - name is the internal id used by the music
// - filename (.wav can be omitted)
// - volume ranges from 0 to 127
// - bank ranges from 0 to 255
// - priority ranges from 0 to 255
bool DynOS_Sound_LoadPresets(const SysPath &aFilename, const SysPath &aFolder) {
   FILE *_File = fopen(aFilename.c_str(), "r");
   if (_File) {
       char _Buffer[1024];
       while (fgets(_Buffer, 1024, _File)) {
           char *_Tokens[5];
           if (TokenizeBuffer(_Buffer, _Tokens, 5)) {
               SysPath _Filename = aFolder + "/" + _Tokens[1];
                if(!access((_Filename + ".wav").c_str(), F_OK )) {
                    _Filename += ".wav";
                }
                else if(!access((_Filename + ".flac").c_str(), F_OK )) {
                    _Filename += ".flac";
                }
                else if(!access((_Filename + ".mp3").c_str(), F_OK )) {
                    _Filename += ".mp3";
                }
                else if(!access((_Filename + ".ogg").c_str(), F_OK )) {
                    _Filename += ".ogg";
                }
               DynOS_Sound_Load(_Tokens[0], String(_Tokens[3]).ParseInt(), _Filename, String(_Tokens[2]).ParseInt() / 127.f, String(_Tokens[4]).ParseInt());
           }
       }
       fclose(_File);
       return true;
   }
   return false;
}

void DynOS_Sound_Play(const String& aName, f32 *aPos) {

    s32 _SoundDataIndex = sLoadedSounds.FindIf([&aName](const SoundData *aSoundData) { return aSoundData->mName == aName; });
    if (_SoundDataIndex == -1) {
        return;
    }

    // Sound data
    SoundData *_SoundData = sLoadedSounds[_SoundDataIndex];
    if (!_SoundData) {
        return;
    }
    ma_result result;
    if (!_SoundData->mAudio.ownsDataSource) {
        /* Now load our sound. */ 
        result = ma_sound_init_from_file(&AudioEngine[0], _SoundData->mFileName.c_str(), MA_SOUND_FLAG_NO_DEFAULT_ATTACHMENT | MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, NULL, NULL, &_SoundData->mAudio);
        if (result != MA_SUCCESS) {
            sys_fatal("Failed to initialize sound.");
        }
        //ma_sound_set_pitch(&_SoundData->mAudio, 5.0f);
        /* Connect the output of the sound to the input of the effect. */
        //ma_node_attach_output_bus(&_SoundData->mAudio, 0, &g_delayNode, 0);
        //ma_sound_set_directional_attenuation_factor(&_SoundData->mAudio, 0);

        /* Connect the output of the delay node to the input of the endpoint. */

    }
    /* We can now wire up the sound to the binaural node and start it. */
    ma_node_attach_output_bus(&_SoundData->mAudio, 0, &g_reverbNode[gCurrLevelNum][gCurrIndex], 0);
    /*
    The sound will not be started by default, so start it now. We won't hear anything until the SDL
    audio device has been opened and started.
    */

    // Don't overwrite playing sounds with higher priority
    // Sounds with equal priority cancel out each other
    if (sPlayingSound != NULL && (sPlayingSound->mPriority == _SoundData->mPriority || ma_sound_is_playing(&_SoundData->mAudio))) {
        ma_sound_stop(&sPlayingSound->mAudio);
        ma_sound_seek_to_pcm_frame(&sPlayingSound->mAudio, 0);
    }
    sPlayingSound = _SoundData;
    ma_sound_start(&sPlayingSound->mAudio);
    //ma_sound_set_position(&_SoundData->mAudio, 1, 1, 1);
    //direction = ma_sound_get_direction_to_listener(&_SoundData->mAudio);

    /* Update the direction of the sound. */
    //ma_steamaudio_binaural_node_set_direction(&g_binauralNode, 1, 1, 0);
    //f32 aVolume = _SoundData->mVolume * (configMasterVolume / 127.f) * (configSfxVolume / 127.f) * !configSfxMute;
    //f32 aDistance = (aPos == NULL ? 0 : vec3f_length(aPos));
    //DynOS_Audio_Mix(_SoundData->mData[1], _SoundData->mData[0], _SoundData->mLength, aVolume, aDistance);
}

void DynOS_Sound_Stop(u8 aBank) {
    if (sPlayingSound != NULL) {
        ma_sound_seek_to_pcm_frame(&sPlayingSound->mAudio, 0);
        ma_sound_stop(&sPlayingSound->mAudio);
    }
    sPlayingSound = NULL;
}

bool DynOS_Sound_IsPlaying(const String& aName) {
    if (sPlayingSound != NULL && sPlayingSound->mName == aName) {
        return ma_sound_is_playing(&sPlayingSound->mAudio);
    }
    return 0;
}

bool DynOS_Sound_IsPlaying(u8 aBank) {
    //return SDL_GetQueuedAudioSize(DynOS_Sound_GetDevice(aBank)) != 0;
    return 0;
}

//
// Jingle
//

bool DynOS_Jingle_Load(const String &aName, const SysPath &aFilename, s32 aLoop, f32 aVolume) {
    if (sLoadedJingles.FindIf([&aName](const JingleData *aJingleData) { return aJingleData->mName == aName; }) != -1) {
        return false;
    }

    JingleData *_JingleData = New<JingleData>();
    _JingleData->mName     = aName;
    _JingleData->mLoop     = aLoop;
    _JingleData->mVolume   = aVolume;
    _JingleData->mFileName = aFilename;
    sLoadedJingles.Add(_JingleData);
    return true;
}

// The file format is a simple txt file
// Each line is something like this:
// [name] [filename] [volume] [loop]
// - name is the internal id used by the Jingle
// - filename (.wav can be omitted)
// - volume ranges from 0 to 127
// - loop can be any positive integer, any negative value acts as no loop
bool DynOS_Jingle_LoadPresets(const SysPath &aFilename, const SysPath &aFolder) {
    FILE *_File = fopen(aFilename.c_str(), "r");
    if (_File) {
        char _Buffer[1024];
        while (fgets(_Buffer, 1024, _File)) {
            char *_Tokens[4];
            if (TokenizeBuffer(_Buffer, _Tokens, 4)) {
                SysPath _Filename = aFolder + "/" + _Tokens[1];
                if(!access((_Filename + ".wav").c_str(), F_OK )) {
                    _Filename += ".wav";
                }
                else if(!access((_Filename + ".flac").c_str(), F_OK )) {
                    _Filename += ".flac";
                }
                // Does not loop!
                //else if(!access((_Filename + ".mp3").c_str(), F_OK )) {
                //    _Filename += ".mp3";
                //}
                //else if(!access((_Filename + ".ogg").c_str(), F_OK )) {
                //    _Filename += ".ogg";
                //}
                DynOS_Jingle_Load(_Tokens[0], _Filename, String(_Tokens[3]).ParseInt(), String(_Tokens[2]).ParseInt() / 127.f);
            }
        }
        fclose(_File);
        return true;
    }
    return false;
}


void DynOS_Jingle_Play(const String& aName, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime)  {
    s32 _JingleDataIndex = sLoadedJingles.FindIf([&aName](const JingleData *aJingleData) { return aJingleData->mName == aName; });
    if (_JingleDataIndex == -1) {
        return;
    }

    // Jingle data
    JingleData *_JingleData = sLoadedJingles[_JingleDataIndex];
    if (!_JingleData) {
        return;
    }

    ma_result result;
    ma_uint64 _TotalLength;
    if (!_JingleData->mAudio.ownsDataSource) {
        result = ma_sound_init_from_file(&AudioEngine[1], _JingleData->mFileName.c_str(), 0, NULL, NULL, &_JingleData->mAudio);
        if (result != MA_SUCCESS) {
            sys_fatal("Failed to initialize Jingle.");
        }
        result = ma_sound_get_length_in_pcm_frames(&_JingleData->mAudio, &_TotalLength);
        if (result != MA_SUCCESS) {
            sys_fatal("Could not get total length.");
        }
        result = ma_sound_set_loop_point_in_pcm_frames(&_JingleData->mAudio, _JingleData->mLoop, _TotalLength);
        if (result != MA_SUCCESS) {
            sys_fatal("Failed to set loop point.");
        }
        if (_JingleData->mLoop != 0) {
            ma_sound_set_looping(&_JingleData->mAudio, TRUE);
        }
    }
    sPlayingJingle = _JingleData;
    ma_sound_set_fade_in_milliseconds(&sPlayingJingle->mAudio, aVolumeBegin, aVolumeEnd, aDelaytime);
    ma_sound_start(&sPlayingJingle->mAudio);
}

void DynOS_Jingle_Stop() {
    if (sPlayingJingle != NULL) {
        ma_sound_seek_to_pcm_frame(&sPlayingJingle->mAudio, 0);
        ma_sound_stop(&sPlayingJingle->mAudio);
    }
    sPlayingJingle = NULL;
}

void DynOS_Jingle_Pause() {
    if (sPlayingJingle != NULL) {
        ma_sound_stop(&sPlayingJingle->mAudio);
    }
}

void DynOS_Jingle_Resume() {
    if (sPlayingJingle != NULL) {
        ma_sound_start(&sPlayingJingle->mAudio);
    }
}

void DynOS_Jingle_Fade(bool aEnd, float aVolumeBegin, float aVolumeEnd, s32 aDelaytime) {
    if (sPlayingJingle != NULL) {
        ma_sound_set_fade_in_milliseconds(&sPlayingJingle->mAudio, aVolumeBegin, aVolumeEnd, aDelaytime);
        EndJingle = aEnd;
    }
}

bool DynOS_Jingle_IsPlaying(const String& aName) {
    if (sPlayingJingle != NULL && sPlayingJingle->mName == aName) {
        return ma_sound_is_playing(&sPlayingJingle->mAudio);
    }
    return 0;
}
