#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"

int N = 13;

void initMinOnes() {
    int i, j;

    for(i = 0; i < 13; i++)
    {
        for(j = 0; j < 13; j++)
        {
            maze[i][j].v = -1;
        }
    }
}

void assignStations() {
    int stationNum = 0;

    for(x = firstOffset; x <= lastOffset; x++) {
        if(!(x%2)) {
            stationNum++;
            sprintf(maze[x][N-1].name, "%d", stationNum);
            stations[stationNum].x = 0;
            stations[stationNum].y = x;
        }
    }

    for(y = lastOffset; y >= firstOffset; y--) {
        if(!(y%2)) {
            stationNum++;
            sprintf(maze[N-1][y].name, "%d", stationNum);
            stations[stationNum].x = y;
            stations[stationNum].y = 0;
        }
    }

    for(x = lastOffset; x >= firstOffset; x--) {
        if(!(x%2)) {
            stationNum++;
            sprintf(maze[x][0].name, "%d", stationNum);
            stations[stationNum].x = (N-1);
            stations[stationNum].y = x;
        }
    }

    for(y = firstOffset; y <= lastOffset; y++) {
        if(!(y%2)) {
            stationNum++;
            sprintf(maze[0][y].name, "%d", stationNum);
            stations[stationNum].x = y;
            stations[stationNum].y = (N-1);
        }
    }
}

void nameMaze() {
    middleLine = (N - 1) / 2;
    firstOffset = middleLine - 2;
    lastOffset = middleLine + 2;
    for(x = 0; x < N; x++) {
        for(y = 0; y < N; y++) {
            if(!(x % 2) && x >= (firstOffset-2) && x <= (lastOffset+2)) {
                maze[x][y].v = 0;
                sprintf(maze[x][y].name, "");
            }else if(!(y % 2) && y >= (firstOffset-2) && y <= (lastOffset+2)) {
                maze[x][y].v = 0;
                sprintf(maze[x][y].name, "");
            }else {
                maze[x][y].v = -1;
                sprintf(maze[x][y].name, "");
            }
            if(!(y%2) && !(x%2) && x >= (firstOffset -2) && y >= (firstOffset -2) && x <= (lastOffset +2) && y <= (lastOffset+2)) {
                sprintf(maze[x][y].name, "c%d%d", countX, countY);
                countY++;
            }

            if(((y%2) ^ (x%2)) && x >= (firstOffset -2) && y >= (firstOffset -2) && x <= (lastOffset +2) && y <= (lastOffset+2)) {
                if(x%2) {
                    /* column is odd */
                    sprintf(maze[x][y].name, "e%d%d%d%d", (countEdgeX - 1), countEdgeY, (countEdgeX), countEdgeY);
                }else {
                    sprintf(maze[x][y].name, "e%d%d%d%d", countEdgeX, countEdgeY, countEdgeX, (countEdgeY + 1));
                }
                countEdgeY++;
            }
        }
        countY = 0;
        countEdgeY = 0;

        if(!(x%2) && x >= (firstOffset -2) && x <= (lastOffset +2)) {
            countX++;
            countEdgeX++;
        }
    }
//    sprintf(maze[firstOffset-2][firstOffset-2].name, "test");
    printf("\n middleline: %d\n firstOffset: %d\n lastOffset: %d\n", middleLine, firstOffset, lastOffset);
}

void blockEdges() {
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


void displayMaze() {
    int i, j;

    for(i = 0; i < 13; i++)
    {
        for(j = 0; j < 13; j++)
        {
            if(maze[j][i].v != -1)
            {
                printf("%3d\t", maze[j][i].v);
            }
            else
            {
                printf("\t");
            }
        }
        printf("\n");
    }
}

