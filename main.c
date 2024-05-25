//mini golf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"

int x = 34, y = 12;
int incX = 1, incY = 1;

int player1 = 0;
int player2 = 0;

struct buraco{
    int x;
    int y;
    int raio;
};

void printbola(int nextX, int nextY);

void printburaco(struct buraco *bur,int x, int y, int raio);


int main(void) {
    static int ch = 0;
    screenInit(20);
    keyboardInit();
    timerInit(60);

    screenGotoxy(x,y);
    screenSetColor(RED, DARKGRAY);
    printf("Mini Golf");
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(25, 22);
    printf("[SELECT ANY KEY TO CONTINUE]");
    screenGotoxy(26, 23);
    printf("                               ");
    ch=getchar();
    screenClear();
    struct buraco *bur = (struct buraco*)malloc(2 * sizeof(struct buraco));
    screenInit(20);
    printbola(x,y);
    printburaco(&bur[0],5, 10, 1);
    printburaco(&bur[1],5, 20, 1);
    ch=getchar();
    free(bur);
}

void printbola(int nextX, int nextY) {
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(x, y);
    printf(" ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("⬤");
}

void printburaco(struct buraco *bur,int x, int y, int raio) {
    screenSetColor(BROWN, DARKGRAY);
    bur-> x = x;
    bur -> y = y;
    bur->raio = raio;
    for (int i = y - raio; i <= y + raio; i++) {
        for (int j = x - raio; j <= x + raio; j++) {
            if ((x - j) * (x - j) + (y - i) * (y - i) <= raio * raio) {
                screenGotoxy(j, i);
                printf("__");
            }
        }
    }
    screenSetColor(WHITE, DARKGRAY);
}