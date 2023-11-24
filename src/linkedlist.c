#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

/* Initialisation of the list
 * */
list_ptr list_new(void)
{

    list_ptr list;
    list = NULL;

    return list;
}

/* Add a new cel to a list.
 *  store the sprite_t to the new cel
 * */
list_ptr list_add(sprite_t sprite, list_ptr list)
{
    list_ptr newCel;
    newCel = malloc(sizeof(list));

    newCel->data = sprite;
    newCel->next = list;

    return newCel;

    return NULL;
}

/* Return the length of a list
 * */
int list_length(list_ptr l)
{

    int i = 0;
    while (l != NULL)
    {
        l = l->next;
        i++;
    }

    return i;
}

/* Reverse the order of a list
 * */
void list_reverse(list_ptr *l)
{
    list_ptr prev = NULL;
    list_ptr current = *l;
    list_ptr next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *l = prev;
}

/* Copy a list to another one.
 *  Return the new list
 * */
list_ptr list_clone(list_ptr list)
{
    return NULL;
}

/* Return true if the list is empty
 * */
bool list_is_empty(list_ptr l)
{
    return true;
}

/* Search the first cel of the list &
 *  return the associated sprite
 * */
sprite_t list_head_sprite(list_ptr l)
{
    return NULL;
}

/* Return the next cel in list or NULL
 * */
list_ptr list_next(list_ptr l)
{
    return NULL;
}

/* Search the last cel of a list
 *  Remove the cel from the list
 *  Return the associated sprite
 * */
sprite_t list_pop_sprite(list_ptr *l)
{
    return NULL;
}

/* Remove the given cel in a list
 * */
void list_remove(list_ptr elt, list_ptr *l)
{
}

/* Wipe out a list.
 *  Don't forget to sprite_free() for each sprite
 * */
void list_free(list_ptr l)
{
}