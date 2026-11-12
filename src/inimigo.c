#include <stdlib.h>
#include "raylib.h"
#include "inimigo.h"
#include <math.h>
#include "sala.h"
#include "recursos.h"

typedef struct {
    float veloc;
    float vida;
    float dano;
    float raio;
    Sprite sprite;
    float escala;
} DadosInimigo;

static DadosInimigo tabela[INIMIGO_TIPOS] = {
    {100.0f, 3.0f, 1.0f, 14.0f, SPR_ESQUELETO, 2.5f},
    {130.0f, 1.0f, 1.0f, 10.0f, SPR_DIABINHO, 2.0f},
    {70.0f, 12.0f, 3.0f, 22.0f, SPR_OGRO, 2.0f}
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
    novo->olhandoEsquerda = 0;
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
        DadosInimigo d = tabela[i->tipo];
        desenharSpriteNoChao(d.sprite, i->x, i->y + i->raio, d.escala, i->olhandoEsquerda);
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
        if (passoX < 0) i->olhandoEsquerda = 1;
        if (passoX > 0) i->olhandoEsquerda = 0;

        if (!colideRaio(i->x + passoX, i->y, i->raio, 1)) i->x += passoX;
        if (!colideRaio(i->x, i->y + passoY, i->raio, 1)) i->y += passoY;
    }
}

Rectangle retanguloInimigo(const Inimigo *i) {
    Rectangle r = { i->x - i->raio, i->y - i->raio, i->raio * 2, i->raio * 2 };
    return r;
}