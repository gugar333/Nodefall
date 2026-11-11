#ifndef RECURSOS_H
#define RECURSOS_H

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
    SPR_TOTAL
} Sprite;

void carregarRecursos(void);
void descarregarRecursos(void);
void desenharSprite(Sprite s, float x, float y, float largura, float altura);
void desenharSpriteGirado(Sprite s, float x, float y, float tamanho, float angulo);

#endif