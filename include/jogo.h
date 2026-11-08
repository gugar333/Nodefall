#ifndef JOGO_H
#define JOGO_H

#include "jogador.h"
#include "inimigo.h"

typedef enum {
    ESTADO_MENU,
    ESTADO_ARSENAL,
    ESTADO_ONDAS,
    ESTADO_BOSS,
    ESTADO_VITORIA,
    ESTADO_DERROTA,
    ESTADO_TOTAL
} Estado;

typedef struct Jogo {
    Estado estado;
    Jogador jogador;
    Inimigo *inimigos;
    int onda;
} Jogo;

void iniciarJogo(Jogo *j);
void atualizarJogo(Jogo *j);
void desenharJogo(const Jogo *j);
void encerrarJogo(Jogo *j);

#endif