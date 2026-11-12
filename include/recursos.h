#ifndef RECURSOS_H
#define RECURSOS_H

#define QUADROS 4
#define QUADROS_FONTE 3

typedef enum {
    SPR_PISO_1,
    SPR_PISO_2,
    SPR_PISO_3,
    SPR_PAREDE,
    SPR_PORTA_FECHADA,
    SPR_PORTA_ABERTA,
    SPR_COLUNA,
    SPR_BAU,
    SPR_ESCADA,
    SPR_CAVALEIRO_PARADO,
    SPR_CAVALEIRO_CORRENDO = SPR_CAVALEIRO_PARADO + QUADROS,
    SPR_ESQUELETO = SPR_CAVALEIRO_CORRENDO + QUADROS,
    SPR_DIABINHO = SPR_ESQUELETO + QUADROS,
    SPR_OGRO = SPR_DIABINHO + QUADROS,
    SPR_ESPADA = SPR_OGRO + QUADROS,
    SPR_ARCO,
    SPR_BANDEIRA_VERMELHA,
    SPR_BANDEIRA_AZUL,
    SPR_BANDEIRA_VERDE,
    SPR_BANDEIRA_AMARELA,
    SPR_FONTE_MEIO,
    SPR_FONTE_BACIA = SPR_FONTE_MEIO + QUADROS_FONTE,
    SPR_CRANIO = SPR_FONTE_BACIA + QUADROS_FONTE,
    SPR_MOEDA,
    SPR_TOTAL = SPR_MOEDA + QUADROS
} Sprite;

void carregarRecursos(void);
void descarregarRecursos(void);
void desenharSprite(Sprite s, float x, float y, float largura, float altura);
void desenharSpriteGirado(Sprite s, float x, float y, float tamanho, float angulo);
void desenharSpriteNoChao(Sprite s, float centroX, float chaoY, float escala, int virado);
int quadroAnimacao(int total);

#endif