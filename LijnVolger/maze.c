#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"

void initMinOnes()
{
    int i, j;

    for(i = 0; i < 13; i++)
    {
        for(j = 0; j < 13; j++)
        {
            maze[i][j].v = -1;
        }
    }
}

void initZeros()
{
    fillLine(4,0,4,12);
    fillLine(6,0,6,12);
    fillLine(8,0,8,12);

    fillLine(0,4,12,4);
    fillLine(0,6,12,6);
    fillLine(0,8,12,8);

    fillLine(2,2,10,2);
    fillLine(2,10,10,10);
    fillLine(2,2,2,10);
    fillLine(10,2,10,10);
}

void fillLine(int x1, int y1, int x2, int y2)
{
    int x, y;

    for(x = x1; x <= x2; x++)
    {
        for(y = y1; y <= y2; y++)
        {
            maze[x][y].v = 0;
        }
    }
}

void nameMaze(char namesFile[])
{
    char buf[8];
    int x, y;
    FILE *file;
    file = fopen(namesFile, "r");

    for(x = 0; x < 13; x++)
    {
        for(y = 0; y < 13; y++)
        {
            if(maze[y][x].v == 0)
            {
                fscanf(file, "%s", buf);
                strcpy(maze[y][x].name, buf);
            }
        }
    }

    fclose(file);
}

void blockEdges()
{
    int i, n;
    char block[8];
    coords cords;

    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        scanf("%s", block);
        cords = getCoords(block);
        if(cords.x == -1 || cords.y == -1)
        {
            printf("Error coord does not exist on map.\n");
        }
        else
        {
            maze[cords.x][cords.y].v = -1;
        }
    }
}


void displayMaze()
{
    int i, j;

    for(i = 0; i < 13; i++)
    {
        for(j = 0; j < 13; j++)
        {
            if(maze[j][i].v != -1)
            {
                printf("%3d", maze[j][i].v);
            }
            else
            {
                printf("   ");
            }
        }
        printf("\n");
    }
}

