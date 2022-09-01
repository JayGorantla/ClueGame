#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "rooms.h"
#include "items.h"

//int and pointer to struct to keep track of room avatar is in
int roomNum = 4;
struct Room *curRoom;

//avatar inventory
struct Item *inventory;

//correct answers
struct Room *roomAns;
struct Item *itemAns;
char *charAns = "";

bool isCorrect = false;
bool invFlag = false;
int guesses = 0;

//free the itemList and rooms 
void freeMem() {
    free(rooms[0]->itemList);
    free(rooms[0]);
    free(rooms[1]->itemList);
    free(rooms[1]);
    free(rooms[2]->itemList);
    free(rooms[2]);
    free(rooms[3]->itemList);
    free(rooms[3]);
    free(rooms[4]->itemList);
    free(rooms[4]);
    free(rooms[5]->itemList);
    free(rooms[5]);
    free(rooms[6]->itemList);
    free(rooms[6]);
    free(rooms[7]->itemList);
    free(rooms[7]);
    free(rooms[8]->itemList);
    free(rooms[8]);
}


void printInventory() {
    struct Item *temp = inventory;
    
    if (!invFlag || temp == NULL) {
        printf("\nThere is nothing in your inventory.\n");
    } else {
        printf("\nYour inventory:\n");
        //prints items in inventory and increments until temp is null
        while (temp != NULL) {
            printf("%s\n", temp->name);
            temp = temp->next;
        }
    }
}

//implemented in clueCommand
void findAndDelCharacter(char *name) {
    bool check = false;
    int roomNumber = 0;
    //loops through all 9 rooms until the character is found and sets that element to an empty string
    //sets check flag to true when found and breaks it out of the loops
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < sizeof(rooms[i]->character)/sizeof(rooms[i]->character[0]); j++) {
            if (rooms[i]->character[j] != NULL) {
                if (strcmp(name, rooms[i]->character[j]) == 0) {
                    rooms[i]->character[j] = "";
                    check = true;
                }
                if (check) {
                    break;
                }
            }
            
        }
        if (check) {
            break;
        }
    }
}

void clueCommand() {
    printf("\nChoose a character: \n");
    printf("Jay, Bob, Mark, Jim, Chip\n\n");
    char *input = (char *) malloc(sizeof(char) * 100);
    bool check = false;
    scanf("%s", input);
    //checks the character name array to see if the entered name is valid
    while (!check) {
        for (int i = 0; i < 5; i++) {
            if (strcmp(input, charNames[i]) == 0) {
                check = true;
            }
        }
        if (!check) {
            printf("\nInvalid character. Please choose again.\n");
            scanf("%s", input);
        }
    }
    findAndDelCharacter(input);

    //adds character name to the array when there is a NULL or empty spot
    check = false;
    for (int i = 0; i < 5; i++) {
        if (curRoom->character[i] == NULL || strcmp(curRoom->character[i], "") == 0) {
            curRoom->character[i] = input;
            check = true;
        }
        if (check) {
            break;
        }
    }

    //checks room condition
    bool flag1 = false;
    if (roomAns == curRoom) {
        printf("\nRooms match\n");
        flag1 = true;
    } else {
        printf("\nRooms don't match\n");
    }

    //checks character condition
    bool flag2 = false;
    for (int j = 0; j < 5; j++) {
        if (curRoom->character[j] == NULL || strcmp(curRoom->character[j], "") == 0) {
            break;
        } else {
            if (strcmp(charAns, curRoom->character[j]) == 0) {
                flag2 = true;
            }
        }
    }

    if (flag2) {
        printf("Character match\n");
    } else {
        printf("Character doesn't match\n");
    }

    //checks item condition with inventory and itemList in the room
    bool flag3 = false;
    struct Item *temp = rooms[roomNum]->itemList;
    while (temp != NULL) {
        if (strcmp(itemAns->name, temp->name) == 0) {
            flag3 = true;
        }
        temp = temp->next;
    }
    temp = inventory;
    while (temp != NULL) {
        if (temp->name == NULL) {
            break;
        }
        if (strcmp(itemAns->name, temp->name) == 0) {
            flag3 = true;
        }
        temp = temp->next;
    }

    if (flag3) {
        printf("Item match\n\n");
    } else {
        printf("Item doesn't match\n\n");
    }

    //checks win condition
    if (flag1 && flag2 && flag3) {
        isCorrect = true;
    }
    
}


void dropCommand(struct Item *inv) {
    struct Item *temp = inventory;
    char *input = (char *) malloc(sizeof(char) * 100);
    bool exists = true;

    //checks inventory for items to drop
    if (inv == NULL || inv->name == NULL) {
        printf("\nYou can not drop anything\n");
        exists = false;
    } else {
        printf("\nPick an item from your inventory to drop: \n");
        while (temp != NULL) {
            printf("%s\n", temp->name);
            temp = temp->next;
        }
        printf("\n");
    }

    //ensures selected item is in inventory
    if (exists) {
        bool check = false;
        temp = inventory;
        scanf("%s", input);
        while (!check) {
            while (temp->name != NULL) {
                if (strcmp(input, temp->name) == 0) {
                    check = true;
                    break;
                }
                temp = temp->next;
            }
            if (!check) {
                printf("Invalid item. Please pick one from the list above");
                scanf("%s", input);
            }
        }

        
        //added item to room
        curRoom->itemList = add_item(curRoom->itemList, input);
        //remove item from inv
        inventory = drop_item(inv, input);
    }    
}

void takeCommand(struct Item *inv) {
    struct Item *temp = curRoom->itemList;
    char *input = (char *) malloc(sizeof(char) * 100);
    bool exists = true;

    //displays room's itemList
    if (curRoom->itemList == NULL) {
        printf("\nThere is nothing to take from this room\n");
        exists = false;
    } else {
        printf("\nPick an item from the room to take: \n");
        while (temp != NULL) {
            printf("%s\n", temp->name);
            temp = temp->next;
        }
        printf("\n");
    }

    //ensures selected item is in the room
    if (exists) {
        bool check = false;
        temp = curRoom->itemList;
        scanf("%s", input);
        while (!check) {
            temp = curRoom->itemList;
            while (temp != NULL) {
                if (strcmp(input, temp->name) == 0) {
                    check = true;
                    break;
                }
                temp = temp->next;
            }
            if (!check) {
                printf("\nInvalid item. Please pick one from the list above:\n");
                scanf("%s", input);
            }
        }

        //Adding the specified item to the inventory
        inventory = add_item(inv, input);
        //Dropping the specified item from the item list of the current room
        curRoom->itemList = drop_item(curRoom->itemList, input);

    }
}


void goCommand() {
    printf("\nWhich direction would you like to move?\n");
    bool check = false;
    char *input = (char *) malloc(sizeof(char) * 100);
    scanf("%s", input);
    //changes roomNum and curRoom when avatar goes to another room
    while (!check) {
        if (strcmp(input, "north") == 0 || strcmp(input, "south") == 0 || strcmp(input, "east") == 0 || strcmp(input, "west") == 0 ) {
            if (strcmp(input, "north") == 0 && roomNum > 2) {
                check = true;
                roomNum = roomNum - 3;
                curRoom = rooms[roomNum];
                free(input);
            } else if (strcmp(input, "south") == 0 && roomNum < 6) {
                check = true;
                roomNum = roomNum + 3;
                curRoom = rooms[roomNum];
                free(input);
            } else if (strcmp(input, "east") == 0 && (roomNum % 3 != 2)) {
                check = true;
                roomNum = roomNum + 1;
                curRoom = rooms[roomNum];
                free(input);
            } else if (strcmp(input, "west") == 0 && (roomNum % 3 != 0)) {
                check = true;
                roomNum = roomNum - 1;
                curRoom = rooms[roomNum];
                free(input);
            }
        }
        //repeats while loop if entered direction is not valid/doesn't exist
        if (!check) {
            free(input);
            char *input = (char *) malloc(sizeof(char) * 100);
            printf("\nPlease enter a valid direction:\n");
            scanf("%s", input);
        }
    }
}

//sets the correct room, item, and character answer
void setAnswers() {
    srand(time(0));
    roomAns = rooms[rand()%9];
    srand(time(0)+20);
    itemAns->name = items[rand()%9];
    charAns = charNames[rand()%5];
}

//list of all items, rooms, characters
void listPrint() {
    printf("\nList of items: knife, gun, shovel, dagger, rocks, poison, axe, bomb, club\n");
    printf("List of rooms: kitchen, hall, bedroom, gym, courtyard, storage, garage, bathroom, cellar\n");
    printf("List of characters: Jay, Bob, Mark, Jim, Chip\n");

}

//help command
void helpPrint() {
    printf("\nCommands: \n");
    printf("help: shows all the available commands\n");
    printf("list: shows list of items, rooms, and characters\n");
    printf("look: shows the rooms in each direction, characters in the room, and items in the room\n");
    printf("go: use this command to choose which direction to move\n");
    printf("take: follow this command with an item name to pick it up\n");
    printf("drop: follow this command with an item name to drop it\n");
    printf("inventory: use this command to check the items in the avatar's inventory\n");
    printf("clue: follow this command with your guess of the character name\n");
}

int main() {

    //explain game and set up gameplay
    printf("Welcome to my clue game. You are placed in the center room of a 3x3 grid with 9 rooms. Spread across the rooms are 9 murder weapons and 5 suspects. You can pick up weapons and summon characters to the room you believe the murder was committed in. You have 10 guesses to correctly guess the character, room, and item for the murder by bringing the weapon and character to the room. Enter \"help\" to see all the possible commands. All commands are to be entered in lowercase.\n");
    itemAns = (struct Item *) malloc(sizeof(struct Item));
    inventory = (struct Item *) malloc(sizeof(struct Item));
    randomizeRooms();
    createRooms();
    setAnswers();
    curRoom = rooms[4];
    /*printf("\n%s", roomAns->name);
    printf("%s", charAns);
    printf("%s", itemAns->name);*/
    while (!isCorrect && guesses < 10) {
        char *input = (char *) malloc(sizeof(char) * 100);
        printf("\nPlease enter a command: \n");
        scanf("%s", input);
        if (strcmp(input, "help") == 0) {
            helpPrint();
        } else if (strcmp(input, "list") == 0) {
            listPrint();
        } else if (strcmp(input, "look") == 0) {
            lookAtMoves(roomNum);
        } else if (strcmp(input, "go") == 0) {
            goCommand();
        } else if (strcmp(input, "take") == 0) {
            takeCommand(inventory);
            invFlag = true;
        } else if (strcmp(input, "drop") == 0) {
            dropCommand(inventory);
        } else if (strcmp(input, "clue") == 0) {
            guesses++;
            clueCommand(); 
            printf("You have made %d guess(es).\n", guesses);
        } else if (strcmp(input, "inventory") == 0) {
            printInventory();
        } else {
            printf("\nInvalid command. Please enter a valid command.\n");
        }
    }

    //checks win/loss conditions
    if (isCorrect) {
        printf("Congrats. You won the game.\n\n");
    } else {
        printf("You have made all 10 guesses. Please try again. Thank you for playing.\n\n");
    }

    //frees memory that was allocated during the game
    freeMem();
    return 0;
}