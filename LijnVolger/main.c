#include <string.h>
#include <time.h>
#include "typedefs.h"
#include "maze.c"
#include "router.c"

coords getCoords(char name[]);
void init_time();
double get_time();
cell maze[13][13];
clock_t t_start;
double t_line = 10.0; //Amount of seconds it takes to travel between two crossings

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

void init_time ()
{
    t_start = clock();
}

double get_time()
{
    return ((double) (clock() - t_start) / CLOCKS_PER_SEC);
}


int signal_in;
int signal_out;
void decide_instruction(signal_in)
{
    double t_elapsed = get_time();
    switch(signal_in)
    {
        case 9: //"00001001" -> mine
            if((t_elapsed > 0.25*t_line) && (t_elapsed < 0.75*t_line))
            {
                //mine:Recheck route
                //Take a turn around left (00001111=15) or right (00001010=10)
            }
            //Go to next place in route
            break;
        case 6: //"00000110" -> crossing, corner state, endpoint
            if((t_elapsed > 0.75*t_line) && (t_elapsed < 1.25*t_line))
            {
                //  Crossing: left(6), right(3) or straight ahead (0), for the corner straight does not exist
            }
            else if ((t_elapsed > 0.15*t_line) && (t_elapsed < 0.65*t_line))
            {
                //endpoint:Take a turn around left (00001111=15) or right (00001010=10)
            }
            //Go to next place in route
            break;
        case 10: //"00001010" ->Receiving error
            break; //Signal_out is not changed
        default: signal_out = 0; break;
    }
}