#ifndef JOGO_H
#define JOGO_H

#include "jogador.h"
#include "inimigo.h"
#include "flecha.h"
#include "boss.h"

typedef enum {
    ESTADO_MENU,
    ESTADO_ARSENAL,
    ESTADO_ONDAS,
    ESTADO_BOSS,
    ESTADO_TESOURO,
    ESTADO_VITORIA,
    ESTADO_DERROTA,
    ESTADO_TOTAL
} Estado;

typedef struct Jogo {
    Estado estado;
    Jogador jogador;
    Inimigo *inimigos;
    Flecha *flechas;
    Boss boss;
    int onda;
    int abates;
    int portaTravada;
} Jogo;

void iniciarJogo(Jogo *j);
void atualizarJogo(Jogo *j);
void desenharJogo(const Jogo *j);
void encerrarJogo(Jogo *j);

#endif