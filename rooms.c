#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "rooms.h"
#include "items.h"

//initialize the names of the rooms and characters in a char string array
char *roomNames[] = {"kitchen", "hall", "bedroom", "gym", "courtyard", "storage", "garage", "bathroom", "cellar"};
char *charNames[] = {"Jay", "Bob", "Mark", "Jim", "Chip"};

//array of rooms 
struct Room *rooms[9];

//randomizes the array of room names to later be used in create rooms
void randomizeRooms() {
    int num1;
    int num2;
    char *temp;
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        num1 = rand() % 9;
        temp = roomNames[num1];
        num2 = rand() % 9;
        roomNames[num1] = roomNames[num2];
        roomNames[num2] = temp;
    }
}

/*creates rooms inside the rooms array and assigns an item and character to each room (not to be confused 
  with room name)*/
void createRooms() {
    
    for (int a = 0; a < 9; a++) {
        rooms[a] = (struct Room *) malloc(sizeof(struct Room));
    }

    for (int i = 0; i < 9; i++) {
        rooms[i]->name = roomNames[i]; 
    }

    struct Item *item1 = (struct Item *) malloc(sizeof(struct Item));
    item1->name = "knife";
    struct Item *item2 = (struct Item *) malloc(sizeof(struct Item));
    item2->name = "gun";
    struct Item *item3 = (struct Item *) malloc(sizeof(struct Item));
    item3->name = "shovel";
    struct Item *item4 = (struct Item *) malloc(sizeof(struct Item));
    item4->name = "dagger";
    struct Item *item5 = (struct Item *) malloc(sizeof(struct Item));
    item5->name = "rocks";
    struct Item *item6 = (struct Item *) malloc(sizeof(struct Item));
    item6->name = "poison";
    struct Item *item7 = (struct Item *) malloc(sizeof(struct Item));
    item7->name = "axe";
    struct Item *item8 = (struct Item *) malloc(sizeof(struct Item));
    item8->name = "bomb";
    struct Item *item9 = (struct Item *) malloc(sizeof(struct Item));
    item9->name = "club";
    
    rooms[0]->character[0] = "Jay";
    rooms[0]->itemList = item1;
    rooms[1]->character[0] = "Bob";
    rooms[1]->itemList = item2;
    rooms[2]->character[0] = "Mark";
    rooms[2]->itemList = item3;
    rooms[3]->character[0] = "Jim";
    rooms[3]->itemList = item4;
    //avatar starts in center room
    rooms[4]->itemList = item5;
    rooms[5]->character[0] = "Chip";
    rooms[5]->itemList = item6;
    rooms[6]->itemList = item7;
    rooms[7]->itemList = item8;
    rooms[8]->itemList = item9;

    //setting the north, south, east, west pointers for each room
    for (int j = 3; j < 9; j++) {
        rooms[j]->north = rooms[j - 3];
    }
    for (int k = 0; k < 6; k++) {
        rooms[k]->south = rooms[k + 3];
    }
    for (int a = 0; a < 9; a++) {
        if (!(a == 0 || a == 3 || a == 6)) {
            rooms[a]->west = rooms[a - 1];
        }
        if (!(a == 2 || a == 5 || a == 8)) {
            rooms[a]->east = rooms[a + 1];
        }
    }
}

//function for look command
//prints out neighboring rooms, characters in the room, and items in the room (not inventory)
void lookAtMoves(int roomNum) {
    printf("\nYou are currently in the %s: \n", rooms[roomNum]->name);
    if (roomNum < 3) {
        printf("There is no room in the north\n");
    } else {
        printf("The %s is in the north\n", rooms[roomNum - 3]->name);
    }

    if (roomNum > 5) {
        printf("There is no room in the south\n");
    } else {
        printf("The %s is in the south\n", rooms[roomNum + 3]->name);
    }

    if (roomNum == 0 || roomNum == 3 || roomNum == 6) {
        printf("There is no room in the west\n");
    } else {
        printf("The %s is in the west\n", rooms[roomNum - 1]->name);
    }

    if (roomNum == 2 || roomNum == 5 || roomNum == 8) {
        printf("There is no room in the east\n\n");
    } else {
        printf("The %s is in the east\n\n", rooms[roomNum + 1]->name);
    }

    printf("The characters in the room are: \n");

    if (rooms[roomNum]->character[0] == NULL || strcmp(rooms[roomNum]->character[0], "") == 0) {
        printf("None\n");
    }

    for (int i = 0; i < MAX_CHARACTER; i++) {
        if (rooms[roomNum]->character[i] == NULL || strcmp(rooms[roomNum]->character[i], "") == 0) {
            continue;
        } else {
            printf("%s\n", rooms[roomNum]->character[i]);
        }
    }

    printf("\nThe items in the room are: \n");

    struct Item* temp = rooms[roomNum]->itemList;
    if (temp == NULL) {
        printf("None\n");
    }
    while (temp != NULL) {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}