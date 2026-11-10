// atividade de lista duplamente encadeada.
#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int dado;
    struct No *anterior;
    struct No *proximo;
}No;

typedef struct Lista{
    No *inicio;
    No *fim;
}Lista;

void inicializar(Lista *lista){
    lista->inicio=NULL;
    lista->fim=NULL;
}

void inserirInicio(Lista *lista, int valor){
    No *novo = (No*) malloc(sizeof(No));
    if(novo==NULL){
        printf("Erro de alocacao!\n");
        return;
    }
    novo->dado = valor;
    novo->anterior=NULL;
    novo->proximo=lista->inicio;
    if(lista->inicio != NULL){
        lista->inicio->anterior = novo;
    } else {
        lista->fim = novo;
    }
    lista->inicio=novo;
}

void inserirFinal(Lista *lista, int valor){
    No *novo = (No*) malloc(sizeof(No));
    if(novo==NULL){
        printf("Erro de alocacao!\n");
        return;
    }
    novo->dado = valor;
    novo->proximo=NULL;
    novo->anterior=lista->fim;
    if(lista->fim != NULL){
        lista->fim->proximo = novo;
    }else{
        lista->inicio = novo;
    }
    lista->fim=novo;
}

void inserirPosicao(Lista *lista, int valor, int posicao){
    int tamanho = 0;
    No *aux = lista->inicio;
    while (aux != NULL){
        tamanho++;
        aux = aux->proximo;
    }
    if(posicao<1 || posicao>tamanho+1){
        printf("Posicao invalida!\n");
        return;
    }
    if(posicao==1){
        inserirInicio(lista, valor);
        return;
    }
    if(posicao==tamanho+1){
        inserirFinal(lista, valor);
        return;
    }
    No *novo = (No*) malloc(sizeof(No));
    if(novo==NULL){
        printf("Erro de alocacao!\n");
        return;
    }
    novo->dado = valor;
    No *atual = lista->inicio;
    for (int i = 1; i < posicao; i++){
        atual = atual->proximo;
    }
    novo->proximo=atual;
    novo->anterior=atual->anterior;
    atual->anterior->proximo=novo;
    atual->anterior=novo;
}

void removerInicio( Lista *lista ){
    if(lista->inicio==NULL){
        printf("Lista vazia!\n");
        return;
    }
    No *removido = lista->inicio;
    if(lista->inicio==lista->fim){
        lista->inicio=NULL;
        lista->fim=NULL;
    }else{
        lista->inicio = removido->proximo;
        lista->inicio->anterior = NULL;
    }
    free(removido);
}

void removerFinal(Lista *lista){
    if(lista->inicio==NULL){
        printf("Lista vazia!\n");
        return;
    }
    No *removido = lista->fim;
    if(lista->inicio==lista->fim){
        lista->inicio=NULL;
        lista->fim=NULL;
    }else{
        lista->fim = removido->anterior;
        lista->fim->proximo = NULL;
    }
    free(removido);
}

void removerValor(Lista *lista, int valor){
    if(lista->inicio==NULL){
        printf("Lista vazia!\n");
        return;
    }
    No *atual = lista->inicio;
    while(atual != NULL && atual->dado != valor){
        atual = atual->proximo;
    }
    if(atual==NULL){
        printf("Valor nao encontrado!\n");
        return;
    }
    if(atual==lista->inicio){
        removerInicio(lista);
    }else if(atual == lista->fim){
        removerFinal(lista);
    }else{
        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;
        free(atual);
    }
}

No *buscar(Lista *lista, int valor){
    No *atual = lista->inicio;
    while(atual != NULL){
        if(atual->dado==valor){
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void imprimirDireto(Lista *lista){
    No *atual = lista->inicio;
    printf("Direto: NULL <-> ");
    while (atual != NULL){
        printf("%d <-> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

void imprimirInverso(Lista *lista){
    No *atual = lista->fim;
    printf("Inverso: <-> ");
    while(atual != NULL){
        printf("%d <-> ", atual->dado);
        atual = atual->anterior;
    }
    printf("NULL\n");   
}

int contarElementos(Lista *lista){
    int cont = 0;
    No *atual = lista->inicio;
    while(atual != NULL){
        cont++;
        atual = atual->proximo;
    }
    return cont;
}

void liberarLista(Lista *lista){
    No *atual = lista->inicio;
    while(atual != NULL){
        No *proximoNo = atual->proximo;
        free(atual);
        atual = proximoNo;
    }
    lista->inicio=NULL;
    lista->fim=NULL;
}

int main(void){
    Lista lista;
    inicializar(&lista);
    int opcao, valor, posicao;

    do{
        printf("\n======= GERENCIADOR DE LISTA =======\n");
        printf("1. Inserir no Inicio\n");
        printf("2. Inserir no Final\n");
        printf("3. Inserir em Posicao Especifica\n");
        printf("4. Remover do Inicio\n");
        printf("5. Remover do Final\n");
        printf("6. Remover por Valor\n");
        printf("7. Buscar Elemento\n");
        printf("8. Visualizar Lista (Ambos os sentidos)\n");
        printf("9. Contar Elementos\n");
        printf("10. Liberar Memoria (Esvaziar Lista)\n");
        printf("0. Sair do Programa\n");
        printf("====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Digite o valor para inserir no inicio: ");
                scanf("%d", &valor);
                inserirInicio(&lista, valor);
                break;
            case 2:
                printf("Digite o valor para inserir no final: ");
                scanf("%d", &valor);
                inserirFinal(&lista, valor);
                break;
            case 3:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                printf("Digite a posicao (comecando em 1): ");
                scanf("%d", &posicao);
                inserirPosicao(&lista, valor, posicao);
                break;
            case 4:
                removerInicio(&lista);
                printf("Tentativa de remocao do inicio executada.\n");
                break;
            case 5:
                removerFinal(&lista);
                printf("Tentativa de remocao do final executada.\n");
                break;
            case 6:
                printf("Digite o valor que deseja remover: ");
                scanf("%d", &valor);
                removerValor(&lista, valor);
                break;
            case 7:
                printf("Digite o valor para buscar: ");
                scanf("%d", &valor);
                if(buscar(&lista, valor) != NULL) {
                    printf("Sucesso: O valor %d foi encontrado na lista!\n", valor);
                } else {
                    printf("Aviso: O valor %d NAO existe na lista.\n", valor);
                }
                break;
            case 8:
                imprimirDireto(&lista);
                imprimirInverso(&lista);
                break;
            case 9:
                printf("Quantidade atual de elementos: %d\n", contarElementos(&lista));
                break;
            case 10:
                liberarLista(&lista);
                printf("Lista completamente esvaziada e memoria liberada!\n");
                break;
            case 0:
                liberarLista(&lista); // Segurança obrigatória antes de fechar
                printf("Programa encerrado com sucesso.\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
}while(opcao !=0);
    return 0;
}