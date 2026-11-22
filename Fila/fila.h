#ifndef FILA_H
#define FILA_H

typedef struct No {
    int dado;
    struct No *proximo;
} No;

typedef struct Fila {
    No *inicio;
    No *fim;
} Fila;

void inicializar(Fila *fila);
int  estaVazia(Fila *fila);
int  enqueue(Fila *fila, int valor);
int  dequeue(Fila *fila, int *valor);
int  front(Fila *fila, int *valor);
int  back(Fila *fila, int *valor);
void imprimirFila(Fila *fila);
int  contarElementos(Fila *fila);
void liberarFila(Fila *fila);

#endif