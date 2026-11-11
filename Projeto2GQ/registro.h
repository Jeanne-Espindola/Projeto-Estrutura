/*
 * Responsável: Jeanne
 * Etapa A - base e estrutura linear
 * O que faz: Define o struct Registro (matrícula, nome e curso), usado por todo o grupo, e a função de imprimir um registro.
 */


 #ifndef REGISTRO_H
 #define REGISTRO_H

 struct registro{
    int matricula;
    char nome[100];
    char curso[100];
 };

 typedef struct registro Registro;

 void registro_imprimir(Registro *r);

 #endif

