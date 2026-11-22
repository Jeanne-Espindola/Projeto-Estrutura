#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash_aberto.h"
#include "hash_encadeado.h"
#include "hash_funcoes.h"
#include "leitura.h"
#include "lista.h"
#include "registro.h"

#define TAM_100K 100003
#define TAM_1M 1000003
#define TAM_10M 10000019

#define QTD_BUSCAS 10000
#define NUM_FAIXAS 3
#define NUM_EST 5

void sorteador_matriculas(Registro *registro, int *indices, int *matriculas, int qtd_atual){
    int m;
    if(qtd_atual < 10000){
        m = qtd_atual;
    }
    else{
        m = 10000;
    }
    if(registro == NULL || indices == NULL || matriculas == NULL || qtd_atual <= 0){
        return;
    }

    for(int i = 0; i < qtd_atual; i++){
        indices[i] = i; 
    }

    for(int i = 0; i < m; i++){
        int j = i + (rand() % (qtd_atual - i));
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;

        matriculas[i] = registro[indices[i]].matricula;
    }
}

static int executar_experimento(const char *rotulo, int n, int tam_hash){
    const int percentuais[NUM_FAIXAS] = {30, 60, 100};
    const char *nomes[NUM_EST] = {"lista", "hash_aberto_div", "hash_aberto_dobra", "hash_encadeado_div", "hash_encadeado_dobra"};
    int matriculas[QTD_BUSCAS];
    int total_lido = 0;

    Registro *base = ler_base("alunos.txt", n, &total_lido);
    if(base == NULL || total_lido < n){
        free(base);
        return 1;
    }

    int *indices = malloc((size_t)n * sizeof(int));
    if(indices == NULL){
        free(base);
        return 1;
    }

    Lista li = criar_lista();
    HashAberto haa = criar_hash_aberto(tam_hash, FuncaoHashDiv);
    HashAberto haa1 = criar_hash_aberto(tam_hash, FuncHashDobra);
    HashEncadeado hae = criar_hash_encadeado(tam_hash, FuncaoHashDiv);
    HashEncadeado hae1 = criar_hash_encadeado(tam_hash, FuncHashDobra);

    long long ant_haa_div = 0, ant_haa_dob = 0, ant_hae_div = 0, ant_hae_dob = 0;

    int inicio = 0;
    for(int i = 0; i < NUM_FAIXAS; i++){
        int fim = (n * percentuais[i]) / 100;

        double t_ins[NUM_EST];
        double t_bus[NUM_EST];
        int falhas[NUM_EST] = {0, 0, 0, 0, 0};
        clock_t t;

        //insercao
        t = clock();
        for(int i = inicio; i < fim; i++){
            if(!inserir_inicio(li, &base[i])) falhas[0]++;
        }
        t_ins[0] = (double)(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        for(int i = inicio; i < fim; i++){
            if(!inserir_hash_aberto(haa, &base[i])) falhas[1]++;
        }
        t_ins[1] = (double)(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        for(int i = inicio; i < fim; i++){
            if(!inserir_hash_aberto(haa1, &base[i])) falhas[2]++;
        }
        t_ins[2] = (double)(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        for(int i = inicio; i < fim; i++){
            if(!inserir_hash_encadeado(hae, &base[i])) falhas[3]++;
        }
        t_ins[3] = (double)(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        for(int i = inicio; i < fim; i++){
            if(!inserir_hash_encadeado(hae1, &base[i])) falhas[4]++;
        }
        t_ins[4] = (double)(clock() - t) / CLOCKS_PER_SEC;

        //colisoes
        long long tot_haa_div = (long long)colisoes_hash_aberto(haa);
        long long tot_haa_dob = (long long)colisoes_hash_aberto(haa1);
        long long tot_hae_div = (long long)colisoes_hash_encadeado(hae);
        long long tot_hae_dob = (long long)colisoes_hash_encadeado(hae1);

        long long col_haa_div = tot_haa_div - ant_haa_div;
        long long col_haa_dob = tot_haa_dob - ant_haa_dob;
        long long col_hae_div = tot_hae_div - ant_hae_div;
        long long col_hae_dob = tot_hae_dob - ant_hae_dob;

        ant_haa_div = tot_haa_div;
        ant_haa_dob = tot_haa_dob;
        ant_hae_div = tot_hae_div;
        ant_hae_dob = tot_hae_dob;

        //fator de carga
        double alfa_haa_div = fator_carga_hash_aberto(haa);
        double alfa_haa_dob = fator_carga_hash_aberto(haa1);
        double alfa_hae = (double)fim / (double)tam_hash;

        //buscas
        sorteador_matriculas(base, indices, matriculas, fim);

        t = clock();
        for(int i = 0; i < QTD_BUSCAS; i++){
            buscar_matricula(li, matriculas[i]);
        }
        t_bus[0] = (double)(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        for(int i = 0; i < QTD_BUSCAS; i++){
            buscar_hash_aberto(haa, matriculas[i]);
        }
        t_bus[1] = (double)(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        for(int i = 0; i < QTD_BUSCAS; i++){
            buscar_hash_aberto(haa1, matriculas[i]);
        }
        t_bus[2] = (double)(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        for(int i = 0; i < QTD_BUSCAS; i++){
            buscar_hash_encadeado(hae, matriculas[i]);
        }
        t_bus[3] = (double)(clock() - t) / CLOCKS_PER_SEC;

        t = clock();
        for(int i = 0; i < QTD_BUSCAS; i++){
            buscar_hash_encadeado(hae1, matriculas[i]);
        }
        t_bus[4] = (double)(clock() - t) / CLOCKS_PER_SEC;

        printf("== %s %d%% ==\n", rotulo, percentuais[i]);
        printf("%-15s ins: %.4fs | busca: %.4fs\n", nomes[0], t_ins[0], t_bus[0]);
        printf("%-15s ins: %.4fs | busca: %.4fs | col: %lld | alfa: %.4f\n", nomes[1], t_ins[1], t_bus[1], col_haa_div, alfa_haa_div);
        printf("%-15s ins: %.4fs | busca: %.4fs | col: %lld | alfa: %.4f\n", nomes[2], t_ins[2], t_bus[2], col_haa_dob, alfa_haa_dob);
        printf("%-15s ins: %.4fs | busca: %.4fs | col: %lld | alfa: %.4f\n", nomes[3], t_ins[3], t_bus[3], col_hae_div, alfa_hae);
        printf("%-15s ins: %.4fs | busca: %.4fs | col: %lld | alfa: %.4f\n", nomes[4], t_ins[4], t_bus[4], col_hae_dob, alfa_hae);

        for(int i = 0; i < NUM_EST; i++){
            if(falhas[i] > 0){
                printf("AVISO: %s teve %d insercoes que falharam\n", nomes[i], falhas[i]);
            }
        }

        inicio = fim;
    }

    destruir(li);
    destruir_hash_aberto(haa);
    destruir_hash_aberto(haa1);
    destruir_hash_encadeado(hae);
    destruir_hash_encadeado(hae1);
    free(indices);
    free(base);
    return 0;
}

int main(){
    srand((unsigned int)time(NULL));

    if(executar_experimento("100k", 100000, TAM_100K) != 0) return 1;
    if(executar_experimento("1M", 1000000, TAM_1M) != 0) return 1;
    if(executar_experimento("10M", 10000000, TAM_10M) != 0) return 1;

    return 0;
}
