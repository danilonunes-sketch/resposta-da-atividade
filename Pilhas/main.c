#include <stdio.h>
#include "pilha.h"

int main(void){
    Pilha pilha;
    inicializar(&pilha);

    int opcao, valor;
    do{
        printf("=== MENU PILHA ===\n");
        printf("1. Inserir elemento (PUSH)\n");
        printf("2. Remover elemento do topo (POP)\n");
        printf("3. Consultar topo (PEEK)\n");
        printf("4. Verificar se a pilha esta vazia\n");
        printf("5. Exibir todos os elementos\n");
        printf("6. Consultar quantidade de elementos\n");
        printf("7. Liberar toda a memoria\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("Digite o valor inteiro a inserir: ");
                scanf("%d", &valor);
                push(&pilha, valor);
                printf("Valor %d foi inserido no topo.\n\n", valor);
                break;
            case 2:
                if(estaVazia(&pilha)){
                    printf("A pilha esta vazia.\n\n");
                }else{
                    valor = pop(&pilha);
                    printf("Elemento removido do topo: %d\n\n", valor);
                }
                break;
            case 3:
                if(peek(&pilha, &valor)){
                    printf("Elemento no topo: %d\n\n", valor);
                }else{
                    printf("A pilha esta vazia.\n\n");
                }
                break;
            case 4:
                if(estaVazia(&pilha)){
                    printf("Sim, a pilha esta vazia.\n\n");
                }else{
                    printf("Nao, a pilha contem elementos.\n\n");
                }
                break;
            case 5:
                imprimirPilha(&pilha);
                break;
            case 6:
                printf("Quantidade de elementos na pilha: %d\n\n", contarElementos(&pilha));
                break;
            case 7:
                liberarPilha(&pilha);
                printf("Toda a memoria da pilha foi liberada.\n\n");
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida, tente novamente.\n\n");
        }
    }while(opcao != 0);

    liberarPilha(&pilha);
    return 0;
}