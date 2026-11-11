/*
 * Responsável: Jeanne
 * Etapa A - base e estrutura linear
 * O que faz: Lê o arquivo da base uma única vez, preservando a ordem dos registros, e guarda tudo em um vetor. O tempo de leitura não entra nas medições.
 */

#ifndef LEITURA_H
#define LEITURA_H

#include "registro.h"

Registro *ler_base(char *nome_arquivo, int limite, int *total_lido);
void liberar_base(Registro *registros);

#endif