#ifndef ITEMS_H
#define ITEMS_H

//globally accessible items array
extern char *items[];

struct Item {
    char *name;
    struct Item *next;
};

//functions to add and drop item from inventory and the room
struct Item * add_item(struct Item *start, char *Name);
struct Item * drop_item(struct Item *start, char *Name);

#endif