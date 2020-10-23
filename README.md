# COMP2113-Group-Project
Group members:
Lin Jianan
Teng Changqing 3035534402

Bumper cars 
 
**Game description** 
A text-based game that user is required to bump the target out of the arena by setting the bumping direction and primary speed. 
 
**Basics**
***Game setting***
- There will be two points in the square arena. One is labelled by "P", which is controlled by the player. Another is labelled by "T", which is the target. For simplicity, we assume that these two points are mass points (i.e. their shape and size could be neglected for the bumping procedure) and have same mass. 
- The two points' starting positions will be randomly selected for each time of game. 
- The default direction is horizontally to the right. Player could set the direction by inputting "+ number" or "- number". E.g. "+ 90" means the direction will rotate counterclockwise by 90 degrees; "- 45" means the direction will rotate clockwise by 45 degrees. The number can be any integer from 0 to 360 (including the boundaries) Four degrees fault-tolerant interval is incorporated. 
- Player could set the primary speed by "a number", the number can be any integer from 1 to 10(including the boundaries)
- Player could set the difficulty levels at the beginning of each round by input "Easy" or "Medium" or "Hard", which will be discussed in detail later
- the movement of "P" and "T" and their final positions will be displayed by employing *text-based animation*
 
***Round***
- For each round of game, player could play at most 5 times. If the player have won 3 times, he/she wins in this round and this round terminates. Else if the player have lost 3 times, he/she lost in this round and this round terminates. 
- The result of each time of game will be saved. Player could input "Progress" or "P" to check how many times he/she has won or lost at the current stage 
 
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

-"Easy": we assume that μ=0 and the collision is perfectly elastic collision (i.e. e=1), then by rules of conservation of momentum and conservation of energy, v1=v0, v2=0, v3=v1. It follows that as long as the direction is correct, no matter what v0 is, the play will win this time of game. The codes will only check for the direction.
- "Medium: we assume that μ=0.4 and the collision is perfectly elastic collision (i.e. e=1), then by rules of conservation of momentum and conservation of energy, mg(v1)^2/2 = mg(v0)^2/2-μmgd1, v2=0, v3=v1. The codes will first check the direction, if true, then check whether “P” hits “T” (i.e. mg(v0)^2/2 > μmgd1), if true, finally check whether “T” will be bumped out of the arena(i.e. mg(v3)^2>umgd2)
- “Difficult”: we assume that μ=0.4 and the collision is inelastic collision(we assume e=0.5 if the texture of the points is wood), then by rules of conservation of momentum and conservation of energy, mg(v1)^2/2 = mg(v0)^2/2-μmgd1, v2=(v1)/4, v3=3(v1)/4. The codes will first check the direction, if true, the check whether “P” hits “T”(i.e. mg(v0)^2/2 > μmgd1), if true, finally check whether “T” will be bumped out of the arena while “P” remains in the arena(i.e. mg(v3)^2>umgd2 and mg(v2)^2<=umgd2) 

**System Command**
- "Save": save the file containing the current game status 
- "Restore": restore a saved game, return to the saved status
- "Quit": end the game 
- "Restart": start a new round  
- "Help": get the useful information about how to play the game 

**Features implemented**
- Generation of random game sets or events: the start position of "P" and "T"
- Data structures for storing game status
- Dynamic memory management: round of game 
- File input/output (e.g., for loading/saving game status): "Save" and "Restore" command 
- Program codes in multiple files



       
    
 


