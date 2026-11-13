/*
 * Responsável: Jeanne
 * Etapa D - hash com encadeamento separado
 * O que faz: Implementa a tabela hash com encadeamento separado (listas nas posições), com tamanho fixo, contagem de colisões, quantidade de elementos e tamanho para o fator de carga.
 */


    #ifndef HASH_ENCADEADO_H
    #define HASH_ENCADEADO_H

    #include "registro.h"
    #include "hash_funcoes.h"

    typedef struct hash_encadeado* HashEncadeado;

    HashEncadeado criar_hash_encadeado(int tamanho, FuncaoHash funcao);
    int inserir_hash_encadeado(HashEncadeado ha, Registro* dado);
    Registro* buscar_hash_encadeado(HashEncadeado ha, int matricula);
    int colisoes_hash_encadeado(HashEncadeado ha);
    void zerar_colisoes_hash_encadeado(HashEncadeado ha);
    int qtd_elementos_hash_encadeado(HashEncadeado ha);
    int tamanho_hash_encadeado(HashEncadeado ha);
    void destruir_hash_encadeado(HashEncadeado ha);

    #endif