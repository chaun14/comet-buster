#ifndef LEVEL_H
#define LEVEL_H

/* constant */

/* could be modulated by some randomness depending on the level (?) */
#define SPACESHIP_INIT_X    304 //304
#define SPACESHIP_INIT_Y    224 //224

#define L_COMET_SPEED       0.35
#define L_COMET_SPEED_MAX   3.0
#define M_COMET_SPEED       0.5
#define M_COMET_SPEED_MAX   3.5
#define S_COMET_SPEED       0.65
#define S_COMET_SPEED_MAX   4.0

#define NYANCAT_SPEED       2.5

#define LEVEL_MIN           1
#define LEVEL_MAX           50

#define BASE_SPAWN_COMET    1 //20 //too much
#define LEVEL_SPAWN_STEP    2

/* Define a security zone for spaceship during comet spawn:
 *
 * ---------------
 * | DANGER      |
 * |    -----    |
 * |    | X |    |
 * |    -----    |
 * |             |
 * ---------------
 *
 * Security zone depends on the level: it decreases with increasing difficulty
 * FIXME:
 * should be adapted, works for now but could be incorrect in initial spaceship
 * spawn is not in the middle of the screen
 * */

/* Maximal and minimal zone around the ship */
#define SECURITY_ZONE_MIN  64  // difficult case
#define SECURITY_ZONE_MAX  200 // easy case

/* Security zone definition
 * y=ax+b (1;200)->(10;32)
 * p1(LEVEL_MIN;SECURITY_ZONE_MAX)
 * p2(LEVEL_MAX;SECURITY_ZONE_MIN)
 * a = y2-y1 / x2-x1
 * b = y1 - a*x1
 * */
#define SECURITY_ZONE_COEFFICIENT ((SECURITY_ZONE_MIN - SECURITY_ZONE_MAX)/(LEVEL_MAX - LEVEL_MIN))
#define SECURITY_ZONE_CST (SECURITY_ZONE_MAX - (SECURITY_ZONE_COEFFICIENT * LEVEL_MIN))

/* Level randomness */
//#define BASE_RANDOM_EVENT_PROBABILITY 0.01 //for level 1
#define BASE_SPAWN_POSITION_RANDOMNESS 0 //not used for the moment

/* for float comparison: fabsf(a-b) < EPSILON */
#define EPSILON 0.000001

/* level functions (and procedures...) */

float spaceship_spawn_randomness(int level);
float get_base_speed(int level, enum sprite_type type);
void security_zone(int level);
const char* get_comet_sprite(int level, enum sprite_type type);
int spawn_comet_number(int level);
void gen_level(int level, list_ptr *comet_list, SDL_Surface *scr);
bool is_in_seczone(int val, int first, int second);
sprite_t gen_nyancat_sprite(int level, SDL_Surface *scr);
const char* get_nyancat_sprite_fname(int level, float dx);
void set_nyancat_spawn_coordinates(int * u, int * v);

#endif /* LEVEL_H */
