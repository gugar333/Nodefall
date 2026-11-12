#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "telafim.h"
#include "placar.h"
#include "sala.h"

#define LARGURA_TELA (COLUNAS * TAM)
#define ALTURA_TELA (LINHAS * TAM)
#define FONTE_TITULO 48
#define FONTE_TEXTO 22
#define ESPACO_ENTRE_LINHAS 32

typedef enum {
    FASE_DIGITANDO_NOME,
    FASE_MOSTRANDO_PLACAR
} FaseDaTela;

static Registro *placarAtual = NULL;
static char nomeDigitado[TAMANHO_MAX_NOME];
static int tamanhoNomeDigitado = 0;
static int pontuacaoDaPartida = 0;
static FaseDaTela faseDaTela = FASE_MOSTRANDO_PLACAR;

void telaFimIniciar(int pontuacaoFinal) {
    liberarPlacar(&placarAtual);
    placarAtual = carregarPlacar(ARQUIVO_PLACAR);
    pontuacaoDaPartida = pontuacaoFinal;
    nomeDigitado[0] = '\0';
    tamanhoNomeDigitado = 0;
    faseDaTela = entraNoPlacar(placarAtual, pontuacaoFinal) ? FASE_DIGITANDO_NOME
                                                             : FASE_MOSTRANDO_PLACAR;
}

int telaFimAtualizar(void) {
    if (faseDaTela == FASE_DIGITANDO_NOME) {
        int caractereDigitado = GetCharPressed();
        while (caractereDigitado > 0) {
            int ehCaractereVisivel = caractereDigitado > 32 && caractereDigitado < 127;
            if (ehCaractereVisivel && tamanhoNomeDigitado < TAMANHO_MAX_NOME - 1) {
                nomeDigitado[tamanhoNomeDigitado++] = (char) caractereDigitado;
                nomeDigitado[tamanhoNomeDigitado] = '\0';
            }
            caractereDigitado = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && tamanhoNomeDigitado > 0) {
            nomeDigitado[--tamanhoNomeDigitado] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER)) {
            inserirRegistro(&placarAtual, nomeDigitado, pontuacaoDaPartida);
            salvarPlacar(ARQUIVO_PLACAR, placarAtual);
            faseDaTela = FASE_MOSTRANDO_PLACAR;
        }
        return 0;
    }

    return IsKeyPressed(KEY_ENTER);
}

static void desenharTextoCentralizado(const char *texto, int posicaoY, int tamanhoFonte, Color cor) {
    int larguraTexto = MeasureText(texto, tamanhoFonte);
    DrawText(texto, (LARGURA_TELA - larguraTexto) / 2, posicaoY, tamanhoFonte, cor);
}

void desenharPlacar(const Registro *listaRegistros, int posicaoYInicial) {
    char textoLinha[64];
    int posicaoY = posicaoYInicial;
    int colocacao = 1;
    for (const Registro *registro = listaRegistros; registro != NULL; registro = registro->proximo) {
        snprintf(textoLinha, sizeof(textoLinha), "%d. %-15s %6d",
                 colocacao, registro->nomeJogador, registro->pontuacao);
        desenharTextoCentralizado(textoLinha, posicaoY, FONTE_TEXTO, LIGHTGRAY);
        posicaoY += ESPACO_ENTRE_LINHAS;
        colocacao++;
    }
    if (listaRegistros == NULL) {
        desenharTextoCentralizado("(ainda vazio)", posicaoY, FONTE_TEXTO, GRAY);
    }
}

void telaFimDesenhar(int jogadorVenceu) {
    char textoPontuacao[64];

    DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, (Color){ 0, 0, 0, 220 });

    if (jogadorVenceu) desenharTextoCentralizado("VITORIA!", 30, FONTE_TITULO, GOLD);
    else desenharTextoCentralizado("DERROTA", 30, FONTE_TITULO, RED);

    snprintf(textoPontuacao, sizeof(textoPontuacao), "Pontos: %d", pontuacaoDaPartida);
    desenharTextoCentralizado(textoPontuacao, 95, 24, WHITE);

    if (faseDaTela == FASE_DIGITANDO_NOME) {
        char textoNome[TAMANHO_MAX_NOME + 2];
        desenharTextoCentralizado("Voce entrou no placar! Digite seu nome:", 150, FONTE_TEXTO, RAYWHITE);
        snprintf(textoNome, sizeof(textoNome), "%s_", nomeDigitado);
        desenharTextoCentralizado(textoNome, 190, 30, YELLOW);
        desenharTextoCentralizado("ENTER para salvar", 400, 18, LIGHTGRAY);
        return;
    }

    desenharTextoCentralizado("MELHORES PONTUACOES", 150, FONTE_TEXTO, RAYWHITE);
    desenharPlacar(placarAtual, 190);
    desenharTextoCentralizado("ENTER para jogar de novo", 420, 18, LIGHTGRAY);
}

void telaFimEncerrar(void) {
    liberarPlacar(&placarAtual);
}
