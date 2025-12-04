#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

// Define o tamanho máximo da fila e da pilha
#define MAX_FILA 5
#define MAX_PILHA 3

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

typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;


// Protótipos das Funções
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
void enqueue(Fila *f, Peca p);
void dequeue(Fila *f, Peca *p);
void mostrarFila(Fila *f);
Peca gerarPeca();

void inicializarPilha(Pilha *p);
int pilhaVazia(Pilha *p);
int pilhaCheia(Pilha *p);
void push(Pilha *p, Peca nova);
void pop(Pilha *p, Peca *removida);
void mostrarPilha(Pilha *p);

void trocaSimples(Fila *f, Pilha *p);
void trocaTripla(Fila *f, Pilha *p);


int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");

    Fila f;
    inicializarFila(&f);

    Pilha p;
    inicializarPilha(&p);

    // Preencher com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&f, gerarPeca());
    }

    int opcao;
    Peca pecaRemovidaFila;
    Peca pecaReservada;
    Peca pecaRemovidaPilha;

    do {
        printf("\n=============================================================\n");
        printf("--- TETRIS STACK - MENU PRINCIPAL ---\n");
        mostrarFila(&f);
        mostrarPilha(&p);
        printf("1. Jogar Peça\n");
        printf("2. Reservar Peça\n");
        printf("3. Usar Peça Reservada\n");
        printf("4. Trocar peça do topo da pilha com a da frente da fila\n");
        printf("5. Trocar os três primeiros da fila com as três peças da pilha\n");
        printf("0. Sair\n");
        printf("=============================================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&f, &pecaRemovidaFila);
                printf("Peça [%c, %d] jogada!\n", pecaRemovidaFila.tipo, pecaRemovidaFila.id);
                enqueue(&f, gerarPeca());
                mostrarFila(&f);
                mostrarPilha(&p);
                break;
            case 2:
                if (!pilhaCheia(&p)) {
                    dequeue(&f, &pecaReservada);
                    enqueue(&f, gerarPeca());
                    printf("Peça [%c, %d] reservada!\n", pecaReservada.tipo, pecaReservada.id);
                }
                push(&p, pecaReservada);
                mostrarFila(&f);
                mostrarPilha(&p);
                break;
            case 3:
                pop(&p, &pecaRemovidaPilha);
                printf("Peça [%c, %d], que estava reservada, jogada!\n", pecaRemovidaPilha.tipo, pecaRemovidaPilha.id);
                mostrarFila(&f);
                mostrarPilha(&p);
                break;
            case 4:
                trocaSimples(&f, &p);
                mostrarFila(&f);
                mostrarPilha(&p);
                break;
            case 5:
                trocaTripla(&f, &p);
                mostrarFila(&f);
                mostrarPilha(&p);
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                printf("Até logo!\n");
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
        printf("Fila cheia! Não é possível adicionar nova peça.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

void dequeue(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia! Não há peças para jogar.\n");
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

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

void push(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Não é possível reservar peça.\n");
        return;
    }

    p->topo++;
    p->itens[p->topo] = nova;
}

void pop(Pilha *p, Peca *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Não é possível remover.\n");
        return;
    }

    *removida = p->itens[p->topo];
    p->topo--;
}

void mostrarPilha(Pilha *p) {
    printf("Pilha (topo -> base):\n");
    if (pilhaVazia(p)) {
        printf("(vazia)\n");
    } else {
        for (int i = p->topo; i >= 0; i--) {
            printf("[%c, %d]\n", p->itens[i].tipo, p->itens[i].id);
        }
    }
    printf("\n");
}

void trocaSimples(Fila *f, Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Não é possível realizar a troca.\n");
        return;
    }
    
    if (filaVazia(f)) {
        printf("Fila vazia! Não é possível realizar a troca.\n");
        return;
    }
    
    // Remove o topo da pilha
    Peca auxPilha;
    pop(p, &auxPilha);
    
    // Remove a frente da fila
    Peca auxFila;
    dequeue(f, &auxFila);
    
    // Insere a peça da fila na pilha
    push(p, auxFila);
    
    // Insere a peça da pilha na frente da fila (ajustando o início)
    f->inicio = (f->inicio - 1 + MAX_FILA) % MAX_FILA;
    f->itens[f->inicio] = auxPilha;
    f->total++;
    
    printf("Troca realizada: [%c, %d] da pilha <-> [%c, %d] da fila\n", 
           auxPilha.tipo, auxPilha.id, auxFila.tipo, auxFila.id);
}

void trocaTripla(Fila *f, Pilha *p) {
    // Verifica se a pilha tem exatamente 3 peças
    if (p->topo < MAX_PILHA - 1) {
        printf("A pilha precisa ter exatamente 3 peças para realizar a troca!\n");
        return;
    }
    
    // Verifica se a fila tem pelo menos 3 peças
    if (f->total < MAX_PILHA) {
        printf("A fila precisa ter pelo menos 3 peças para realizar a troca!\n");
        return;
    }
    
    // Array temporário para armazenar as 3 peças da fila
    Peca filaTemp[MAX_PILHA];
    
    // Remove 3 peças da frente da fila
    for (int i = 0; i < MAX_PILHA; i++) {
        dequeue(f, &filaTemp[i]);
    }
    
    // Array temporário para armazenar as 3 peças da pilha
    Peca pilhaTemp[MAX_PILHA];
    
    // Remove todas as 3 peças da pilha (do topo para a base)
    for (int i = 0; i < MAX_PILHA; i++) {
        pop(p, &pilhaTemp[i]);
    }
    
    // Insere as 3 peças da pilha no início da fila
    for (int i = MAX_PILHA - 1; i >= 0; i--) {
        f->inicio = (f->inicio - 1 + MAX_FILA) % MAX_FILA;
        f->itens[f->inicio] = pilhaTemp[i];
        f->total++;
    }
    
    // Insere as 3 peças da fila na pilha (a primeira da fila vai para a base da pilha)
    for (int i = 0; i < MAX_PILHA; i++) {
        push(p, filaTemp[i]);
    }
    
    printf("Troca completa realizada: 3 peças da fila <-> 3 peças da pilha\n");
}