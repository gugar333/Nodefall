#ifndef JOGADOR_H
#define JOGADOR_H

#include "raylib.h"
#include "arma.h"

typedef struct Jogador {
    float x, y;
    float veloc;
    float vida;
    float invulnerab;
    float ataque;
    Arma arma;
} Jogador;

void iniciarJogador(Jogador *p, float x, float y);
void atualizarJogador(Jogador *p, float dt, int portaTravada);
void desenharJogador(const Jogador *p);
Rectangle retanguloJogador(const Jogador *p);

#endif