#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"

int x = 34, y = 12;
int incX = 1, incY = 1;

struct player{
    char nome[21];
    int score;
};

struct buraco {
    int x;
    int y;
    int raio;
};

void menuinit();
void printbola(int nextX, int nextY);
void printburaco(struct buraco *bur, int x, int y, int raio);
void apagarburaco(struct buraco *bur);
void moveBall(char direction);

int main(void) {
    int ch = 0;
    screenInit(20);
    keyboardInit();
    timerInit(60);
    menuinit();

    if (keyhit()) {
        ch = getchar();
        screenClear();
        screenInit(1);
        screenSetColor(WHITE, DARKGRAY);
        screenGotoxy(x - 4, y);
        printf("Selecione o modo de jogo");
        screenGotoxy(x - 4, y + 1);
        printf("Opção - 1");
        screenGotoxy(x - 4, y + 2);
        printf("Opção - 2");

        struct buraco *bur = (struct buraco *) malloc(2 * sizeof(struct buraco));
        ch = getchar();

        switch (ch) {
            case '1':
            case '2':
                screenInit(1);
                printbola(x, y);
                printburaco(&bur[0], 5, 10, 1);
                printburaco(&bur[1], 5, 20, 1);
                while (1) {
                    if (keyhit()) {
                        ch = getchar();
                        moveBall(ch);
                    }
                }
                break;
            default:
                screenGotoxy(x - 4, y + 3);
                printf("Digite uma opção válida");
                ch = getchar();
        }
        free(bur);
    }
    return 0;
}

void menuinit() {
    int x1 = 10;
    int y1 = 8;
    screenGotoxy(x1, y1);
    screenSetColor(WHITE, DARKGRAY);
    printf("███╗░░░███╗██╗███╗░░██╗██╗  ░██████╗░░█████╗░██╗░░░░░███████╗");
    screenGotoxy(x1, y1+1);
    printf("████╗░████║██║████╗░██║██║  ██╔════╝░██╔══██╗██║░░░░░██╔════╝");
    screenGotoxy(x1, y1+2);
    printf("██╔████╔██║██║██╔██╗██║██║  ██║░░██╗░██║░░██║██║░░░░░█████╗░░");
    screenGotoxy(x1, y1+3);
    printf("██║╚██╔╝██║██║██║╚████║██║  ██║░░╚██╗██║░░██║██║░░░░░██╔══╝░░");
    screenGotoxy(x1, y1+4);
    printf("██║░╚═╝░██║██║██║░╚███║██║  ╚██████╔╝╚█████╔╝███████╗██║░░░░░");
    screenGotoxy(x1, y1+5);
    printf("╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝  ░╚═════╝░░╚════╝░╚══════╝╚═╝░░░░░");
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(25, 22);
    screenSetBlink();
    printf("[SELECT ANY KEY TO CONTINUE]");
    screenGotoxy(26, 23);
    printf("                               ");
    screenSetNormal();
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

void printburaco(struct buraco *bur, int x, int y, int raio) {
    screenSetColor(RED, DARKGRAY);
    bur->x = x;
    bur->y = y;
    bur->raio = raio;
    int i, j;
    for (i = y - raio; i <= y + raio; i++) {
        for (j = x - raio; j <= x + raio; j++) {
            if ((x - j) * (x - j) + (y - i) * (y - i) <= raio * raio) {
                screenGotoxy(j, i);
                printf("-");
            }
        }
    }
    screenGotoxy(j - 2, i - 4);
    printf("⚐");
    screenSetColor(WHITE, DARKGRAY);
}

void apagarburaco(struct buraco *bur) {
    int x = bur->x;
    int y = bur->y;
    int raio = bur->raio;
    int i, j;
    for (i = y - raio; i <= y + raio; i++) {
        for (j = x - raio; j <= x + raio; j++) {
            if ((x - j) * (x - j) + (y - i) * (y - i) <= raio * raio) {
                screenGotoxy(j, i);
                printf(" ");
            }
        }
    }
    screenGotoxy(x, y);
    printf(" ");
    screenSetColor(WHITE, DARKGRAY);  // Restore the default text color
}

void moveBall(char direcao) {
    int nextX = x;
    int nextY = y;
    switch (direcao) {
        case 'w':
            nextY = y - incY;

            break;
        case 'a':
            nextX = x - incX;

            break;
        case 's':

            nextY = y + incY;
            break;
        case 'd':

            nextX = x + incX;
            break;
    }
    printbola(nextX, nextY);
    screenUpdate();
}
