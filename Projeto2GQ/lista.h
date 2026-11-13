/*
 * Responsável: Jeanne
 * Etapa A - base e estrutura linear
 * O que faz: Implementa a estrutura linear (lista encadeada) com criar, inserir, buscar e liberar, como TAD.
 */

    #ifndef LISTA_H
    #ifndef LISTA_H
    #define LISTA_H

    #include "registro.h"

    typedef struct lista* Lista;

    Lista criar_lista();
    int inserir_inicio(Lista li, Registro* dado);
    Registro* buscar_matricula(Lista li, int matricula);
    int qtd_elementos(Lista li);
    void destruir(Lista li);

#endif

    #endif