#include "raylib.h"
#include "sala.h"
#include "jogo.h"

int main(void) {
    InitWindow(COLUNAS * TAM, LINHAS * TAM, "Nodefall");
    SetTargetFPS(60);

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
    CloseWindow();
    return 0;
}

