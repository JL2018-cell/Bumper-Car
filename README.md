# COMP2113-Group-Project
Group members:

Lin Jianan 3035577595
Teng Changqing 3035534402

**Bumper cars**
 
A text-based game that user is required to bump the target out of the arena by setting the bumping direction and primary speed. 
 
**Game Basics**

***Game Description***
- There will be 2 points in the rectangle arena. One is labelled by "P", which is controlled by the player. The other are labelled by "T", which are the targets. For simplicity, we assume that these points are mass points (i.e. their shape and size could be neglected for the bumping procedure) and have same mass. 
- The points' starting positions will be randomly selected for each time of game. 
- The default direction is horizontally to the right. Player could set the direction by inputting "+*number*" or "-*number*". E.g. "+90" means the direction will rotate counterclockwise by 90 degrees; "-45" means the direction will rotate clockwise by 45 degrees. The number can be any integer from 0 to 180 (inclusive) but -180 is not supported. 20 degrees fault-tolerant interval is incorporated. 
- Player could set the primary speed by "*number*", the number can be any integer from 1 to 15(including the boundaries)
- Player could set the difficulty levels at the beginning of each round by input "Easy" or "Medium" or "Hard", which will be discussed in detail later
- the movement of "P" and "T" will be displayed by employing *text-based animation* if the input direction is correct and "T" bumped out finally
 
***Rounds***
- For each session of game, player could play at most 5 rounds. If the player has won 3 rounds, he/she gains SUCCESS for this session and the session terminates. Else if the player has lost 3 rounds, he/she FAILS in this session and the session terminates. 
- The result of each round of game will be saved. The player may choose whether to check the progress after each round of game 
 
***Win or lose***
*There will be 3 possible outcomes for each time of game*

- "P" does not hit "T", which is regarded as *lose*
- "P" hits "T" but does not bump it out of the arena( both "P" and "T" are in the arena finally) or "P" hits "T" but "P" itself moves out of  the arena ( both "P" and "T" are out of the arena finally), both cases are regarded as *lose*
- "P" hits "T" and bumps it out of the arena while "P" remains in the arena, which is regarded as *win*

***Difficulty level***
*Some notations* 

- coefficient of friction: μ
- the mass of “P” and “T”: m
- the gravitational acceleration: g
- force of friction: fk=μmg
- primary speed of "P": v0 
- speed of "P" before the moment of collision: v1
- speed of "P" after the moment of collision: v2
- speed of "T" after the moment of collision: v3
- coefficient of restitution: e=(v3-v2)/v1
-	the distance between "P" and "T" at the starting position: d1
- the line connecting "P" and "T": l
- the intercept of l's extension and the boundary: "Q"
- the distance between "T" and "Q": d2
 
*There will be three different levels for each round of game*

- "Easy": we assume that μ=0 and the collision is perfectly elastic collision (i.e. e=1), then by rules of conservation of momentum and conservation of energy, v1=v0, v2=0, v3=v1. It follows that as long as the direction is correct, no matter what v0 is, the play will win this time of game. The codes will only check for the direction.
- "Medium: we assume that μ=0.4 and the collision is perfectly elastic collision (i.e. e=1), then by rules of conservation of momentum and conservation of energy, mg(v1)^2/2 = mg(v0)^2/2-μmgd1, v2=0, v3=v1. The codes will first check the direction, if true, then check whether “P” hits “T” (i.e. mg(v0)^2/2 > μmgd1), if true, finally check whether “T” will be bumped out of the arena(i.e. mg(v3)^2/2>μmgd2)
- “Difficult”: we assume that μ=0.4 and the collision is inelastic collision(we assume e=0.5 if the texture of the points is wood), then by rules of conservation of momentum and conservation of energy, mg(v1)^2/2 = mg(v0)^2/2-μmgd1, v2=(v1)/4, v3=3(v1)/4. The codes will first check the direction, if true, the check whether “P” hits “T”(i.e. mg(v0)^2/2 > μmgd1), if true, finally check whether “T” will be bumped out of the arena while “P” remains in the arena(i.e. mg(v3)^2/2>umgd2 and mg(v2)^2/2<=μmgd2) 

**Features implemented**
- Generation of random game sets or events

a random number generator function will generate the starting coordinates of "P" and "T". 
- Data structures for storing game status

a dynamic 1D array will be employed to store the game progress, the WIN or LOSE situation for each round of game
- Dynamic memory management

a dynamic 1D array will be employed to store the game progress, the WIN or LOSE situation for each round of game. As the number of rounds played of each session is uncertain(can be at least 3 and at most 5), such array will store the number of wins and loses. When the session terminates, this array will be freed.
- File input/output (e.g., for loading/saving game status)

"Temp.txt" stores the progress of the saved game. Its first line stores the WIN (1) and LOSE (0) situations and second line stores the difficulty level of the saved game. At the beginning of each game session, the program will check whether "Temp.txt" is empty or not. If "Temp.txt" is empty, which means no saved game, the program will prompts the guide "Enter "New" to start a new game: ". Else if "Temp.txt" is not empty, the programs will update the progress into the progress array and update the difficulty level. After that, the program will prompts the guide "Enter \"Log\" to log the saved game or enter "New" to start a new game: ".

After each round of game, the program will ask whether to save the game or start a new round. If the user choose to save the game, the number stores in the progress array will be written in "Temp.txt" and the difficulty level will be saved as well. After that, the session terminates. 

If the player achieved SUCCESS OR Failure, "Temp.txt" will be cleared.
- Program codes in multiple files

Different .cpp files are used. car.h and car.cpp define several functions on cars' (p and t) performance. screen.h and screen.cpp include functions on the screen display. Main.cpp means to describe the program flows. 

**Compilation and execution instructions**
- input "g++ -pedantic-errors -std=c++ car.cpp screen.cpp main.cpp -o main" in the terminal
- input "g++ -pedantic-errors -std=c++ main.cpp -o main" in the terminal





       
    
 


