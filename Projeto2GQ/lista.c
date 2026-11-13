/*
 * Responsável: Jeanne
 * Etapa A - base e estrutura linear
 * O que faz: Implementa a estrutura linear (lista encadeada) com criar, inserir, buscar e liberar, como TAD.
 */

    #include <stdio.h>
    #include <stdlib.h>
    #include "lista.h"

     struct elemento{
        Registro* dado;
        struct elemento* prox;
    };

    typedef struct elemento Elem;

    struct lista{
        Elem* inicio;
        int qtd;
    };

    

    Lista criar_lista(){
        Lista li = malloc(sizeof(struct lista));
        if(li != NULL){
            li->inicio = NULL;
            li->qtd = 0;
    }
        return li;
 }

    int inserir_inicio(Lista li, Registro* dado){
        if(li == NULL){
            return 0;
    }

    Elem* no = malloc(sizeof(struct elem));
    if(no == NULL){
        return 0;
    }

    no->valor = dado;
    no->prox = li->inicio;
    li->qtd++;
    return 1;
}

//buscar

Registro* buscar_matricula(Lista li, int matricula){
    if(li == NULL){
        return 0;
    }

    Elem* aux = li->inicio;

    while(aux != NULL){
        if(aux->dado->matricula == matricula){
            return aux->dado;
        }
        aux = aux->prox;
    }

    return NULL;
}


int qtd_elementos(Lista li){
    if(li == NULL){
        return 0;
    }

    return li->qtd;
}

void destruir(Lista li){
    if(li == NULL){
        return 0;
    }

    Elem* aux = li->inicio;
    while(aux != NULL){
        Elem* ant = aux;
        aux = aux->prox;
        free(ant);
    }
    free(li);
}