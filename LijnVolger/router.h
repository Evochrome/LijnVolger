#ifndef ROUTER_H_INCLUDED
#define ROUTER_H_INCLUDED

#include "typedefs.h"

extern cell maze[13][13];



coords getCoords(char name[]); //Defined in main.c

//Lee's algorithm to find a route, using the functions below.
void router();
void spread(coords endPos, coords startPos);
void traceBack(coords endPos, coords startPos);

void setSurroundings(int x, int y, int i);
coords checkSurroundings(coords curPos);

#endif // ROUTER_H_INCLUDED
