#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

/* Initialisation of the list
 * */
list_ptr list_new(void)
{
    // printf("list_new\n");
    // create a new empty list
    list_ptr list = NULL;

    // return the new list
    return list;
}

/* Add a new cel to a list.
 *  store the sprite_t to the new cel
 * */
list_ptr list_add(sprite_t sprite, list_ptr list)
{
    // printf("list_add\n");

    list_ptr newListCel; // init the cel
    // allocate memory for the new cel
    newListCel = malloc(sizeof(struct list_node));

    // fill the cel
    newListCel->data = sprite;

    // add the cel to the list
    newListCel->next = list;

    // return the new list
    return newListCel;
}

/* Return the length of a list
 * */
int list_length(list_ptr l)
{
    // printf("list_length\n");
    int listLengh = 0;

    // go thought the list while there is a cel
    while (l)
    {
        listLengh++;
        l = l->next;
    }

    return listLengh;
}

/* Reverse the order of a list
 * */
void list_reverse(list_ptr *l)
{
    //    printf("list_reverse\n");

    int i = list_length(*l);
    list_ptr newList;
    newList = *l;

    // go thought the list while there is a cel but this time in reverse, and fill a new list
    while (i != 0)
    {
        *l = (newList + i);
        i--;
        *l = (*l)->next;
    }
}

/* Copy a list to another one.
 *  Return the new list
 * */
list_ptr list_clone(list_ptr list)
{
    // printf("list_clone\n");

    // I'll use recursion to copy the list
    if (list == NULL)
    {
        return NULL;
    }
    else
    {
        list_ptr newList = list_new();
        newList->data = list->data;
        newList->next = list_clone(list->next);
        return newList;
    }
}

/* Return true if the list is empty
 * */
bool list_is_empty(list_ptr list)
{
    // printf("list_is_empty %i\n", list ? 0 : 1);
    if (list)
        return false;
    else
        return true;
}

/* Search the first cel of the list &
 *  return the associated sprite
 * */
sprite_t list_head_sprite(list_ptr l)
{
    // printf("list_head_sprite\n");
    return l->data;
}

/* Return the next cel in list or NULL
 * */
list_ptr list_next(list_ptr l)
{
    // printf("list_next\n");
    if (!l || l->next == NULL) // if there is no next cel or no cel at all return NULL
    {
        return NULL;
    }
    else
        return l->next;
}
/* Search the last cel of a list
 *  Remove the cel from the list
 *  Return the associated sprite
 * */
sprite_t list_pop_sprite(list_ptr *l)
{
    // printf("list_pop_sprite\n");

    sprite_t data = NULL;
    list_ptr currentList = *l;
    list_ptr lastItem = NULL;
    if (currentList != NULL)
    {
        while (currentList->next->next != NULL) // while there is a next cel
        {
            currentList = currentList->next; // go through the list
        }
        lastItem = currentList->next; // get the last cel
        data = lastItem->data;        // get the sprite
        currentList->next = NULL;     // remove the last cel from the list
        return data;                  // return the sprite
    }
    else
        return NULL;
}

/* Remove the given cel in a list
 * */
void list_remove(list_ptr toDeleteCel, list_ptr *l)
{
    // printf("list_remove\n");

    list_ptr tmpCurrent;
    list_ptr tmpNext;
    tmpCurrent = *l;            // fill our actual cell with the first cell of the list
    tmpNext = tmpCurrent->next; //  fill the next cell with the second cell of the list
    if (tmpCurrent == toDeleteCel)
    {
        *l = tmpCurrent->next; // if the first cell is the one to delete, we just override the first cell with the second one
    }
    else
    {
        while (tmpCurrent->next != toDeleteCel) // otherwise we go through the list until we find the cell to delete
        {
            tmpCurrent = tmpCurrent->next; // go to next cell
            tmpNext = tmpNext->next;       // go to next->next cell
        }
        tmpCurrent->next = tmpNext->next; // and we override the current cell with the next cell to delete the current cell
    }
}
/* Wipe out a list.
 *  Don't forget to sprite_free() for each sprite
 * */
void list_free(list_ptr l)

{
    // printf("list_free\n");

    list_ptr toDelete = l;
    list_ptr next;
    while (toDelete != NULL) // while there is something to delete
    {
        next = toDelete->next;       // go to next cel
        sprite_free(toDelete->data); // remove the sprite from the cel
        free(toDelete);              // remove the cel itself from the list
    }
}