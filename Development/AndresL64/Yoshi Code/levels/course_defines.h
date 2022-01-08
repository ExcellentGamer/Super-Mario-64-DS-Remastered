/* Define lists for list of course for macros. Each of the following fields are described:
 * Argument 1: Course macro for define.
 * Argument 2: Star collection dance cutscenes
 * Each hex digit determines what dance cutscene to play for the stars in the course. The last digit is
 * unused. See determine_dance_cutscene() in camera.c for details.
 * Cutscene Digits:
 *      0: Lakitu flies away after the dance
 *      1: The camera rotates around mario
 *      2: The camera goes to a closeup of mario
 *      3: Bowser keys and the grand star
 *      4: Default, used for 100 coin stars, 8 red coin stars in bowser levels, and secret stars
 */
DEFINE_COURSE(COURSE_NONE, 0x44444444) // (0)  Course Hub (Castle Grounds)
DEFINE_COURSE(COURSE_BOB, 0x00022244) // (1)  Bob Omb Battlefield
DEFINE_COURSE(COURSE_WF, 0x00002044) // (2)  Whomp's Fortress
DEFINE_COURSE(COURSE_JRB, 0x22222244) // (3)  Jolly Rodger's Bay
DEFINE_COURSE(COURSE_CCM, 0x00220044) // (4)  Cool Cool Mountain
DEFINE_COURSE(COURSE_BBH, 0x22222244) // (5)  Big Boo's Haunt
DEFINE_COURSE(COURSE_HMC, 0x22222244) // (6)  Hazy Maze Cave
DEFINE_COURSE(COURSE_LLL, 0x21212144) // (7)  Lethal Lava Land
DEFINE_COURSE(COURSE_SSL, 0x20222244) // (8)  Shifting Sand Land
DEFINE_COURSE(COURSE_DDD, 0x22222244) // (9)  Dire Dire Docks
DEFINE_COURSE(COURSE_SL, 0x02020244) // (10) Snowman's Land
DEFINE_COURSE(COURSE_WDW, 0x22102244) // (11) Wet Dry World
DEFINE_COURSE(COURSE_TTM, 0x00000044) // (12) Tall Tall Mountain
DEFINE_COURSE(COURSE_THI, 0x11112144) // (13) Tiny Huge Island
DEFINE_COURSE(COURSE_TTC, 0x22222244) // (14) Tick Tock Clock
DEFINE_COURSE(COURSE_RR, 0x00000044) // (15) Rainbow Ride
DEFINE_COURSES_END()
DEFINE_BONUS_COURSE(COURSE_BITDW, 0x34444444) // (16) Bowser in the Dark World
DEFINE_BONUS_COURSE(COURSE_BITFS, 0x34444444) // (17) Bowser in the Fire Sea
DEFINE_BONUS_COURSE(COURSE_BITS, 0x34444444) // (18) Bowser in the Sky
DEFINE_BONUS_COURSE(COURSE_PSS, 0x24444444) // (19) Princess's Secret Slide
DEFINE_BONUS_COURSE(COURSE_COTMC, 0x44444444) // (20) Cavern of the Metal Cap
DEFINE_BONUS_COURSE(COURSE_TOTWC, 0x04444444) // (21) Tower of the Wing Cap
DEFINE_BONUS_COURSE(COURSE_VCUTM, 0x24444444) // (22) Vanish Cap Under the Moat
DEFINE_BONUS_COURSE(COURSE_WMOTR, 0x04444444) // (23) Winged Mario over the Rainbow
DEFINE_BONUS_COURSE(COURSE_SA, 0x24444444) // (24) Secret Aquarium
DEFINE_BONUS_COURSE(COURSE_CAKE_END, 0x44444444) // (25) The End (Cake Scene)
DEFINE_COURSE(COURSE_FOURTH_FLOOR, 0x44444444) // (26) Character Swap Room