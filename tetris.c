#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  // tamanho máximo da fila

// ----------------------
// Struct da peça
// ----------------------
typedef struct {
    char nome;  // tipo da peça: 'I', 'O', 'T', 'L'
    int id;     // identificador único
} Peca;

// ----------------------
// Struct da fila circular
// ----------------------
typedef struct {
    Peca elementos[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// ----------------------
// Protótipos
// ----------------------
void inicializarFila(Fila *f);
int filaCheia(Fila *f);
int filaVazia(Fila *f);
Peca gerarPeca(int *contadorID);
void enqueue(Fila *f, Peca p);
Peca dequeue(Fila *f);
void exibirFila(Fila *f);

// ----------------------
// Programa principal
// ----------------------
int main() {
    Fila fila;
    int opcao;
    int contadorID = 0;

    srand(time(NULL));

    inicializarFila(&fila);

    // Inicializa fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca(&contadorID));
    }

    do {
        printf("\n===== Fila de Peças do Tetris Stack =====\n");
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (!filaVazia(&fila)) {
                    Peca jogada = dequeue(&fila);
                    printf("\nPeça jogada: [%c %d]\n", jogada.nome, jogada.id);
                } else {
                    printf("\nA fila está vazia! Não há peças para jogar.\n");
                }
                break;

            case 2:
                if (!filaCheia(&fila)) {
                    enqueue(&fila, gerarPeca(&contadorID));
                    printf("\nNova peça adicionada!\n");
                } else {
                    printf("\nA fila está cheia! Não é possível inserir nova peça.\n");
                }
                break;

            case 0:
                printf("\nEncerrando o programa.\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// ----------------------
// Implementações
// ----------------------
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Gera peça automaticamente
Peca gerarPeca(int *contadorID) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = (*contadorID)++;
    return nova;
}

// Inserção na fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (!filaCheia(f)) {
        f->elementos[f->fim] = p;
        f->fim = (f->fim + 1) % TAM_FILA;
        f->quantidade++;
    }
}

// Remoção da fila (dequeue)
Peca dequeue(Fila *f) {
    Peca removida = f->elementos[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

// Exibe fila formatada
void exibirFila(Fila *f) {
    printf("\nFila de peças:\n");
    
    if (filaVazia(f)) {
        printf("[Vazia]\n");
        return;
    }

    int i = f->inicio;
    for (int c = 0; c < f->quantidade; c++) {
        Peca p = f->elementos[i];
        printf("[%c %d] ", p.nome, p.id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}
