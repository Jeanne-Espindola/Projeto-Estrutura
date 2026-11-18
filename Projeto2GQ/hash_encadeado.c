/*
 * Responsável: Jeanne
 * Etapa D - hash com encadeamento separado
 * O que faz: Implementa a tabela hash com encadeamento separado (listas nas posições), com tamanho fixo, contagem de colisões, quantidade de elementos e tamanho para o fator de carga.
 */
#include <stdio.h>
#include <stdlib.h>

#include "hash_encadeado.h"
#include "lista.h"

struct hash_encadeado{
    Lista* posicoes;
    int tamanho;
    int qtd;
    int colisoes;
    FuncaoHash funcao;
}

HashEncadeado criar_hash_encadeado(int tamanho, FuncaoHash funcao){
    HashEncadeado h = malloc(sizeof(struct HashEncadeado));
    if(h != NULL){
        h->posicoes = malloc(tamanho * sizeof(struct lista));
        if(h->posicoes == NULL){
            free(h);
            return NULL;
        }

        int i;
        for(i = 0; i < tamanho; i++){
            h[i]->posicoes = NULL;
        }

        h->tamanho = tamanho;
        h->qtd = 0;
        h->colisoes = 0;
        h->funcao = funcao;
    }
    return h;
}

int inserir_hash_encadeado(HashEncadeado h, Registro* dado){
    if(h == NULL || dado == NULL){
        return 0;
    }

    int pos = h->funcao(dado->matricula, h->tamanho);

    if(h->posicoes[pos] == NULL){

        h->posicoes[pos] = criar_lista(); 

        if(h->posicoes[pos] == NULL){
            return 0;
        }
    }

    else{
        h->colisoes++;
    }

    if(inserir_inicio(h->posicoes[pos], dado)){
        h->qtd++;
        return 1;
    }

    return 0;
}

//buscar












void zerar_colisoes_hash_aberto(HashAberto ha){
    if(ha == NULL){
        return;
    }
    ha->colisoes = 0;
}

int qtd_elementos_hash_aberto(HashAberto ha){
    if(ha == NULL){
        return 0;
    }
    return ha->qtd;
}

int tamanho_hash_aberto(HashAberto ha){
    if(ha == NULL){
        return 0;
    }
    return ha->tamanho;
}


//destruir




