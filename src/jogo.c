#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "sala.h"

#define INICIO_X (COLUNAS * TAM / 2.0f)
#define INICIO_Y (9 * TAM + TAM / 2.0f)

static const char *nomesEstados[ESTADO_TOTAL] = {
    "MENU", "ARSENAL", "ONDAS", "BOSS", "TESOURO", "VITORIA", "DERROTA"
};

static int emSala(Estado e) {
    return e == ESTADO_ARSENAL || e == ESTADO_ONDAS || e == ESTADO_BOSS || e == ESTADO_TESOURO;
}

static void entrarNoEstado(Jogo *j, Estado e) {
    j->estado = e;

    if (e == ESTADO_ARSENAL) mudarSala(0);
    else if (e == ESTADO_ONDAS) mudarSala(1);
    else if (e == ESTADO_BOSS) mudarSala(2);
    else if (e == ESTADO_TESOURO) mudarSala(3);

    if (emSala(e)) {
        j->jogador.x = INICIO_X;
        j->jogador.y = INICIO_Y;
    }
}

void iniciarJogo(Jogo *j) {
    iniciarJogador(&j->jogador, INICIO_X, INICIO_Y);
    j->inimigos = NULL;
    j->onda = 0;
    j->portaTravada = 0;
    entrarNoEstado(j, ESTADO_ARSENAL);
}

void atualizarJogo(Jogo *j) {
    if (IsKeyPressed(KEY_N)) {
        entrarNoEstado(j, (j->estado + 1) % ESTADO_TOTAL);
    }

    if (emSala(j->estado)) {
        atualizarJogador(&j->jogador, GetFrameTime(), j->portaTravada);

        if (naPorta(j->jogador.x, j->jogador.y)) {
            if (j->estado == ESTADO_ARSENAL) entrarNoEstado(j, ESTADO_ONDAS);
            else if (j->estado == ESTADO_ONDAS) entrarNoEstado(j, ESTADO_BOSS);
            else if (j->estado == ESTADO_BOSS) entrarNoEstado(j, ESTADO_TESOURO);
        }

        if (j->estado == ESTADO_TESOURO && noTesouro(j->jogador.x, j->jogador.y)) {
            entrarNoEstado(j, ESTADO_VITORIA);
        }
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