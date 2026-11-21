#include "registro.h"
#include <stdio.h>

 void imprimir_registro(Registro *r){
    if(r == NULL){
        return;
    }

    printf("\n| Matricula: %d / Nome: %s / Curso: %s\n", r->matricula, r->nome, r->curso);
 }