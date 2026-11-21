#ifndef LEITURA_H
#define LEITURA_H

#include "registro.h"

Registro *ler_base(char *nome_arquivo, int limite, int *total_lido);
void liberar_base(Registro *registros);

#endif