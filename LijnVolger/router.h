#ifndef ROUTER_H_INCLUDED
#define ROUTER_H_INCLUDED

#include "typedefs.h"

extern cell maze[13][13];

nav *head;
nav *list;

coords getCoords(char name[]); //Defined in main.c

//Lee's algorithm to find a route, using the functions below.
void router();
void spread(coords endPos, coords startPos);
void traceBack(coords endPos, coords startPos);
int find_nearest_point(char* point1, char* point2, char* point3);

void setSurroundings(int x, int y, int i);
coords checkSurroundings(coords curPos);

void map_translator(coords LastPos, coords CurPos, coords NextPos);
void initialize_translator();

void recheckRoute(int steps);
coords tracePos(int steps);

int coordinatepoints[2][4];
int ends_reached, mine_found;
coords Start_point, mine;


#endif // ROUTER_H_INCLUDED
