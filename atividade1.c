#include "raylib.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

// Struct para a Bola
typedef struct {
    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;
} Bola;

// 1. Funcao para criar uma matriz dinamica (int **)
int **criarMatriz(int linhas, int colunas) {
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = GetRandomValue(0, 1);
        }
    }
    return matriz;
}

// 2. Funcao para liberar a matriz dinamica
void liberarMatriz(int **matriz, int linhas) {
    if (matriz == NULL) return;
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main(void) {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 1 - Alocacao Dinamica");
    SetTargetFPS(60);

    // Alocacao inicial com malloc (inicia com 2 bolas)
    int quantidadeBolas = 2;
    Bola *bolas = (Bola *)malloc(quantidadeBolas * sizeof(Bola));

    // Inicializa as bolas iniciais
    for (int i = 0; i < quantidadeBolas; i++) {
        Bola *b = (bolas + i);
        b->pos = (Vector2){ GetRandomValue(50, LARGURA_JANELA - 50), GetRandomValue(50, ALTURA_JANELA - 50) };
        b->vel = (Vector2){ (float)GetRandomValue(-4, 4), (float)GetRandomValue(-4, 4) };
        if (b->vel.x == 0) b->vel.x = 2;
        if (b->vel.y == 0) b->vel.y = 2;
        b->raio = (float)GetRandomValue(10, 25);
        b->cor = (Color){ GetRandomValue(50, 255), GetRandomValue(50, 255), GetRandomValue(50, 255), 255 };
    }

    // Criacao de matriz de teste
    int linhasMatriz = 5, colunasMatriz = 5;
    int **matriz = criarMatriz(linhasMatriz, colunasMatriz);

    while (!WindowShouldClose()) {
        // --- QUESTAO 1: Redimensionamento Dinamico ---

        // ESPACO: Adiciona nova bola (realloc +1)
        if (IsKeyPressed(KEY_SPACE)) {
            quantidadeBolas++;
            Bola *temp = (Bola *)realloc(bolas, quantidadeBolas * sizeof(Bola));
            if (temp != NULL) {
                bolas = temp;
                Bola *b = (bolas + quantidadeBolas - 1);
                b->pos = (Vector2){ GetRandomValue(50, LARGURA_JANELA - 50), GetRandomValue(50, ALTURA_JANELA - 50) };
                b->vel = (Vector2){ (float)GetRandomValue(-4, 4), (float)GetRandomValue(-4, 4) };
                if (b->vel.x == 0) b->vel.x = 2;
                if (b->vel.y == 0) b->vel.y = 2;
                b->raio = (float)GetRandomValue(10, 25);
                b->cor = (Color){ GetRandomValue(50, 255), GetRandomValue(50, 255), GetRandomValue(50, 255), 255 };
            } else {
                quantidadeBolas--;
            }
        }

        // BACKSPACE: Remove ultima bola (realloc -1)
        if (IsKeyPressed(KEY_BACKSPACE) && quantidadeBolas > 0) {
            quantidadeBolas--;
            if (quantidadeBolas > 0) {
                Bola *temp = (Bola *)realloc(bolas, quantidadeBolas * sizeof(Bola));
                if (temp != NULL) {
                    bolas = temp;
                }
            } else {
                free(bolas);
                bolas = NULL;
            }
        }

        // --- Movimentacao das Bolas ---
        for (int i = 0; i < quantidadeBolas; i++) {
            Bola *b = (bolas + i);
            b->pos.x += b->vel.x;
            b->pos.y += b->vel.y;

            if (b->pos.x - b->raio <= 0 || b->pos.x + b->raio >= LARGURA_JANELA) b->vel.x *= -1;
            if (b->pos.y - b->raio <= 0 || b->pos.y + b->raio >= ALTURA_JANELA) b->vel.y *= -1;
        }

        // --- Desenho na Tela ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < quantidadeBolas; i++) {
            Bola *b = (bolas + i);
            DrawCircleV(b->pos, b->raio, b->cor);
        }

        DrawText("ESPACO: Adiciona bola | BACKSPACE: Remove bola", 10, 10, 18, DARKGRAY);
        DrawText(TextFormat("Total de Bolas: %d", quantidadeBolas), 10, 35, 18, BLUE);

        EndDrawing();
    }

    // Liberacao de Memoria
    if (bolas != NULL) free(bolas);
    liberarMatriz(matriz, linhasMatriz);

    CloseWindow();
    return 0;
}