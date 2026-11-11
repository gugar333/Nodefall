#include "raylib.h"
#include "sala.h"
#include "jogo.h"
#include "recursos.h"

int main(void) {
    InitWindow(COLUNAS * TAM, LINHAS * TAM, "Nodefall");
    SetTargetFPS(60);
    carregarRecursos();

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
    descarregarRecursos();
    CloseWindow();
    return 0;
}