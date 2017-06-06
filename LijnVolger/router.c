#include <stdio.h>
#include <string.h>
#include "router.h"

void router()
{
    coords startPos, endPos;
    char startChar[8], endChar[8];

    do
    {
        scanf("%s%s", endChar, startChar);

        startPos = getCoords(startChar);
        endPos = getCoords(endChar);



        if(startPos.x == -1 || endPos.x == -1)
        {
            printf("One or more positions unknown.\n");
        }
    } while (startPos.x == -1 || endPos.x == -1);

    spread(endPos, startPos);
    traceBack(endPos, startPos);
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
    if(maze[x+1][y].v == 0)
    {
        maze[x+1][y].v = i+1;
    }

    if(maze[x-1][y].v == 0)
    {
        maze[x-1][y].v = i+1;
    }

    if(maze[x][y+1].v == 0)
    {
        maze[x][y+1].v = i+1;
    }

    if(maze[x][y-1].v == 0)
    {
        maze[x][y-1].v = i+1;
    }
}

int find_nearest_point(char* point1, char* point2, char* point3){
    int minVal = 30, nearest, x, y;
    for(x=0; x<13; x+=12){
        for(y=0; y<13; y++){
            if(strcmp(maze[x][y].name, point1)==0) {
                if (maze[x][y].v < minVal) {
                    minVal = maze[x][y].v;
                    nearest = 1;
                }
            }else if(strcmp(maze[x][y].name, point2)==0){
                if (maze[x][y].v < minVal) {
                    minVal = maze[x][y].v;
                    nearest = 2;
                }
            }else if(strcmp(maze[x][y].name, point3)==0){
                if(maze[x][y].v<minVal){
                    minVal = maze[x][y].v;
                    nearest = 3;
                }
            }
        }
    }

    for(y=0; y<13; y+=12){
        for(x=0; x<13; x++){
            if(strcmp(maze[x][y].name, point1)==0) {
                if (maze[x][y].v < minVal) {
                    minVal = maze[x][y].v;
                    nearest = 1;
                }
            }else if(strcmp(maze[x][y].name, point2)==0){
                if (maze[x][y].v < minVal) {
                    minVal = maze[x][y].v;
                    nearest = 2;
                }
            }else if(strcmp(maze[x][y].name, point3)==0){
                if(maze[x][y].v<minVal){
                    minVal = maze[x][y].v;
                    nearest = 3;
                }
            }
        }
    }
//    printf("\n%d\n", nearest);
    return nearest;
}

void traceBack(coords endPos, coords startPos)
{
    coords currentPos;
    currentPos.x = startPos.x;
    currentPos.y = startPos.y;

    while(!((currentPos.x == endPos.x) && (currentPos.y == endPos.y)))
    {
        currentPos = checkSurroundings(currentPos);
    }

    printf("%s\n", maze[currentPos.x][currentPos.y].name);
    printf("\n%d\n", find_nearest_point("12", "10", "3"));
}

coords checkSurroundings(coords curPos)
{
    if(maze[curPos.x + 1][curPos.y].v == maze[curPos.x][curPos.y].v - 1)
    {
        if(!((curPos.x % 2 == 1) || (curPos.y % 2 == 1)))
            printf("%s ", maze[curPos.x][curPos.y].name);
        curPos.x++;
        return curPos;
    }

    if(maze[curPos.x - 1][curPos.y].v == maze[curPos.x][curPos.y].v - 1)
    {
        if(!((curPos.x % 2 == 1) || (curPos.y % 2 == 1)))
            printf("%s ", maze[curPos.x][curPos.y].name);
        curPos.x--;
        return curPos;
    }

    if(maze[curPos.x][curPos.y + 1].v == maze[curPos.x][curPos.y].v - 1)
    {
        if(!((curPos.x % 2 == 1) || (curPos.y % 2 == 1)))
            printf("%s ", maze[curPos.x][curPos.y].name);
        curPos.y++;
        return curPos;
    }

    if(maze[curPos.x][curPos.y-1].v == maze[curPos.x][curPos.y].v - 1)
    {
        if(!((curPos.x % 2 == 1) || (curPos.y % 2 == 1)))
        {
            printf("%s ", maze[curPos.x][curPos.y].name);
        }

        curPos.y--;
        return curPos;
    }

    return curPos;
}
