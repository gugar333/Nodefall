#include "raylib.h"
#include "arma.h"

static void desenharEspada(float x, float y, float e) {
    DrawRectangle(x + 17 * e, y + 4 * e, 6 * e, 22 * e, LIGHTGRAY);
    DrawRectangle(x + 10 * e, y + 26 * e, 20 * e, 4 * e, GOLD);
    DrawRectangle(x + 18 * e, y + 30 * e, 4 * e, 7 * e, BROWN);
}

static void desenharArco(float x, float y, float e) {
    Vector2 centro = { x + 14 * e, y + 20 * e };
    DrawRing(centro, 13 * e, 16 * e, -90, 90, 16, BROWN);
    DrawLine(x + 14 * e, y + 5 * e, x + 14 * e, y + 35 * e, RAYWHITE);
}

void desenharArma(Arma arma, float x, float y, float escala) {
    if (arma == ARMA_ESPADA) desenharEspada(x, y, escala);
    else if (arma == ARMA_ARCO) desenharArco(x, y, escala);
}