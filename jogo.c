#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>


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
static char sala[LINHAS][COLUNAS + 1] ={
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

void removerMortos(Inimigo **lista){
    Inimigo **pp = lista;
    while (*pp != NULL){
        if ((*pp)->vida <= 0){
            Inimigo *morto = *pp;
            *pp = morto->prox;
            free(morto);
        } else {
            pp = &(*pp)->prox;
        }
    }
}

void liberar(Inimigo **lista) {
    while (*lista != NULL){
        Inimigo *tmp = *lista;  
        *lista = tmp->prox;
        free(tmp);
    }
}

int contarInimigos(Inimigo *lista) {
    int n = 0;
    for (Inimigo *p = lista; p != NULL; p = p->prox) n++;
    return n;
}

int bloqueado(float px, float py, int porta_travada){
    if (px < 0 || py < 0) return 1;
    int c = (int)px / TAM;
    int l = (int)py/ TAM;

    if (l >= LINHAS || c >= COLUNAS) return 1;
    char t = sala[l][c];
    return t == '#' || (t == 'P' && porta_travada);
}

int colide (float x, float y, int porta_travada){
    float m = 14;
    return bloqueado(x-m, y-m, porta_travada) ||
            bloqueado(x+m, y-m, porta_travada) ||
            bloqueado(x-m, y+m, porta_travada) ||
            bloqueado(x+m, y+m, porta_travada);
}


