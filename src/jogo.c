#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "sala.h"

#define INICIO_X (COLUNAS * TAM / 2.0f)
#define INICIO_Y (9 * TAM + TAM / 2.0f)

static const char *nomesEstados[ESTADO_TOTAL] = {
    "MENU", "ARSENAL", "ONDAS", "BOSS", "TESOURO", "VITORIA", "DERROTA"
};

static const Rectangle pedestalEspada = { 5 * TAM, 5 * TAM, TAM, TAM };
static const Rectangle pedestalArco = { 14 * TAM, 5 * TAM, TAM, TAM };

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

    j->portaTravada = (e == ESTADO_ARSENAL && j->jogador.arma == ARMA_NENHUMA);
}

static Rectangle alcance(Rectangle pedestal) {
    Rectangle r = { pedestal.x - 10, pedestal.y - 10, pedestal.width + 20, pedestal.height + 20 };
    return r;
}

static void atualizarArsenal(Jogo *j) {
    if (j->jogador.arma != ARMA_NENHUMA) return;
    if (!IsKeyPressed(KEY_E)) return;

    Rectangle r = retanguloJogador(&j->jogador);
    if (CheckCollisionRecs(r, alcance(pedestalEspada))) j->jogador.arma = ARMA_ESPADA;
    else if (CheckCollisionRecs(r, alcance(pedestalArco))) j->jogador.arma = ARMA_ARCO;

    if (j->jogador.arma != ARMA_NENHUMA) {
        j->portaTravada = 0;
    }
}

static void desenharArsenal(const Jogo *j) {
    if (j->jogador.arma != ARMA_NENHUMA) return;

    desenharArma(ARMA_ESPADA, pedestalEspada.x, pedestalEspada.y - 30, 1.0f);
    DrawText("ESPADA", pedestalEspada.x - 10, pedestalEspada.y - 50, 16, BLACK);

    desenharArma(ARMA_ARCO, pedestalArco.x, pedestalArco.y - 30, 1.0f);
    DrawText("ARCO", pedestalArco.x, pedestalArco.y - 50, 16, BLACK);

    const char *dica = "Fique ao lado de um pedestal e aperte E para pegar a arma";
    int largura = MeasureText(dica, 18);
    DrawText(dica, (COLUNAS * TAM - largura) / 2, 10 * TAM + 10, 18, DARKGRAY);
}

void iniciarJogo(Jogo *j) {
    iniciarJogador(&j->jogador, INICIO_X, INICIO_Y);
    j->inimigos = NULL;
    inserirInimigo(&j->inimigos, INIMIGO_SERVO,       100, 100);
    inserirInimigo(&j->inimigos, INIMIGO_CORREDOR,    400, 100);
    inserirInimigo(&j->inimigos, INIMIGO_BRUTAMONTES, 700, 100);
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
        atualizarInimigos(j->inimigos, j->jogador.x, j->jogador.y, GetFrameTime());

        if (j->estado == ESTADO_ARSENAL) {
            atualizarArsenal(j);
        }

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
        if (j->estado == ESTADO_ARSENAL) {
            desenharArsenal(j);
        }
        desenharJogador(&j->jogador);
        desenharInimigos(j->inimigos);
    }
    DrawText(nomesEstados[j->estado], 10, 10, 20, WHITE);
}

void encerrarJogo(Jogo *j) {
    liberar(&j->inimigos);
}