#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#include "typedefs.h"
#include "maze.h"
#include "router.h"
#include "xbee.h"

coords getCoords(char name[]);
void init_time();
double get_time();
cell maze[13][13];
char byteBuffer[BUFSIZ+1];
int programStatus = 1; //0 = program should turn of, 1 = should run.

clock_t t_start;


int main()
{
    byteBuffer[0] = '0';
    //Initialization of maze.
    initMinOnes(); //Generate grid of -1's
    nameMaze(); //Generate maze's not -1 values
    assignStations(); //Add station names


    //Post initialization events here.
    blockEdges();   //Find out what edges/crossings need to be blocked.
    router();       //Lee's algorithm.

    //Xbee initialization.
    HANDLE hSerial = NULL;
    hSerial = initXbee(hSerial);

    //Main loop of the program.
    while(programStatus) {
    readByte(hSerial, byteBuffer);

    printf("Local byteBuffer: %s\n", byteBuffer);

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

void init_time()
{
    t_start = clock();
}

double get_time()
{
    return (double)((clock() - t_start)/CLOCKS_PER_SEC);
}
