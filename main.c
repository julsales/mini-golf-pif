#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"

#define LARGURA 80
#define ALTURA 24
#define ESPESSURA 2

int x = 34, y = 12;

struct player {
    char nome[21];
    int movimentos;
    int score;
};

struct buraco {
    int x;
    int y;
    int raio;
};


void menuinit();
void desenharParedes();
void printbola(int nextX, int nextY);
void printburaco(struct buraco *bur, int x, int y, int raio);
void apagarburaco(struct buraco *bur);
void moverbola(struct player *ptp ,char direcao);
void animacaobola(int initX, int initY, int endX, int endY);
int calcularForca(int mov);
int colisao(struct buraco *bur, int Ox, int Oy);

int main(void) {
    int ch = 0;
    screenInit(20);
    keyboardInit();
    timerInit(60);
    menuinit();

    if (keyhit()) {
        ch=getchar();
        screenClear();
        screenInit(1);
        screenSetColor(WHITE, DARKGRAY);
        screenGotoxy(x - 4, y);
        printf("Selecione o modo de jogo");
        screenGotoxy(x - 4, y + 1);
        printf("Opção - 1");
        screenGotoxy(x - 4, y + 2);
        printf("Opção - 2");

        struct buraco *bur = (struct buraco *)malloc(2 * sizeof(struct buraco));
        struct player *ptp = (struct player *)malloc(1 * sizeof(struct player));
        ch = getchar();

        switch (ch) {
            case '1':
            case '2':
                screenInit(1);
                desenharParedes();
                printbola(x, y);
                printburaco(&bur[0], 5, 10, 1);
                printburaco(&bur[1], 5, 20, 1);

                int buraco1_acertado = 0;
                int buraco2_acertado = 0;

                while (1) {
                    if (keyhit()) {
                        ch = getchar();
                        moverbola(&ptp[0], ch);
                        if (!buraco1_acertado && colisao(&bur[0], x, y)) {
                            buraco1_acertado = 1;
                            screenGotoxy(0, MAXY + 1);
                            apagarburaco(&bur[0]);
                            screenGotoxy(x, y);
                        }

                        if (!buraco2_acertado && colisao(&bur[1], x, y)) {
                            buraco2_acertado = 1;
                            screenGotoxy(0, MAXY + 2);
                        }

                        if (buraco1_acertado && buraco2_acertado) {
                            screenGotoxy(0, MAXY + 3);
                            printf("Você acertou todos os buracos! Jogo encerrado.\n");
                            break;
                        }
                    }
                }
                break;
            default:
                screenGotoxy(x - 4, y + 3);
                printf("Digite uma opção válida");
                ch = getchar();
        }
        free(ptp);
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
    screenGotoxy(x1, y1 + 1);
    printf("████╗░████║██║████╗░██║██║  ██╔════╝░██╔══██╗██║░░░░░██╔════╝");
    screenGotoxy(x1, y1 + 2);
    printf("██╔████╔██║██║██╔██╗██║██║  ██║░░██╗░██║░░██║██║░░░░░█████╗░░");
    screenGotoxy(x1, y1 + 3);
    printf("██║╚██╔╝██║██║██║╚████║██║  ██║░░╚██╗██║░░██║██║░░░░░██╔══╝░░");
    screenGotoxy(x1, y1 + 4);
    printf("██║░╚═╝░██║██║██║░╚███║██║  ╚██████╔╝╚█████╔╝███████╗██║░░░░░");
    screenGotoxy(x1, y1 + 5);
    printf("╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝  ░╚═════╝░░╚════╝░╚══════╝╚═╝░░░░░");
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(25, 22);
    screenSetBlink();
    printf("[SELECT ANY KEY TO CONTINUE]");
    screenGotoxy(26, 23);
    printf("                               ");
    screenSetNormal();
}

void desenharParedes() {
    int i, j;
    screenSetColor(DARKGRAY, BLACK);
    for (i = 0; i < ESPESSURA; i++) {
        for (j = 1; j < LARGURA - 1; j++) {
            screenGotoxy(j, i);
            printf("■");
            screenGotoxy(j, ALTURA - 1 - i);
            printf("■");
        }
        for (j = 1; j < ALTURA - 1; j++) {
            screenGotoxy(i, j);
            printf("■");
            screenGotoxy(LARGURA - 1 - i, j);
            printf("■");
        }
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
    screenGotoxy(j-2, i-4);
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
    screenGotoxy(j-2, i-4);
    printf(" ");
    screenSetColor(WHITE, DARKGRAY);
}

int calcularForca(int mov) {
    switch (mov) {
        case 1:
            return 1;
        case 2:
            return 3;
        case 3:
            return 5;
        case 4:
            return 7;
        case 5:
            return 9;
        default:
            return 1; // Valor padrão se algo inesperado acontecer
    }
}

void moverbola(struct player *ptp, char direcao) {
    int nextX = x;
    int nextY = y;
    int mov;
    screenGotoxy(2, 4);
    printf("Insira a força do movimento (1-5): ");
    if (scanf("%d", &mov) != 1) {
        return;
    }
    if (mov < 1) {
        mov = 1;
    }
    if (mov > 5) {
        mov = 5;
    }
    int forca = calcularForca(mov);
    screenGotoxy(2, 2);
    printf("Força: %d", forca);
    ptp->movimentos++;
    screenGotoxy(2, 3);
    printf("Movimentos: %d", ptp->movimentos);

    switch (direcao) {
        case 'w':
            nextY = y - forca;
            break;
        case 'a':
            nextX = x - forca;
            break;
        case 's':
            nextY = y + forca;
            break;
        case 'd':
            nextX = x + forca;
            break;
        case 'q':
            nextX = x - forca;
            nextY = y - forca;
            break;  // Movimento diagonal superior esquerdo
        case 'e':
            nextX = x + forca;
            nextY = y - forca;
            break;  // Movimento diagonal superior direito
        case 'z':
            nextX = x - forca;
            nextY = y + forca;
            break;  // Movimento diagonal inferior esquerdo
        case 'c':
            nextX = x + forca;
            nextY = y + forca;
            break;  // Movimento diagonal inferior direito
    }
    if (nextX >= ESPESSURA && nextX < LARGURA - ESPESSURA && nextY >= ESPESSURA && nextY < ALTURA - ESPESSURA) {
        animacaobola(x, y, nextX, nextY);
    }
}

void animacaobola(int initX, int initY, int endX, int endY) {
    int currentX = initX;
    int currentY = initY;

    while (currentX != endX || currentY != endY) {
        screenSetColor(WHITE, DARKGRAY);
        screenGotoxy(currentX, currentY);
        printf(" ");

        if (currentX < endX) {
            currentX++;
        } else if (currentX > endX) {
            currentX--;
        }
        if (currentY < endY) {
            currentY++;
        } else if (currentY > endY) {
            currentY--;
        }
        screenGotoxy(currentX, currentY);
        printf("⬤");
        screenUpdate();
        usleep(50000); // Aguarda 50ms (0.05s)
    }
    x = endX;
    y = endY;
}

int colisao(struct buraco *bur, int Ox, int Oy) {
    int dx = bur->x - Ox;
    int dy = bur->y - Oy;
    int distancia = dx * dx + dy * dy;
    int raioQuadrado = bur->raio * bur->raio;
    return distancia <= raioQuadrado;
}
