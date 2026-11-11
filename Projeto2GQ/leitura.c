/*
 * Responsável: Jeanne
 * Etapa A - base e estrutura linear
 * O que faz: Lê o arquivo da base uma única vez, preservando a ordem dos registros, e guarda tudo em um vetor. O tempo de leitura não entra nas medições.
 */

    #include <stdio.h>
    #include <stdlib.h>
    #include "leitura.h"

    Registro *ler_base(char *nome_arquivo, int limite, int *total_lido) {
        *total_lido = 0;

    FILE *arquivo = fopen(nome_arquivo, "r");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo\n");
            return NULL;
    }

    Registro *registros = malloc(limite * sizeof(Registro));
        if (registros == NULL) {
            printf("Sem memoria\n");
            fclose(arquivo);
                return NULL;
    }

    char primeira_linha[512];
    fgets(primeira_linha, 512, arquivo);   /* pula a primeira linha: tirar se o arquivo NAO tiver cabecalho */

    int i = 0;
    while (i < limite &&
           fscanf(arquivo, "%d,%99[^,],%99[^\n]\n",
                  &registros[i].matricula, registros[i].nome, registros[i].curso) == 3) {
        i++;
    }

    fclose(arquivo);
    *total_lido = i;
    return registros;
}

void liberar_base(Registro *registros) {
    free(registros);
}