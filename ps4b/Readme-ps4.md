# PS4a: Sokoban UI

## Contact
Name: Jake Shick

Section: 202

Time to Complete: 10+ hours


## Description
Part A: 
The program is Sokoban, a japanese box moving game that has your player pushing boxes into the correct positions with a finite number of moves.  In part A, we were asked to design the UI for the game or to draw the character and their position relative to the window and the grid given.  This will set us up for part B when we have to design player movement and boundries.  As a whole, all the program does at the given movement is it reads the information given by the file, and transform said information into our window.

Part B:
The program has now been modified to it's implementation phase, being able to have the player move, push boxes, and have walls stop both player and box movement.  The player can only push one box at a time, trying to push more than one will result in the player not or either of the boxes moving.  To achieve this, I needed to keep track of the all moveable and unmovable objects(besides the regular ground) in order to compare the spots with one another.  

### Features
Part A: 
I decided to use a vector of vectors of characters to represent the grid/matrix.  By doing this, I was able to step through at each position and extract each character one by one until I reach the end of the file.  Before doing this however, I extract the height and then the width of the grid, and then set the window according to the grid by taking the dimensions of the images and setting the window accordingly.  To put values into the grid and draw the grid, I used nested for loops to iterate throughout each and drawing each block or image to the screen one at a time.  I did this by using multiple if else statements to check where we were in the grid and what chracter was held at that position and would then draw it.  If the character was either the player or a crate, I would draw the ground behind him so they would have some backround besides a black space.  

Part B:
For this, I implemented a lot more vectors then I did in part A.  I used one Vector2i to represent the position of the player since their will always be one player in the game and we don't need to run through multiple iterations to check for more than one player.  I used three vectors of Vector2i to represent the walls, the crates, and the floors that needed to be filled with crates for the player to win.  Since there were multiple of all of these, it made sense to have a vector for each of them that iterated throughout them in order to know which crate or which wall we were currently at.  In my movePlayer function, I had a helper function to get the next and previous position of the player or the crate.  This allowed me to do my checking before I set the new values for my positions.  I also had a isNoWall function to check and see if there was a no wall and if there wasn't, then the moveable object or player could go into said position.  In my isWon function, I just checked to see if the crates and the filled spots matched up and if they didn't return false.  Didn't really add too much to my main, just added a music file to play whenever the player would win.

### Issues
No issues that I ran into.

### Tests
Part A: No tests.
Part B: No tests.

### Extra Credit
Added a sound that plays when you win, and added a change in texture for whenever the player changed direction, meaning that I included the other three player textures in the zip file and used them to change the players position relative to the their direction.

## Acknowledgements
Part A:
Doctor Daly- Office hours

Porchhay B- Tutor hours

https://www.sfml-dev.org/tutorials/2.6/graphics-sprite.php

https://gamedev.stackexchange.com/questions/114405/problem-with-transparent-textures-in-sfml

https://stackoverflow.com/questions/6260883/c-function-receiving-an-enum-as-one-of-its-parameters

https://en.sfml-dev.org/forums/index.php?topic=27809.0

Part B:
Doctor Daly- Office hours

Porchhay B- Tutor hours

https://www.youtube.com/watch?v=482weZjwVHY

https://www.geeksforgeeks.org/lambda-expression-in-c/



