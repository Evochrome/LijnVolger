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

void assignStations()
{
    int stationNum = 0;
    for(r = firstOffset; r <= lastOffset; r++) {
        if(!(r%2)) {
            stationNum++;
            sprintf(maze[N-1][r].name, "%d", stationNum);
            stations[stationNum].x = r;
            stations[stationNum].y = (N-1);
        }
    }

    for(c = lastOffset; c >= firstOffset; c--) {
        if(!(c%2)) {
            stationNum++;
            sprintf(maze[c][N-1].name, "%d", stationNum);
            stations[stationNum].x = (N-1);
            stations[stationNum].y = c;
        }
    }

    for(r = lastOffset; r >= firstOffset; r--) {
        if(!(r%2)) {
            stationNum++;
            sprintf(maze[0][r].name, "%d", stationNum);
            stations[stationNum].x = r;
            stations[stationNum].y = 0;
        }
    }

    for(c = firstOffset; c <= lastOffset; c++) {
        if(!(c%2)) {
            stationNum++;
            sprintf(maze[c][0].name, "%d", stationNum);
            stations[stationNum].x = 0;
            stations[stationNum].y = c;
        }
    }

}

void nameMaze()
{
    middleLine = (N - 1) / 2;
    firstOffset = middleLine - 2;
    lastOffset = middleLine + 2;
    for(c = 0; c < N; c++) {
        for(r = 0; r < N; r++) {
            if(!(c % 2) && c >= firstOffset && c <= lastOffset) {
                maze[c][r].v = 0;
                sprintf(maze[c][r].name, "");
            }else if(!(r % 2) && r >= firstOffset && r <= lastOffset) {
                maze[c][r].v = 0;
                sprintf(maze[c][r].name, "");
            }else {
                maze[c][r].v = -1;
                sprintf(maze[c][r].name, "");
            }
            if(!(r%2) && !(c%2) && c >= (firstOffset -2) && r >= (firstOffset -2) && c <= (lastOffset +2) && r <= (lastOffset+2)) {
                sprintf(maze[c][r].name, "r%d%d", countC, countR);
                countR++;
            }

            if(((r%2) ^ (c%2)) && c >= (firstOffset -2) && r >= (firstOffset -2) && c <= (lastOffset +2) && r <= (lastOffset+2)) {
                if(c%2) {
                    /* row is odd */
                    sprintf(maze[c][r].name, "e%d%d%d%d", (countEdgeC - 1) , countEdgeR, (countEdgeC), countEdgeR);
                }else {
                    sprintf(maze[c][r].name, "e%d%d%d%d", countEdgeC, countEdgeR, countEdgeC, (countEdgeR + 1));
                }
                countEdgeR++;
            }
        }
        countR = 0;
        countEdgeR = 0;

        if(!(c%2) && c >= (firstOffset -2) && c <= (lastOffset +2)) {
            countC++;
            countEdgeC++;
        }
    }
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
                printf("%s\t", maze[j][i].name);
            }
            else
            {
                printf("   ");
            }
        }
        printf("\n");
    }
}

