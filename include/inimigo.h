#ifndef INIMIGO_H
#define INIMIGO_H

typedef enum {
    INIMIGO_SERVO,
    INIMIGO_CORREDOR, 
    INIMIGO_BRUTAMONTES,
    INIMIGO_TIPOS
}TipoInimigo;

typedef struct Inimigo {
    float x, y;
    float veloc;
    float vida;
    TipoInimigo tipo;
    float dano;
    float raio;
    struct Inimigo *prox;
} Inimigo;

void inserirInimigo(Inimigo **lista,TipoInimigo tipo, float x, float y);
void removerMortos(Inimigo **lista);
void liberar(Inimigo **lista);
int contarInimigos(Inimigo *lista);
void desenharInimigos(Inimigo *lista);
void atualizarInimigos(Inimigo *lista, float jogadorX, float jogadorY, float dt);


#endif 