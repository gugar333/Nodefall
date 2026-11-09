#include <stdlib.h>
#include "raylib.h"
#include "inimigo.h"
#include <math.h>
#include "sala.h"

typedef struct {
    float veloc;
    float vida;
    float dano;
    float raio;
} DadosInimigo;

static DadosInimigo tabela[INIMIGO_TIPOS] = {
    {100.0f, 3.0f, 1.0f, 14.0f},
    {220.0f, 1.0f, 1.0f, 10.0f}, 
    {50.0f, 12.0f, 3.0f, 22.0f}
};

void inserirInimigo(Inimigo **lista, TipoInimigo tipo, float x, float y){
    Inimigo *novo = (Inimigo *) malloc(sizeof(Inimigo));
    if (novo == NULL){
        return;
    }
    novo->x = x;
    novo->y = y;
    novo->tipo = tipo;
    novo->veloc = tabela[tipo].veloc;
    novo->vida = tabela[tipo].vida;
    novo->dano = tabela[tipo].dano;
    novo->raio = tabela[tipo].raio;
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

void desenharInimigos(Inimigo *lista){
    for (Inimigo *i = lista; i != NULL; i = i->prox){
        Color cor = RED;
        if (i->tipo == INIMIGO_CORREDOR) cor = ORANGE;
        if(i->tipo == INIMIGO_BRUTAMONTES) cor = PURPLE;
        DrawCircle((int)i->x, (int)i->y, i->raio, cor);
    }
}

void atualizarInimigos(Inimigo *lista, float jogadorX, float jogadorY, float dt){
    for (Inimigo *i = lista; i!= NULL; i = i->prox){
        float dx = jogadorX - i->x;
        float dy = jogadorY - i->y;
        float dist = sqrtf(dx * dx + dy * dy);
        if (dist < 1.0f) continue;
        float passoX = (dx/dist) * i->veloc * dt;
        float passoY = (dy/dist) * i->veloc * dt;

        if (!colide(i->x + passoX, i->y, 0)) i->x += passoX;
        if (!colide(i->x, i->y +passoY, 0)) i->y += passoY;
    }
}