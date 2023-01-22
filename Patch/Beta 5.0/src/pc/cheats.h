#ifndef _CHEATS_H
#define _CHEATS_H

#include <stdbool.h>
typedef unsigned int uint;

struct CheatList {
    bool EnableCheats;

    // Classic cheats
    bool MoonJump;
    bool GodMode;
    bool InfiniteLives;
    bool Responsive;
    bool MoonGravity;
    bool DebugMove;
    bool SuperCopter;
    bool AutoWallKick;
    bool NoHoldHeavy;

    // Modifiers
    uint SpeedModifier;
    uint JumpModifier;
    uint SwimModifier;
    uint SizeModifier;
    bool CapModifier;
    bool SuperWingCap;
    uint PlayAs;
    bool Jukebox;
    uint JukeboxMusic;
    bool SpeedDisplay;

    // Time-Space
    uint BLJAnywhere;
    bool SwimAnywhere;
    bool ExitAnywhere;
    bool WalkOnHazards;
    bool NoDeathBarrier;
    bool NoBounds;
    uint WaterLevel;
    bool CoinsMagnet;
    bool TimeStop;
    bool QuickEnding;
    uint HurtMario;

    // Spamba
    bool Spamba;
    uint SpambaIndex;

    // Chaos
    bool ChaosMode;
    uint Chaos[64];
};

enum {
    CHAOS_LIFE_DRAIN,
    CHAOS_CONTROLS,
    CHAOS_GRAVITY,
    CHAOS_WALL_KICKS,
    CHAOS_HOLD_MODIFIER,
    CHAOS_SPEED_MODIFIER,
    CHAOS_JUMP_MODIFIER,
    CHAOS_SWIM_MODIFIER,
    CHAOS_SIZE_MODIFIER,
    CHAOS_CAP_MODIFIER,
    CHAOS_PLAY_AS,
    CHAOS_RELEASIO,
    CHAOS_SWIM_ANYWHERE,
    CHAOS_FLOOR_IS_LAVA,
    CHAOS_DEADLY_OBJECTS,
    CHAOS_NO_BOUNDS,
    CHAOS_WATER_LEVEL,
    CHAOS_OBJECT_MAGNET,
    CHAOS_SLOW_TIME,
    CHAOS_HURT_MARIO,
    CHAOS_DISPLAY,
    CHAOS_RAINBOW,
    CHAOS_INVERTED_SCREEN,
    CHAOS_WIREFRAME,
    CHAOS_JACKPOT,
    CHAOS_GREEN_DEMON,
    CHAOS_STAR,
    CHAOS_GOOMBA_PLAGUE,
    CHAOS_BOBOMB_RAIN,
    CHAOS_CHAIRS,
    CHAOS_STALKERS,
    CHAOS_SHOOTERS,
    CHAOS_CHUCKSTERS,
    CHAOS_DODGEBALL,
    CHAOS_BOSS_FIGHT,
    CHAOS_BOWSER_TIME,
    CHAOS_HOOT,
    CHAOS_NPCS,
    CHAOS_MINECRAFT,
    CHAOS_SURPRISE,
    CHAOS_COUNT
};

#define ChaosControls           Chaos[CHAOS_CONTROLS]
#define ChaosWallKicks          Chaos[CHAOS_WALL_KICKS]
#define ChaosSpeedModifier      Chaos[CHAOS_SPEED_MODIFIER]
#define ChaosJumpModifier       Chaos[CHAOS_JUMP_MODIFIER]
#define ChaosSwimModifier       Chaos[CHAOS_SWIM_MODIFIER]
#define ChaosSizeModifier       Chaos[CHAOS_SIZE_MODIFIER]
#define ChaosPlayAs             Chaos[CHAOS_PLAY_AS]
#define ChaosSwimAnywhere       Chaos[CHAOS_SWIM_ANYWHERE]
#define ChaosNoBounds           Chaos[CHAOS_NO_BOUNDS]
#define ChaosSlowTime           Chaos[CHAOS_SLOW_TIME]
#define ChaosHurtMario          Chaos[CHAOS_HURT_MARIO]
#define ChaosRainbow            Chaos[CHAOS_RAINBOW]
#define ChaosInvertedScreen     Chaos[CHAOS_INVERTED_SCREEN]
#define ChaosWireframe          Chaos[CHAOS_WIREFRAME]
#define ChaosGreenDemon         Chaos[CHAOS_GREEN_DEMON]
#define ChaosBowserTime         Chaos[CHAOS_BOWSER_TIME]

struct CheatControls {
    uint TimeStopButton[3];
    uint SpambaControls[3]; // 0 is previous object, 1 is next object, 2 is spawn object
};

extern struct CheatList Cheats;
extern struct CheatControls CheatsControls;
extern const char **CheatJukeboxMusics[];

#endif // _CHEATS_H
