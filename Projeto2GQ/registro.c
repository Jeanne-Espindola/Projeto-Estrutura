/*
 * Responsável: Jeanne
 * Etapa A - base e estrutura linear
 * O que faz: Define o struct Registro (matrícula, nome e curso), usado por todo o grupo, e a função de imprimir um registro.
 */
#include "registro.h"

 void imprimir_registro(Registro *r){
    if(r == NULL){
        return;
    }

    printf("\n| Matricula: %d / Nome: %s / Curso: %s\n", r->matricula, r->nome, r->curso);
 }