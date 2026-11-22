#include <stdio.h>
#include "fila.h"

int main(){
    Fila fila;
    inicializar(&fila);

    int opcao, senha;
    int proxima = 101;   // proxima senha a ser gerada

    do{
        printf("\n===== SISTEMA DE ATENDIMENTO =====\n");
        printf("1 - Adicionar pessoa na fila\n");
        printf("2 - Chamar proxima pessoa\n");
        printf("3 - Consultar quem sera atendido em seguida\n");
        printf("4 - Exibir pessoas aguardando\n");
        printf("5 - Quantidade de pessoas na fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                if(enqueue(&fila, proxima)){
                    printf("Pessoa adicionada. Senha: %d\n", proxima);
                    proxima++;
                } else {
                    printf("Erro ao adicionar pessoa.\n");
                }
                break;

            case 2:
                if(dequeue(&fila, &senha)){
                    printf("Chamando a senha %d!\n", senha);
                } else {
                    printf("Ninguem aguardando atendimento.\n");
                }
                break;

            case 3:
                if(front(&fila, &senha)){
                    printf("Proxima a ser atendida: senha %d\n", senha);
                } else {
                    printf("Ninguem aguardando atendimento.\n");
                }
                break;

            case 4:
                imprimirFila(&fila);
                break;

            case 5:
                printf("Pessoas aguardando: %d\n", contarElementos(&fila));
                break;

            case 0:
                printf("Encerrando atendimento...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    liberarFila(&fila);
    return 0;
}