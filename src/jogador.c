#include "raylib.h"
#include "jogador.h"
#include "sala.h"

void iniciarJogador(Jogador *p, float x, float y) {
    p->x = x;
    p->y = y;
    p->veloc = 200;
    p->vida = 5;
    p->invulnerab = 0;
    p->ataque = 1;
}

void atualizarJogador(Jogador *p, float dt) {
    float dx = 0, dy = 0;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += 1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  dx -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  dy += 1;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    dy -= 1;

    float novoX = p->x + dx * p->veloc * dt;
    if (!colide(novoX, p->y, 1)) p->x = novoX;

    float novoY = p->y + dy * p->veloc * dt;
    if (!colide(p->x, novoY, 1)) p->y = novoY;
}

void desenharJogador(const Jogador *p) {
    DrawRectangle(p->x - 14, p->y - 14, 28, 28, BLUE);
}