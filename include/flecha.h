#ifndef FLECHA_H
#define FLECHA_H

#include "raylib.h"
#include "inimigo.h"

typedef struct Flecha {
    float x, y;
    float dirX, dirY;
    struct Flecha *prox;
} Flecha;

void dispararFlecha(Flecha **lista, float x, float y, float dirX, float dirY);
void atualizarFlechas(Flecha **lista, Inimigo *inimigos, float dano, float dt);
void desenharFlechas(const Flecha *lista);
void liberarFlechas(Flecha **lista);

#endif