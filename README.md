# 9_puzzle_A_Star
A* search algorithm implemented to solve the 9 puzzle problem


We used 4 different heuristics for A*, the first being Uniform Cost Search, then displaced tiles, next Manhattan distance. 

The forth is a custom heuristic, I used Euclidean distance. It's performance was somewhere between displaced and Manhattan. The reason was because our 9 tile puzzle could only go in the 4 cardinal directions. 

report.pdf has more information.


### Instructions:
1. compile the project with:
 ```make```
 
2. run the code for greedy hill climbing, where heuristic number 0-3 for the heuristics labeled above:<br>
```./a-star heuristic_number```<br>
or simply,<br>
```./bash-script.sh```<br>
to see them all run at once.
