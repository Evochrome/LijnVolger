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
void writeFor(int direction, double seconds, HANDLE hSerial);
//void writeFor_Start(int direction, double seconds, HANDLE hSerial);
void clearBuf();
clock_t t_start;
clock_t t_spam;
double t_line = 3.6; //seconds required to drive a straight line
double t_turn = 1.0; //seconds required to make a turn
double t_back = 5.0; //seconds required to turn around at a mine
double t_req = 3.6; //seconds required until he next crossing (calculated with the above constants)
int READ;
int start = 0, atCrossing = 0;


int main()
{
    byteBuffer[0] = '0';
    writeBuffer[0] = '0';
    int WRITE;


    //Initialization of maze.
    initMinOnes(); //Generate grid of -1's
    nameMaze(); //Generate maze's not -1 values
    assignStations(); //Add station names


    //Post initialization events here.
    //blockEdges();   //Find out what edges/crossings need to be blocked.
    router();       //Lee's algorithm.
    list = head;

    //Xbee initialization.
    HANDLE hSerial = NULL;
    hSerial = initXbee(hSerial);

    //list = list->next; //One ahead of list. Necessary?

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
    if(list->c == 's')
        writeFor(1, 2.0, hSerial);
    else if (list->c == 'l')
        writeFor(3, 2.0, hSerial);
    else if (list->c == 'r')
        writeFor(6, 2.0, hSerial);
    printf("\nI RESET\n\n");
    //init_time(); //Needs to be timed correctly
    list = list->next;


    //Main loop of the program.
    while(programStatus)
    {



    //scanf("%d", &READ); //Temporary user input.

    if (list->next == NULL)
        programStatus = 0;

    READ = readByte(hSerial, byteBuffer);

    printf("READ = %d\n", READ);

    //scanf("%d", &READ); //Temporary user input.

    if(READ == 4){
        if(list->c == 's')
            writeFor(1, 10.0, hSerial);
        else if (list->c == 'l')
            writeFor(3, 10.0, hSerial);
        else if (list->c == 'r')
            writeFor(6, 10.0, hSerial);
        init_time();
        list = list->next;
    }
    WRITE = decide_instruction(READ, hSerial);

    printf("WRITE = %d\n\n", WRITE);
    //////////////////////////////

    writeBuffer[0] = WRITE;

    writeByte(hSerial, writeBuffer);

    clearBuf();
    //displayMaze();
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
    double t_elapsed = get_time();

    if(start){
        init_time();
        start = 0;
        printf("INIT TIME!");
    }

//    if(list->v==1){
//        t_req = 1.5;
//        printf("\n\nENDPOINT!!!!!!!\n\n");
//    }else{
        t_req = t_line;
//    }

    if(t_elapsed>0.75*t_req){
            printf("DO SOMETHING @time= %f\n", t_elapsed);
        if(list->c == 's'){
            writeFor(1, t_line-t_elapsed + 3.0, hSerial);
            signal_out = 1;
        }
        else if (list->c == 'l'){
            writeFor(3, t_line-t_elapsed + 3.0, hSerial);
            signal_out = 3;
        }
        else if (list->c == 'r'){
            writeFor(6, t_line-t_elapsed + 3.0, hSerial);
            signal_out = 6;
        }

        /*while(signal_in != 1)
        {
            READ = readByte(hSerial, byteBuffer);
            if(READ!=6||READ!=9||READ!=3||READ!=4)
                signal_in = 1;
        }

        init_time();*/
        list = list->next;
    }else{
        signal_out = 1;
    }


    return signal_out;
}

void writeFor(int direction, double seconds, HANDLE hSerial)
{
    double t_elapsed = 0.0;
    init_spam_time();
    writeBuffer[0] = direction;

    while(t_elapsed < seconds)
    {
        clearBuf();
        READ = readByte(hSerial, byteBuffer);
        printf("READ = %d\nSpam: %d\n@time= %f\n", READ, direction, t_elapsed);
        printf("WRITE = %d\n\n", direction);
        writeByte(hSerial, writeBuffer);
        t_elapsed = get_spam_time();
        if(READ==6){
            atCrossing = 1;
        }
        printf("At crossing: %d, READ = %d\n", atCrossing, READ);
        if(atCrossing && (READ==3)){
            break;
        }

    }
    init_time();
    atCrossing = 0;

}

/*void writeFor_Start(int direction, double seconds, HANDLE hSerial)
{
    double t_elapsed = 0.0;
    init_spam_time();

    while(t_elapsed < seconds)
    {
        clearBuf();
        READ = readByte(hSerial, byteBuffer);
        writeBuffer[0] = direction;
        printf("Spam: %d\n", direction);
        writeByte(hSerial, writeBuffer);
        t_elapsed = get_spam_time();


    }

}*/

void clearBuf(){
    byteBuffer[0] = 0;
}
