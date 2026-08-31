#include "raylib.h"
#include <stdlib.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600
#define TAM_CELULA 40 // Tamanho em pixels de cada celula da grade

// Struct para a Bola
typedef struct {
    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;
} Bola;

// 1. Criacao da matriz dinamica zerada (0 = nao visitada)
int **criarMatriz(int linhas, int colunas) {
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = 0; // Inicia todas as celulas zeradas
        }
    }
    return matriz;
}

// 2. Liberacao de memoria da matriz dinamica
void liberarMatriz(int **matriz, int linhas) {
    if (matriz == NULL) return;
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main(void) {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 2 - Mapa de Calor");
    SetTargetFPS(60);

    // Calculo do numero de linhas e colunas baseado no tamanho da celula
    int linhasMatriz = ALTURA_JANELA / TAM_CELULA;
    int colunasMatriz = LARGURA_JANELA / TAM_CELULA;

    // Criacao da matriz da grade e do contador de celulas visitadas
    int **grade = criarMatriz(linhasMatriz, colunasMatriz);
    int celulasVisitadas = 0;

    // Alocacao inicial para 3 bolas
    int quantidadeBolas = 3;
    Bola *bolas = (Bola *)malloc(quantidadeBolas * sizeof(Bola));

    // Inicializa as bolas
    for (int i = 0; i < quantidadeBolas; i++) {
        Bola *b = (bolas + i);
        b->pos = (Vector2){ GetRandomValue(50, LARGURA_JANELA - 50), GetRandomValue(50, ALTURA_JANELA - 50) };
        b->vel = (Vector2){ (float)GetRandomValue(-4, 4), (float)GetRandomValue(-4, 4) };
        if (b->vel.x == 0) b->vel.x = 3;
        if (b->vel.y == 0) b->vel.y = 3;
        b->raio = (float)GetRandomValue(12, 20);
        b->cor = (Color){ GetRandomValue(50, 255), GetRandomValue(50, 255), GetRandomValue(50, 255), 255 };
    }

    while (!WindowShouldClose()) {
        // --- Movimentacao e Verificacao do Mapa de Calor ---
        for (int i = 0; i < quantidadeBolas; i++) {
            Bola *b = (bolas + i);

            // Atualiza posicao
            b->pos.x += b->vel.x;
            b->pos.y += b->vel.y;

            // Colisao com as bordas da janela
            if (b->pos.x - b->raio <= 0 || b->pos.x + b->raio >= LARGURA_JANELA) b->vel.x *= -1;
            if (b->pos.y - b->raio <= 0 || b->pos.y + b->raio >= ALTURA_JANELA) b->vel.y *= -1;

            // --- EXERCICIO 2: Converte posicao em pixels para indice da matriz ---
            int coluna = (int)(b->pos.x / TAM_CELULA);
            int linha = (int)(b->pos.y / TAM_CELULA);

            // Valida se esta dentro dos limites da matriz [0, linhas) e [0, colunas)
            if (linha >= 0 && linha < linhasMatriz && coluna >= 0 && coluna < colunasMatriz) {
                // Se a celula ainda nao foi visitada, marca e incrementa o contador
                if (grade[linha][coluna] == 0) {
                    grade[linha][coluna] = 1;
                    celulasVisitadas++;
                }
            }
        }

        // --- Desenho da Tela ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // 1. Desenha a Grade (Mapa de Calor)
        for (int l = 0; l < linhasMatriz; l++) {
            for (int c = 0; c < colunasMatriz; c++) {
                int posX = c * TAM_CELULA;
                int posY = l * TAM_CELULA;

                // Cor da celula: Amarelo claro se visitada (1), Cinza bem claro se nao (0)
                Color corCelula = (grade[l][c] == 1) ? LIGHTGRAY : RAYWHITE;

                DrawRectangle(posX, posY, TAM_CELULA, TAM_CELULA, corCelula);
                DrawRectangleLines(posX, posY, TAM_CELULA, TAM_CELULA, LIGHTGRAY); // Bordas da celula
            }
        }

        // 2. Desenha as Bolas
        for (int i = 0; i < quantidadeBolas; i++) {
            Bola *b = (bolas + i);
            DrawCircleV(b->pos, b->raio, b->cor);
        }

        // 3. Exibe o Contador de Celulas Visitadas na tela
        int totalCelulas = linhasMatriz * colunasMatriz;
        DrawText(TextFormat("Celulas Visitadas: %d / %d", celulasVisitadas, totalCelulas), 10, 10, 20, DARKBLUE);

        EndDrawing();
    }

    // Liberacao de Memoria Dinamica
    if (bolas != NULL) free(bolas);
    liberarMatriz(grade, linhasMatriz);

    CloseWindow();
    return 0;
}