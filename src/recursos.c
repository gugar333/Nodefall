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
    "assets/floor_stairs.png",
    "assets/knight_m_idle_anim_f0.png",
    "assets/knight_m_idle_anim_f1.png",
    "assets/knight_m_idle_anim_f2.png",
    "assets/knight_m_idle_anim_f3.png",
    "assets/knight_m_run_anim_f0.png",
    "assets/knight_m_run_anim_f1.png",
    "assets/knight_m_run_anim_f2.png",
    "assets/knight_m_run_anim_f3.png",
    "assets/skelet_run_anim_f0.png",
    "assets/skelet_run_anim_f1.png",
    "assets/skelet_run_anim_f2.png",
    "assets/skelet_run_anim_f3.png",
    "assets/imp_run_anim_f0.png",
    "assets/imp_run_anim_f1.png",
    "assets/imp_run_anim_f2.png",
    "assets/imp_run_anim_f3.png",
    "assets/ogre_run_anim_f0.png",
    "assets/ogre_run_anim_f1.png",
    "assets/ogre_run_anim_f2.png",
    "assets/ogre_run_anim_f3.png",
    "assets/weapon_knight_sword.png",
    "assets/weapon_bow.png",
    "assets/wall_banner_red.png",
    "assets/wall_banner_blue.png",
    "assets/wall_banner_green.png",
    "assets/wall_banner_yellow.png",
    "assets/wall_fountain_mid_red_anim_f0.png",
    "assets/wall_fountain_mid_red_anim_f1.png",
    "assets/wall_fountain_mid_red_anim_f2.png",
    "assets/wall_fountain_basin_red_anim_f0.png",
    "assets/wall_fountain_basin_red_anim_f1.png",
    "assets/wall_fountain_basin_red_anim_f2.png",
    "assets/skull.png",
    "assets/coin_anim_f0.png",
    "assets/coin_anim_f1.png",
    "assets/coin_anim_f2.png",
    "assets/coin_anim_f3.png",
    "assets/big_demon_run_anim_f0.png",
    "assets/big_demon_run_anim_f1.png",
    "assets/big_demon_run_anim_f2.png",
    "assets/big_demon_run_anim_f3.png"
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

void desenharSpriteNoChao(Sprite s, float centroX, float chaoY, float escala, int virado) {
    Texture2D t = texturas[s];
    float largura = t.width * escala;
    float altura = t.height * escala;
    Rectangle origem = { 0, 0, virado ? -t.width : t.width, t.height };
    Rectangle destino = { centroX - largura / 2, chaoY - altura, largura, altura };
    Vector2 centro = { 0, 0 };
    DrawTexturePro(t, origem, destino, centro, 0, WHITE);
}

int quadroAnimacao(int total) {
    return (int)(GetTime() * 8) % total;
}