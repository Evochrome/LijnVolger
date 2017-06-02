#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include "typedefs.h"

extern cell maze[13][13];

coords getCoords(char name[]); //Defined in main.c

void initMinOnes();
void displayMaze();
void initZeros();
void fillLine(int x1, int y1, int x2, int y2);
void nameMaze(char namesFile[]);
void blockEdges();

#endif // MAZE_H_INCLUDED
