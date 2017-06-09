#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#include "typedefs.h"
#include "maze.c"
#include "router.c"
#include "maze.h"
#include "router.h"
#include "xbee.h"


coords getCoords(char name[]);
int decide_instruction(int signal_in);
void init_time();
double get_time();
cell maze[13][13];
char byteBuffer[BUFSIZ+1];
int programStatus = 1; //0 = program should turn of, 1 = should run.

clock_t t_start;


int main()
{
    int READ;
    int WRITE;
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
    while(programStatus)
    {
    READ = readByte(hSerial, byteBuffer);

    printf("Local byteBuffer: %s\n", byteBuffer);


    //////////////////////////////
    //    Decide what do to based on byteBuffer here, and write to it.

    WRITE = decide_instruction(READ);


    //////////////////////////////

    byteBuffer[0] = WRITE;

    writeByte(hSerial, byteBuffer);

    scanf("%d", &READ); //Temporary user input.

    if (READ == 113) // end the loop by typing 'q'
        programStatus = 0;


    //displayMaze();
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
    return ((double) (clock() - t_start) / CLOCKS_PER_SEC);
}

int decide_instruction(int signal_in)
{
    int signal_out;

    double t_elapsed = get_time();
    switch(signal_in)
    {
        case 9: //"00001001" -> mine
            if((t_elapsed > 0.25*t_line) && (t_elapsed < 0.75*t_line))
            {
                //mine:Recheck route
                //Take a turn around left (00001111=15) or right (00001010=10)
                //Go to next place in route
            }
            else signal_out = 0;
            break;

        case 6: //"00000110" -> crossing, corner state, endpoint
            printf("CASE 6\n");
            if((t_elapsed > 0.75*t_line) && (t_elapsed < 1.25*t_line))
            {
                //  Crossing: left(6), right(3) or straight ahead (0), for the corner straight does not exist
                //Go to next place in route
            }
            else if ((t_elapsed > 0.15*t_line) && (t_elapsed < 0.65*t_line))
            {
                //endpoint:Take a turn around left (00001111=15) or right (00001010=10)
                //Go to next place in route
            }
            else signal_out = 0;
            break;

        case 10: //"00001010" ->Receiving error
            break; //Signal_out is not changed

        default: signal_out = 0; break;
    }

    return signal_out;
}
