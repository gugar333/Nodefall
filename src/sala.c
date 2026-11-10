#include "raylib.h"
#include "sala.h"

static char salas[NUM_SALAS][LINHAS][COLUNAS + 1] = {
    {
        "#########PP#########",
        "#..................#",
        "#..................#",
        "#..................#",
        "#..................#",
        "#....A........A....#",
        "#..................#",
        "#..................#",
        "#..................#",
        "#..................#",
        "#..................#",
        "####################"
    },
    {
        "#########PP#########",
        "#..................#",
        "#..................#",
        "#..................#",
        "#..................#",
        "#....##......##....#",
        "#....##......##....#",
        "#..................#",
        "#..................#",
        "#..................#",
        "#..................#",
        "####################"
    },
    {
        "#########PP#########",
        "#..................#",
        "#..................#",
        "#...##........##...#",
        "#...##........##...#",
        "#..................#",
        "#..................#",
        "#...##........##...#",
        "#...##........##...#",
        "#..................#",
        "#..................#",
        "####################"
    },
    {
        "####################",
        "#..................#",
        "#..................#",
        "#..................#",
        "#.......####.......#",
        "#.......#TT#.......#",
        "#.......#TT#.......#",
        "#..................#",
        "#..................#",
        "#..................#",
        "#..................#",
        "####################"
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
    return t == '#' || t == 'A' || (t == 'P' && porta_travada);
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

void desenharSala(void) {
    for (int l = 0; l < LINHAS; l++) {
        for (int c = 0; c < COLUNAS; c++) {
            Color cor;
            if (salas[atual][l][c] == '#') cor = DARKGRAY;
            else if (salas[atual][l][c] == 'P') cor = BROWN;
            else if (salas[atual][l][c] == 'T') cor = GOLD;
            else if (salas[atual][l][c] == 'A') cor = GRAY;
            else cor = BEIGE;
            

            DrawRectangle(c * TAM, l * TAM, TAM, TAM, cor);
        }
    }
}