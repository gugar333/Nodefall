#include "raylib.h"
#include "sala.h"
#include "menu.h"

#define LARGURA_TELA (COLUNAS * TAM)
#define ALTURA_TELA  (LINHAS * TAM)

static Texture2D fundoMenu;

void carregarMenu(void) {
    fundoMenu = LoadTexture("assets/menu_fundo.png");
}

void descarregarMenu(void) {
    UnloadTexture(fundoMenu);
}

int atualizarMenu(void) {
    return IsKeyPressed(KEY_ENTER);
}

static void desenharTextoCentralizado(const char *texto, int posicaoY, int tamanhoFonte, Color cor) {
    int larguraTexto = MeasureText(texto, tamanhoFonte);
    DrawText(texto, (LARGURA_TELA - larguraTexto) / 2, posicaoY, tamanhoFonte, cor);
}

void desenharMenu(void) {
    Rectangle origem = { 0, 0, fundoMenu.width, fundoMenu.height };
    Rectangle destino = { 0, 0, LARGURA_TELA, ALTURA_TELA };
    Vector2 centro = { 0, 0 };
    DrawTexturePro(fundoMenu, origem, destino, centro, 0, WHITE);

    desenharTextoCentralizado("NODEFALL", 45, 80, GOLD);

    DrawRectangle(0, ALTURA_TELA - 88, LARGURA_TELA, 88, Fade(BLACK, 0.6f));
    desenharTextoCentralizado("Se a dor não me matar, ela apenas me tornará mais forte", ALTURA_TELA - 75, 18, LIGHTGRAY);
    desenharTextoCentralizado("Aperte ENTER para entrar na masmorra", ALTURA_TELA - 40, 20, RAYWHITE);
}
