#ifndef INIMIGO_H
#define INIMIGO_H

typedef struct Inimigo {
    float x, y;
    float veloc;
    float vida;
    struct Inimigo *prox;
} Inimigo;

void inserirInimigo(Inimigo **lista, float x, float y);
void removerMortos(Inimigo **lista);
void liberar(Inimigo **lista);
int contarInimigos(Inimigo *lista);

#endif