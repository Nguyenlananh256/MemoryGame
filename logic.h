#ifndef _LOGIC__H
#define _LOGIC__H
#include "graphics.h"

#define BOARD_SIZE 4

struct Tictactoe {

    int board[4][4];
    int card[4][4];

    int count;
    int preN, preM;
    bool k ;
    int number;

    void init() {
        count =1;
        k = false;
        number = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                board[i][j] = 0;
                card[i][j]=0;
            }
        }
        for (int i=1; i<=8; i++) {
            int n, m;
            for (int j = 0; j < 2; j++) {
                do {
                    n = rand() % 4;
                    m = rand() % 4;
                } while (card[n][m] != 0);
                card[n][m] = i;
            }
        }
    }

    void move(int x, int y) {
        int n = (x-BOARD_X) / CELL_SIZE;
        int m = (y-BOARD_Y) / CELL_SIZE;

        if(n<0 || n>=4 || m<0 || m>4) return;

        int minX = BOARD_X + n * CELL_SIZE;
        int minY = BOARD_Y + m * CELL_SIZE;
        if (x >= minX && x <= (minX + 150)
         && y >= minY && y <= (minY + 150)
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
        int n = (x-BOARD_X) / CELL_SIZE;
        int m = (y-BOARD_Y) / CELL_SIZE;
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
