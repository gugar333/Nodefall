#ifndef SALA_H
#define SALA_H

#define LINHAS 12
#define COLUNAS 20
#define TAM 40

int bloqueado(float px, float py, int porta_travada);
int colide(float x, float y, int porta_travada);
void desenharSala(void);

#endif