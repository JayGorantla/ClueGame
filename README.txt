# Compilation
This program can be compiled with the given Makefile using the "make" command. In the Makefile, there is 
a -g flag that allows for using the GDB Debugger. After using the "make" command, run "final" with "./final"
to access the Clue game. 

#User Input
User input is clearly prompted by the game after "final" is run. This is a user based game and the program 
will not terminate without user interaction. Users are expected to give commands (full list shown by entering
"help" after the program starts) and also make guesses as to who the murderer is, what weapon was used, and 
which room it was done in. After 10 incorrect user guesses, the program will terminate.


#Game Structure 
All rubric requirements are satisfied.

-->POINTERS
Pointers were fun to use. The arguably largest implementation of pointers was used to assign north, south, east,
and west rooms to any given room. This is done in ROOMS.C. Pointers were also used abundantly under the variable 
name of "temp" whenever looping through an item linked list for the room, inventory, or even char arrays that had
names of characters. This is because it is easier to create and discard a temporary pointer when looping rather 
than changing the current global pointer just for trivial uses. A pointer was used to keep track of the current 
room the avatar was in at all times. Additionally, pointers were used to keep a reference to the correct answers 
for any given gameplay. 

-->ITEMS.C/ITEMS.H
Item struct is defined in the header file. It has a char pointer as a name and an item pointer to the next item
in the presumed linked list. The add_item and drop_item methods are defined in ITEMS.C along with all the possible
items in the game. 

-->ROOMS.C/ROOMS.H
Rooms header file has a defined Room struct that includes a char pointer to a name, Room pointers to rooms in all
directions, and a char array that has names of all the characters in that room. Each room is initialized with an
item and five rooms have a character (not the avatar). In ROOMS.C, the room names are randomized, then assigned
to rooms along with items and characters across two methods (randomizeRooms(), createRooms()). Room direction 
pointers are assigned in createRooms() too. The method lookAtMoves() takes care of the look command (shows the
rooms in each direction, characters in the room, and items in the room). 

-->ADVENTURE.C
This main method took care of all the user interaction with a while loop that ran as long as the end conditions
were not met. All user commands other than "look" are programmed in this method. Helper methods such as 
findAndDelCharacter are here along with behind the scenes code like freeing memory (freeMem()). Answers are set 
with the setAnswers method in this class. 

-->RUBRIC GUIDELINES
2a-2c: Done in ROOMS.C across randomizeRooms() and createRooms() methods
2d: setAnswers() method in ADVENTURE.C
2e: Room struct has an itemList pointer which is initialized in createRooms()
2f: Inventory is created and updated in takeCommand and dropCommand methods in ADVENTURE.C
2g: All commands other than "look"(ROOMS.C) are written for in ADVENTURE.C including error checking in cases where
the input is not valid. In this case, the user is asked again until the input is valid. 
2h: This is done in the clueCommand method in ADVENTURE.C with the helper method findAndDelCharacter used to delete
the character from its original room. clueCommand also prints the matching detail. 
2i: ROOMS.C, ITEMS.C, ADVENTURE.C

Design, style, and comments are abundant throughout the entire program in a way that makes viewing the code much
more pleasant. 

Thank you for reading the README file. 
 
