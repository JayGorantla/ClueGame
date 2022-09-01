#ifndef ROOMS_H
#define ROOMS_H

//0 through 5 character indices for the array
#define MAX_CHARACTER 5 

//globally accessible rooms and character name arrays
extern struct Room *rooms[];
extern char *charNames[];

struct Room {
    char *name;
    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
    struct Item *itemList;
    char *character[MAX_CHARACTER];
};

//functions to create gameplay
void randomizeRooms();
void createRooms();

//look function 
void lookAtMoves(int roomNum);

#endif 