#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct Jogador {
    float x, y;
    float veloc;
    float vida;
    float invulnerab;
    float ataque;
} Jogador;

void iniciarJogador(Jogador *p, float x, float y);
void atualizarJogador(Jogador *p, float dt);
void desenharJogador(const Jogador *p);

#endif