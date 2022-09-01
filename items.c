#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "items.h"
#include "rooms.h"

char *items[] = {"knife", "gun", "shovel", "dagger", "rocks", "poison", "axe", "bomb", "club"};

/**
 * @param start - itemList that you want the item added to
 * @param Name - name of the item (char string)
 * @return struct Item* - returns the linked list with the item added onto the end
 * 
 */
struct Item * add_item(struct Item *start, char *Name) {
    struct Item *newItem = (struct Item *) malloc(sizeof(struct Item));
    struct Item *lastItem = start;
    newItem->name = Name;
    newItem->next = NULL;
    //if inventory is empty
    if (start == NULL) {
        start = newItem;
        return start;
    } else if (start->name == NULL) {
        start = newItem;
        return start;
    }
    //if not, loop to end of linked list and add the item
    while (lastItem->next != NULL) {
        lastItem = lastItem->next;
    }
    lastItem->next = newItem;
    return start;
}


/**
 * Precondition: The item to drop is within the item list pointed to by start
 * 
 * @param start - linked list that contains the item
 * @param Name - name of item to remove
 * @return struct Item* - ipdated linked list
 */
struct Item * drop_item(struct Item *start, char *Name) {
    struct Item *temp = start;
    //if the item to be removed is the first item in the linked list
    if (strcmp(start->name, Name) == 0) {
        start = start->next;
        return start;
    //else, find the element and leap frog the item to be removed by setting next to nextnext
    } else {
        while (strcmp(temp->next->name, Name) != 0) {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        return start;
    }
}
