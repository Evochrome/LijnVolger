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
    countEdgeX = countEdgeY = countX = countY = 0;
    for(x = 0; x < N; x++) {
        for(y = 0; y < N; y++) {
            if(!(x % 2) && x >= (firstOffset) && x <= (lastOffset)) {
                maze[x][y].v = 0;
                sprintf(maze[x][y].name, "");
            }else if(!(y % 2) && y >= (firstOffset) && y <= (lastOffset)) {
                maze[x][y].v = 0;
                sprintf(maze[x][y].name, "");
            }else if (x >= (firstOffset-2) && x <= (lastOffset+2) && y>=(firstOffset-2) && y <= (lastOffset+2)){
                if (!(x % 2)){
                    maze[x][y].v = 0;
                    sprintf(maze[x][y].name, "");
                }else if(!(y % 2)){
                    maze[x][y].v = 0;
                    sprintf(maze[x][y].name, "");
                }
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
    if (mine_head->next != NULL) {
        block *mines = mine_head;
        while (mines->next != NULL) {
            mines = mines->next;
            maze[mines->x][mines->y].v = -1;
        }
    }
}

void initialize_blocks()
{
    mine_head = (block*)malloc(sizeof(block));
    mine_head->next = NULL;
}

void blockEdges(int x, int y) {
    maze[x][y].v = -1;
    block *mines = mine_head;
    block *new = (block*)malloc(sizeof(block));
    new->next = NULL;
    new->x = x;
    new->y = y;
    if (mine_head->next != NULL)
    {
        while (mines->next != NULL)
        {
            mines = mines->next;
        }
        mines->next = new;
    }
    else
    {
        mine_head->next = new;
    }
}

void display_mines()
{
    block *mines = mine_head;
    while (mines->next != NULL) {
        mines = mines->next;
        printf("The mine position is: (%d, %d)\n", mines->x, mines->y);
    }
}


void displayMaze() {
    int i, j;

    for(i = 0; i < 13; i++)
    {
        for(j = 0; j <= 13; j++)
        {
            if(maze[j][i].v != -1)
            {
                printf("%4d\t", maze[j][i].v);
            }
            else
            {
                printf("\t");
            }
        }
        printf("\n");
    }
}

