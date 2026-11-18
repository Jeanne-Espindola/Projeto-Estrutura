#include <stdio.h>
#include <stdlib.h>

int FuncaoHash(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

int FuncHashDobra(int chave, int TABLE_SIZE){
    int parte_1 = chave / 100;
    int parte_2 = chave % 100;
    int soma = (parte_1 + parte_2);
    while(soma > TABLE_SIZE){
        soma = (soma/10) + (soma % 10);

    }
    return soma % TABLE_SIZE;
}
