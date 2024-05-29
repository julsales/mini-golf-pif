#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "keyboard.h"
#include "screen.h"

#define LARGURA 80
#define ALTURA 24
#define ESPESSURA 1

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
void instrucoes();
void desenharParedes();
void printbola(int nextX, int nextY);
void printburaco(struct buraco *bur, int x, int y, int raio);
void apagarburaco(struct buraco *bur);
void moverbola(struct player *ptp ,char direcao);
void animacaobola(int initX, int initY, int endX, int endY, int *forcarebote);
int calcularForca(int mov);
int colisao(struct buraco *bur, int Ox, int Oy);
int calcularPontuacao(int movimentos);
void escrevernome(struct player *ptp);
void salvarPontuacao(struct player *ptp);

int main(void) {
    int ch = 0;
    screenInit(20);
    keyboardInit();
    menuinit();

    if (keyhit()) {
        ch = getchar();
        screenClear();
        screenInit(1);
        screenSetColor(WHITE, DARKGRAY);
        screenGotoxy(x - 4, y);
        printf("Selecione o modo de jogo");
        screenGotoxy(x - 4, y + 1);
        printf("Modo INICIANTE - 1");
        screenGotoxy(x - 4, y + 2);
        printf("Modo PROFISSIONAL - 2");

        struct buraco *bur = (struct buraco *)malloc(8 * sizeof(struct buraco));
        struct player *ptp = (struct player *)malloc(2 * sizeof(struct player));
        ch = getchar();
        screenClear();
        int buraco1_acertado = 0;
        int buraco2_acertado = 0;
        int buraco3_acertado = 0;
        int buraco4_acertado = 0;

        switch (ch) {
            case '1':
                screenInit(1);
                instrucoes();
                ch=getchar();
                escrevernome(&ptp[0]);
                escrevernome(&ptp[1]);
                screenInit(1);
                desenharParedes();
                printbola(x, y);
                printburaco(&bur[0], 45, 18, 2);
                printburaco(&bur[1], 5, 20, 2);

                while (1) {
                    if (keyhit()) {
                        ch = getchar();
                        moverbola(&ptp[0], ch);
                        if (!buraco1_acertado && colisao(&bur[0], x, y)) {
                            buraco1_acertado = 1;
                            apagarburaco(&bur[0]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }
                        if (!buraco2_acertado && colisao(&bur[1], x, y)) {
                            buraco2_acertado = 1;
                            apagarburaco(&bur[1]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }

                        if (buraco1_acertado && buraco2_acertado) {
                            screenGotoxy(0, MAXY + 3);
                            printf("Você acertou todos os buracos! Jogo encerrado");
                            break;
                        }
                    }
                }
                screenGotoxy(0, MAXY + 3);
                printf("Vez do player 2");
                ch = getchar();
                screenInit(1);
                x = 34;
                y = 12;
                printbola(x, y);
                printburaco(&bur[0], 45, 18, 2);
                printburaco(&bur[1], 5, 20, 2);
                buraco1_acertado = 0;
                buraco2_acertado = 0;

                while (1) {
                    if (keyhit()) {
                        ch = getchar();
                        moverbola(&ptp[1], ch);
                        if (!buraco1_acertado && colisao(&bur[0], x, y)) {
                            buraco1_acertado = 1;
                            apagarburaco(&bur[0]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }
                        if (!buraco2_acertado && colisao(&bur[1], x, y)) {
                            buraco2_acertado = 1;
                            apagarburaco(&bur[1]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }

                        if (buraco1_acertado && buraco2_acertado) {
                            screenGotoxy(0, ALTURA + 3);
                            printf("Você acertou todos os buracos! Jogo encerrado");
                            break;
                        }
                    }
                }
                break;
            case '2':
                screenInit(1);
                instrucoes();
                ch=getchar();
                escrevernome(&ptp[0]);
                escrevernome(&ptp[1]);
                screenInit(1);
                desenharParedes();
                printbola(x, y);
                printburaco(&bur[0], 40, 5, 1);
                printburaco(&bur[1], 45, 18, 1);
                printburaco(&bur[2], 70, 10, 1);
                printburaco(&bur[3], 5, 10, 1);

                while (1) {
                    if (keyhit()) {
                        ch = getchar();
                        moverbola(&ptp[0], ch);
                        if (!buraco1_acertado && colisao(&bur[0], x, y)) {
                            buraco1_acertado = 1;
                            apagarburaco(&bur[0]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }
                        if (!buraco2_acertado && colisao(&bur[1], x, y)) {
                            buraco2_acertado = 1;
                            apagarburaco(&bur[1]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }
                        if (!buraco3_acertado && colisao(&bur[2], x, y)) {
                            buraco3_acertado = 1;
                            apagarburaco(&bur[2]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }
                        if (!buraco4_acertado && colisao(&bur[3], x, y)) {
                            buraco4_acertado = 1;
                            apagarburaco(&bur[3]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }

                        if (buraco1_acertado && buraco2_acertado && buraco3_acertado && buraco4_acertado) {
                            screenGotoxy(0, ALTURA + 3);
                            printf("Você acertou todos os buracos! Jogo encerrado");
                            break;
                        }
                    }
                }

                screenGotoxy(0, ALTURA + 4);
                printf("Vez do player 2");
                ch = getchar();
                screenInit(1);
                x = 34;
                y = 12;
                printbola(x, y);
                printburaco(&bur[0], 40, 5, 1);
                printburaco(&bur[1], 45, 18, 1);
                printburaco(&bur[2], 70, 10, 1);
                printburaco(&bur[3], 5, 10, 1);
                buraco1_acertado = 0;
                buraco2_acertado = 0;
                buraco3_acertado = 0;
                buraco4_acertado = 0;

                while (1) {
                    if (keyhit()) {
                        ch = getchar();
                        moverbola(&ptp[1], ch);
                        if (!buraco1_acertado && colisao(&bur[0], x, y)) {
                            buraco1_acertado = 1;
                            apagarburaco(&bur[0]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }
                        if (!buraco2_acertado && colisao(&bur[1], x, y)) {
                            buraco2_acertado = 1;
                            apagarburaco(&bur[1]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }
                        if (!buraco3_acertado && colisao(&bur[2], x, y)) {
                            buraco3_acertado = 1;
                            apagarburaco(&bur[2]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }
                        if (!buraco4_acertado && colisao(&bur[3], x, y)) {
                            buraco4_acertado = 1;
                            apagarburaco(&bur[3]);
                            screenGotoxy(x, y);
                            printbola(x, y);
                            ptp->score += calcularPontuacao(ptp->movimentos);
                        }

                        if (buraco1_acertado && buraco2_acertado && buraco3_acertado && buraco4_acertado) {
                            screenGotoxy(0, ALTURA + 3);
                            printf("Você acertou todos os buracos! Jogo encerrado");
                            break;
                        }
                    }
                }
                break;
            default:
                screenGotoxy(x - 4, y + 3);
                printf("Reinicie o Jogo");
                ch = getchar();
        }
        salvarPontuacao(ptp);
        free(ptp);
        free(bur);
    }

    keyboardDestroy();
    screenDestroy();
    return 0;
}

void instrucoes(){
    int x1 = 10;
    int y1 = 8;
    screenGotoxy(x1 - 4, y1-5);
    printf("Instruções de Jogo");
    screenGotoxy(x1 - 4, y1 + 1);
    printf("Selecione a força da tacada com as teclas 1 a 5");
    screenGotoxy(x1 - 4, y1 + 2);
    printf("Após selecionar a força, decida que direção a bola irá");
    screenGotoxy(x1 - 4, y1 + 3);
    printf("W - A - S - D para se mover nas quatro direções:");
    screenGotoxy(x1 - 4, y1 + 4);
    printf("CIMA, BAIXO, ESQUERDA, DIREITA");
    screenGotoxy(x1 - 4, y1 + 5);
    printf(" Q - E - Z - C para se mover nas diagonais: ");
    screenGotoxy(x1 - 4, y1 + 6);
    printf("CIMA ESQUERDA, CIMA DIREITA, BAIXO ESQUERDA, BAIXO DIREITA.");
    screenGotoxy(25, 22);
    screenSetBlink();
    printf("[SELECT ANY KEY TO CONTINUE]");
    screenGotoxy(26, 23);
    printf("                               ");
    screenSetNormal();

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
        for (j = 1; j < LARGURA; j++) {
            screenGotoxy(j, i);
            printf("■");
            screenGotoxy(j, ALTURA - i);
            printf("■");
        }for (j = 1; j < ALTURA; j++){
            screenGotoxy(i, j);
            printf("■");
            screenGotoxy(LARGURA - i, j);
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
    screenSetColor(BROWN, BROWN);
    bur->x = x;
    bur->y = y;
    bur->raio = raio;
    int i, j;
    for (i = y - raio; i <= y + raio; i++) {
        for (j = x - raio; j <= x + raio; j++) {
            if ((x - j) * (x - j) + (y - i) * (y - i) <= raio * raio) {
                screenGotoxy(j, i);
                printf(" ");
            }
        }
    }
    screenSetColor(BROWN, DARKGRAY);
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
    screenGotoxy(j - 2, i - 4);
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
            return 1;
    }
}

void moverbola(struct player *ptp, char direcao) {
    screenGotoxy(2, 2);
    printf("Força:");
    screenGotoxy(2, 3);
    printf("Movimentos: %d", ptp->movimentos);

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
    int score = ptp->score;
    screenGotoxy(65, 2);
    printf("Pontuação: %d", score);
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
            break;
        case 'e':
            nextX = x + forca;
            nextY = y - forca;
            break;
        case 'z':
            nextX = x - forca;
            nextY = y + forca;
            break;
        case 'c':
            nextX = x + forca;
            nextY = y + forca;
            break;
    }
    int forcarebote = forca;
    animacaobola(x, y, nextX, nextY, &forcarebote);
}

void animacaobola(int initX, int initY, int endX, int endY, int *forcarebote) {
    int atualX = initX;
    int atualY = initY;

    while ((atualX != endX || atualY != endY) && *forcarebote > 0) {
        screenSetColor(WHITE, DARKGRAY);
        screenGotoxy(atualX, atualY);
        printf(" ");

        if (atualX < endX) {
            atualX++;
        } else if (atualX > endX) {
            atualX--;
        }
        if (atualY < endY) {
            atualY++;
        } else if (atualY > endY) {
            atualY--;
        }
        if (atualX <= ESPESSURA) {
            atualX = ESPESSURA;
            endX = LARGURA - ESPESSURA - 1;
        } else if (atualX >= LARGURA - ESPESSURA - 1) {
            atualX = LARGURA - ESPESSURA - 1;
            endX = ESPESSURA;
        }
        if (atualY <= ESPESSURA) {
            atualY = ESPESSURA;
            endY = ALTURA - ESPESSURA - 1;
        } else if (atualY >= ALTURA - ESPESSURA - 1) {
            atualY = ALTURA - ESPESSURA - 1;
            endY = ESPESSURA;
        }

        screenGotoxy(atualX, atualY);
        printf("⬤");
        screenUpdate();
        usleep(50000);
        (*forcarebote)--;
    }

    x = atualX;
    y = atualY;
}

int colisao(struct buraco *bur, int Ox, int Oy) {
    int dx = bur->x - Ox;
    int dy = bur->y - Oy;
    int distancia = dx * dx + dy * dy;
    int raioQuadrado = bur->raio * bur->raio;
    return distancia <= raioQuadrado;
}

int calcularPontuacao(int movimentos) {
    if (movimentos >= 1 && movimentos <= 2) {
        return 10;
    } else if (movimentos >= 3 && movimentos <= 4) {
        return 8;
    } else if (movimentos >= 5 && movimentos <= 6) {
        return 6;
    } else if (movimentos >= 7 && movimentos <= 8) {
        return 3;
    } else if (movimentos >= 9 && movimentos <= 10) {
        return 2;
    } else {
        return 1;
    }
}

void salvarPontuacao(struct player *ptp) {
    FILE *arquivo = fopen("pontuacao.txt", "a");
    if (arquivo != NULL) {
        for (int i = 0; i < 2; i++) {
            fprintf(arquivo, "Jogador %s: Pontuação = %d\n", ptp[i].nome, ptp[i].score);
        }
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo de pontuação.\n");
    }
}


void escrevernome(struct player *ptp) {
    screenClear();
    screenInit(1);
    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(MAXX / 2 - 10, MAXY / 2 - 6);
    printf("Digite seu nome: ");

    char ch;
    int i = 0;

    while ((ch = getchar()) != '\n' && ch != EOF);
    while (i < 20) {
        ch = getchar();
        if (ch == '\n') {
            break;
        } else if (ch == 127) {
            if (i > 0) {
                i--;
                screenSetColor(WHITE, DARKGRAY);
                screenGotoxy(MAXX / 2 - 10 + i, MAXY / 2 - 5);
                printf(" ");
                screenGotoxy(MAXX / 2 - 10 + i, MAXY / 2 - 5);
                screenUpdate();
            }
        } else {
            ptp->nome[i] = ch;
            screenSetColor(WHITE, DARKGRAY);
            screenGotoxy(MAXX / 2 - 10 + i, MAXY / 2 - 5);
            printf("%c", ch);
            i++;
        }
    }
    ptp->nome[i] = '\0';
    screenUpdate();
}
