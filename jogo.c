#include "raylib.h"
#include <stdio.h>


#define LINHAS 12
#define COLUNAS 20
#define TAM 40



typedef struct Jogador {
    float x, y;
    float veloc;
    float vida;
    float invulnerab;
    float ataque;
}Jogador;

typedef struct Inimigo {
    float x, y;
    float veloc;
    float vida;
    struct Inimigo *prox;
}Inimigo;

static const char sala[LINHAS][COLUNAS + 1] ={
    "#########P##########",
    "#..................#",
    "#..................#",
    "#..................#",
    "#..................#",
    "#....##......##....#",
    "#....##......##....#",
    "#..................#",
    "#..................#",
    "#..................#",
    "#..................#",
    "####################"
};

void inserirInimigo(Inimigo **lista, float x, float y){
    Inimigo *novo = (Inimigo *) malloc(sizeof(Inimigo));
    if (novo == NULL){
        return;
    }
    novo->x = x;
    novo->y = y;
    novo->veloc = 60 + rand() % 40;
    novo->vida = 2;
    novo->prox = *lista;
    *lista = novo;
}

