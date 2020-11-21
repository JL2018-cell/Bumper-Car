# COMP2113-Group-Project

***Group members***
Lin Jianan 3035577595
Teng Changqing 3035534402

***Description of Game: Bumper cars***
A text-based game that user is required to bump the target out of the arena by setting appropriate bumping direction and primary speed.

***Problem Statement***
- Aim of the game: To test the players' intuition/sense about direction and speed of bumper cars.
- The game is a C++ program
- Assumption: This game is designed for 1 player.

***Basic Game Rules***
- There will be 2 bumper cars in the square arena. Both are labelled with "A". The left one is controlled by the player. The one at right hand side is target. For simplicity, we assume that these points are mass points (i.e. their shape and size could be neglected for the bumping procedure) and have same mass.
- After each collision, positions of both player and target will be randomly generated.
- The default direction is horizontally to the right. Player could set the direction by inputting 'q' and 'z' to turn pointer anti-clockwisely and clockwisely respectively.
- Player could set the primary speed by pressing 'a' repeatedly. The speed is any integer from 1 to 32 inclusive.
- Press 's' to start colliding with the target.
- the movement of the player and target and their final positions will be displayed by employing *text-based animation*.
- Press 'x' to exit and save the game: current positions of the player and target will be saved in "Temp.txt" in the same directory as game code. 

**Features implemented**
- Generation of random game sets or events: positions of each bumper car is random at the beginning of each round of game.
- Data structures for storing game status: Class (C++): store information and relevant function calls of each bumper car.
- Dynamic memory management: Declaration of bumper car 1 and bumper car 2 are dynamically allocated. After the program ends, the space storing bumper car 1 and 2 is released.
- File Input/Output: save positions of bumper cars in Temp.txt (Write file) and resume progress of game (Read file).
- Program codes in multiple files: There is "Makefile" compiling "bumper.cpp", "car.cpp", "car.h", "screen.cpp", "screen.h" into an executable: "bumper".
- <unistd.h>: Use function "sleep(useconds_t useconds)" to suspend the execution of a program for a specified period of time.
- <clocale>: Change locale of C so as to affect the behaviour of input/output functions
- <sys/select.h>: define timeval structure.
- <termios.h>: contains the definitions used by the terminal I/O interfaces (see the XBD specification, General Terminal Interface for the structures and names defined)

***How to run the program***
1. Compile by typing "make".
2. Run by typing "./bumper"
