#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int total_elementos = 5000; 
    FILE *f = fopen("dados.txt", "w");
    
    if (f == NULL) {
        printf("Erro ao criar o arquivo dados.txt\n");
        return 1;
    }

    srand(time(NULL)); // Inicializa a semente aleatória

    for (int i = 0; i < total_elementos; i++) {
        // Gera números entre 10 e 400 para caberem bem na tela
        int num = rand() % 391 + 10; 
        fprintf(f, "%d\n", num);
    }

    fclose(f);
    printf("Arquivo dados.txt gerado com sucesso com %d elementos!\n", total_elementos);
    return 0;
}