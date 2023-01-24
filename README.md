# The Eater Game

I created this two-player text-based game using C++ for a university assignment. The aim of this course was to learn object-oriented programming in C++. 

This game allows one player to be the 'Passer' and one player to be the 'Eater'. The game is played on an m x m grid, the size of which can be chosen by the players. The Passer player places their token on the grid, with the aim to place their tokens adjacently in order to make a path from the top of the grid to the bottom. The Eater player can place their token anywhere - if they happen to place their token on the same square as where the Passer intends to place theirs, only the Eater's token will remain. The Eater must try to block the Passer from reaching the bottom. The game continues until either the Passer has created a path to the bottom, or the grid fills up and the Eater wins.

This game also allows the option to play against an AI player, a random player, or a 'straight line' player. 

<img src = "https://github.com/lilystraker/TheEater/blob/main/passerwins.png" width = 450px height = "450px">
