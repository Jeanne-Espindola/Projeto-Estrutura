
#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"

Registro *ler_base(char *nome_arquivo, int limite, int *total_lido){

    *total_lido = 0;

    FILE *arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }

    Registro *registros = malloc(limite * sizeof(Registro));

    if(registros == NULL){
        printf("Sem memoria\n");
        fclose(arquivo);
        return NULL;
    }

    char linha[512];
    int i = 0;

    while(i < limite && fgets(linha, 512, arquivo) != NULL){

        if(sscanf(linha, "%d;%99[^;];%99[^\r\n]", &registros[i].matricula, registros[i].nome,registros[i].curso) == 3){

            i++;
        }
    }

    fclose(arquivo);

    *total_lido = i;

    return registros;
}

void liberar_base(Registro *registros){
    free(registros);
}
