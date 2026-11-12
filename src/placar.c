#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "placar.h"

static int contarRegistros(const Registro *listaRegistros) {
    int quantidade = 0;
    for (const Registro *atual = listaRegistros; atual != NULL; atual = atual->proximo) {
        quantidade++;
    }
    return quantidade;
}

int entraNoPlacar(const Registro *listaRegistros, int pontuacao) {
    if (contarRegistros(listaRegistros) < MAX_REGISTROS) return 1;

    const Registro *ultimoRegistro = listaRegistros;
    while (ultimoRegistro->proximo != NULL) ultimoRegistro = ultimoRegistro->proximo;
    return pontuacao > ultimoRegistro->pontuacao;
}

void inserirRegistro(Registro **listaRegistros, const char *nomeJogador, int pontuacao) {
    Registro *novoRegistro = (Registro *) malloc(sizeof(Registro));
    if (novoRegistro == NULL) return;

    strncpy(novoRegistro->nomeJogador, nomeJogador, TAMANHO_MAX_NOME - 1);
    novoRegistro->nomeJogador[TAMANHO_MAX_NOME - 1] = '\0';
    if (novoRegistro->nomeJogador[0] == '\0') strcpy(novoRegistro->nomeJogador, "ANONIMO");
    for (char *caractere = novoRegistro->nomeJogador; *caractere != '\0'; caractere++) {
        if (*caractere == ' ') *caractere = '_';
    }
    novoRegistro->pontuacao = pontuacao;
    Registro **ligacao = listaRegistros;
    while (*ligacao != NULL && (*ligacao)->pontuacao >= pontuacao) {
        ligacao = &(*ligacao)->proximo;
    }
    novoRegistro->proximo = *ligacao;
    *ligacao = novoRegistro;

    int posicao = 0;
    ligacao = listaRegistros;
    while (*ligacao != NULL) {
        if (posicao >= MAX_REGISTROS) {
            Registro *registroExcedente = *ligacao;
            *ligacao = registroExcedente->proximo;
            free(registroExcedente);
        } else {
            ligacao = &(*ligacao)->proximo;
            posicao++;
        }
    }
}

Registro *carregarPlacar(const char *caminhoArquivo) {
    Registro *listaRegistros = NULL;
    FILE *arquivo = fopen(caminhoArquivo, "r");
    if (arquivo == NULL) return NULL;

    char nomeLido[TAMANHO_MAX_NOME];
    int pontuacaoLida;
    while (fscanf(arquivo, "%15s %d", nomeLido, &pontuacaoLida) == 2) {
        inserirRegistro(&listaRegistros, nomeLido, pontuacaoLida);
    }
    fclose(arquivo);
    return listaRegistros;
}

int salvarPlacar(const char *caminhoArquivo, const Registro *listaRegistros) {
    FILE *arquivo = fopen(caminhoArquivo, "w");
    if (arquivo == NULL) return -1;

    for (const Registro *atual = listaRegistros; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "%s %d\n", atual->nomeJogador, atual->pontuacao);
    }
    fclose(arquivo);
    return 0;
}

void liberarPlacar(Registro **listaRegistros) {
    while (*listaRegistros != NULL) {
        Registro *registroAtual = *listaRegistros;
        *listaRegistros = registroAtual->proximo;
        free(registroAtual);
    }
}
