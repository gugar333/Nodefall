#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "sala.h"

#define INICIO_X (COLUNAS * TAM / 2.0f)
#define INICIO_Y (9 * TAM + TAM / 2.0f)

static const char *nomesEstados[ESTADO_TOTAL] = {
    "MENU", "ARSENAL", "ONDAS", "BOSS", "TESOURO", "VITORIA", "DERROTA"
};

static const Rectangle pedestalEspada = { 4 * TAM, 5 * TAM, TAM, 2 * TAM };
static const Rectangle pedestalArco = { 15 * TAM, 5 * TAM, TAM, 2 * TAM };

static int emSala(Estado e) {
    return e == ESTADO_ARSENAL || e == ESTADO_ONDAS || e == ESTADO_BOSS || e == ESTADO_TESOURO;
}

static void entrarNoEstado(Jogo *j, Estado e) {
    j->estado = e;

    if (e == ESTADO_ARSENAL) mudarSala(0);
    else if (e == ESTADO_ONDAS) mudarSala(1);
    else if (e == ESTADO_BOSS) mudarSala(2);
    else if (e == ESTADO_TESOURO) mudarSala(3);
    liberar(&j->inimigos);
    if (e == ESTADO_ONDAS) {
        inserirInimigo(&j->inimigos, INIMIGO_SERVO,       2 * TAM + TAM / 2, 2 * TAM + TAM / 2);
        inserirInimigo(&j->inimigos, INIMIGO_CORREDOR,    17 * TAM + TAM / 2, 2 * TAM + TAM / 2);
        inserirInimigo(&j->inimigos, INIMIGO_BRUTAMONTES, 2 * TAM + TAM / 2, 9 * TAM + TAM / 2);
    }

    if (emSala(e)) {
        j->jogador.x = INICIO_X;
        j->jogador.y = INICIO_Y;
    }

    j->portaTravada = (e == ESTADO_ARSENAL && j->jogador.arma == ARMA_NENHUMA) || e == ESTADO_ONDAS;
}

static Rectangle alcance(Rectangle pedestal) {
    Rectangle r = { pedestal.x - 10, pedestal.y - 10, pedestal.width + 20, pedestal.height + 20 };
    return r;
}

static void atualizarArsenal(Jogo *j) {
    if (j->jogador.arma != ARMA_NENHUMA) return;
    if (!IsKeyPressed(KEY_E)) return;

    Rectangle r = retanguloJogador(&j->jogador);
        if (CheckCollisionRecs(r, alcance(pedestalEspada))) {
        j->jogador.arma = ARMA_ESPADA;
        j->jogador.ataque = 2;
    } else if (CheckCollisionRecs(r, alcance(pedestalArco))) {
        j->jogador.arma = ARMA_ARCO;
        j->jogador.ataque = 1;
    }

    if (j->jogador.arma != ARMA_NENHUMA) {
        j->portaTravada = 0;
    }
}

static void desenharArsenal(const Jogo *j) {
    if (j->jogador.arma != ARMA_NENHUMA) return;

    desenharArma(ARMA_ESPADA, pedestalEspada.x, pedestalEspada.y - 45, 1.0f);
    DrawText("ESPADA", pedestalEspada.x - 10, pedestalEspada.y - 65, 16, WHITE);

    desenharArma(ARMA_ARCO, pedestalArco.x, pedestalArco.y - 45, 1.0f);
    DrawText("ARCO", pedestalArco.x, pedestalArco.y - 65, 16, WHITE);

    DrawText("E: pegar a arma (ao lado da coluna)", 10, LINHAS * TAM - 28, 16, WHITE);
}

static void verificarDano(Jogo *j) {
    if (j->jogador.invulnerab > 0) return;

    Rectangle r = retanguloJogador(&j->jogador);
    for (Inimigo *i = j->inimigos; i != NULL; i = i->prox) {
        if (CheckCollisionRecs(r, retanguloInimigo(i))) {
            j->jogador.vida -= i->dano;
            j->jogador.invulnerab = 1.0f;
            break;
        }
    }

    if (j->jogador.vida <= 0) {
        entrarNoEstado(j, ESTADO_DERROTA);
    }
}

static void atacarComEspada(Jogo *j) {
    if (j->jogador.arma != ARMA_ESPADA) return;
    if (!IsKeyPressed(KEY_SPACE) || j->jogador.recarga > 0) return;

    j->jogador.recarga = 0.4f;
    j->jogador.tempoGolpe = 0.15f;

    Rectangle golpe = areaGolpe(&j->jogador);
    for (Inimigo *i = j->inimigos; i != NULL; i = i->prox) {
        if (CheckCollisionRecs(golpe, retanguloInimigo(i))) {
            i->vida -= j->jogador.ataque;
        }
    }

    removerMortos(&j->inimigos);
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

    if (j->estado == ESTADO_DERROTA && IsKeyPressed(KEY_ENTER)) {
    liberar(&j->inimigos);
    iniciarJogo(j);
    }

    if (emSala(j->estado)) {
        atualizarJogador(&j->jogador, GetFrameTime(), j->portaTravada);
        atualizarInimigos(j->inimigos, j->jogador.x, j->jogador.y, GetFrameTime());
        atacarComEspada(j);
        verificarDano(j);
        if (j->estado == ESTADO_ONDAS && contarInimigos(j->inimigos) == 0) {
            j->portaTravada = 0;
        }

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
        desenharSala(j->portaTravada);
        if (j->estado == ESTADO_ARSENAL) {
            desenharArsenal(j);
        }
        desenharInimigos(j->inimigos);
        desenharJogador(&j->jogador);
    }
        if (j->estado == ESTADO_DERROTA) {
        const char *msg = "Voce perdeu! Aperte ENTER para tentar de novo";
        int largura = MeasureText(msg, 24);
        DrawText(msg, (COLUNAS * TAM - largura) / 2, LINHAS * TAM / 2, 24, RED);
    }

    DrawText(nomesEstados[j->estado], 10, 10, 20, WHITE);
    DrawText(TextFormat("Vida: %d", (int)j->jogador.vida), COLUNAS * TAM - 100, 10, 20, WHITE);
}

void encerrarJogo(Jogo *j) {
    liberar(&j->inimigos);
}