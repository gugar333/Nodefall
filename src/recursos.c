#include "raylib.h"
#include "recursos.h"

static const char *arquivos[SPR_TOTAL] = {
    "assets/floor_1.png",
    "assets/floor_2.png",
    "assets/floor_3.png",
    "assets/wall_mid.png",
    "assets/doors_leaf_closed.png",
    "assets/doors_leaf_open.png",
    "assets/column.png",
    "assets/chest_full_open_anim_f0.png",
    "assets/floor_stairs.png"
};

static Texture2D texturas[SPR_TOTAL];

void carregarRecursos(void) {
    for (int i = 0; i < SPR_TOTAL; i++) {
        texturas[i] = LoadTexture(arquivos[i]);
    }
}

void descarregarRecursos(void) {
    for (int i = 0; i < SPR_TOTAL; i++) {
        UnloadTexture(texturas[i]);
    }
}

void desenharSprite(Sprite s, float x, float y, float largura, float altura) {
    Texture2D t = texturas[s];
    Rectangle origem = { 0, 0, t.width, t.height };
    Rectangle destino = { x, y, largura, altura };
    Vector2 centro = { 0, 0 };
    DrawTexturePro(t, origem, destino, centro, 0, WHITE);
}

void desenharSpriteGirado(Sprite s, float x, float y, float tamanho, float angulo) {
    Texture2D t = texturas[s];
    Rectangle origem = { 0, 0, t.width, t.height };
    Rectangle destino = { x + tamanho / 2, y + tamanho / 2, tamanho, tamanho };
    Vector2 centro = { tamanho / 2, tamanho / 2 };
    DrawTexturePro(t, origem, destino, centro, angulo, WHITE);
}