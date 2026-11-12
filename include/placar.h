#ifndef PLACAR_H
#define PLACAR_H

#define ARQUIVO_PLACAR "placar.txt"
#define MAX_REGISTROS 5
#define TAMANHO_MAX_NOME 16

typedef struct Registro {
    char nomeJogador[TAMANHO_MAX_NOME];
    int pontuacao;
    struct Registro *proximo;
} Registro;

Registro *carregarPlacar(const char *caminhoArquivo);

int salvarPlacar(const char *caminhoArquivo, const Registro *listaRegistros);

int entraNoPlacar(const Registro *listaRegistros, int pontuacao);

void inserirRegistro(Registro **listaRegistros, const char *nomeJogador, int pontuacao);

void liberarPlacar(Registro **listaRegistros);

#endif
