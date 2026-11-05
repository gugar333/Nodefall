#include "raylib.h"

#include "sala.h"
#include "inimigo.h"
#include "jogador.h"

int main(void) {
    InitWindow(COLUNAS * TAM, LINHAS * TAM, "Nodefall");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        desenharSala();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


