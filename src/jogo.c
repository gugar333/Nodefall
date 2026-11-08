#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "sala.h"

static const char *nomesEstados[ESTADO_TOTAL] = {
    "MENU", "ARSENAL", "ONDAS", "BOSS", "VITORIA", "DERROTA"
};

static int emSala(Estado e) {
    return e == ESTADO_ARSENAL || e == ESTADO_ONDAS || e == ESTADO_BOSS;
}

void iniciarJogo(Jogo *j) {
    j->estado = ESTADO_ARSENAL;
    iniciarJogador(&j->jogador, COLUNAS * TAM / 2.0f, 9 * TAM + TAM / 2.0f);
    j->inimigos = NULL;
    j->onda = 0;
}

void atualizarJogo(Jogo *j) {
    if (IsKeyPressed(KEY_N)) {
        j->estado = (j->estado + 1) % ESTADO_TOTAL;
    }

    if (emSala(j->estado)) {
        atualizarJogador(&j->jogador, GetFrameTime());
    }
}

void desenharJogo(const Jogo *j) {
    if (emSala(j->estado)) {
        desenharSala();
        desenharJogador(&j->jogador);
    }
    DrawText(nomesEstados[j->estado], 10, 10, 20, WHITE);
}

void encerrarJogo(Jogo *j) {
    liberar(&j->inimigos);
}