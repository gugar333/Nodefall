#include "raylib.h"
#include "sala.h"
#include "jogo.h"
#include "recursos.h"
#include "som.h"
#include "menu.h"

int main(void) {
    InitWindow(COLUNAS * TAM, LINHAS * TAM, "Nodefall");
    SetTargetFPS(60);
    carregarRecursos();
    carregarSons();
    carregarMenu();

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
    descarregarMenu();
    descarregarSons();
    descarregarRecursos();
    CloseWindow();
    return 0;
}