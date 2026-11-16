#include "raylib.h"
#include "sala.h"
#include "menu.h"

#define LARGURA_TELA (COLUNAS * TAM)
#define ALTURA_TELA  (LINHAS * TAM)

int atualizarMenu(void) {
    return IsKeyPressed(KEY_ENTER);
}

static void desenharTextoCentralizado(const char *texto, int posicaoY, int tamanhoFonte, Color cor) {
    int larguraTexto = MeasureText(texto, tamanhoFonte);
    DrawText(texto, (LARGURA_TELA - larguraTexto) / 2, posicaoY, tamanhoFonte, cor);
}

void desenharMenu(void) {
    desenharTextoCentralizado("NODEFALL", ALTURA_TELA / 3, 80, GOLD);
    desenharTextoCentralizado("Se a dor não me matar, ela apenas me tornará mais forte", ALTURA_TELA / 3 + 100, 18, LIGHTGRAY);
    desenharTextoCentralizado("Aperte ENTER para entrar na masmorra", ALTURA_TELA * 2 / 3, 20, RAYWHITE);
}
