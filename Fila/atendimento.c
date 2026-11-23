#include <stdio.h>    
#include <stdlib.h>   
#include "fila.h"     

void inicializar(Fila *fila){//O(1)
    fila->inicio = NULL;
    fila->fim = NULL;
}

int estaVazia(Fila * fila){//O(1)
    if(fila->inicio == NULL){
         return 1;
    }
    return 0;
}

int enqueue(Fila *fila, int valor){//O(1)
    No *novo = (No*)malloc(sizeof(No));
    if(novo == NULL){
        printf("Falha na alocacao de memoria.\n");
        return 0;
    }
    novo->dado = valor;
    novo->proximo = NULL;
    
    if(estaVazia(fila)){
        fila->inicio = novo;
    }else{
        fila->fim->proximo = novo;
    }
    fila->fim = novo;

    return 1;
}

int dequeue(Fila *fila, int *valor){//O(1)
    if(estaVazia(fila)){
        return 0;
    }
    No *remover = fila->inicio;
    *valor = remover->dado;
    fila->inicio = remover->proximo;
    if(fila->inicio == NULL){
        fila->fim=NULL;
    }
    free(remover);
    return 1;
}

int front(Fila *fila, int *valor){//O(1)
    if(estaVazia(fila)){
        return 0;
    }
    *valor = fila->inicio->dado;
    return 1;
}

int back(Fila *fila, int *valor){//O(1)
    if(estaVazia(fila)){
        return 0;
    }
    *valor = fila->fim->dado;
    return 1;
}

void imprimirFila(Fila *fila ){//O(n)
    if(estaVazia(fila)){
        printf("Fila vazia.\n");
        return;
    }
    No *atual = fila->inicio;
    while(atual!=NULL){
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

int contarElementos(Fila *fila){//O(n)
    int cont = 0;
    No *atual = fila->inicio;

    while(atual!=NULL){
        cont++;
        atual= atual->proximo;
    }
    return cont;
}

void liberarFila(Fila *fila){//O(n)
    No *atual = fila->inicio;
    while(atual!=NULL){
        No *proximo=atual->proximo;
        free(atual);
        atual = proximo;
    }
    fila->inicio = NULL;
    fila->fim =  NULL; 
}
