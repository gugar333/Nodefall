#ifndef BOSS_H
#define BOSS_H

#include "raylib.h"

typedef struct Boss {
    float x, y;
    float vida, vidaMax;
    float veloc;
    float dano;
    float raio;
    int vivo;
    int olhandoEsquerda;
} Boss;

void iniciarBoss(Boss *b, float x, float y);
void atualizarBoss(Boss *b, float alvoX, float alvoY, float dt);
void desenharBoss(const Boss *b);
void desenharBarraBoss(const Boss *b);
Rectangle retanguloBoss(const Boss *b);

#endif