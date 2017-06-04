#include <string.h>
#include <stdio.h>
#include <Windows.h>

#include "typedefs.h"
#include "maze.h"
#include "router.h"
#include "xbee.h"


coords getCoords(char name[]);
cell maze[13][13];
int programStatus = 1; //0 = program should turn of, 1 = should run.


int main()
{
    char byteBuffer[BUFSIZ+1];
    //Initialization of maze.
    initMinOnes();
    initZeros();
    nameMaze("MazeNames.txt"); //Filename with description of maze.
    blockEdges();   //Find out what edges/crossings need to be blocked.
    router();       //Lee's algorithm.

    //Xbee initialization.
    HANDLE hSerial = NULL;

    initXbee(hSerial);

    //Main loop of the program.
    while(programStatus)
    {
    readByte(hSerial, byteBuffer);

    //////////////////////////////
    //    Decide what do to based on byteBuffer here, and write to it.

    gets(byteBuffer); //Temporary user input.
    //////////////////////////////

    writeByte(hSerial, byteBuffer);

    if (byteBuffer[0] == 'q') // end the loop by typing 'q'
        programStatus = 0;


    displayMaze();
    }


    CloseHandle(hSerial); //Close serial handle (important).
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
