#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include "typedefs.h"

extern cell maze[13][13];
coords stations[12];
int firstOffset, middleLine, lastOffset, N = 13;
int countC, countR, countEdgeR, countEdgeC, r, c;


coords getCoords(char name[]); //Defined in main.c

void initMinOnes();
void displayMaze();
void assignStations();
void nameMaze();
void blockEdges();

#endif // MAZE_H_INCLUDED
