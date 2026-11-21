#include <stdio.h>
#include <stdlib.h>

int FuncaoHashDiv(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

int FuncHashDobra(int chave, int TABLE_SIZE){
    if (TABLE_SIZE <= 0){
        return 0;
    }
    int k = chave & 0x7FFFFFFF;
    int soma = 0;

    while(k > 0){
        soma += k % 10000;
        k /= 10000;

    }
    return (soma * 17) % TABLE_SIZE;
}
