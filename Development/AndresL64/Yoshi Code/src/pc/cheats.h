#ifndef _CHEATS_H
#define _CHEATS_H

#include <stdbool.h>

struct CheatList {
    bool         EnableCheats;
    bool         MoonJump;
    bool         GodMode;
    bool         InfiniteLives;
    bool         SuperSpeed;
    bool         Responsive;
    bool         ExitAnywhere;
    bool         HugeMario;
    bool         TinyMario;
    unsigned int Coin;
    bool         Hover;
    bool         Moon;
    unsigned int Run;
    bool         NDB;
    bool         Jump;
    bool         SPD;
    bool         TPF;
    unsigned int JB;
    bool         JBC;
    bool         QuikEnd;
    unsigned int Hurt;
    bool         Cann;
    bool         AutoWK;
    bool         GetShell;
    bool         GetBob;
    unsigned int Spamba;
    bool         Swim;
    bool         WingCap;
    bool         MetalCap;
    bool         VanishCap;
    bool         RemoveCap;
    bool         NormalCap;
    unsigned int BLJAnywhere;
    unsigned int PAC;
    bool         Triple;
    bool         Fly;
    bool         NoBounds;
    bool         FLJ;
    bool         TimeStop;
};

extern struct CheatList Cheats;

#endif // _CHEATS_H
