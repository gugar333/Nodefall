#ifndef TELAFIM_H
#define TELAFIM_H
#include "placar.h"


void desenharPlacar(const Registro *listaRegistros, int posicaoYInicial);

void telaFimIniciar(int pontuacaoFinal);
int telaFimAtualizar(void);          
void telaFimDesenhar(int jogadorVenceu);
void telaFimEncerrar(void);

#endif
