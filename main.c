//mini golf

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"

int x = 34, y = 12;
int incX = 1, incY = 1;

int player1 = 0;
int player2 = 0;

void printbola(int nextX, int nextY);

void printburaco(int x, int y, int raio);

int main(void) {
    static int ch = 0;
    screenInit(20);
    keyboardInit();
    timerInit(50);
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
    screenInit(20);
    printbola(x,y);
    printburaco(5, 10, 1);
    ch=getchar();
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

void printburaco(int x, int y, int raio) {
    screenSetColor(BROWN, DARKGRAY);
    for (int i = y - raio; i <= y + raio; i++) {
        for (int j = x - raio; j <= x + raio; j++) {
            if ((x - j) * (x - j) + (y - i) * (y - i) <= raio * raio) {
                screenGotoxy(j, i);
                printf("__");
            }
        }
    }
    screenSetColor(WHITE, DARKGRAY);
