#include "raylib.h"
#include "sala.h"
#include "jogo.h"
#include "recursos.h"
#include "som.h"

int main(void) {
    InitWindow(COLUNAS * TAM, LINHAS * TAM, "Nodefall");
    SetTargetFPS(60);
    carregarRecursos();
    carregarSons();

    Jogo jogo;
    iniciarJogo(&jogo);

    while (!WindowShouldClose()) {
        atualizarJogo(&jogo);

        BeginDrawing();
        ClearBackground(BLACK);
        desenharJogo(&jogo);
        EndDrawing();
    }

    encerrarJogo(&jogo);
    descarregarSons();
    descarregarRecursos();
    CloseWindow();
    return 0;
}