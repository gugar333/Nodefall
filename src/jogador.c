#include "raylib.h"
#include "jogador.h"
#include "sala.h"
#include "recursos.h"

void iniciarJogador(Jogador *p, float x, float y) {
    p->x = x;
    p->y = y;
    p->veloc = 200;
    p->vida = 5;
    p->invulnerab = 0;
    p->ataque = 1;
    p->arma = ARMA_NENHUMA;
    p->dirX = 0;
    p->dirY = -1;
    p->recarga = 0;
    p->tempoGolpe = 0;
    p->olhandoEsquerda = 0;
    p->andando = 0;
}

void atualizarJogador(Jogador *p, float dt, int portaTravada) {
    if (p->invulnerab > 0) p->invulnerab -= dt;
    if (p->recarga > 0) p->recarga -= dt;
    if (p->tempoGolpe > 0) p->tempoGolpe -= dt;

    float dx = 0, dy = 0;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += 1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  dx -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  dy += 1;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    dy -= 1;

    if (dx != 0 || dy != 0) {
        p->dirX = dx;
        p->dirY = dy;
    }

    if (dx < 0) p->olhandoEsquerda = 1;
    if (dx > 0) p->olhandoEsquerda = 0;
    p->andando = (dx != 0 || dy != 0);

    float novoX = p->x + dx * p->veloc * dt;
    if (!colide(novoX, p->y, portaTravada)) p->x = novoX;

    float novoY = p->y + dy * p->veloc * dt;
    if (!colide(p->x, novoY, portaTravada)) p->y = novoY;
}

void desenharJogador(const Jogador *p) {
    if (p->invulnerab > 0 && (int)(p->invulnerab * 10) % 2 == 0) return;

    Sprite base = p->andando ? SPR_CAVALEIRO_CORRENDO : SPR_CAVALEIRO_PARADO;
    desenharSpriteNoChao(base + quadroAnimacao(QUADROS), p->x, p->y + 14, 2.5f, p->olhandoEsquerda);

    float armaX = p->olhandoEsquerda ? p->x - 36 : p->x + 8;
    desenharArma(p->arma, armaX, p->y - 16, 0.7f, p->olhandoEsquerda);

    if (p->tempoGolpe > 0) {
        DrawRectangleRec(areaGolpe(p), Fade(WHITE, 0.5f));
    }
}

Rectangle retanguloJogador(const Jogador *p) {
    Rectangle r = { p->x - 14, p->y - 14, 28, 28 };
    return r;
}

Rectangle areaGolpe(const Jogador *p) {
    float cx = p->x + p->dirX * 34;
    float cy = p->y + p->dirY * 34;
    Rectangle r = { cx - 20, cy - 20, 40, 40 };
    return r;
}