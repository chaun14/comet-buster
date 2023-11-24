#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define PI 3.1415927

enum sprite_type {S_COMET, M_COMET, L_COMET, BULLET, SHIP, ET, SMILEY, EXPLOSION, TXT, LIFE_COUNTER};

typedef struct sprite {
  enum sprite_type type;
  float x; // x pos
  float y; // y pos
  float vx; // x velocity
  float vy; // y velocity
  float ax; // x acceleration
  float ay; // y acceleration
  int size; //sprite size in pixels
  int anim_sprite_num_max; // number of sprites in the animation frame
  int anim_sprite_num; // position (number) of the sprite in the animation frame (for ship and comets) 0 <= anim_sprite_num < anim_sprite_num_max
  int colorkey;
  SDL_Rect rc_screen_xy; // sprite position on the screen
  SDL_Rect rc_anim_xy; // sprite position (x,y) in the animation frame
  SDL_Surface * sprite; // sprite surface
  float friction; //kind of "air resistance" (0 to disable)
  float lifetime; //age
} s_sprite_t, *sprite_t;

// create sprite and initialize attributes
sprite_t sprite_new(enum sprite_type type, const char *fname, int colorkey, int sprite_size, int anim_sprite_num_max, int anim_pos, int screen_x, int screen_y, float init_vx, float init_vy, float friction);

// create text sprite and initialize attributes
sprite_t sprite_new_text(SDL_Surface * text_surf, int screen_x, int screen_y);

// self-explaineng functions names
void sprite_turn_left(sprite_t sprite);
void sprite_turn_right(sprite_t sprite);

// apply physics (friction, acceleration, etc.)
void sprite_play_physics(sprite_t sprite);

// move forward
void sprite_boost(sprite_t sprite, float accel);

// useful for bullets
void sprite_get_older(sprite_t sprite);

// can a sprite die ?
bool sprite_can_die(sprite_t sprite);

// Am I dead? Does my lifetime reach 0? Sick, sad world...
bool sprite_is_dead(sprite_t sprite);


// think about memory management
void sprite_free(sprite_t sprite);


#define sprite_is_comet(sprite) (sprite->type==S_COMET || sprite->type==M_COMET || sprite->type==L_COMET)
#define sprite_is_ennemy(sprite) (sprite->type==S_COMET || sprite->type==M_COMET || sprite->type==L_COMET || sprite->type==ET)


#endif // SPRITE_H
