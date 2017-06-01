#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct cell {
    int v;
    char name[8];
};
struct stations {
    int c;
    int r;
};

int noLines = 3, midLine = 0, firstOffset = 0, lastOffset = 0, numOfPoints = 2, r, c, countR = 0, countC = 0, countEdgeR = 0 , countEdgeC = 0, stations, mineNum, i, j, k, station[3];
const int N = 13;
struct cell maze[13][13];

void find_route(int sr, int sc, int er, int ec);
int wayUp(int pointR, int pointC, int er, int ec, char *printString);
int wayDown(int pointR, int pointC, int er, int ec, char *printString);
int wayLeft(int pointR, int pointC, int er, int ec, char *printString);
int wayRight(int pointR, int pointC, int er, int ec, char *printString);


int lowestAroundPoint(int r, int c) {
    int lowest, b, t, l, ri;
    lowest = 999;
    /* values around */
    b = r < N ? maze[r - 1][c].v : -1;
    t = r > 0 ? maze[r + 1][c].v : -1;
    l = c > 0 ? maze[r][c - 1].v : -1;
    ri = c < N ? maze[r][c + 1].v : -1;

    if(b <= lowest && b > 0) {
        lowest = b;
    }
    if(t <= lowest && t > 0) {
        lowest = t;
    }
    if(l <= lowest && l > 0) {
        lowest = l;
    }
    if(ri <= lowest && ri > 0) {
        lowest = ri;
    }
    return lowest == 999 ? 0 : lowest;
}

int wayUp(int pointR, int pointC, int er, int ec, char *printString){
    int up, down, left, right;
    char printRoute[60];
    if(pointR+2<=12) {
        if ((maze[pointR + 1][pointC].v != -1) && (maze[pointR][pointC].v > maze[pointR + 1][pointC].v)) {
            pointR += 2;
            sprintf(printRoute, "%s %s", printString, maze[pointR][pointC].name);
            if (pointC == ec && pointR == er) {
                printf("%s\n", printRoute);
                return 1;
            }
            up = wayUp(pointR, pointC, er, ec, printRoute);
            down = wayDown(pointR, pointC, er, ec, printRoute);
            left = wayLeft(pointR, pointC, er, ec, printRoute);
            right = wayRight(pointR, pointC, er, ec, printRoute);
            return (up || down || left || right);
        }else{
            return 0;
        }
    }else{
        return 0;
    }
};

int wayDown(int pointR, int pointC, int er, int ec, char *printString){
    int up, down, left, right;
    char printRoute[60];
    if(pointR-2>=0) {
        if ((maze[pointR - 1][pointC].v != -1) && (maze[pointR][pointC].v > maze[pointR - 2][pointC].v)) {
            pointR -= 2;
            sprintf(printRoute, "%s %s", printString, maze[pointR][pointC].name);
            if (pointC == ec && pointR == er) {
                printf("%s\n", printRoute);
                return 1;
            }
            up = wayUp(pointR, pointC, er, ec, printRoute);
            down = wayDown(pointR, pointC, er, ec, printRoute);
            left = wayLeft(pointR, pointC, er, ec, printRoute);
            right = wayRight(pointR, pointC, er, ec, printRoute);
            return (up || down || left || right);
        }else{
            return 0;
        }
    }else{
        return 0;
    }
};

int wayLeft(int pointR, int pointC, int er, int ec, char *printString){
    int up, down, left, right;
    char printRoute[60];
    if(pointC-2>=0) {
        if ((maze[pointR][pointC - 1].v != -1) && (maze[pointR][pointC].v > maze[pointR][pointC - 2].v)) {
            pointC -= 2;
            sprintf(printRoute, "%s %s", printString, maze[pointR][pointC].name);
            if (pointC == ec && pointR == er) {
                printf("%s\n", printRoute);
                return 1;
            }
            up = wayUp(pointR, pointC, er, ec, printRoute);
            down = wayDown(pointR, pointC, er, ec, printRoute);
            left = wayLeft(pointR, pointC, er, ec, printRoute);
            right = wayRight(pointR, pointC, er, ec, printRoute);
            return (up || down || left || right);
        }else{
            return 0;
        }
    }else{
        return 0;
    }
};

int wayRight(int pointR, int pointC, int er, int ec, char *printString){
    int up, down, left, right;
    char printRoute[60];
    if(pointC+2<=12) {
        if ((maze[pointR][pointC + 1].v != -1) && (maze[pointR][pointC].v > maze[pointR][pointC + 2].v)) {
            pointC += 2;
            sprintf(printRoute, "%s %s", printString, maze[pointR][pointC].name);
            if (pointC == ec && pointR == er) {
                printf("%s\n", printRoute);
                return 1;
            }
            up = wayUp(pointR, pointC, er, ec, printRoute);
            down = wayDown(pointR, pointC, er, ec, printRoute);
            left = wayLeft(pointR, pointC, er, ec, printRoute);
            right = wayRight(pointR, pointC, er, ec, printRoute);
            return (up || down || left || right);
        }else{
            return 0;
        }
    }else{
        return 0;
    }
};

void find_route(int sr, int sc, int er, int ec){
    int lowest = 0, found = 0, count = 0, limit;
    char printString[60] = "\0";

    maze[er][ec].v = 1;
    limit = noLines * 2 * N;
    while(found == 0 && count < limit) {
        count++;
        for(r = 0; r < N; r++) {
            for(c = 0; c < N; c++) {
                lowest = lowestAroundPoint(r, c);
                if((lowest != 0 && maze[r][c].v == 0) || (lowest < (maze[r][c].v - 1) && lowest != 0)) {
                    maze[r][c].v = lowest + 1;
                    if(r == sr && c == sc) {
                        found = 1;
                    }
                }
            }
        }
    }

    for(r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
//            printf("%d\t",maze[r][c].v);
            printf("%s\t", maze[r][c].name);
        }
        printf("\n");
    }

    if(found == 1) {
        /* route */
        sprintf(printString,"%s", maze[sr][sc].name);

        if(!(wayUp(sr, sc, er, ec, printString) || wayDown(sr, sc, er, ec, printString) || wayLeft(sr, sc, er, ec, printString) || wayRight(sr, sc, er, ec, printString))){
            printf("Startpoint is surrounded by mines, OH NO!!");
        }
    }else {
        printf("End point can not be reached because of the mines :(");
    }
}

int main() {
    char tmpEdge[6];

    midLine = (N - 1) / 2;
    firstOffset = midLine - (noLines - 1);
    lastOffset = midLine + (noLines - 1);


    struct stations stationArr[4*noLines];

    for(r = 0; r < N; r++) {
        for(c = 0; c < N; c++) {
            if(!(r % 2) && r >= firstOffset && r <= lastOffset) {
                maze[r][c].v = 0;
                sprintf(maze[r][c].name, "");
            }else if(!(c % 2) && c >= firstOffset && c <= lastOffset) {
                maze[r][c].v = 0;
                sprintf(maze[r][c].name, "");
            }else {
                maze[r][c].v = -1;
                sprintf(maze[r][c].name, "");
            }
            if(!(c%2) && !(r%2) && r >= (firstOffset -2) && c >= (firstOffset -2) && r <= (lastOffset +2) && c <= (lastOffset+2)) {
                sprintf(maze[r][c].name, "c%d%d", countR, countC);
                countC++;
            }

            if(((c%2) ^ (r%2)) && r >= (firstOffset -2) && c >= (firstOffset -2) && r <= (lastOffset +2) && c <= (lastOffset+2)) {
                if(r%2) {
                    /* row is odd */
                    sprintf(maze[r][c].name, "e%d%d%d%d", (countEdgeR - 1) , countEdgeC, (countEdgeR), countEdgeC);
                }else {
                    sprintf(maze[r][c].name, "e%d%d%d%d", countEdgeR, countEdgeC, countEdgeR, (countEdgeC + 1));
                }
                countEdgeC++;
            }


        }
        countC = 0;
        countEdgeC = 0;

        if(!(r%2) && r >= (firstOffset -2) && r <= (lastOffset +2)) {
            countR++;
            countEdgeR++;
        }
        if(r >= firstOffset && r <= lastOffset) {

        }

    }

    for(r = 0; r < N; r++) {
        for(c = 0; c < N; c++) {
            if(c >= firstOffset && c <= lastOffset && !(c % 2) && !(r % 2) && r >= firstOffset && r <= lastOffset) {
                maze[r - 1][c - 2].v = 0;
                maze[r - 2][c - 2].v = 0;
                maze[r - 2][c - 1].v = 0;

                maze[r + 1][c - 2].v = 0;
                maze[r + 2][c - 2].v = 0;
                maze[r + 2][c - 1].v = 0;

                maze[r - 1][c + 2].v = 0;
                maze[r - 2][c + 2].v = 0;
                maze[r - 2][c + 1].v = 0;

                maze[r + 1][c + 2].v = 0;
                maze[r + 2][c + 2].v = 0;
                maze[r + 2][c + 1].v = 0;
            }
        }
    }

    stations = 0;
    /* row = max*/
    for(c = firstOffset; c <= lastOffset; c++) {
        if(!(c%2)) {
            stations++;
            sprintf(maze[N-1][c].name, "%d", stations);
            stationArr[stations].c = c;
            stationArr[stations].r = (N-1);
        }
    }

    for(r = lastOffset; r >= firstOffset; r--) {
        if(!(r%2)) {
            stations++;
            sprintf(maze[r][N-1].name, "%d", stations);
            stationArr[stations].c = (N-1);
            stationArr[stations].r = r;
        }
    }

    for(c = lastOffset; c >= firstOffset; c--) {
        if(!(c%2)) {
            stations++;
            sprintf(maze[0][c].name, "%d", stations);
            stationArr[stations].c = c;
            stationArr[stations].r = 0;
        }
    }

    for(r = firstOffset; r <= lastOffset; r++) {
        if(!(r%2)) {
            stations++;
            sprintf(maze[r][0].name, "%d", stations);
            stationArr[stations].c = 0;
            stationArr[stations].r = r;
        }
    }



    scanf("%d", &mineNum);
    for(i = 0; i < mineNum; i++){
        scanf("%s", tmpEdge);
        for(r = firstOffset -2; r <= lastOffset + 2; r++) {
            for(c = firstOffset - 2; c <= lastOffset + 2; c = c+2) {
                if(c == (firstOffset-2) && !(r%2)){
                    c++;
                }
                if(strcmp(maze[r][c].name,tmpEdge) == 0) {
                    maze[r][c].v = -1;
                }
            }
        }
    }

    scanf("%d %d", &station[1], &station[2]);

    find_route(stationArr[station[1]].r, stationArr[station[1]].c, stationArr[station[2]].r, stationArr[station[2]].c);

    return 0;
}
