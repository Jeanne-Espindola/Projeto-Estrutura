#ifndef HASH_ABERTO_H
#define HASH_ABERTO_H

#include "registro.h"

typedef int (*FuncHashAbertoPtr)(int chave, int TABLE_SIZE);

typedef struct hash_aberto *HashAberto;


HashAberto criar_hash_aberto(int tamanho, FuncHashAbertoPtr funcao);


int inserir_hash_aberto(HashAberto h, Registro *dado);


Registro *buscar_hash_aberto(HashAberto h, int matricula);


int colisoes_hash_aberto(HashAberto h);
void zerar_colisoes_hash_aberto(HashAberto h);

int qtd_elementos_hash_aberto(HashAberto h);
int tamanho_hash_aberto(HashAberto h);


double fator_carga_hash_aberto(HashAberto h);


void destruir_hash_aberto(HashAberto h);

#endif