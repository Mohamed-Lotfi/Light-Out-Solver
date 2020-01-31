# Light-Out-Solver
A solver for the famous lights out game using DFS on incomplete graphs

Although there exists a well-known solution to this game using linear algebra, I created this solver to practice working with
graph algorithms such as Depth first search and their variations. My approach adds a couple of layers of complexity to standard
DFS since this uses a variation that I call "Constructive DFS" which builds the graph as it searches. The second twist to regular 
DFS is that the algorithm uses a heuristic to search as opposed to blindly searching through the moves. Below is a more detailed
description of each file as well as the game representation.


1)Board.cpp

- This File handles the board representation and the functions for making and storing moves and board states. 
A board position is simply stored as the 25 righmost bits in an unsigned integer since this is the fastest and
most compact representation possible. The squares of the board are numbered from the top left to the bottom right where the
nth bit (0-24) of the integer is a one if the nth square is on. This representation speeds up all functions considerably since bit-shifitng is much
more effecient for memory and speed purposes than the traditional array representation.

2)ExpandableGraph.cpp

- This file contains the implementation of the expandable graph data-structure that I wrote which is simply the adjacency-list
representation of a graph but with additional capabilities such as adding edges and vertices. The file also includes the
function for expanding the graph by branching out at a specific node.

3)Solver.cpp

- This file Contains the solver itself and the constructive DFS function which constructs the graph as it searches. Each node in the graph represents a board position and two nodes are connected if one position can be reached from another by toggling  one light. The heuristic added to DFS sorts all possible moves to be searched based on the number of lights on after making the move by keeping the moves in a priority queue implemented as a min-heap and then popping all moves in order of higher priority. One additional limitation is added to DFS which does not allow the same light to be toggled more than once in one branch of the search since toggling a light twice is equivalent to doing nothing. The main() function in the solver can be used by converting a board position to its corresponding unsigned integer as described above and plugging this integer to the board variable in the main function and running it. The function will then print out the squares to be toggled in order to solve the puzzle.

