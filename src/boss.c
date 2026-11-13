#include <math.h>
#include "raylib.h"
#include "boss.h"
#include "sala.h"
#include "recursos.h"

void iniciarBoss(Boss *b, float x, float y) {
    b->x = x;
    b->y = y;
    b->vidaMax = 30;
    b->vida = b->vidaMax;
    b->veloc = 100;
    b->dano = 2;
    b->raio = 30;
    b->vivo = 1;
    b->olhandoEsquerda = 0;
}

void atualizarBoss(Boss *b, float alvoX, float alvoY, float dt) {
    if (!b->vivo) return;

    float dx = alvoX - b->x;
    float dy = alvoY - b->y;
    float dist = sqrtf(dx * dx + dy * dy);
    if (dist < 1.0f) return;

    float passoX = (dx / dist) * b->veloc * dt;
    float passoY = (dy / dist) * b->veloc * dt;
    if (passoX < 0) b->olhandoEsquerda = 1;
    if (passoX > 0) b->olhandoEsquerda = 0;

    if (!colideRaio(b->x + passoX, b->y, b->raio, 1)) b->x += passoX;
    if (!colideRaio(b->x, b->y + passoY, b->raio, 1)) b->y += passoY;
}

void desenharBoss(const Boss *b) {
    if (!b->vivo) return;
    desenharSpriteNoChao(SPR_DEMONIO + quadroAnimacao(QUADROS), b->x, b->y + b->raio, 3.0f, b->olhandoEsquerda);
}

void desenharBarraBoss(const Boss *b) {
    if (!b->vivo) return;

    int largura = 400;
    int x = (COLUNAS * TAM - largura) / 2;
    int y = 44;
    float proporcao = b->vida / b->vidaMax;

    DrawText("DEMONIO", x, y - 2, 18, WHITE);
    DrawRectangle(x + 90, y, largura - 90, 16, DARKGRAY);
    DrawRectangle(x + 90, y, (largura - 90) * proporcao, 16, RED);
    DrawRectangleLines(x + 90, y, largura - 90, 16, BLACK);
}

Rectangle retanguloBoss(const Boss *b) {
    Rectangle r = { b->x - b->raio, b->y - b->raio, b->raio * 2, b->raio * 2 };
    return r;
}