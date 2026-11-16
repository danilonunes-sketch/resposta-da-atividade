#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "pilha.h"

void inicializar(Pilha *pilha){
    pilha->topo = NULL;
}

int estaVazia(Pilha *pilha){
    if (pilha->topo == NULL){
        return 1;
    }else{
        return 0;
    }
}

void push(Pilha *pilha, int valor){
    No *novo = (No*)malloc(sizeof(No));
    if(novo == NULL){
        printf("Falha na alocacao de memoria.\n");
        return;
    }
    novo->dado = valor;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}

int pop(Pilha *pilha){
    if (estaVazia(pilha)){
        printf("Erro: Pilha vazia! Nao e possivel desempilhar.\n");
        return INT_MIN;
    }
    No *aux = pilha->topo;
    int valorRemovido = aux->dado;
    pilha->topo = aux->proximo;
    free(aux);
    return valorRemovido;
}

int peek(Pilha *pilha, int *valor){
    if(estaVazia(pilha)){
        return 0;
    }
    *valor = pilha->topo->dado;
    return 1;
}

void imprimirPilha(Pilha *pilha){
    if(estaVazia(pilha)){
        printf("Pilha vazia.\n");
        return;
    }
    No *atual = pilha->topo;
    printf("\nTOPO\n |\n v\n");
    while (atual != NULL) {
        printf("%d\n", atual->dado);
        atual = atual->proximo;
    }
    printf(" |\nNULL\n\n");
}

int contarElementos(Pilha *pilha){
    int contador = 0;
    No *atual = pilha->topo;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

void liberarPilha(Pilha *pilha){
    No *atual = pilha->topo;
    while(atual != NULL){
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    pilha->topo = NULL;
}