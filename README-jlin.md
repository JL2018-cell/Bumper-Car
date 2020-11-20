# COMP2113-Group-Project
Group members:

Lin Jianan 3035577595
Teng Changqing 3035534402

**Bumper cars**
 
A text-based game that user is required to bump the target out of the arena by setting the bumping direction and primary speed. 
 
**Game Basics**

***Game Description***
- There will be at least 2 points in the square arena. Both are labelled with "A". The left one is controlled by the player. The one at right hand side is target. For simplicity, we assume that these points are mass points (i.e. their shape and size could be neglected for the bumping procedure) and have same mass. 
- The points' starting positions will be randomly selected for each time of game. Besides, the number of "T" is random as well for each time of game, it can be 1 or 2. 
- After each collision, positions of both player and target will be randomly generated.
- The default direction is horizontally to the right. Player could set the direction by inputting 'q' and 'z' to turn pointer anti-clockwisely and clockwisely respectively.
- Player could set the primary speed by pressing 'a' repeatedly. The speed any integer from 1 to 32 inclusive.
- the movement of the player and target and their final positions will be displayed by employing *text-based animation*.
- Press 'q' to exit and save the game: current positions of the player and target will be saved in "Temp.txt" in the same directory as game code. 

**Features implemented**
- Generation of random game sets or events

a random number generator function will generate the starting coordinates of "P" and "T". Also, the number of "T" is randomly generated between 1 and 2 inclusive.
- Data structures for storing game status

a dynamic 2D array will be employed to store the game progress(how many times of wins and loses) and status(the starting position of “P” and "T" of the last time of game that has not yet completed)
- Dynamic memory management

a dynamic 2D array will be employed to store the game progress and status. As the number of times played of each round is uncertain(can be at least 2 and at most 3), such array will store the number of wins and loses. When the round terminates, the variables in this array will return to zero.
- File input/output (e.g., for loading/saving game status)

Progress of game is stored in "Temp.txt". When user execute file to play the game, he/she must include an argument: "New" (stand for New game) or "Log" (stand for loaging game from previous status). If the argument is "New", then, "Temp.txt" will become an empty file through file IO. Otherwise, computer will read "Temp.txt" to load position of points and scores of player in the previous game.
- Program codes in multiple files

Different .cpp files are used to show status of points on screen, calculating result of collision, describing the flow of the game.


       
    
 


