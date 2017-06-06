#include <string.h>
#include "typedefs.h"
#include "maze.c"
#include "router.c"

coords getCoords(char name[]);
cell maze[13][13];

int main()
{
    //Initialization of maze.
    initMinOnes();
//    initZeros();
    nameMaze(); //Filename with description of maze.
    assignStations();


    //Post initialization events here.
    blockEdges();   //Find out what edges/crossings need to be blocked.
    router();       //Lee's algorithm.

    displayMaze();

    return 0;
}

// COMMENT VOOR BRANCHTEST

coords getCoords(char name[])
{
    int x, y;
    coords cords;
    cords.x = -1;
    cords.y = -1;

    for(x = 0; x < 13; x++)
    {
        for(y = 0; y < 13; y++)
        {
            if(strcmp(name, maze[x][y].name) == 0)
            {
                cords.x = x;
                cords.y = y;
            }
        }
    }

    return cords;
}
