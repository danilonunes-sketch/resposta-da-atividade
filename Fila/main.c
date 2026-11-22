#include <stdio.h>
#include "fila.h"

int main(){
    Fila fila;
    inicializar(&fila);

    int opcao, valor, removido;

    do{
        printf("\n===== MENU FILA =====\n");
        printf("1 - Inserir no final (enqueue)\n");
        printf("2 - Remover do inicio (dequeue)\n");
        printf("3 - Consultar primeiro elemento\n");
        printf("4 - Consultar ultimo elemento\n");
        printf("5 - Verificar se esta vazia\n");
        printf("6 - Exibir elementos\n");
        printf("7 - Quantidade de elementos\n");
        printf("8 - Liberar memoria (esvaziar fila)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                if(enqueue(&fila, valor)){
                    printf("Inserido com sucesso!\n");
                } else {
                    printf("Erro ao inserir.\n");
                }
                break;

            case 2:
                if(dequeue(&fila, &removido)){
                    printf("Removido: %d\n", removido);
                } else {
                    printf("Fila vazia!\n");
                }
                break;

            case 3:
                if(front(&fila, &valor)){
                    printf("Primeiro: %d\n", valor);
                } else {
                    printf("Fila vazia!\n");
                }
                break;

            case 4:
                if(back(&fila, &valor)){
                    printf("Ultimo: %d\n", valor);
                } else {
                    printf("Fila vazia!\n");
                }
                break;

            case 5:
                if(estaVazia(&fila)){
                    printf("A fila esta vazia.\n");
                } else {
                    printf("A fila NAO esta vazia.\n");
                }
                break;

            case 6:
                imprimirFila(&fila);
                break;

            case 7:
                printf("Quantidade: %d\n", contarElementos(&fila));
                break;

            case 8:
                liberarFila(&fila);
                printf("Memoria liberada. Fila vazia.\n");
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    liberarFila(&fila);   // garante que nada vaza ao sair

    return 0;
}