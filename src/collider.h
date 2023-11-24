#ifndef COLLIDER_H
#define COLLIDER_H

#include <stdbool.h>
#include "sprite.h"

bool collide_test(sprite_t sprite1, sprite_t sprite2, SDL_PixelFormat* format, int * cu, int * cv);

#endif /* COLLIDER_H */
