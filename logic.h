#ifndef _LOGIC__H
#define _LOGIC__H
#include "graphics.h"

struct Tictactoe {

    int board[ROW][COL];
    int card[ROW][COL];

    int count;
    int preN, preM;
    bool k ;
    int number;

    void init() {
        count = 1;
        k = false;
        number = 0;
        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                board[i][j] = 0;
                card[i][j]=0;
            }
        }
        for (int i=1; i<=PAIR; i++) {
            int n, m;
            for (int j = 0; j < 2; j++) {
                do {
                    n = rand() % ROW;
                    m = rand() % COL;
                } while (card[n][m] != 0);
                card[n][m] = i;
            }
        }
    }

    void move(int x, int y) {
        int n = (x-BOARD_X) / DISTANCE;
        int m = (y-BOARD_Y) / DISTANCE;

        if(n<0 || n>=ROW || m<0 || m>=COL) return;

        int minX = BOARD_X + n * DISTANCE;
        int minY = BOARD_Y + m * DISTANCE;
        if (x >= minX && x <= (minX + CELL_SIZE)
         && y >= minY && y <= (minY + CELL_SIZE)
         && card[m][n] != -1) {
                if(count == 2 && (n!= preN || m!= preM)) {
                    board[m][n] = card[m][n];
                    k = true;
                    count = 1;
                } else if(count == 1) {
                    count = 2;
                    preN = n;
                    preM = m;
                    board[m][n] = card[m][n];
                }
        }
    }

    void move1(int x, int y) {
        int n = (x-BOARD_X) / DISTANCE;
        int m = (y-BOARD_Y) / DISTANCE;
        if(card[m][n] == card[preM][preN]) {
            board[preM][preN] = -1;
            board[m][n] = -1;
            card[preM][preN] = -1;
            card[m][n] = -1;
            number++;
        }
        else {
            board[preM][preN] = 0;
            board[m][n]= 0;
        }
    }
};

#endif
