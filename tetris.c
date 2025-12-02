#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Difine o tamanho máximo da fila
#define MAX_FILA 5

// Criando as estruturas Peça e Fila
typedef struct {
    char tipo;
    int id;
} Peca;

typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// Protótipos das Funções
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void enqueue(Fila *f, Peca p);
void dequeue(Fila *f, Peca *p);
void mostrarFila(Fila *f);
Peca gerarPeca();


int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    Fila f;
    inicializarFila(&f);

    // Preencher com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&f, gerarPeca());
    }

    int opcao;
    Peca pecaRemovida;

    do {
        printf("\n=============================================================\n");
        printf("--- TETRIS STACK - MENU PRINCIPAL ---\n");
        mostrarFila(&f);
        printf("1. Jogar Nova Peça\n");
        printf("2. Inserir Nova Peça\n");
        printf("0. Sair\n");
        printf("=============================================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&f, &pecaRemovida);
                if (f.total >= 0) {
                    printf("Peça [%c, %d] jogada!\n", pecaRemovida.tipo, pecaRemovida.id);
                }
                mostrarFila(&f);
                break;
            case 2:
                enqueue(&f, gerarPeca());
                mostrarFila(&f);
                break;
            case 0:
                printf("\nSaindo do jogo...");
                printf("Até logo!");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
    

    return 0;
}

// Implementação das Funções
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

void dequeue(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia! Não é possível remover.\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
}

void mostrarFila(Fila *f) {
    printf("Fila: ");

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX_FILA) {
        printf("[%c, %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }

    printf("\n");
}

Peca gerarPeca() {
    static int proximoId = 0;
    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca novaPeca;
    novaPeca.tipo = tipos[rand() % 4];
    novaPeca.id = proximoId++;

    return novaPeca;
}