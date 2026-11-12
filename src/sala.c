#include "raylib.h"
#include "sala.h"
#include "recursos.h"

static char salas[NUM_SALAS][LINHAS][COLUNAS + 1] = {
    {
        "#########PP#########",
        "#..F....BPPB....F..#",
        "#..................#",
        "#..................#",
        "#..................#",
        "#...A..........A...#",
        "#...A..........A...#",
        "#..................#",
        "#..................#",
        "#..................#",
        "#.......#EE#.......#",
        "#########EE#########"
    },
    {
        "#########PP#########",
        "#.......BPPB.......#",
        "#.S..............S.#",
        "#..................#",
        "#C.................#",
        "#....##......##....#",
        "#....##......##....#",
        "#.................C#",
        "#..................#",
        "#.S..............S.#",
        "#.....C.#EE#.......#",
        "#########EE#########"
    },
    {
        "#########PP#########",
        "#.......BPPB.......#",
        "#.....C............#",
        "#...##........##...#",
        "#...##........##...#",
        "#C.................#",
        "#..................#",
        "#...##........##...#",
        "#...##........##...#",
        "#............C.....#",
        "#.......#EE#.......#",
        "#########EE#########"
    },
    {
        "######B######B######",
        "####.F........F.####",
        "####...$.TT.$...####",
        "####.....TT.....####",
        "####............####",
        "#######>....<#######",
        "#######......#######",
        "#######>....<#######",
        "#######......#######",
        "#######>....<#######",
        "#########EE#########",
        "#########EE#########"
    }
};

static int atual = 0;

void mudarSala(int indice) {
    if (indice >= 0 && indice < NUM_SALAS) {
        atual = indice;
    }
}

int bloqueado(float px, float py, int porta_travada){
    if (px < 0 || py < 0) return 1;
    int c = (int)px / TAM;
    int l = (int)py/ TAM;

    if (l >= LINHAS || c >= COLUNAS) return 1;
    char t = salas[atual][l][c];
    return t == '#' || t == 'A' || t == 'E' || t == 'B' || t == 'F' || t == '>' || t == '<' || (t == 'P' && porta_travada);
}

int colideRaio(float x, float y, float m, int porta_travada){
    return bloqueado(x-m, y-m, porta_travada) ||
            bloqueado(x+m, y-m, porta_travada) ||
            bloqueado(x-m, y+m, porta_travada) ||
            bloqueado(x+m, y+m, porta_travada);
}

int colide (float x, float y, int porta_travada){
    return colideRaio(x, y, 14, porta_travada);
}

int naPorta(float x, float y) {
    int c = (int)x / TAM;
    int l = (int)y / TAM;

    if (l < 0 || c < 0 || l >= LINHAS || c >= COLUNAS) return 0;
    return salas[atual][l][c] == 'P';
}

int noTesouro(float x, float y) {
    int c = (int)x / TAM;
    int l = (int)y / TAM;

    if (l < 0 || c < 0 || l >= LINHAS || c >= COLUNAS) return 0;
    return salas[atual][l][c] == 'T';
}

static int cantoDoBloco(int l, int c) {
    char t = salas[atual][l][c];
    int esquerdaIgual = (c > 0 && salas[atual][l][c - 1] == t);
    int cimaIgual = (l > 0 && salas[atual][l - 1][c] == t);
    return !esquerdaIgual && !cimaIgual;
}

static Sprite pisoDaPosicao(int l, int c) {
    int v = (l * 7 + c * 13) % 10;
    if (v < 7) return SPR_PISO_1;
    if (v < 9) return SPR_PISO_2;
    return SPR_PISO_3;
}

void desenharSala(int portaTravada) {
    for (int l = 0; l < LINHAS; l++) {
        for (int c = 0; c < COLUNAS; c++) {
            char t = salas[atual][l][c];
            float x = c * TAM;
            float y = l * TAM;

            if (t == '#' || t == 'P' || t == 'E' || t == 'B' || t == 'F' || t == '>' || t == '<') desenharSprite(SPR_PAREDE, x, y, TAM, TAM);
            else desenharSprite(pisoDaPosicao(l, c), x, y, TAM, TAM);
        }
    }

    for (int l = 0; l < LINHAS; l++) {
        for (int c = 0; c < COLUNAS; c++) {
            char t = salas[atual][l][c];
            float x = c * TAM;
            float y = l * TAM;

            if (t == 'P' && cantoDoBloco(l, c)) {
                if (portaTravada) {
                    desenharSprite(SPR_PORTA_FECHADA, x, y, 2 * TAM, 2 * TAM);
                } else {
                    DrawRectangle(x + 18, y + 10, 55, 60, BLACK);
                    desenharSprite(SPR_PORTA_ABERTA, x, y, 2 * TAM, 2 * TAM);
                }
            } else if (t == 'E' && cantoDoBloco(l, c)) {
                desenharSprite(SPR_PORTA_FECHADA, x, y, 2 * TAM, 2 * TAM);
            } else if (t == 'T' && cantoDoBloco(l, c)) {
                desenharSprite(SPR_BAU, x, y, 2 * TAM, 2 * TAM);
            } else if (t == 'S') {
                float angulo;
                if (l < LINHAS / 2) angulo = (c < COLUNAS / 2) ? 270 : 0;
                else angulo = (c < COLUNAS / 2) ? 180 : 90;
                desenharSpriteGirado(SPR_ESCADA, x, y, TAM, angulo);
            } else if (t == 'A' && cantoDoBloco(l, c)) {
                desenharSprite(SPR_COLUNA, x, y - 18, TAM, 3 * TAM);
            } else if (t == 'B') {
                desenharSprite(SPR_BANDEIRA_VERMELHA + atual, x, y, TAM, TAM);
            } else if (t == 'F') {
                int q = quadroAnimacao(QUADROS_FONTE);
                desenharSprite(SPR_FONTE_MEIO + q, x, y - TAM, TAM, TAM);
                desenharSprite(SPR_FONTE_BACIA + q, x, y, TAM, TAM);
            } else if (t == '>') {
                int q = quadroAnimacao(QUADROS_FONTE);
                desenharSpriteGirado(SPR_FONTE_MEIO + q, x - TAM, y, TAM, 270);
                desenharSpriteGirado(SPR_FONTE_BACIA + q, x, y, TAM, 270);
            } else if (t == '<') {
                int q = quadroAnimacao(QUADROS_FONTE);
                desenharSpriteGirado(SPR_FONTE_MEIO + q, x + TAM, y, TAM, 90);
                desenharSpriteGirado(SPR_FONTE_BACIA + q, x, y, TAM, 90);
            } else if (t == 'C') {
                desenharSprite(SPR_CRANIO, x, y, TAM, TAM);
            } else if (t == '$') {
                desenharSpriteNoChao(SPR_MOEDA + quadroAnimacao(QUADROS), x + TAM / 2, y + 30, 3.0f, 0);
            }
        }
    }
}