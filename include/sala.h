#ifndef SALA_H
#define SALA_H

#define LINHAS 12
#define COLUNAS 20
#define TAM 40
#define NUM_SALAS 4

void mudarSala(int indice);
int bloqueado(float px, float py, int porta_travada);
int colideRaio(float x, float y, float m, int porta_travada);
int colide(float x, float y, int porta_travada);
int naPorta(float x, float y);
int noTesouro(float x, float y);
void desenharSala(void);

#endif