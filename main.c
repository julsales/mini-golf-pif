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

void menuinit();

void printbola(int nextX, int nextY);

void printburaco(struct buraco *bur,int x, int y, int raio);

void moverbola();

int main(void) {
    static int ch = 0;
    screenInit(20);
    keyboardInit();
    timerInit(60);
    menuinit();
    if (keyhit()) {
        ch = getchar();
        screenClear();
        screenInit(1);
        screenSetColor(WHITE, DARKGRAY);
        screenGotoxy(x-4, y);
        printf("Selecione o modo de jogo");
        screenGotoxy(x-4, y+1);
        printf("Opção - 1");
        screenGotoxy(x-4, y+2);
        printf("Opção - 2");
        struct buraco *bur = (struct buraco *) malloc(2 * sizeof(struct buraco));
        ch = getchar();
            switch (ch) {
                case '1':
                    screenInit(1);
                    printbola(x, y);
                    printburaco(&bur[0], 5, 10, 1);
                    printburaco(&bur[1], 5, 20, 1);
                    ch = getchar();
                case '2':
                    screenInit(1);
                    printbola(x, y);
                    printburaco(&bur[0], 5, 10, 1);
                    printburaco(&bur[1], 5, 20, 1);
                    ch = getchar();
                default:
                    screenGotoxy(x-4,y+3);
                    printf("Digite uma opção válida");
                    ch=getchar();
            }
            free(bur);
        }
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
    screenSetColor(RED, DARKGRAY);
    bur-> x = x;
    bur -> y = y;
    bur->raio = raio;
    int i;
    int j;
    for ( i = y - raio; i <= y + raio; i++) {
        for (j = x - raio; j <= x + raio; j++) {
            if ((x - j) * (x - j) + (y - i) * (y - i) <= raio * raio) {
                screenGotoxy(j, i);
                printf("-");
            }

        }
    }
    screenGotoxy(j-2, i-4);
    printf("⚐");
    screenSetColor(WHITE, DARKGRAY);
}

void menuinit(){
    screenGotoxy(x, y);
    screenSetColor(RED, DARKGRAY);
    printf("MINI GOLF");
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(25, 22);
    screenSetBlink();
    printf("[SELECT ANY KEY TO CONTINUE]");
    screenGotoxy(26, 23);
    printf("                               ");
    screenSetNormal();
}
