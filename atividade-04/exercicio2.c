
/*
 * Ponteiros para Struct + Vetor de Struct com raylib
 * ---------------------------------------------------------------
 * Evolução da atividade3: agora o foco é em como PONTEIROS PARA
 * STRUCT permitem localizar e alterar um elemento específico dentro
 * de um vetor de struct, sem copiar a struct inteira.
 *
 * O vetor de inimigos é um VETOR DE STRUCT (bloco contíguo, alocado
 * uma única vez com malloc). As funções recebem e retornam
 * "Inimigo *" (ponteiro para struct) para localizar e modificar um
 * elemento específico desse vetor.
 *
 * Conceitos praticados:
 *   - vetor de struct (bloco contíguo de memória)
 *   - ponteiro para struct como retorno de função (localizar um
 *     elemento dentro do vetor e devolver o endereço dele)
 *   - ponteiro para struct como parâmetro de função (alterar o
 *     elemento apontado diretamente, sem cópia)
 *   - enum para representar o estado de cada inimigo
 *   - malloc / free do vetor
 *
 * Compilar (Linux, com raylib instalada):
 *   gcc atividade4.c -o atividade4 -lraylib -lm -lpthread -ldl -lrt -lX11
 */

#include <raylib.h> //
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600
#define RAIO_JOGADOR   20.0f
#define TOTAL_INIMIGOS 8 // 
#define DANO_TIRO      20

typedef enum {
    INIMIGO_VIVO,
    INIMIGO_MORTO, // enum para representar o estado de cada inimigo
} EstadoInimigo;

typedef struct { // struct para representar cada inimigo
    Vector2       pos;
    float         raio;
    int           vida;
    EstadoInimigo estado; 
} Inimigo;

/* preenche o vetor de struct (recebido por ponteiro) com valores iniciais */
void inicializarInimigos(Inimigo *vetor, int n) { //
    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i); // ponteiro para o i-ésimo elemento
        ini->pos    = (Vector2){ GetRandomValue(30, LARGURA_JANELA - 30),
                                  GetRandomValue(30, ALTURA_JANELA - 30) };
        ini->raio   = 15.0f;
        ini->vida   = 60;
        ini->estado = INIMIGO_VIVO;
    }
}

/* recebe um ponteiro para UM inimigo específico do vetor e altera
 * a vida/estado diretamente na memória original (sem cópia) */
void atingirInimigo(Inimigo *inimigo, int dano) { 
    if (inimigo == NULL || inimigo->estado == INIMIGO_MORTO) return;

    inimigo->vida -= dano;
    if (inimigo->vida <= 0) {
        inimigo->vida = 0;
        inimigo->estado = INIMIGO_MORTO;
    }
}

/* percorre o vetor de struct e RETORNA UM PONTEIRO para o inimigo
 * vivo mais próximo da posição informada (ou NULL se não houver) */
Inimigo *encontrarInimigoMaisProximo(Inimigo *vetor, int n, Vector2 posJogador) {
    Inimigo *maisProximo = NULL;
    float menorDistancia = 0.0f;

    for (int i = 0; i < n; i++) {
        Inimigo *ini = (vetor + i);
        if (ini->estado == INIMIGO_MORTO) continue;

        float dx = ini->pos.x - posJogador.x;
        float dy = ini->pos.y - posJogador.y;
        float distancia = sqrtf(dx * dx + dy * dy);

        if (maisProximo == NULL || distancia < menorDistancia) {
            maisProximo = ini;
            menorDistancia = distancia;
        }
    }
    return maisProximo;
}

void curarTodos(Inimigo *vetor, int n, int cura) { // percorre o vetor de struct e altera a vida de cada inimigo vivo
    for (int i = 0; i < n; i++) { // percorre o vetor de struct
        Inimigo *ini = vetor + i; // ponteiro para o i-ésimo elemento (aritmética de ponteiros)
         if (ini->estado == INIMIGO_VIVO) { // verifica se o inimigo está vivo 
        ini->vida += cura; // altera a vida diretamente na memória original (sem cópia)
            if (ini->vida > 100){ // vida máxima é 100
            ini->vida = 100; // limita a vida máxima 
       }
     }
  }
}
Inimigo *encontrarInimigoMaisFraco(Inimigo *vetor, int n){// percorre o vetor de struct e RETORNA UM PONTEIRO para o inimigo
    // vivo mais fraco (menor vida) encontrado (ou NULL se não houver)
    Inimigo *maisFraco = NULL; // guarda o endereço para o inimigo mais fraco encontrado
    int menorVida = 300; // guarda a menor vida encontrada (inicialmente um valor alto)
    for (int i = 0; i < n; i++) {
        Inimigo *ini = vetor + i; // ponteiro para o i-ésimo elemento
        if (ini->estado == INIMIGO_MORTO) continue; // ignora inimigos mortos
        if (ini->vida < menorVida) { // se a vida do inimigo atual for menor que a menor vida encontrada
            menorVida = ini->vida; // atualiza a menor vida encontrada
            maisFraco = ini; // atualiza o ponteiro para o inimigo mais fraco encontrado
        }
    }
    return maisFraco;   
}
    
void desenharInimigo(Inimigo *ini) {
    if (ini->estado == INIMIGO_MORTO) return;
    Color cor = (ini->vida > 30) ? MAROON : ORANGE;
    DrawCircleV(ini->pos, ini->raio, cor);
    DrawText(TextFormat("%d", ini->vida), ini->pos.x - 8, ini->pos.y - 26, 14, BLACK);
}

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Atividade 4 - Ponteiros para Struct + Vetor de Struct");
    SetTargetFPS(60);

    Vector2 jogador = { LARGURA_JANELA / 2.0f, ALTURA_JANELA / 2.0f };

    // vetor de struct: um único bloco contíguo de memória com TOTAL_INIMIGOS structs
    Inimigo *inimigos = (Inimigo *)malloc(TOTAL_INIMIGOS * sizeof(Inimigo));
    inicializarInimigos(inimigos, TOTAL_INIMIGOS);

    while (!WindowShouldClose()) {

        float vel = 250.0f * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT)) jogador.x += vel;
        if (IsKeyDown(KEY_LEFT))  jogador.x -= vel;
        if (IsKeyDown(KEY_UP))    jogador.y -= vel;
        if (IsKeyDown(KEY_DOWN))  jogador.y += vel;

        if (IsKeyPressed(KEY_SPACE)) {
            // ponteiro para o inimigo vivo mais próximo (ou NULL)
            Inimigo *alvo = encontrarInimigoMaisProximo(inimigos, TOTAL_INIMIGOS, jogador);
            atingirInimigo(alvo, DANO_TIRO);
        }
        // cura todos os inimigos vivos em 15 pontos de vida quando a tecla C é pressionada
        if(IsKeyPressed(KEY_C)) {
            curarTodos(inimigos, TOTAL_INIMIGOS,15);
        }
        if(IsKeyPressed(KEY_F)) { // verifica se a tecla F foi pressionada
            Inimigo *alvo = encontrarInimigoMaisFraco(inimigos, TOTAL_INIMIGOS); // ponteiro para o inimigo vivo mais fraco (ou NULL)
            if(alvo != NULL) { // verifica se o ponteiro não é NULL
              atingirInimigo(alvo, DANO_TIRO); // atinge o inimigo mais fraco encontrado
            }
        }
        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < TOTAL_INIMIGOS; i++) {
                desenharInimigo(inimigos + i);
            }

            DrawCircleV(jogador, RAIO_JOGADOR, BLUE);

            DrawText("ESPACO atira no inimigo vivo mais proximo", 10, 10, 20, DARKGRAY);
            DrawText("Setas movem o jogador | ESC sai", 10, ALTURA_JANELA - 25, 16, GRAY);

        EndDrawing();
    }

    free(inimigos); // libera o vetor de struct

    CloseWindow();
    return 0;
}
