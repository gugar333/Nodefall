#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "sala.h"

static const char *nomesEstados[ESTADO_TOTAL] = {
    "MENU", "ARSENAL", "ONDAS", "BOSS", "VITORIA", "DERROTA"
};

void iniciarJogo(Jogo *j) {
    j->estado = ESTADO_ARSENAL;
    j->jogador = (Jogador){0};
    j->inimigos = NULL;
    j->onda = 0;
}

void atualizarJogo(Jogo *j) {
    if (IsKeyPressed(KEY_N)) {
        j->estado = (j->estado + 1) % ESTADO_TOTAL;
    }
}

void desenharJogo(const Jogo *j) {
    if (j->estado == ESTADO_ARSENAL || j->estado == ESTADO_ONDAS || j->estado == ESTADO_BOSS) {
        desenharSala();
    }
    DrawText(nomesEstados[j->estado], 10, 10, 20, WHITE);
}

void encerrarJogo(Jogo *j) {
    liberar(&j->inimigos);
}