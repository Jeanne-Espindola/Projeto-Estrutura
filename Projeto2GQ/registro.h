 #ifndef REGISTRO_H
 #define REGISTRO_H

 struct registro{
    int matricula;
    char nome[100];
    char curso[100];
 };

 typedef struct registro Registro;

 void imprimir_registro(Registro *r);

 #endif

