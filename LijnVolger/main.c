#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#include "typedefs.h"
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

clock_t t_start; //starting time of the clock
double t_line = 3.6; //seconds required to drive a straight line
double t_turn = 1; //seconds required to make a turn
double t_back = 5.0; //seconds required to turn around at a mine
double t_req = 3.6; //seconds required until he next crossing (calculated with the above constants)



int main()
{
    int READ;
    int WRITE;
    byteBuffer[0] = '0';

    //Initialization of maze.
    initMinOnes(); //Generate grid of -1's
    nameMaze(); //Generate maze's not -1 values
    assignStations(); //Add station names
    init_time();


    //Post initialization events here.
    //blockEdges();   //Find out what edges/crossings need to be blocked.
    router();       //Lee's algorithm.
    list = head;
    //Xbee initialization.
    HANDLE hSerial = NULL;
    hSerial = initXbee(hSerial);

    list = list->next;



    //Main loop of the program.
    while(programStatus)
    {

    //scanf("%d", &READ); //Temporary user input.

    if (list->next == NULL)
        READ = 113;

    if (READ == 113) // end the loop by typing 'q'
        programStatus = 0;
    READ = readByte(hSerial, byteBuffer);

    printf("READ = %d\n", READ);

    //scanf("%d", &READ); //Temporary user input.
    //////////////////////////////
    //    Decide what do to based on byteBuffer here, and write to it.

    WRITE = decide_instruction(READ);



    printf("WRITE = %d\n\n", WRITE);
    //////////////////////////////

    byteBuffer[0] = WRITE;

    writeByte(hSerial, byteBuffer);




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
    static int signal_out;
    double t_elapsed = get_time();
    switch(signal_in)
    {
        case 0: //"00000000" -> clear
            signal_out = 1;
            break;

        case 9: //"00001001" -> mine
            if((t_elapsed > 0.25*t_req) && (t_elapsed < 0.75*t_req))
            {
                //mine:Recheck route
                //Take a turn around left (00001111=15) or right (00001010=10)
                //Go to next place in route
            }
            else signal_out = 1;
            break;

        case 6: //"00000110" -> crossing, corner state, endpoint
            printf("t_elapsed: %2f\n", t_elapsed);
            printf("list: %c\n", list->c);
            if(((t_elapsed > 0.75*t_req) && (t_elapsed < 1.25*t_req)) || t_elapsed < 0.2)
            {
                if (list->c == 'l')
                {
                    signal_out = 3;
                    if (t_elapsed > 1.0*t_req)
                        t_req = t_line + t_turn;
                }
                else if (list->c == 'r')
                {
                    signal_out = 6;
                    if (t_elapsed > 1.0*t_req)
                        t_req = t_line + t_turn;
                }
                else if (list->c == 's')
                {
                    signal_out = 1;
                    t_req = t_line;
                }

                if (t_elapsed > 1.1*t_req)
                list = list->next;

            }
            if (t_elapsed > 1.1*t_req){
                    init_time();}
            //else if ((t_elapsed > 0.15*t_req) && (t_elapsed < 0.65*t_req))
           // {
                //endpoint:Take a turn around left (00001111=15) or right (00001010=10)
                //Go to next place in route
          //  }
            //else signal_out = 1;
            break;

        case 10: //"00001010" ->Receiving error
            break; //Signal_out is not changed

        default:
            signal_out = 1;
            printf("ERROR unknown signal.\n");
            break;
    }

    return signal_out;
}
