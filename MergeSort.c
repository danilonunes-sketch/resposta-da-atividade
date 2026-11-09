#include "C:/msys64/ucrt64/include/raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTOS 20000

typedef enum {
    PARADO,
    EXECUTANDO,
    PAUSADO,
    CONCLUIDO
} EstadoSimulador;

typedef union {
    char tagText[16];
    int idNum;
} Metadado;

typedef struct {
    int valor;
    Color cor;
    Metadado info;
} Elemento;

Elemento lista[MAX_ELEMENTOS];
Elemento listaAux[MAX_ELEMENTOS];
int qtd = 0;

long comparacoes = 0;
long trocas = 0;
long passos = 0;

EstadoSimulador estado = PARADO;

int tamAtual = 1;
int esqInicio = 0;
int i_merge = 0, j_merge = 0, k_merge = 0;
int fimEsq = 0, fimDir = 0;
bool fazendoMerge = false;

bool carregarArquivo(const char* nomeArq) {
    FILE* f = fopen(nomeArq, "r");
    if (f == NULL) return false;

    qtd = 0;
    comparacoes = 0;
    trocas = 0;
    passos = 0;
    estado = PARADO;
    tamAtual = 1;
    esqInicio = 0;
    fazendoMerge = false;

    while (qtd < MAX_ELEMENTOS && fscanf(f, "%d", &lista[qtd].valor) == 1) {
        lista[qtd].cor = BLUE;
        lista[qtd].info.idNum = qtd;
        qtd++;
    }

    fclose(f);
    return (qtd > 0);
}

void executarPassoMergeSort() {
    if (estado != EXECUTANDO) return;

    if (!fazendoMerge) {
        if (tamAtual >= qtd) {
            estado = CONCLUIDO;
            for (int i = 0; i < qtd; i++) lista[i].cor = GREEN;
            return;
        }

        if (esqInicio >= qtd - 1) {
            tamAtual *= 2;
            esqInicio = 0;
            return;
        }

        int meio = esqInicio + tamAtual - 1;
        fimEsq = meio;
        
        int dirFim = esqInicio + 2 * tamAtual - 1;
        if (dirFim >= qtd) dirFim = qtd - 1;
        fimDir = dirFim;

        if (fimEsq >= qtd) fimEsq = qtd - 1;

        i_merge = esqInicio;
        j_merge = meio + 1;
        k_merge = esqInicio;

        fazendoMerge = true;
    }

    for (int idx = esqInicio; idx <= fimDir; idx++) {
        if (idx < qtd) lista[idx].cor = ORANGE;
    }

    if (i_merge <= fimEsq && j_merge <= fimDir) {
        comparacoes++;
        passos++;
        if (lista[i_merge].valor <= lista[j_merge].valor) {
            listaAux[k_merge] = lista[i_merge];
            i_merge++;
        } else {
            listaAux[k_merge] = lista[j_merge];
            j_merge++;
        }
        trocas++;
        k_merge++;
    }

    else if (i_merge <= fimEsq) {
        passos++;
        listaAux[k_merge] = lista[i_merge];
        i_merge++;
        trocas++;
        k_merge++;
    } 

    else if (j_merge <= fimDir) {
        passos++;
        listaAux[k_merge] = lista[j_merge];
        j_merge++;
        trocas++;
        k_merge++;
    } 

    else {
        for (int idx = esqInicio; idx <= fimDir; idx++) {
            lista[idx] = listaAux[idx];
            lista[idx].cor = BLUE;
        }
        esqInicio += 2 * tamAtual;
        fazendoMerge = false;
    }
}

int main(void) {
    const int largura = 800;
    const int altura = 600;
    InitWindow(largura, altura, "ED1 - Trabalho Bimestral: Merge Sort");

    carregarArquivo("dados.txt");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_I)) {
            if (estado == PARADO || estado == PAUSADO) estado = EXECUTANDO;
        }
        if (IsKeyPressed(KEY_P)) {
            if (estado == EXECUTANDO) estado = PAUSADO;
        }
        if (IsKeyPressed(KEY_R)) {
            carregarArquivo("dados.txt");
        }
        if (IsKeyPressed(KEY_N)) {
            if (estado == PAUSADO || estado == PARADO) {
                estado = EXECUTANDO;
                executarPassoMergeSort();
                estado = PAUSADO;
            }
        }

        if (estado == EXECUTANDO) {
            executarPassoMergeSort();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Simulador Interativo: Merge Sort (Divisao e Conquista)", 20, 20, 22, DARKGRAY);
        DrawText("Teclas: [I] Iniciar/Continuar | [P] Pausar | [R] Reiniciar | [N] Proximo Passo", 20, 50, 16, GRAY);

        DrawRectangle(20, 480, 760, 100, LIGHTGRAY);
        DrawText("Algoritmo: Merge Sort (Iterativo)", 35, 490, 16, BLACK);
        DrawText(TextFormat("Elementos: %d", qtd), 35, 515, 16, BLACK);
        DrawText(TextFormat("Comparacoes: %ld", comparacoes), 35, 540, 16, BLACK);
        DrawText(TextFormat("Trocas/Copias: %ld", trocas), 260, 515, 16, BLACK);
        DrawText(TextFormat("Passo Atual: %ld", passos), 260, 540, 16, BLACK);

        if (estado == PARADO)      DrawText("Estado: PARADO", 550, 490, 18, RED);
        if (estado == EXECUTANDO)  DrawText("Estado: ORDENANDO", 550, 490, 18, ORANGE);
        if (estado == PAUSADO)     DrawText("Estado: PAUSADO", 550, 490, 18, BLUE);
        if (estado == CONCLUIDO)   DrawText("Estado: CONCLUIDO!", 550, 490, 18, GREEN);

        if (qtd > 0) {
            int largBarra = (largura - 80) / qtd;
            if (largBarra < 1) largBarra = 1;
            
            for (int i = 0; i < qtd; i++) {
                int altBarra = lista[i].valor;
                int xPos = 40 + i * largBarra;
                int yPos = 440 - altBarra;

                DrawRectangle(xPos, yPos, largBarra, altBarra, lista[i].cor);
            }
        } else {
            DrawText("Erro: 'dados.txt' nao encontrado ou vazio na pasta!", 40, 250, 20, RED);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}