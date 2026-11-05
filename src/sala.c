#include "raylib.h"
#include "sala.h"

static char sala[LINHAS][COLUNAS + 1] ={
    "#########P##########",
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
};

int bloqueado(float px, float py, int porta_travada){
    if (px < 0 || py < 0) return 1;
    int c = (int)px / TAM;
    int l = (int)py/ TAM;

    if (l >= LINHAS || c >= COLUNAS) return 1;
    char t = sala[l][c];
    return t == '#' || (t == 'P' && porta_travada);
}

int colide (float x, float y, int porta_travada){
    float m = 14;
    return bloqueado(x-m, y-m, porta_travada) ||
            bloqueado(x+m, y-m, porta_travada) ||
            bloqueado(x-m, y+m, porta_travada) ||
            bloqueado(x+m, y+m, porta_travada);
}

void desenharSala(void) {
    for (int l = 0; l < LINHAS; l++) {
        for (int c = 0; c < COLUNAS; c++) {
            Color cor;
            if (sala[l][c] == '#') cor = DARKGRAY;
            else if (sala[l][c] == 'P') cor = BROWN;
            else cor = BEIGE;

            DrawRectangle(c * TAM, l * TAM, TAM, TAM, cor);
        }
    }
}