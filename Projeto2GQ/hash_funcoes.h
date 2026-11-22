#ifndef HASH_FUNCOES_H
#define HASH_FUNCOES_H

typedef int (*funcaoHash)(int chave, int TABLE_SIZE);
int FuncaoHashDiv(int chave, int TABLE_SIZE);
int FuncHashDobra(int chave, int TABLE_SIZE);

#endif
