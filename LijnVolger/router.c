#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "router.h"
#include "maze.h"


void router()
{
    int i, j, nearestPoint = 0;
    coords startPos, endPos[3];
    char startChar[8], endChar[3][8];
    mine_found = 0;

    do {

        scanf("%s%s%s%s", startChar, endChar[0], endChar[1], endChar[2]);
        startPos = getCoords(startChar);
        endPos[0] = getCoords(endChar[0]);
        endPos[1] = getCoords(endChar[1]);
        endPos[2] = getCoords(endChar[2]);
        ends_reached = 0;

        coordinatepoints[0][0] = startPos.x;
        coordinatepoints[1][0] = startPos.y;

        if((endPos[0].x == -1) || (startPos.x == -1) || (endPos[1].x == -1) || (endPos[2].x == -1))
        {
            printf("One or more positions unknown.\n");
        }
    } while ((endPos[0].x == -1) || (startPos.x == -1) || (endPos[1].x == -1) || (endPos[2].x == -1));

    for(i=0+ends_reached; i<3; i++) {
        for(j = 0; j<3; j++) {
            if(strcmp(endChar[j], "13")!=0) {
                spread(startPos, endPos[j]);                //doesn't matter which position is chosen
                break;//from loop                           // as long as it's not already been visited
            }
        }
        nearestPoint = find_nearest_point(endChar[0], endChar[1], endChar[2]);

        //Re-initialization of maze.
        nameMaze();         //Generate maze's not -1 values
        assignStations();   //Add station names

        //The right order of end points is read into the mine rerouter
        coordinatepoints[0][i + 1] = endPos[nearestPoint].x;
        coordinatepoints[1][i + 1] = endPos[nearestPoint].y;


        //Create lee map
        spread(endPos[nearestPoint], startPos);

        //Get route by tracing backwards
        traceBack(endPos[nearestPoint], startPos);
        //Does not exist, so will not come up in results anymore
        sprintf(endChar[nearestPoint], "14");

        startPos = endPos[nearestPoint];

        //Re-initialization of maze.
        nameMaze();         //Generate maze's not -1 values
        assignStations();   //Add station names
    }
}

void rerouter()
{
    int i;
    coords startPos, endPos[3];

    startPos = Start_point;
    for (i = 0; i < ends_reached; i++)
    {
        endPos[i].x = 15;
        endPos[i].y = 15;
    }
    for (i = ends_reached; i < 3; i++)
    {
        endPos[i].x = coordinatepoints[0][i + 1];
        endPos[i].y = coordinatepoints[1][i + 1];
    }
    printf("I found the rerouter.\n");
    coordinatepoints[0][0] = startPos.x;
    coordinatepoints[1][0] = startPos.y;


    for(i=0+ends_reached; i<3; i++) {

        //Re-initialization of maze.
        nameMaze();         //Generate maze's not -1 values
        assignStations();   //Add station names

        //Create lee map
        spread(endPos[i], startPos);

        //Get route by tracing backwards
        traceBack(endPos[i], startPos);

        startPos = endPos[i];

        //Re-initialization of maze.
        nameMaze();         //Generate maze's not -1 values
        assignStations();   //Add station names
    }
    display_mines();
}

void spread(coords endPos, coords startPos)
{
    int i, x, y;

    maze[endPos.x][endPos.y].v = 1;

    for(i = 1; maze[startPos.x][startPos.y].v == 0; i++)
    {
        for(x = 0; x < 13; x++)
        {
            for(y = 0; y < 13; y++)
            {
                if(maze[x][y].v == i)
                {
                    setSurroundings(x, y, i);
                }
            }
        }
    }
}

void setSurroundings(int x, int y, int i)
{
    if(x!=12){
        if(maze[x+1][y].v == 0)
        {
            maze[x+1][y].v = i+1;
        }
    }

    if(maze[x-1][y].v == 0)
    {
        maze[x-1][y].v = i+1;
    }

    if(y!=12){
        if(maze[x][y+1].v == 0)
        {
            maze[x][y+1].v = i+1;
        }
    }

    if(maze[x][y-1].v == 0)
    {
        maze[x][y-1].v = i+1;
    }
}

int find_nearest_point(char* point1, char* point2, char* point3){
    int minVal = 30, nearest = 0, x, y;

    for(x=0; x<13; x+=12){
        for(y=0; y<13; y++){
            if(strcmp(maze[x][y].name, point1)==0) {
                if (maze[x][y].v < minVal && maze[x][y].v !=0) {
                    minVal = maze[x][y].v;
                    nearest = 0;
                }
            }else if(strcmp(maze[x][y].name, point2)==0){
                if (maze[x][y].v < minVal && maze[x][y].v !=0) {
                    minVal = maze[x][y].v;
                    nearest = 1;
                }
            }else if(strcmp(maze[x][y].name, point3)==0){
                if(maze[x][y].v < minVal && maze[x][y].v !=0){
                    minVal = maze[x][y].v;
                    nearest = 2;
                }
            }
        }
    }

    for(y=0; y<13; y+=12){
        for(x=0; x<13; x++){
            if(strcmp(maze[x][y].name, point1)==0) {
                if (maze[x][y].v < minVal && maze[x][y].v !=0) {
                    minVal = maze[x][y].v;
                    nearest = 0;
                }
            }else if(strcmp(maze[x][y].name, point2)==0){
                if (maze[x][y].v < minVal && maze[x][y].v !=0) {
                    minVal = maze[x][y].v;
                    nearest = 1;
                }
            }else if(strcmp(maze[x][y].name, point3)==0){
                if(maze[x][y].v < minVal && maze[x][y].v !=0){
                    minVal = maze[x][y].v;
                    nearest = 2;
                }
            }
        }
    }
    return nearest;
}

void traceBack(coords endPos, coords startPos)
{
    coords currentPos, PreCross, Cross;
    currentPos.x = startPos.x;
    currentPos.y = startPos.y;

    initialize_translator();
    Cross.x = 97;
    while(!((currentPos.x == endPos.x) && (currentPos.y == endPos.y)))
    {
        if (mine_found == 1)
        {
            PreCross = mine;
            mine_found = 0;
        }
        else PreCross = Cross;
        Cross = currentPos;
        currentPos = checkSurroundings(currentPos);
        map_translator(PreCross, Cross, currentPos);
    }

    printf("%s\n", maze[currentPos.x][currentPos.y].name);
}

coords checkSurroundings(coords curPos)
{
    if(maze[curPos.x + 1][curPos.y].v == maze[curPos.x][curPos.y].v - 1) {
        if(!((curPos.x % 2 == 1) || (curPos.y % 2 == 1)))
            printf("%s ", maze[curPos.x][curPos.y].name);
        curPos.x++;
        return curPos;
    }

    else if(maze[curPos.x - 1][curPos.y].v == maze[curPos.x][curPos.y].v - 1) {
        if(!((curPos.x % 2 == 1) || (curPos.y % 2 == 1)))
            printf("%s ", maze[curPos.x][curPos.y].name);
        curPos.x--;
        return curPos;
    }

    else if(maze[curPos.x][curPos.y + 1].v == maze[curPos.x][curPos.y].v - 1) {
        if(!((curPos.x % 2 == 1) || (curPos.y % 2 == 1)))
            printf("%s ", maze[curPos.x][curPos.y].name);
        curPos.y++;
        return curPos;
    }

    else if(maze[curPos.x][curPos.y-1].v == maze[curPos.x][curPos.y].v - 1) {
        if(!((curPos.x % 2 == 1) || (curPos.y % 2 == 1)))
        {
            printf("%s ", maze[curPos.x][curPos.y].name);
        }

        curPos.y--;
        return curPos;
    }
    return curPos;
}


void initialize_translator()
{
    head = (nav*)malloc(sizeof(nav));
    head->next = NULL;
}


void map_translator(coords LastPos, coords CurPos, coords NextPos)
{
    if (strncmp(maze[CurPos.x][CurPos.y].name, "c", 1) == 0 && LastPos.x != 97 && CurPos.x != 97) {
        nav *list = head;
        nav *new = (nav*)malloc(sizeof(nav));
        new->next = NULL;
        if (head->next != NULL) {
            while (list->next != NULL) {
                list = list->next;
            }
        }
        list->next = new;
        if (CurPos.x > LastPos.x) {
            if (NextPos.y < CurPos.y) list->c = 'l';
            else if (NextPos.x > CurPos.x) list->c = 's';
            else if (NextPos.y > CurPos.y) list->c = 'r';
            else printf("Direction algorithm failed in directing to the next position, driving to the right side of the grid.\n");
        } else if (CurPos.y > LastPos.y) {
            if (NextPos.x > CurPos.x) list->c = 'l';
            else if (NextPos.y > CurPos.y) list->c = 's';
            else if (NextPos.x < CurPos.x) list->c = 'r';
            else printf("\nDirection algorithm failed in directing to the next position, driving to the bottom of the grid.\n");
        } else if (CurPos.x < LastPos.x) {
            if (NextPos.y > CurPos.y) list->c = 'l';
            else if (NextPos.x < CurPos.x) list->c = 's';
            else if (NextPos.y < CurPos.y) list->c = 'r';
            else printf("\nDirection algorithm failed in directing to the next position, driving to the left side of the grid.\n");
        } else if (CurPos.y < LastPos.y) {
            if (NextPos.x < CurPos.x) list->c = 'l';
            else if (NextPos.y < CurPos.y) list->c = 's';
            else if (NextPos.x > CurPos.x) list->c = 'r';
            else printf("\nDirection algorithm failed in directing to the next position, driving to the top of the grid.\n");
        } else printf("\nDirection algorithm failed in determining the current direction.\n");
    }
};

void recheckRoute(int steps)
{
    coords block;
    block = tracePos(steps);
    blockEdges(block.x, block.y);
    mine.x = x;
    mine.y = y;
    mine_found = 1;
    rerouter();
}

coords tracePos(int steps)
{
    coords currentPos, endPos, startPos;
    int i, j = 0;

    currentPos.x = coordinatepoints[0][0];
    currentPos.y = coordinatepoints[1][0];
    startPos.x = coordinatepoints[0][0];
    startPos.y = coordinatepoints[1][0];

    for (i = 1; i < 4; i++)
    {
        endPos.x = coordinatepoints[0][i];
        endPos.y = coordinatepoints[1][i];
        nameMaze();         //Generate maze's not -1 values
        assignStations();   //Add station names
        spread(endPos, startPos);
        while(!((currentPos.x == endPos.x) && (currentPos.y == endPos.y)))
        {
            Start_point = currentPos; //Makes sure the last point is recorded as the new startpoint
            currentPos = checkSurroundings(currentPos);
            j++;
            if (j == steps) return currentPos;
        }
        ends_reached++;
    }
}