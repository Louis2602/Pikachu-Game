# Pikachu-Game
Pikachu Game made with C++ | HCMUS Programming Techniques Project
### I. Introduction
The Matching Game (commonly known as Pikachu Puzzle Game) includes a board of multiple cells, each of which
presents a figure. The player finds and matches a pair of cells that contain the same figure and connect each other
in some particular pattern. A legal match will make the two cells disappear. The game ends when all matching
pairs are found. Figure 1 shows some snapshots from the Pikachu Puzzle Game.
In this project, we will develop a simplified version of this Matching Game by remaking the game with characters
(instead of figures).
![pikachu-game](https://cdn.shortpixel.ai/spai/w_995+q_lossy+ret_img+to_webp/https://1ktut.com/wp-content/uploads/2019/05/tai-Game-Pikachu-Co-Dien-ve-may-tinh.png)
### II. Detailed Description
#### II.1 Standard Mode
This mode contains the essential steps to make the game possible.
1. Game starting: Initialize a board with the given size while satisfying the following conditions
- The total number of cells must be even.
- The number of distinct characters is specified in advance.
- For each character, determine an even number to define the number of occurrences for that character.
2. Any matching pair must satisfy the following conditions
- Characters on the two cells must be identical.
- When the cells disappear, their positions are replaced with blank spaces.
- The matching pattern must be one of the below motifs.
	+ I Matching
	+ L Matching
	+ U Matching
	+ Z Matching
3. Game finishing: check the following conditions
- Are there any cells left?
- Are there any valid pairs left?
#### II.2 Difficult Mode
In this mode, the neighboring cells should slide into the newly emptied spaces in a particular direction (left to right,
up to down, etc.) Students may decide to use Pointer, LinkedList, or both for implementation. If you choose to use
both data structures, only one is needed to make the game run, and the other should help with the report (The
details will be given below)
#### II.3 Advaned Features
Players will experience the game better if you can add one (or more) of the following extra features to the game.
- Color and sound effects
- Visual effects (Figure 6)
- Background: You can design anything for a background. Then, when a matching pair disappears, the background content corresponds to those emptied cells.
- Leaderboard: The top N players that finished their games with the shortest time will register their information
to the Leaderboard.
- Move suggestion: Show player a valid match when they press the "Help" key.