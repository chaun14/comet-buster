#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <SDL.h>

#include "sprite.h"

typedef struct list_node {
  sprite_t data;
  struct list_node * next;
} s_list_node_t, *list_ptr;


list_ptr list_new(void);//new_empty
list_ptr list_add(sprite_t v, list_ptr l);
list_ptr list_clone(list_ptr l);
void list_reverse(list_ptr * l);
list_ptr list_next(list_ptr l);

sprite_t list_head_sprite(list_ptr l);
sprite_t list_pop_sprite(list_ptr *l);

bool list_is_empty(list_ptr l);
int  list_length(list_ptr l);
void list_free(list_ptr l);
void list_remove(list_ptr elt, list_ptr *l);


#endif /* LINKEDLIST_H */
