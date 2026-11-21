
#include <stdlib.h>
#include "hash_aberto.h"

struct hash_aberto {
    Registro **posicoes;        
    unsigned char *inicial;    
    int tamanho;               
    int qtd;                    
    int colisoes;               
    FuncHashAbertoPtr funcao;
};

HashAberto criar_hash_aberto(int tamanho, FuncHashAbertoPtr funcao){
    if(tamanho <= 0 || funcao == NULL){
        return NULL;
    }

    HashAberto h = malloc(sizeof(struct hash_aberto));
    if(h == NULL){
        return NULL;
    }

    h->posicoes = calloc(tamanho, sizeof(Registro *));
    h->inicial = calloc(tamanho, sizeof(unsigned char));
    if(h->posicoes == NULL || h->inicial == NULL){
        free(h->posicoes);
        free(h->inicial);
        free(h);
        return NULL;
    }

    h->tamanho = tamanho;
    h->qtd = 0;
    h->colisoes = 0;
    h->funcao = funcao;
    return h;
}


static int indice_inicial(HashAberto h, int chave){
    int pos = h->funcao(chave, h->tamanho) % h->tamanho;
    if(pos < 0){
        pos += h->tamanho;
    }
    return pos;
}

int inserir_hash_aberto(HashAberto h, Registro *dado){
    if(h == NULL || dado == NULL || h->qtd >= h->tamanho){
        return 0;
    }

    int inicio = indice_inicial(h, dado->matricula);


    if(h->inicial[inicio]){
        h->colisoes++;
    }
    else{
        h->inicial[inicio] = 1;
    }


    int i;
    for(i = 0; i < h->tamanho; i++){
        int pos = (inicio + i) % h->tamanho;
        if(h->posicoes[pos] == NULL){
            h->posicoes[pos] = dado;
            h->qtd++;
            return 1;
        }
        if(h->posicoes[pos]->matricula == dado->matricula){
            return 0; 
        }
    }
    return 0;
}

Registro *buscar_hash_aberto(HashAberto h, int matricula){
    if(h == NULL){
        return NULL;
    }

    int inicio = indice_inicial(h, matricula);

    int i;
    for(i = 0; i < h->tamanho; i++){
        int pos = (inicio + i) % h->tamanho;
        if(h->posicoes[pos] == NULL){
            return NULL; 
        }
        if(h->posicoes[pos]->matricula == matricula){
            return h->posicoes[pos];
        }
    }
    return NULL;
}

int colisoes_hash_aberto(HashAberto h){
    if(h == NULL){
        return 0;
    }
    return h->colisoes;
}

void zerar_colisoes_hash_aberto(HashAberto h){
    if(h == NULL){
        return;
    }
    h->colisoes = 0;
}

int qtd_elementos_hash_aberto(HashAberto h){
    if(h == NULL){
        return 0;
    }
    return h->qtd;
}

int tamanho_hash_aberto(HashAberto h){
    if(h == NULL){
        return 0;
    }
    return h->tamanho;
}

double fator_carga_hash_aberto(HashAberto h){
    if(h == NULL){
        return 0.0;
    }
    return (double)h->qtd / (double)h->tamanho;
}

void destruir_hash_aberto(HashAberto h){
    if(h == NULL){
        return;
    }
    free(h->posicoes);
    free(h->inicial);
    free(h);
}