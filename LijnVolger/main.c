#include <string.h>

#include "typedefs.h"
#include "maze.h"
#include "router.h"

coords getCoords(char name[]);
cell maze[13][13];

int main()
{
    //Initialization of maze.
    initMinOnes();
    initZeros();
    nameMaze("MazeNames.txt"); //Filename with description of maze.


    //Post initialization events here.
    blockEdges();   //Find out what edges/crossings need to be blocked.
    router();       //Lee's algorithm.

    displayMaze();

    return 0;
}

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
