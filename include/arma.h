#ifndef ARMA_H
#define ARMA_H

typedef enum {
    ARMA_NENHUMA,
    ARMA_ESPADA,
    ARMA_ARCO
} Arma;

void desenharArma(Arma arma, float x, float y, float escala);

#endif