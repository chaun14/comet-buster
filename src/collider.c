/* TODO:
 * here we will find collisions management
 * */

#include <stdbool.h>
#include <SDL.h>

#include "collider.h"
#include "sprite.h"

bool collide_test(sprite_t sprite1, sprite_t sprite2, SDL_PixelFormat* format, int * cu, int * cv) 
{
  /* rough test using the bounding boxes (bb) only */
  bool test = !(sprite2->rc_screen_xy.x > sprite1->rc_screen_xy.x + sprite1->size ||
      sprite2->rc_screen_xy.x + sprite2->size < sprite1->rc_screen_xy.x ||
      sprite2->rc_screen_xy.y > sprite1->rc_screen_xy.y + sprite1->sprite->h ||
      sprite2->rc_screen_xy.y + sprite2->sprite->h < sprite1->rc_screen_xy.y);

  /* if the rough test succeeded, a fine test is performed using the colorkeys (transparency colors) of the sprites (may be optimized!) */
  if (test) {
    Uint32 *bmp1 = (Uint32*)malloc(sizeof(Uint32) * sprite1->size * sprite1->sprite->h), *sprite_it, *bmp_it;
    Uint32 *bmp2 = (Uint32*)malloc(sizeof(Uint32) * sprite2->size * sprite2->sprite->h);
    int u, v, v1 = 0; 

    /* lock the video memory and copy the sprite bitmaps into cpu memory */
    // printf("SDL_MUSTLOCK(sprite1->sprite) : %d\n", SDL_MUSTLOCK(sprite1->sprite));
    SDL_LockSurface(sprite1->sprite);
    SDL_LockSurface(sprite2->sprite);
    bmp_it = bmp1;
    sprite_it = (Uint32*)(sprite1->sprite->pixels) +  sprite1->anim_sprite_num * sprite1->size;
    for (v = 0; v < sprite1->sprite->h; v++) {
      for (u = 0; u < sprite1->size; u++) {
	*bmp_it++ = *sprite_it++;
      }
      sprite_it += (sprite1->sprite->w - sprite1->size);
    }
    bmp_it = bmp2;
    sprite_it = (Uint32*)(sprite2->sprite->pixels) +  sprite2->anim_sprite_num * sprite2->size;
    for (v = 0; v < sprite2->sprite->h; v++) {
      for (u = 0; u < sprite2->size; u++) {
	*bmp_it++ = *sprite_it++;
      }
      sprite_it += (sprite2->sprite->w - sprite2->size);
    }
    SDL_UnlockSurface(sprite1->sprite);
    SDL_UnlockSurface(sprite2->sprite);

    bmp_it = bmp1;
    test = false;

    /* for each pixel p1 in bmp1, until test = true... */
    while (!test && v1 < sprite1->sprite->h) {
      int u1 = 0;
      while (!test && u1 < sprite1->size) {
	/* get the screen coordinates of pixel p1 */
	int screen_u = u1 + sprite1->rc_screen_xy.x;
	int screen_v = v1 + sprite1->rc_screen_xy.y;

	/* if the screen coordinates of p1 are inside the bb of sprite2... */
	if (screen_u >= sprite2->rc_screen_xy.x &&
	    screen_u < sprite2->rc_screen_xy.x + sprite2->size &&
	    screen_v >= sprite2->rc_screen_xy.y &&
	    screen_v < sprite2->rc_screen_xy.y + sprite2->sprite->h) {
	  Uint32 pixel1 = *bmp_it;
	  int col1;
	  Uint8 r, g, b;

	  /* get the color col1 of p1*/
	  SDL_GetRGB(pixel1, format, &r, &g, &b);
	  col1 = SDL_MapRGB(format, r, g, b);

	  /* if col1 is a NON transparent color... */
	  if (col1 != sprite1->colorkey) {
	    Uint32 pixel2;
	    int col2;
	    Uint8 r, g, b;
	    int u2, v2;

	    /* get the local coordinates of pixel p2 in sprite2 corresponding to the screen coordinates of p1 */
	    u2 = screen_u - sprite2->rc_screen_xy.x;
	    v2 = screen_v - sprite2->rc_screen_xy.y;

	    /* get the color col2 of p2 */
	    pixel2 = *(bmp2 + u2 + v2 * sprite2->size);
	    SDL_GetRGB(pixel2, format, &r, &g, &b);
	    col2 = SDL_MapRGB(format, r, g, b);

	    /* if col2 is also a non transparent color, a collision occurs  */
	    if (col2 != sprite2->colorkey) {
	      test = true;
	      *cu = screen_u; 
	      *cv = screen_v;
	    }
	  }
	}
	u1++;
	bmp_it++;
      }
      v1++;
    }
    free(bmp1);
    free(bmp2);
  }

  return test;
}
