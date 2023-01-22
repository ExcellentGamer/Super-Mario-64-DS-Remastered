#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "txtconv.h"

struct Character charmap[512] = {
    {"0", {0x0, 0}}, {"{65296}", {0x0, 0}}, {"1", {0x1, 0}}, {"{65297}", {0x1, 0}}, {"2", {0x2, 0}}, {"{65298}", {0x2, 0}}, {"3", {0x3, 0}}, {"{65299}", {0x3, 0}}, {"4", {0x4, 0}}, 
    {"{65300}", {0x4, 0}}, {"5", {0x5, 0}}, {"{65301}", {0x5, 0}}, {"6", {0x6, 0}}, {"{65302}", {0x6, 0}}, {"7", {0x7, 0}}, {"{65303}", {0x7, 0}}, {"8", {0x8, 0}}, {"{65304}", {0x8, 0}}, 
    {"9", {0x9, 0}}, {"{65305}", {0x9, 0}}, {"A", {0xa, 0}}, {"{65313}", {0xa, 0}}, {"B", {0xb, 0}}, {"{65314}", {0xb, 0}}, {"C", {0xc, 0}}, {"{65315}", {0xc, 0}}, {"D", {0xd, 0}}, 
    {"{65316}", {0xd, 0}}, {"E", {0xe, 0}}, {"{65317}", {0xe, 0}}, {"F", {0xf, 0}}, {"{65318}", {0xf, 0}}, {"G", {0x10, 0}}, {"{65319}", {0x10, 0}}, {"H", {0x11, 0}}, {"{65320}", {0x11, 0}}, 
    {"I", {0x12, 0}}, {"{65321}", {0x12, 0}}, {"J", {0x13, 0}}, {"{65322}", {0x13, 0}}, {"K", {0x14, 0}}, {"{65323}", {0x14, 0}}, {"L", {0x15, 0}}, {"{65324}", {0x15, 0}}, {"M", {0x16, 0}}, 
    {"{65325}", {0x16, 0}}, {"N", {0x17, 0}}, {"{65326}", {0x17, 0}}, {"O", {0x18, 0}}, {"{65327}", {0x18, 0}}, {"P", {0x19, 0}}, {"{65328}", {0x19, 0}}, {"Q", {0x1a, 0}}, {"{65329}", {0x1a, 0}}, 
    {"R", {0x1b, 0}}, {"{65330}", {0x1b, 0}}, {"S", {0x1c, 0}}, {"{65331}", {0x1c, 0}}, {"T", {0x1d, 0}}, {"{65332}", {0x1d, 0}}, {"U", {0x1e, 0}}, {"{65333}", {0x1e, 0}}, {"V", {0x1f, 0}}, 
    {"{65334}", {0x1f, 0}}, {"W", {0x20, 0}}, {"{65335}", {0x20, 0}}, {"X", {0x21, 0}}, {"{65336}", {0x21, 0}}, {"Y", {0x22, 0}}, {"{65337}", {0x22, 0}}, {"Z", {0x23, 0}}, {"{65338}", {0x23, 0}}, 
    {"a", {0x24, 0}}, {"{65345}", {0x24, 0}}, {"b", {0x25, 0}}, {"{65346}", {0x25, 0}}, {"c", {0x26, 0}}, {"{65347}", {0x26, 0}}, {"d", {0x27, 0}}, {"{65348}", {0x27, 0}}, {"e", {0x28, 0}}, 
    {"{65349}", {0x28, 0}}, {"f", {0x29, 0}}, {"{65350}", {0x29, 0}}, {"g", {0x2a, 0}}, {"{65351}", {0x2a, 0}}, {"h", {0x2b, 0}}, {"{65352}", {0x2b, 0}}, {"i", {0x2c, 0}}, {"{65353}", {0x2c, 0}}, 
    {"j", {0x2d, 0}}, {"{65354}", {0x2d, 0}}, {"k", {0x2e, 0}}, {"{65355}", {0x2e, 0}}, {"l", {0x2f, 0}}, {"{65356}", {0x2f, 0}}, {"m", {0x30, 0}}, {"{65357}", {0x30, 0}}, {"n", {0x31, 0}}, 
    {"{65358}", {0x31, 0}}, {"o", {0x32, 0}}, {"{65359}", {0x32, 0}}, {"p", {0x33, 0}}, {"{65360}", {0x33, 0}}, {"q", {0x34, 0}}, {"{65361}", {0x34, 0}}, {"r", {0x35, 0}}, {"{65362}", {0x35, 0}}, 
    {"s", {0x36, 0}}, {"{65363}", {0x36, 0}}, {"t", {0x37, 0}}, {"{65364}", {0x37, 0}}, {"u", {0x38, 0}}, {"{65365}", {0x38, 0}}, {"v", {0x39, 0}}, {"{65366}", {0x39, 0}}, {"w", {0x3a, 0}}, 
    {"{65367}", {0x3a, 0}}, {"x", {0x3b, 0}}, {"{65368}", {0x3b, 0}}, {"y", {0x3c, 0}}, {"{65369}", {0x3c, 0}}, {"z", {0x3d, 0}}, {"{65370}", {0x3d, 0}}, {"'", {0x3e, 0}}, {"{65287}", {0x3e, 0}}, 
    {".", {0x3f, 0}}, {"{65294}", {0x3f, 0}}, {",", {0x6f, 0}}, {"{65292}", {0x6f, 0}}, {"-", {0x9f, 0}}, {"{65293}", {0x9f, 0}}, {"(", {0xe1, 0}}, {"{65288}", {0xe1, 0}}, {")(", {0xe2, 0}}, 
    {"）（", {0xe2, 0}}, {")", {0xe3, 0}}, {"{65289}", {0xe3, 0}}, {"+", {0xe4, 0}}, {"{65291}", {0xe4, 0}}, {"&", {0xe5, 0}}, {"{65286}", {0xe5, 0}}, {":", {0xe6, 0}}, {"{65306}", {0xe6, 0}}, 
    {"!", {0xf2, 0}}, {"{65281}", {0xf2, 0}}, {"%", {0xf3, 0}}, {"{65285}", {0xf3, 0}}, {"?", {0xf4, 0}}, {"{65311}", {0xf4, 0}}, {"~", {0xf7, 0}}, {"{65374}", {0xf7, 0}}, {" ", {0x9e, 0}}, 
    {"{12288}", {0x9e, 0}}, {"\n", {0xfe, 0}}, {"{12443}", {0xf0, 0}}, {"{12444}", {0xf1, 0}}, {"{12302}", {0xf5, 0}}, {"{12303}", {0xf6, 0}}, {"{08230}", {0xf8, 0}}, {"{08596}", {0xe4, 0}}, {"$", {0xf9, 0}}, 
    {"{09733}", {0xfa, 0}}, {"{00215}", {0xfb, 0}}, {"{12539}", {0xfc, 0}}, {"{09734}", {0xfd, 0}}, {"^", {0x50, 0}}, {"|", {0x51, 0}}, {"<", {0x52, 0}}, {">", {0x53, 0}}, {"[%]", {0xe0, 0}}, 
    {"[A]", {0x54, 0}}, {"[B]", {0x55, 0}}, {"[C]", {0x56, 0}}, {"[Z]", {0x57, 0}}, {"[R]", {0x58, 0}}, {"/", {0xd0, 0}}, {"the", {0xd1, 0}}, {"you", {0xd2, 0}}, {"{09786}", {0x40, 0x41}}, 


    // SPECIAL CHARACTERS
    {"{00161}",  {66, 0}},    // INVERTED EXCLAMATION MARK
    {"{00191}",  {67, 0}},    // INVERTED QUESTION MARK
    {"{00192}",  {68, 0}},    // LATIN CAPITAL LETTER A WITH GRAVE
    {"{00193}",  {69, 0}},    // LATIN CAPITAL LETTER A WITH ACUTE
    {"{00194}",  {70, 0}},    // LATIN CAPITAL LETTER A WITH CIRCUMFLEX
    {"{00195}",  {71, 0}},    // LATIN CAPITAL LETTER A WITH TILDE
    {"{00196}",  {72, 0}},    // LATIN CAPITAL LETTER A WITH DIAERESIS
    {"{00197}",  {73, 0}},    // LATIN CAPITAL LETTER A WITH RING ABOVE
    {"{00198}",  {74, 0}},    // LATIN CAPITAL LETTER AE
    {"{00199}",  {75, 0}},    // LATIN CAPITAL LETTER C WITH CEDILLA
    {"{00200}",  {76, 0}},    // LATIN CAPITAL LETTER E WITH GRAVE
    {"{00201}",  {77, 0}},    // LATIN CAPITAL LETTER E WITH ACUTE
    {"{00202}",  {78, 0}},    // LATIN CAPITAL LETTER E WITH CIRCUMFLEX
    {"{00203}",  {79, 0}},    // LATIN CAPITAL LETTER E WITH DIAERESIS
    ////////////
    {"{00204}",  {89, 0}},    // LATIN CAPITAL LETTER I WITH GRAVE
    {"{00205}",  {90, 0}},    // LATIN CAPITAL LETTER I WITH ACUTE
    {"{00206}",  {91, 0}},    // LATIN CAPITAL LETTER I WITH CIRCUMFLEX
    {"{00207}",  {92, 0}},    // LATIN CAPITAL LETTER I WITH DIAERESIS
    {"{00208}",  {93, 0}},    // LATIN CAPITAL LETTER ETH
    {"{00209}",  {94, 0}},    // LATIN CAPITAL LETTER N WITH TILDE
    {"{00210}",  {95, 0}},    // LATIN CAPITAL LETTER O WITH GRAVE
    {"{00211}",  {96, 0}},    // LATIN CAPITAL LETTER O WITH ACUTE
    {"{00212}",  {97, 0}},    // LATIN CAPITAL LETTER O WITH CIRCUMFLEX
    {"{00213}",  {98, 0}},    // LATIN CAPITAL LETTER O WITH TILDE
    {"{00214}",  {99, 0}},    // LATIN CAPITAL LETTER O WITH DIAERESIS
    ///////////
    {"{00216}", {100, 0}},    // LATIN CAPITAL LETTER O WITH STROKE]
    {"{00217}", {101, 0}},    // LATIN CAPITAL LETTER U WITH GRAVE
    {"{00218}", {102, 0}},    // LATIN CAPITAL LETTER U WITH ACUTE
    {"{00219}", {103, 0}},    // LATIN CAPITAL LETTER U WITH CIRCUMFLEX
    {"{00220}", {104, 0}},    // LATIN CAPITAL LETTER U WITH DIAERESIS
    {"{00221}", {105, 0}},    // LATIN CAPITAL LETTER Y WITH ACUTE
    {"{00222}", {106, 0}},    // LATIN CAPITAL LETTER THORN
    {"{00223}", {107, 0}},    // LATIN SMALL LETTER SHARP S = Eszett
    {"{00224}", {108, 0}},    // LATIN SMALL LETTER A WITH GRAVE
    {"{00225}", {109, 0}},    // LATIN SMALL LETTER A WITH ACUTE
    {"{00226}", {110, 0}},    // LATIN SMALL LETTER A WITH CIRCUMFLEX
    /////////////
    {"{00227}", {112, 0}},    // LATIN SMALL LETTER A WITH TILDE
    {"{00228}", {113, 0}},    // LATIN SMALL LETTER A WITH DIAERESIS
    {"{00229}", {114, 0}},    // LATIN SMALL LETTER A WITH RING ABOVE
    {"{00230}", {115, 0}},    // LATIN SMALL LETTER AE
    {"{00231}", {116, 0}},    // LATIN SMALL LETTER C WITH CEDILLA
    {"{00232}", {117, 0}},    // LATIN SMALL LETTER E WITH GRAVE
    {"{00233}", {118, 0}},    // LATIN SMALL LETTER E WITH ACUTE
    {"{00234}", {119, 0}},    // LATIN SMALL LETTER E WITH CIRCUMFLEX
    {"{00235}", {120, 0}},    // LATIN SMALL LETTER E WITH DIAERESIS
    {"{00236}", {121, 0}},    // LATIN SMALL LETTER I WITH GRAVE
    {"{00237}", {122, 0}},    // LATIN SMALL LETTER I WITH ACUTE
    {"{00238}", {123, 0}},    // LATIN SMALL LETTER I WITH CIRCUMFLEX
    {"{00239}", {124, 0}},    // LATIN SMALL LETTER I WITH DIAERESIS
    {"{00240}", {125, 0}},    // LATIN SMALL LETTER ETH
    {"{00241}", {126, 0}},    // LATIN SMALL LETTER N WITH TILDE
    {"{00242}", {127, 0}},    // LATIN SMALL LETTER O WITH GRAVE
    {"{00243}", {128, 0}},    // LATIN SMALL LETTER O WITH ACUTE
    {"{00244}", {129, 0}},    // LATIN SMALL LETTER O WITH CIRCUMFLEX
    {"{00245}", {130, 0}},    // LATIN SMALL LETTER O WITH TILDE
    {"{00246}", {131, 0}},    // LATIN SMALL LETTER O WITH DIAERESIS
    ///////////
    {"{00248}", {132, 0}},    // LATIN SMALL LETTER O WITH STROKE
    {"{00249}", {133, 0}},    // LATIN SMALL LETTER U WITH GRAVE
    {"{00250}", {134, 0}},    // LATIN SMALL LETTER U WITH ACUTE
    {"{00251}", {135, 0}},    // LATIN SMALL LETTER U WITH CIRCUMFLEX
    {"{00252}", {136, 0}},    // LATIN SMALL LETTER U WITH DIAERESIS
    {"{00253}", {137, 0}},    // LATIN SMALL LETTER Y WITH ACUTE
    {"{00254}", {138, 0}},    // LATIN SMALL LETTER THORN
    {"{00255}", {139, 0}},    // LATIN SMALL LETTER Y WITH DIAERESIS
    ///////////
    {"{00260}", {140, 0}},    // LATIN CAPITAL LETTER A WITH OGONEK
    {"{00261}", {141, 0}},    // LATIN SMALL LETTER A WITH OGONEK
    {"{00262}", {142, 0}},    // LATIN CAPITAL LETTER C WITH ACUTE
    {"{00263}", {143, 0}},    // LATIN SMALL LETTER C WITH ACUTE
    ///////////
    {"{00280}", {144, 0}},    // LATIN CAPITAL LETTER E WITH OGONEK
    {"{00281}", {145, 0}},    // LATIN SMALL LETTER E WITH OGONEK
    ///////////
    {"{00286}", {146, 0}},    // LATIN CAPITAL LETTER G WITH BREVE
    {"{00287}", {147, 0}},    // LATIN SMALL LETTER G WITH BREVE
    ///////////
    {"{00304}", {148, 0}},    // LATIN CAPITAL LETTER S WITH CEDILLA
    {"{00305}", {149, 0}},    // LATIN SMALL LETTER S WITH CEDILLA
    ///////////
    {"{00321}", {150, 0}},    // LATIN CAPITAL LETTER L WITH STROKE
    {"{00322}", {151, 0}},    // LATIN SMALL LETTER L WITH STROKE
    {"{00323}", {152, 0}},    // LATIN CAPITAL LETTER N WITH ACUTE
    {"{00324}", {153, 0}},    // LATIN SMALL LETTER N WITH ACUTE
    ///////////
    {"{00338}", {154, 0}},    // LATIN CAPITAL LIGATURE OE
    {"{00339}", {155, 0}},    // LATIN SMALL LIGATURE OE
    ///////////
    {"{00346}", {156, 0}},    // LATIN CAPITAL LETTER S WITH ACUTE
    {"{00347}", {157, 0}},    // LATIN SMALL LETTER S WITH ACUTE
    /////////////////////////
    {"{00350}", {160, 0}},    // LATIN CAPITAL LETTER I WITH DOT ABOVE
    {"{00351}", {161, 0}},    // LATIN SMALL LETTER DOTLESS I
    ///////////
    {"{00376}", {162, 0}},    // LATIN CAPITAL LETTER Y WITH DIAERESIS
    {"{00377}", {163, 0}},    // LATIN CAPITAL LETTER Z WITH ACUTE
    {"{00378}", {164, 0}},    // LATIN SMALL LETTER Z WITH ACUTE
    {"{00379}", {165, 0}},    // LATIN CAPITAL LETTER Z WITH DOT ABOVE
    /////////////
    {"{00380}", {166, 0}},    // LATIN SMALL LETTER Z WITH DOT ABOVE
    ///////////
    {"{07838}", {167, 0}},    // LATIN EXTENDED ADDITIONAL = small eszett
    ///////////
    {"{00928}", {168, 0}},    // Greek Capital Letter Pi
    {"{00929}", {169, 0}},    // Greek Capital Letter Rho
    {"{00931}", {170, 0}},    // Greek Capital Letter Sigma
    {"{00932}", {171, 0}},    // Greek Capital Letter Tau
    {"{00933}", {172, 0}},    // Greek Capital Letter Upsilon
    {"{00934}", {173, 0}},    // Greek Capital Letter Phi
    {"{00935}", {174, 0}},    // Greek Capital Letter Chi
    {"{00936}", {175, 0}},    // Greek Capital Letter Psi
    {"{00937}", {176, 0}},    // Greek Capital Letter Omega
    {"{00938}", {177, 0}},    // Imagine the rest are documented
    {"{00939}", {178, 0}},    // 
    {"{00940}", {179, 0}},    // 
    {"{00941}", {180, 0}},    // 
    {"{00942}", {181, 0}},    // 
    {"{00943}", {182, 0}},    // 
    {"{00944}", {183, 0}},    // 
    {"{00945}", {184, 0}},    // 
    {"{00946}", {185, 0}},    // 
    {"{00947}", {186, 0}},    // 
    {"{00948}", {187, 0}},    // 
    {"{00949}", {188, 0}},    // 
    {"{00950}", {189, 0}},    // 
    {"{00951}", {190, 0}},    // 
    {"{00952}", {191, 0}},    // 
    {"{00953}", {192, 0}},    // 
    {"{00954}", {193, 0}},    // 
    {"{00955}", {194, 0}},    // 
    {"{00956}", {195, 0}},    // 
    {"{00957}", {196, 0}},    // 
    {"{00958}", {197, 0}},    // 
    {"{00959}", {198, 0}},    // 
    {"{00960}", {199, 0}},    // 
    {"{00961}", {200, 0}},    // 
    {"{00962}", {201, 0}},    // 
    {"{00963}", {202, 0}},    // 
    {"{00964}", {203, 0}},    // 
    {"{00965}", {204, 0}},    // 
    {"{00966}", {205, 0}},    // 
    {"{00967}", {206, 0}},    // 
    {"{00968}", {207, 0}},    // 
    ///////////
    {"{00969}", {211, 0}},    // 
    {"{00970}", {212, 0}},    // 
    {"{00971}", {213, 0}},    // 
    {"{00972}", {214, 0}},    // 
    {"{00973}", {215, 0}},    // 
    {"{00974}", {216, 0}},    // 
    {"{00922}", {217, 0}},    // 
    {"{00923}", {218, 0}},    // 
    {"{00924}", {219, 0}},    // 
    {"{00925}", {220, 0}},    // 
    {"{00926}", {221, 0}},    // 
    {"{00927}", {222, 0}},    // 
    {"{00913}", {223, 0}},    // 
    ///////////
    {"{00914}", {231, 0}},    // 
    {"{00915}", {232, 0}},    // 
    {"{00916}", {233, 0}},    // 
    {"{00917}", {234, 0}},    // 
    {"{00918}", {235, 0}},    // 
    {"{00919}", {236, 0}},    // 
    {"{00920}", {237, 0}},    //
    {"{00921}", {238, 0}},    //  
    ///////////
    {"{00906}", {255, 0}},    // 
    {"{00908}", {256, 0}},    // 
    {"{00910}", {257, 0}},    // 
    {"{00911}", {258, 0}},    // 
    {"{00902}", {259, 0}},    // 
    {"{00904}", {260, 0}},    // 
    {"{00905}", {261, 0}},    // 
    {"{00912}", {262, 0}},    // 
    ////////////////////////
};

struct Character getCharacter(char *ch){
    struct Character tmp = {NULL, {0, 0}};
    for(s32 cmid = 0; cmid < (s32) (sizeof(charmap) / sizeof(struct Character)); cmid++){
        if(charmap[cmid].txt != NULL){
            if(strncmp(charmap[cmid].txt, ch, strlen(charmap[cmid].txt)) == 0) {
                tmp = charmap[cmid];
                break;
            }
        }
    }
    return tmp;
}

u8 *getTranslatedText(char  *txt){

    txt = (txt == NULL ? "" : txt);

    s32 cid = 0;
    s32 shiftArr = 0;
    s32 strSize = strlen(txt);

    u8 *tmp = malloc((strSize + 1) * sizeof(u8));

    char tmpIcon[3];
    char tmpSpecialChar[7];

    memset(tmpIcon, 0, sizeof(tmpIcon));
    memset(tmpSpecialChar, 0, sizeof(tmpSpecialChar));

    for(cid = 0; cid < strSize; cid++){
    char ch = txt[cid];
    
        if(ch == '['){
            tmpIcon[0] = ch;
            tmpIcon[1] = txt[cid + 1];
            tmpIcon[2] = txt[cid + 2];
            struct Character ctm = getCharacter(tmpIcon);
            if(ctm.txt != NULL){
                shiftArr += 2;
                cid += 2;
                for(int cl = 0; cl < 2; cl++){
                    if(ctm.value[cl] != 0){
                        tmp[cid - shiftArr + cl] = ctm.value[cl];
                        shiftArr-=cl;
                    }
                }
                memset(tmpIcon, 0, sizeof(tmpIcon));
            }
        } else if(ch == ')'){

            struct Character ctm;

            // case: ')' at end of string
            if (cid == (strSize - 1)) {
                ctm = getCharacter(")");
                if(ctm.txt != NULL){
                    tmp[cid - shiftArr] = ctm.value[0];
                }
                break; // avoids out of bounds read/write
            }

            char tmpIcon[2];
            tmpIcon[0] = ch;
            tmpIcon[1] = txt[cid + 1];

            // case: ')(' contained in string
            if (tmpIcon[1] == '(') {
                ctm = getCharacter(")(");
                shiftArr += 1;
                cid += 1;
                for(int cl = 0; cl < 2; cl++){
                    if(ctm.value[cl] != 0){
                        tmp[cid - shiftArr + cl] = ctm.value[cl];
                        shiftArr-=cl;
                    }
                }
            // case: ')' contained in string
            } else {
                ctm = getCharacter(")");
                if(ctm.txt != NULL){
                    tmp[cid - shiftArr] = ctm.value[0];
                }
            }
            memset(tmpIcon, 0, sizeof(tmpIcon));

        } else if(ch == '{'){
            tmpSpecialChar[0] = ch;
            tmpSpecialChar[1] = txt[cid + 1];
            tmpSpecialChar[2] = txt[cid + 2];
            tmpSpecialChar[3] = txt[cid + 3];
            tmpSpecialChar[4] = txt[cid + 4];
            tmpSpecialChar[5] = txt[cid + 5];
            tmpSpecialChar[6] = txt[cid + 6];

            struct Character ctm = getCharacter(tmpSpecialChar);

            if(ctm.txt != NULL){
                shiftArr += 5;
                cid += 5;
                for(int cl = 0; cl < 2; cl++){
                    if(ctm.value[cl] != 0){
                        tmp[cid - shiftArr + cl] = ctm.value[cl];
                        shiftArr-=cl;
                    }
                }
            } else {
                printf("Loading File: missing special character found: %s\n", tmpSpecialChar);
            }
            memset(tmpSpecialChar, 0, sizeof(tmpSpecialChar));
        } else {
            char findTxt[1] = {ch};

            struct Character ctm = getCharacter(findTxt);
            if(ctm.txt != NULL){
                tmp[cid - shiftArr] = ctm.value[0];
            }else{
                tmp[cid - shiftArr] = 0x9E;
            }
        }
    }

    tmp = realloc(tmp, (strSize - shiftArr + 1) * sizeof(u8));
    tmp[strSize - shiftArr] = 0xFF;

    return tmp;
}