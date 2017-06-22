#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>

#include "typedefs.h"
#include "maze.h"
#include "router.h"
#include "xbee.h"


coords getCoords(char name[]);
int decide_instruction(int signal_in, HANDLE hSerial);
void init_time();
double get_time();
cell maze[13][13];
char byteBuffer[BUFSIZ+1];
char writeBuffer[BUFSIZ+1];
int programStatus = 1; //0 = program should turn of, 1 = should run.
void clearBuf();
clock_t t_start;
clock_t t_spam;
double t_line = 3.6; //seconds required to drive a straight line
double t_elapsed;
int READ;
int ready = 0, start = 0, steps = 1;


int main()
{
    byteBuffer[0] = '0';
    writeBuffer[0] = '0';
    int WRITE;

    //Initialization of maze.
    initialize_blocks(); //Creates an empty list of mines
    initMinOnes(); //Generate grid of -1's
    nameMaze(); //Generate maze's not -1 values
    assignStations(); //Add station names


    //Post initialization events here.
    router();       //Lee's algorithm.
    list = head;

    //Xbee initialization.
    HANDLE hSerial = NULL;
    hSerial = initXbee(hSerial);

    //From starting position check if an immediate right or left is needed, then continue.
    while(start == 0){
        clearBuf();
        READ = readByte(hSerial, byteBuffer);
        printf("executed\nREAD: %d\n", READ);
        writeBuffer[0] = 1;
        writeByte(hSerial, writeBuffer);
        if(READ!=6){
            start = 1;
        }
    }
    //writeFor(1, 0.2, hSerial);

    ready = 1;
    WRITE = 0;
    writeBuffer[0] = WRITE;
    writeByte(hSerial, writeBuffer);
    printf("\nI RESET\n\n");



    //Main loop of the program.
    while(programStatus)
{

    if (READ == 113) { // end the loop by typing 'q'
        programStatus = 0;
    }
    while(1) { //Endless loop until break
        t_elapsed = get_time();
        clearBuf();
        READ = readByte(hSerial, byteBuffer);

        if((t_elapsed>0.65*t_line)||READ==4){
            //ready for next instruction if time is right or read == 4
            ready = 1;
            WRITE = 0;
            writeBuffer[0] = WRITE;
            writeByte(hSerial, writeBuffer);
        }

        if(READ==4){
            if(list->next==NULL){
                WRITE = 0;
                writeBuffer[0] = WRITE;
                writeByte(hSerial, writeBuffer);
                READ = 113;
                break;
            }
        }

        if(READ==100) printf("READ = %d\n", READ);

        //////////////////////////////
        //    Decide what do to based on byteBuffer here, and write to it.

        if (READ == 6 && ready) {
            WRITE = decide_instruction(6, hSerial);
            writeBuffer[0] = WRITE;
            writeByte(hSerial, writeBuffer);
            printf("WRITE = %d\n\n", WRITE);
            //reset_time
            init_time();
            t_elapsed = get_time();
            while (t_elapsed < 0.6) {
                t_elapsed = get_time();
            }
            while (READ != 3){ //&& READ != 0) {
                READ = readByte(hSerial, byteBuffer);
            }
            WRITE = 1;// Go straight after instruction :)
            printf("WRITE = %d\n\n", WRITE);
            //////////////////////////////
            writeBuffer[0] = WRITE;
            writeByte(hSerial, writeBuffer);
            ready = 0;
            init_time();
        }

        if(READ == 9){
            printf("FOUND A MINE BITCHES!");
            WRITE = decide_instruction(9, hSerial);
            writeBuffer[0] = WRITE;
            writeByte(hSerial, writeBuffer);
            printf("WRITE = %d\n\n", WRITE);
            //reset_time
            init_time();
            t_elapsed = get_time();
            while (t_elapsed < 0.6) {
                t_elapsed = get_time();
            }
            while (READ != 3){ //&& READ != 0) {
                READ = readByte(hSerial, byteBuffer);
            }
            WRITE = 1;// Go straight after instruction :)
            printf("WRITE = %d\n\n", WRITE);
            //////////////////////////////
            writeBuffer[0] = WRITE;
            writeByte(hSerial, writeBuffer);
            ready = 0;
            init_time();
        }
    }
}

    writeBuffer[0] = 0;

    writeByte(hSerial, writeBuffer);

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


void init_spam_time(){
    t_spam = clock();
}

double get_spam_time(){
    return ((double) (clock() - t_spam) / CLOCKS_PER_SEC);
}

void init_time()
{
    t_start = clock();
}

double get_time()
{
    return ((double) (clock() - t_start) / CLOCKS_PER_SEC);
}

int decide_instruction(int signal_in, HANDLE hSerial)
{
    static int signal_out;

    switch(signal_in)
    {
        case 0: //"00000000" -> clear
            signal_out = 0;
            break;

        case 9: //"00001001" -> mine
            printf("MIIINEEEEEE!!!!\n");
            recheckRoute(steps);
            list = head;
            if (list->c == 'r')
            {
                signal_out = 6;
            }
            else if (list->c == 'l')
            {
                signal_out = 3;
            }
            else if (list->c == 's')
            {
                signal_out = 1;
            }
            if(list->next!=NULL){
                list = list->next;
            }
            steps = 1;
            //Go to next place in route
            break;

        case 6: //"00000110" -> crossing, corner state, endpoint
            printf("list: %c\n", list->c);

            if (list->c == 'r')
            {
                signal_out = 6;
            }
            else if (list->c == 'l')
            {
                signal_out = 3;
            }
            else if (list->c == 's')
            {
                signal_out = 1;
            }
            if(list->next!=NULL){
                list = list->next;
            }
            steps+= 2;
            break;

        case 10: //"00001010" ->Receiving error
            break; //Signal_out is not changed

        default:
            signal_out = 0;
            break;
    }

    return signal_out;
}

void clearBuf(){
    byteBuffer[0] = 0;
}