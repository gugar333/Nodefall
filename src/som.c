#include "raylib.h"
#include "som.h"

static const char *arquivosSom[SOM_TOTAL] = {
    "assets/sons/espada.wav",
    "assets/sons/flecha.wav",
    "assets/sons/inimigo_morre.wav",
    "assets/sons/dano.wav",
    "assets/sons/despertar.wav",
    "assets/sons/vitoria.wav",
    "assets/sons/derrota.wav"
};

static Sound sons[SOM_TOTAL];
static Music musicaMenu;

void carregarSons(void) {
    InitAudioDevice();
    for (int i = 0; i < SOM_TOTAL; i++) {
        sons[i] = LoadSound(arquivosSom[i]);
    }
    musicaMenu = LoadMusicStream("assets/sons/musica_menu.mp3");
}

void descarregarSons(void) {
    for (int i = 0; i < SOM_TOTAL; i++) {
        UnloadSound(sons[i]);
    }
    UnloadMusicStream(musicaMenu);
    CloseAudioDevice();
}

void tocarSom(Som som) {
    PlaySound(sons[som]);
}

void tocarMusicaMenu(void) {
    if (!IsMusicStreamPlaying(musicaMenu)) PlayMusicStream(musicaMenu);
}

void atualizarMusica(void) {
    UpdateMusicStream(musicaMenu);
}

void pararMusicaMenu(void) {
    StopMusicStream(musicaMenu);
}
