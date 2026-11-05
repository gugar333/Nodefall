#include <stdlib.h>
#include "inimigo.h"

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