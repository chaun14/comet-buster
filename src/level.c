/* TODO:
 * introduction of planets, etc.
 * */

#include <SDL.h>
#include <math.h>
#include <time.h>

#include "linkedlist.h"
// #include "config.h"
#include "level.h"
#include "sprite.h"

// just initialize with parameters for n00bs :)
int sec_zone_x_max = SPACESHIP_INIT_X + SECURITY_ZONE_MAX;
int sec_zone_x_min = SPACESHIP_INIT_X - SECURITY_ZONE_MAX;
int sec_zone_y_max = SPACESHIP_INIT_Y + SECURITY_ZONE_MAX;
int sec_zone_y_min = SPACESHIP_INIT_Y - SECURITY_ZONE_MAX;

/* Define the randomness of spawn position
 * Not used for the moment
 * */
float spaceship_spawn_randomness(int level)
{
  // FIXME
  return BASE_SPAWN_POSITION_RANDOMNESS * level;
}

/* Compute the base speed of comets
 * At the 1st level, it's OK; but at the last level it's really crazy
 * Comet base speed definition: it depends on the level (comet speed increases
 * with level -> level 10 is crazy!
 *
 * speed = speed_coef * level + speed_cst
 * p1(LEVEL_MIN;x_COMET_SPEED) p2(LEVEL_MAX;x_COMET_SPEED_MAX)
 * coef = x_COMET_SPEED_MAX - x_COMET_SPEED / LEVEL_MAX-LEVEL_MIN
 * cst = x_COMET_SPEED_MAX - coef * LEVEL_MAX
 * */
float get_base_speed(int level, enum sprite_type type)
{
  float speed_coef;
  float speed_cst;
  switch (type)
  {
  case L_COMET:
    speed_coef = (L_COMET_SPEED_MAX - L_COMET_SPEED) / (LEVEL_MAX - LEVEL_MIN);
    speed_cst = (L_COMET_SPEED_MAX - speed_coef * LEVEL_MAX);
    break;
  case M_COMET:
    speed_coef = (M_COMET_SPEED_MAX - M_COMET_SPEED) / (LEVEL_MAX - LEVEL_MIN);
    speed_cst = (M_COMET_SPEED_MAX - speed_coef * LEVEL_MAX);
    break;
  case S_COMET:
    speed_coef = (S_COMET_SPEED_MAX - S_COMET_SPEED) / (LEVEL_MAX - LEVEL_MIN);
    speed_cst = (S_COMET_SPEED_MAX - speed_coef * LEVEL_MAX);
    break;
  }
  return (float)((speed_coef * level) + speed_cst);
}

/* Define the zone where asteroids cannot spawn during level generation */
void security_zone(int level)
{
  float modifier = (SECURITY_ZONE_COEFFICIENT * level) + SECURITY_ZONE_CST;
  /* security zone X (not real max and min) */
  sec_zone_x_max = (int)(SCREEN_WIDTH + SPACESHIP_INIT_X + modifier) % SCREEN_WIDTH;
  sec_zone_x_min = (int)(SCREEN_WIDTH + SPACESHIP_INIT_X - modifier) % SCREEN_WIDTH;

  /* security zone Y (not real max and min) */
  sec_zone_y_max = (int)(SCREEN_HEIGHT + SPACESHIP_INIT_Y + modifier) % SCREEN_HEIGHT;
  sec_zone_y_min = (int)(SCREEN_HEIGHT + SPACESHIP_INIT_Y - modifier) % SCREEN_HEIGHT;
  // DEBUG
  // printf("debug: Xinit(%d,%d) => xmax=%d,xmin=%d and ymax=%d,ymin=%d\n",SPACESHIP_INIT_X,SPACESHIP_INIT_Y,sec_zone_x_max,sec_zone_x_min,sec_zone_y_max,sec_zone_y_min);
  // fflush(stdout);
}

/*
 * returns the comet sprite file name depending on the level (%10)
 * Not sure if it is the right way to do that
 * FIXME: more sprites! L M S for each type
 * FIXME: double ternary operator OR switch OR if else if else
 * */
const char *get_comet_sprite(int level, enum sprite_type type)
{
  const char *comet_sprite_fname;
  switch (level % 10)
  {
  case 1:
    // comet_sprite_fname = "sprites/asteroid-model1-32_64x64.bmp";
    comet_sprite_fname = (type == L_COMET) ? "sprites/asteroid-model1-32_64x64.bmp" : ((type == M_COMET) ? "sprites/asteroid-model1-32_32x32.bmp" : "sprites/asteroid-model1-32_16x16.bmp");

    break;
  case 2:
    // FIXME: quick and dirty sprite, only to be different from model1
    // comet_sprite_fname = "sprites/asteroid-model2-32_64x64.bmp";
    comet_sprite_fname = (type == L_COMET) ? "sprites/asteroid-model2-32_64x64.bmp" : ((type == M_COMET) ? "sprites/asteroid-model2-32_32x32.bmp" : "sprites/asteroid-model2-32_16x16.bmp");
    break;
  case 3:
    // FIXME: quick and dirty sprite, only to be different from model1
    // comet_sprite_fname = "sprites/asteroid-model3-32_64x64.bmp";
    comet_sprite_fname = (type == L_COMET) ? "sprites/asteroid-model3-32_64x64.bmp" : ((type == M_COMET) ? "sprites/asteroid-model3-32_32x32.bmp" : "sprites/asteroid-model3-32_16x16.bmp");
    break;
  case 4:
    // FIXME: quick and dirty sprite, only to be different from model1
    // comet_sprite_fname = "sprites/asteroid-model4-32_64x64.bmp";
    comet_sprite_fname = (type == L_COMET) ? "sprites/asteroid-model4-32_64x64.bmp" : ((type == M_COMET) ? "sprites/asteroid-model4-32_32x32.bmp" : "sprites/asteroid-model4-32_16x16.bmp");
    break;
  case 5:
    // FIXME: quick and dirty sprite, only to be different from model1
    // comet_sprite_fname = "sprites/asteroid-model5-32_64x64.bmp";
    comet_sprite_fname = (type == L_COMET) ? "sprites/asteroid-model5-32_64x64.bmp" : ((type == M_COMET) ? "sprites/asteroid-model5-32_32x32.bmp" : "sprites/asteroid-model5-32_16x16.bmp");
    break;
  case 6:
    // FIXME: quick and dirty sprite, only to be different from model1
    // comet_sprite_fname = "sprites/asteroid-model6-32_64x64.bmp";
    comet_sprite_fname = (type == L_COMET) ? "sprites/asteroid-model6-32_64x64.bmp" : ((type == M_COMET) ? "sprites/asteroid-model6-32_32x32.bmp" : "sprites/asteroid-model6-32_16x16.bmp");
    break;
  case 7:
    // FIXME: quick and dirty sprite, only to be different from model1
    // comet_sprite_fname = "sprites/asteroid-model7-32_64x64.bmp";
    comet_sprite_fname = (type == L_COMET) ? "sprites/asteroid-model7-32_64x64.bmp" : ((type == M_COMET) ? "sprites/asteroid-model7-32_32x32.bmp" : "sprites/asteroid-model7-32_16x16.bmp");
    break;
  case 8:
    // FIXME: quick and dirty sprite, only to be different from model1
    // comet_sprite_fname = "sprites/asteroid-model8-32_64x64.bmp";
    comet_sprite_fname = (type == L_COMET) ? "sprites/asteroid-model8-32_64x64.bmp" : ((type == M_COMET) ? "sprites/asteroid-model8-32_32x32.bmp" : "sprites/asteroid-model8-32_16x16.bmp");
    break;
  case 9:
    // FIXME: quick and dirty sprite, only to be different from model1
    // comet_sprite_fname = "sprites/asteroid-model9-32_64x64.bmp";
    comet_sprite_fname = (type == L_COMET) ? "sprites/asteroid-model9-32_64x64.bmp" : ((type == M_COMET) ? "sprites/asteroid-model9-32_32x32.bmp" : "sprites/asteroid-model9-32_16x16.bmp");
    break;
  case 0:
    // FIXME: quick and dirty sprite, only to be different from model1
    // comet_sprite_fname = "sprites/asteroid-model10-32_64x64.bmp";
    comet_sprite_fname = (type == L_COMET) ? "sprites/asteroid-model10-32_64x64.bmp" : ((type == M_COMET) ? "sprites/asteroid-model10-32_32x32.bmp" : "sprites/asteroid-model10-32_16x16.bmp");
    break;
  }
  return comet_sprite_fname;
}

/* in the future, after level 10 we increase the number of comets */
int spawn_comet_number(int level)
{
  /* 20 + level * 5
   * lvl 1 -> 10: 0,
   * lvl 11-> 20: 1,
   * lvl 21-> 30: 2,
   * etc.
   * */
  return BASE_SPAWN_COMET + (((level - 1) / 10) * LEVEL_SPAWN_STEP);
}

/* Generate sprites depending on the level:
 *   define security spawn zone (decrease with increasing level)
 *   define the comet number (increase with level, threshold every 10 levels)
 *   define the comet sprite file (10)
 *   define the large comet base speed (increase with levels)
 *
 *   define randomness coefficient (for ET and smileys)
 *
 * => parameters should be refined, it becomes crazy when level number is to
 * high; and other comet sizes are not yet handled
 * */
void gen_level(int level, list_ptr *comet_list, SDL_Surface *scr)
{

  // define security spawn zone (decrease with increasing level)
  security_zone(level);
  int colorkey = SDL_MapRGB(scr->format, 0, 255, 255);
  srand(time(NULL));
  int i;

  //  define the comet number (increase with level, threshold every 10 levels)
  int comet_number = spawn_comet_number(level);
  for (i = 0; i < comet_number; i++)
  {
    int u = rand() % SCREEN_WIDTH;
    int v = rand() % SCREEN_HEIGHT;
    // FIXME: it is not efficient at all
    if (is_in_seczone(u, sec_zone_x_min, sec_zone_x_max))
    {
      do
      {
        v = rand() % SCREEN_HEIGHT;
      } while (is_in_seczone(v, sec_zone_y_min, sec_zone_y_max));
    }
    int angle = (float)(rand() % 360) / 360 * 2 * PI;
    float speed = get_base_speed(level, L_COMET);

    // define the comet sprite file (10)
    sprite_t sprite_comet = sprite_new(L_COMET, get_comet_sprite(level, L_COMET), colorkey, 64, 32, 0, u, v, speed * cos(angle), speed * sin(angle), 0.);
    *comet_list = list_add(sprite_comet, *comet_list);
  }
  sprite_t sprite_nyancat = gen_nyancat_sprite(level, scr);
  *comet_list = list_add(sprite_nyancat, *comet_list);
}

/* Helper: return True when the value is in the security zone */
bool is_in_seczone(int val, int first, int second)
{
  bool a = val > first;
  bool b = val < second;
  if (first < second)
  {
    return (a && b);
  }
  else
  {
    return (a || b);
  }
}

/* Generate the Nyan cat (E.T.) sprite w00t! \o/
 * returns the nyan cat sprite depending on the level (%10)
 * Not sure if it is the right way to do that, but Nyan cat is funny
 * */
sprite_t gen_nyancat_sprite(int level, SDL_Surface *scr)
{
  int colorkey;
  ;
  int angle = (float)(rand() % 360) / 360 * 2 * PI;
  float dx = NYANCAT_SPEED * cos(angle);
  ///////
  int sprite_size, anim_sprite_num_max;
  int anim_pos = 0;
  bool test = dx > 0;
  const char *nyancat_sprite_fname;
  switch (level % 10)
  {
  case 1:
    colorkey = SDL_MapRGB(scr->format, 0, 0, 0);
    nyancat_sprite_fname = test ? "sprites/nyancat-original-right-6_32x50.bmp" : "sprites/nyancat-original-left-6_32x50.bmp";
    sprite_size = 50;
    anim_sprite_num_max = 6;
    break;
  case 2:
    colorkey = SDL_MapRGB(scr->format, 0, 255, 255);
    nyancat_sprite_fname = test ? "sprites/nyancat-pirate-right-12_32x83.bmp" : "sprites/nyancat-pirate-left-12_32x83.bmp";
    sprite_size = 83;
    anim_sprite_num_max = 12;
    break;
  case 3:
    colorkey = SDL_MapRGB(scr->format, 0, 255, 255);
    nyancat_sprite_fname = test ? "sprites/nyancat-mummy-right-12_32x51.bmp" : "sprites/nyancat-mummy-left-12_32x51.bmp";
    sprite_size = 51;
    anim_sprite_num_max = 12;
    break;
  case 4:
    colorkey = SDL_MapRGB(scr->format, 0, 0, 0);
    nyancat_sprite_fname = test ? "sprites/nyancat-pumpkin-right-12_32x51.bmp" : "sprites/nyancat-pumpkin-left-12_32x51.bmp";
    sprite_size = 51;
    anim_sprite_num_max = 12;
    break;
  case 5:
    colorkey = SDL_MapRGB(scr->format, 0, 255, 255);
    nyancat_sprite_fname = test ? "sprites/nyancat-nyaninja-right-12_32x70.bmp" : "sprites/nyancat-nyaninja-left-12_32x70.bmp";
    sprite_size = 70;
    anim_sprite_num_max = 12;
    break;
  case 6:
    colorkey = SDL_MapRGB(scr->format, 0, 255, 255);
    nyancat_sprite_fname = test ? "sprites/nyancat-zombie-right-12_32x51.bmp" : "sprites/nyancat-zombie-left-12_32x51.bmp";
    sprite_size = 51;
    anim_sprite_num_max = 12;
    break;
  case 7:
    colorkey = SDL_MapRGB(scr->format, 0, 255, 255);
    nyancat_sprite_fname = test ? "sprites/nyancat-jamaicnyan-right-12_32x54.bmp" : "sprites/nyancat-jamaicnyan-left-12_32x54.bmp";
    sprite_size = 54;
    anim_sprite_num_max = 12;
    break;
  case 8:
    colorkey = SDL_MapRGB(scr->format, 0, 255, 255);
    nyancat_sprite_fname = test ? "sprites/nyancat-mexinyan-right-12_32x49.bmp" : "sprites/nyancat-mexinyan-left-12_32x49.bmp";
    sprite_size = 49;
    anim_sprite_num_max = 12;
    break;
  case 9:
    colorkey = SDL_MapRGB(scr->format, 0, 255, 255);
    nyancat_sprite_fname = test ? "sprites/nyancat-gb-right-12_32x52.bmp" : "sprites/nyancat-gb-left-12_32x52.bmp";
    sprite_size = 52;
    anim_sprite_num_max = 12;
    break;
  case 0:
    colorkey = SDL_MapRGB(scr->format, 0, 255, 255);
    nyancat_sprite_fname = test ? "sprites/nyancat-technyancolor-right-12_32x51.bmp" : "sprites/nyancat-technyancolor-left-12_32x51.bmp";
    sprite_size = 51;
    anim_sprite_num_max = 12;
    break;
  }
  // FIXME (will only appear at the edges)
  int u = rand() % SCREEN_WIDTH;
  int v = rand() % SCREEN_HEIGHT;
  // printf("DEBUG: random init spawn (%d,%d)\n",u,v);
  set_nyancat_spawn_coordinates(&u, &v);
  // printf("DEBUG: nyancat spawned at (%d,%d)\n",u,v);
  // fflush(stdout);
  // FIXME: anim_sprite_num_max=64, anim_sprite_num=32
  sprite_t sprite_nyancat = sprite_new(ET, nyancat_sprite_fname, colorkey, sprite_size, anim_sprite_num_max, anim_pos, u, v, dx, NYANCAT_SPEED * sin(angle), 0.);
  return sprite_nyancat;
}

/* Adjust spawn coordinates for nyancat: it can only spwan from an edge of the
 * screen. Therefore we compute random values of the spawn point, and project
 * it to the edges depending on the quadran where it is */

// A I(W/2, H/2) - 0,0 => (0-H/2)/(0-W/2) = H/W
// B I           - W,0 => (0-H/2)/(W-W/2) = -H/W
// C I           - 0,H => (H-H/2)/(0-W/2) = -H/W
// D I           - W,H => (H-H/2)/(W-W/2) = H/W

void set_nyancat_spawn_coordinates(int *u, int *v)
{
  float x, y;
  int xi = SCREEN_WIDTH / 2;
  int yi = SCREEN_HEIGHT / 2;
  int dx = *u - xi;  // TODO: check if == 0 => *u=xi
  int dy = *v - yi;  // TODO: check if == 0 => *v=yi
  float a = dy / dx; // TODO: to check
  //(IS) : y = ax+b
  //       a = v-yi / u-xi
  //       b = y-ax => b = v-au
  float b = (*v) - (a * (*u));
  // unsafe (division by 0)
  float bissec_coef = SCREEN_HEIGHT / SCREEN_WIDTH;
  // on simplifiera plus tard, d'abord on met les formules avec tous les cas
  if (*u < xi)
  { // A & C
    if (*v < yi)
    { // A
      if (fabsf(bissec_coef - a) < EPSILON)
      { // cannot write equality with float
        x = 0;
        y = 0;
      }
      else if (bissec_coef < a)
      {
        x = (0 - b) / a; //(IS) inter (y=0)
        y = 0;
      }
      else
      {
        x = 0;
        y = (a * 0) + b; //(IS) inter (x=0)
      }
    }
    else
    { // C
      if (fabsf(bissec_coef - a) < EPSILON)
      { // idem
        x = 0;
        y = SCREEN_HEIGHT;
      }
      else if (bissec_coef < a)
      {
        x = 0;
        y = (a * 0) + b; //(IS) inter (x=0)
      }
      else
      {
        x = (SCREEN_HEIGHT - b) / a; //(IS) inter (y=H)
        y = SCREEN_HEIGHT;
      }
    }
  }
  else
  { // B & D
    bissec_coef = (-1) * bissec_coef;
    // TODO
    //  *u == xi => x=xi
    //  *v == yi => y=yi
    if (*v < yi)
    { // B
      if (fabsf(bissec_coef - a) < EPSILON)
      { // idem
        x = SCREEN_WIDTH;
        y = 0;
      }
      else if (bissec_coef < a)
      {
        x = SCREEN_WIDTH;
        y = (a * SCREEN_WIDTH) + b; //(IS) inter (x=W)
      }
      else
      {
        x = (0 - b) / a; //(IS) inter (y=0)
        y = 0;
      }
    }
    else
    { // D
      if (fabsf(bissec_coef - a) < EPSILON)
      { // idem
        x = SCREEN_WIDTH;
        y = SCREEN_HEIGHT;
      }
      else if (bissec_coef < a)
      {
        x = (SCREEN_HEIGHT - b) / a; //(IS) inter (y=H)
        y = SCREEN_HEIGHT;
      }
      else
      {
        x = SCREEN_WIDTH;
        y = (a * SCREEN_WIDTH) + b; //(IS) inter (x=W)
      }
    }
  }
  *u = (int)x;
  *v = (int)y;
}

/* TODO: implement nyancat cproba
 *
 * chance do make a nyancat appear increases with destroyed comets and level
 * (0.01 + destroyed_comets_coef)*level OR (0.01 + destroyed_comets)*(level-level_min)
 * [20] (0 destroyed)  => coef = 0
 * [1]  (19 destroyed) => coef = 0.01
 * =>
 * lvl1 : [20] (0.01+0.0005)*1  = 0.0105 OR (0.01+0.0005)*0  = 0
 *        [1]  (0.01+0.01)*1    = 0.02   OR (0.01+0.01)*0    = 0
 * lvl10: [20] (0.01+0.0005)*10 = 0.105  OR (0.01+0.0005)*9  = 0.0945
 *        [1]  (0.01+0.01)*10   = 0.2    OR (0.01+0.01)*9    = 0.18
 * lvl50: [20] (0.01+0.0005)*50 = 0.525  OR (0.01+0.0005)*49 = 0.5145
 *        [1]  (0.01+0.01)*50   = 1      OR (0.01+0.01)*49   = 0.98
 * */
