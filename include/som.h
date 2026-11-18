#ifndef SOM_H
#define SOM_H

typedef enum {
    SOM_ESPADA,
    SOM_FLECHA,
    SOM_INIMIGO_MORRE,
    SOM_DANO,
    SOM_DESPERTAR,
    SOM_VITORIA,
    SOM_DERROTA,
    SOM_BOSS_MORRE,
    SOM_TOTAL
} Som;

void carregarSons(void);
void descarregarSons(void);
void tocarSom(Som som);
void tocarMusicaMenu(void);
void atualizarMusica(void);
void pararMusicaMenu(void);

#endif
