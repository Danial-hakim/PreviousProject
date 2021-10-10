# Description of MVP

When the game is first run, 16 letters are randomized and put into a 4 x 4 grid. The game so far will only be single player. The screen will display the player’s total score, the 3 minute timer that is counting down every second, followed by the grid. The player must make sure they’re following the rules, as the game doesn’t check the dictionary to make sure the word is real, and it doesn’t check if the letters used are beside each other. The player is prompted to enter in a word using the letters displayed in the grid, the letters are counted and a score is added to the player’s total score. The screen is then updated to show the new score and the player is prompted again. This repeats until the player runs out of time. In order to reshuffle the letters, the player must quit the game and run it again. The total score from the last game, however, will not be saved.
This will be a C++ Command Line game.

## List of features of the MVP

1. 16 letters are randomised to form a standard 4x4 dive grid
2. Any word is accepted, the words aren't checked in a dictionary 
3. The score is automatically being added after every word based on boggle's rules (defined in research doc)
4. A 3 minute timer, where game ends when timer reaches 0
5. Single player mode, the player tests their own knowledge 

## Define "out-of-scope"

The identified elements which we have deemed ‘out of scope’ for the project are:

1. Words checked to exist within the English dictionary.
2. Multiplayer (including local multiplayer on the same machine).
3. Save players data to local file(and cloud) & restore player data.
4. Limit the number of letters required to be considered a ‘word’.
5. Game console controller as input device.
6. Display words which have already been found by the player.
7. Hints 	
8. Show potential max score.
9. Display the amount of potential words left within game session.
10. Wild characters.
11. Friendly letter distribution.
12. Dies containing more than one letter.
13. Game configurations.

# List of stories needed to complete the MVP

1. "As a Boggle player, I want the letters I have to play with for that round to be displayed in a 4x4 grid on screen so I can accurately see where they lie on the board"  
Example of grid as seen on command line screen:  
ABCD  
EFGH  
IJKL  
MNOP  

2. "As a Boggle player, I want a 3 minute timer to be displayed so I know how much time I have remaining in the current round"

3. "As a Boggle player, I want the game to have automatic scoring that follows Boggle's rules so I don't have to work out the score myself. I also want to be able to see my score at any given time"  
(rules defined in Game Rules in research report.md)

4. "As a Competitive Boggle player, I want the dice to follow the configuration of the real physical board game so I can accurately practice remotely without having to bring my physical copy everywhere."

5. "As a Boggle player, I want the game to accept any word I enter into the command line so that I can use words that may not be in the dictionary, such as slang, or any word from another language that uses English characters"  
(For our MVP, any word is accepted, regardless if the letters used to make that word are adjacent to each other on the boggle board, any letter is used more than once, or on the board at all)
