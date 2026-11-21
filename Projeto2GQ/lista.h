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
