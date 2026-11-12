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

static char caractereEm(float x, float y) {
    if (x < 0 || y < 0) return '#';
    int c = (int)x / TAM;
    int l = (int)y / TAM;

    if (l >= LINHAS || c >= COLUNAS) return '#';
    return salas[atual][l][c];
}

static int ehParede(char t) {
    return t == '#' || t == 'E' || t == 'B' || t == 'F' || t == '>' || t == '<';
}

int bloqueado(float px, float py, int porta_travada){
    char t = caractereEm(px, py);
    return ehParede(t) || t == 'A' || (t == 'P' && porta_travada);
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
    return caractereEm(x, y) == 'P';
}

int noTesouro(float x, float y) {
    return caractereEm(x, y) == 'T';
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

static float anguloEscada(int l, int c) {
    if (l < LINHAS / 2) return (c < COLUNAS / 2) ? 270 : 0;
    return (c < COLUNAS / 2) ? 180 : 90;
}

static void desenharFundo(int l, int c) {
    char t = salas[atual][l][c];
    float x = c * TAM;
    float y = l * TAM;

    if (ehParede(t) || t == 'P') desenharSprite(SPR_PAREDE, x, y, TAM, TAM);
    else desenharSprite(pisoDaPosicao(l, c), x, y, TAM, TAM);
}

static void desenharObjeto(int l, int c, int portaTravada) {
    char t = salas[atual][l][c];
    float x = c * TAM;
    float y = l * TAM;
    int q = quadroAnimacao(QUADROS_FONTE);

    switch (t) {
        case 'P':
            if (!cantoDoBloco(l, c)) break;
            if (portaTravada) {
                desenharSprite(SPR_PORTA_FECHADA, x, y, 2 * TAM, 2 * TAM);
            } else {
                DrawRectangle(x + 18, y + 10, 55, 60, BLACK);
                desenharSprite(SPR_PORTA_ABERTA, x, y, 2 * TAM, 2 * TAM);
            }
            break;
        case 'E':
            if (cantoDoBloco(l, c)) desenharSprite(SPR_PORTA_FECHADA, x, y, 2 * TAM, 2 * TAM);
            break;
        case 'T':
            if (cantoDoBloco(l, c)) desenharSprite(SPR_BAU, x, y, 2 * TAM, 2 * TAM);
            break;
        case 'A':
            if (cantoDoBloco(l, c)) desenharSprite(SPR_COLUNA, x, y - 18, TAM, 3 * TAM);
            break;
        case 'S':
            desenharSpriteGirado(SPR_ESCADA, x, y, TAM, anguloEscada(l, c));
            break;
        case 'B':
            desenharSprite(SPR_BANDEIRA_VERMELHA + atual, x, y, TAM, TAM);
            break;
        case 'F':
            desenharSprite(SPR_FONTE_MEIO + q, x, y - TAM, TAM, TAM);
            desenharSprite(SPR_FONTE_BACIA + q, x, y, TAM, TAM);
            break;
        case '>':
            desenharSpriteGirado(SPR_FONTE_MEIO + q, x - TAM, y, TAM, 270);
            desenharSpriteGirado(SPR_FONTE_BACIA + q, x, y, TAM, 270);
            break;
        case '<':
            desenharSpriteGirado(SPR_FONTE_MEIO + q, x + TAM, y, TAM, 90);
            desenharSpriteGirado(SPR_FONTE_BACIA + q, x, y, TAM, 90);
            break;
        case 'C':
            desenharSprite(SPR_CRANIO, x, y, TAM, TAM);
            break;
        case '$':
            desenharSpriteNoChao(SPR_MOEDA + quadroAnimacao(QUADROS), x + TAM / 2, y + 30, 3.0f, 0);
            break;
    }
}

void desenharSala(int portaTravada) {
    for (int l = 0; l < LINHAS; l++) {
        for (int c = 0; c < COLUNAS; c++) {
            desenharFundo(l, c);
        }
    }

    for (int l = 0; l < LINHAS; l++) {
        for (int c = 0; c < COLUNAS; c++) {
            desenharObjeto(l, c, portaTravada);
        }
    }
}