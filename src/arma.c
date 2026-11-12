#include "raylib.h"
#include "arma.h"
#include "recursos.h"

void desenharArma(Arma arma, float x, float y, float escala, int virado) {
    Sprite s;
    if (arma == ARMA_ESPADA) s = SPR_ESPADA;
    else if (arma == ARMA_ARCO) s = SPR_ARCO;
    else return;

    desenharSpriteNoChao(s, x + 20 * escala, y + 38 * escala, 1.3f * escala, virado);
}