#include <SDL.h>
#include <math.h>

#include "sprite.h"

sprite_t sprite_new(enum sprite_type type, const char *fname, int colorkey, int sprite_size, int anim_sprite_num_max, int anim_sprite_num, int screen_x, int screen_y, float init_vx, float init_vy, float friction)
{
  sprite_t sprite;
  SDL_Surface * tmp_surf;

  /* allocate sprite struct */
  sprite = (sprite_t)malloc(sizeof(s_sprite_t));

  /* set sprite type */
  sprite->type = type;

  /* load sprite */
  tmp_surf = SDL_LoadBMP(fname);
  //  printf("tmp_surf->format->BitsPerPixel: %d\n", tmp_surf->format->BitsPerPixel);
  sprite->sprite = SDL_DisplayFormat(tmp_surf);
  SDL_FreeSurface(tmp_surf);

  /* set initial sprite size and position */
  sprite->size = sprite_size;
  sprite->rc_screen_xy.x = screen_x;
  sprite->rc_screen_xy.y = screen_y;
  sprite->x = (float)screen_x;
  sprite->y = (float)screen_y;

  /* set animation frame */
  sprite->anim_sprite_num_max = anim_sprite_num_max;
  sprite->anim_sprite_num = anim_sprite_num;
  sprite->rc_anim_xy.x = anim_sprite_num * sprite_size;
  sprite->rc_anim_xy.y = 0;
  sprite->rc_anim_xy.w = sprite_size;
  sprite->rc_anim_xy.h = sprite_size;

  /* set sprite colorkey */
  sprite->colorkey = colorkey;
  SDL_SetColorKey(sprite->sprite, SDL_SRCCOLORKEY, colorkey);

  /* set inital velocity, initial acceleration (0.) and friction */

  sprite->vx = init_vx;
  sprite->vy = init_vy;
  sprite->ax = 0.;
  sprite->ay = 0.;
  sprite->friction = friction;

  /* set default lifetime to -1 (immortal) */
  sprite->lifetime = -1;

  return sprite;
}

sprite_t sprite_new_text(SDL_Surface * text_surf, int screen_x, int screen_y)
{
  /* allocate sprite struct and define type */
  sprite_t sprite = (sprite_t)malloc(sizeof(s_sprite_t));
  sprite->type = TXT;

  /* set text surface */
  sprite->sprite = text_surf;

  /* set text position */
  sprite->rc_screen_xy.x = screen_x;
  sprite->rc_screen_xy.y = screen_y;

  /* set default lifetime to -1 (immortal) */
  sprite->lifetime = -1;

  return sprite;
}

void sprite_turn_left(sprite_t sprite)
{
  sprite->anim_sprite_num = (sprite->anim_sprite_num+1)%sprite->anim_sprite_num_max;
  sprite->rc_anim_xy.x =sprite->anim_sprite_num * sprite->size;
}

void sprite_turn_right(sprite_t sprite)
{
  sprite->anim_sprite_num = (sprite->anim_sprite_num-1+sprite->anim_sprite_num_max)%sprite->anim_sprite_num_max;
  sprite->rc_anim_xy.x =sprite->anim_sprite_num * sprite->size;
}

void sprite_play_physics(sprite_t sprite)
{
  /* apply physics */
  sprite->vx += sprite->ax - sprite->friction*sprite->vx;
  sprite->vy += sprite->ay - sprite->friction*sprite->vy;

  /* move the sprite according to the new velocity */
  sprite->x += sprite->vx;
  sprite->y += sprite->vy;
  sprite->rc_screen_xy.x = (int)sprite->x;
  sprite->rc_screen_xy.y = (int)sprite->y;

  /* infinite window */
  if (sprite->rc_screen_xy.x < 0) {
    sprite->rc_screen_xy.x += SCREEN_WIDTH;
    sprite->x = (float)sprite->rc_screen_xy.x;
  } else if (sprite->rc_screen_xy.x >= SCREEN_WIDTH) {
    sprite->rc_screen_xy.x -= SCREEN_WIDTH;
    sprite->x = (float)sprite->rc_screen_xy.x;
  }
  if (sprite->rc_screen_xy.y < 0) {
    sprite->rc_screen_xy.y += SCREEN_HEIGHT;
    sprite->y = (float)sprite->rc_screen_xy.y;
  } else if (sprite->rc_screen_xy.y >= SCREEN_HEIGHT) {
    sprite->rc_screen_xy.y -= SCREEN_HEIGHT;
    sprite->y = (float)sprite->rc_screen_xy.y;
  }

  /* stop the boost */
  sprite->ax = 0.;
  sprite->ay = 0.;
}

void sprite_boost(sprite_t sprite, float accel)
{
  float dir_angle = 2.*PI*sprite->anim_sprite_num/sprite->anim_sprite_num_max;
  sprite->ax = accel*cos(dir_angle);
  sprite->ay = -accel*sin(dir_angle);
}

void sprite_get_older(sprite_t sprite) {
  if (sprite->lifetime >= 0) {
    sprite->lifetime--;
  }
}

bool sprite_is_dead(sprite_t sprite) {
  return (sprite->lifetime == 0);
}

bool sprite_can_die(sprite_t sprite) {
  if (sprite->lifetime == -1.0)
    return false;
  return true;
}

void sprite_free(sprite_t sprite) {
  SDL_FreeSurface(sprite->sprite);
  free(sprite);
}
