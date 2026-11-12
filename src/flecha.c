#include <stdlib.h>
#include <math.h>
#include "raylib.h"
#include "flecha.h"
#include "sala.h"

#define VELOC_FLECHA 450.0f

void dispararFlecha(Flecha **lista, float x, float y, float dirX, float dirY) {
    float tam = sqrtf(dirX * dirX + dirY * dirY);
    if (tam == 0) return;

    Flecha *nova = (Flecha *) malloc(sizeof(Flecha));
    if (nova == NULL) return;

    nova->x = x;
    nova->y = y;
    nova->dirX = dirX / tam;   // normaliza para a diagonal não ser mais rápida
    nova->dirY = dirY / tam;
    nova->prox = *lista;
    *lista = nova;
}

void atualizarFlechas(Flecha **lista, Inimigo *inimigos, float dano, float dt) {
    Flecha **pp = lista;
    while (*pp != NULL) {
        Flecha *f = *pp;
        f->x += f->dirX * VELOC_FLECHA * dt;
        f->y += f->dirY * VELOC_FLECHA * dt;

        int remover = bloqueado(f->x, f->y, 1);   // parede ou porta fechada

        if (!remover) {
            Vector2 ponto = { f->x, f->y };
            for (Inimigo *i = inimigos; i != NULL; i = i->prox) {
                if (CheckCollisionPointRec(ponto, retanguloInimigo(i))) {
                    i->vida -= dano;
                    remover = 1;
                    break;
                }
            }
        }

        if (remover) {
            *pp = f->prox;
            free(f);
        } else {
            pp = &f->prox;
        }
    }
}

void desenharFlechas(const Flecha *lista) {
    for (const Flecha *f = lista; f != NULL; f = f->prox) {
        Vector2 ponta = { f->x, f->y };
        Vector2 cauda = { f->x - f->dirX * 16, f->y - f->dirY * 16 };
        DrawLineEx(cauda, ponta, 3, BROWN);
        DrawCircleV(ponta, 3, LIGHTGRAY);
    }
}

void liberarFlechas(Flecha **lista) {
    while (*lista != NULL) {
        Flecha *tmp = *lista;
        *lista = tmp->prox;
        free(tmp);
    }
}