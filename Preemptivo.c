#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int tempoChegada;
    int duracaoOriginal;
    int tempoRestante;
    int prioridade;
    int tempoTermino;
    int tempoPrimeiroAtendimento;
} Processo;

typedef struct No {
    Processo *processo;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
} Fila;


Fila* criar_fila() {
    Fila *f = malloc(sizeof(Fila));
    f->inicio = NULL;
    return f;
}

void enfileirar_prioridade(Fila *f, Processo *p) {
    No *novo = malloc(sizeof(No));
    novo->processo = p;
    novo->prox = NULL;

    if (!f->inicio || p->prioridade < f->inicio->processo->prioridade) {
        novo->prox = f->inicio;
        f->inicio = novo;
        return;
    }

    No *atual = f->inicio;
    while (atual->prox &&
           atual->prox->processo->prioridade <= p->prioridade)
        atual = atual->prox;

    novo->prox = atual->prox;
    atual->prox = novo;
}

Processo* desenfileirar(Fila *f) {
    if (!f->inicio) return NULL;
    No *aux = f->inicio;
    Processo *p = aux->processo;
    f->inicio = aux->prox;
    free(aux);
    return p;
}


void calcular_metricas(Fila *concluidos, int n, int tempo_total) {
    float wt = 0, tat = 0, rt = 0;

    printf("\nID | Chegada | Duracao | Termino | Turnaround | Waiting | Response\n");
    printf("-------------------------------------------------------------------\n");

    for (No *aux = concluidos->inicio; aux; aux = aux->prox) {
        Processo *p = aux->processo;

        int turnaround = p->tempoTermino - p->tempoChegada;
        int waiting = turnaround - p->duracaoOriginal;
        int response = p->tempoPrimeiroAtendimento - p->tempoChegada;

        wt += waiting;
        tat += turnaround;
        rt += response;

        printf("%2d | %7d | %7d | %7d | %10d | %7d | %8d\n",
               p->id,
               p->tempoChegada,
               p->duracaoOriginal,
               p->tempoTermino,
               turnaround,
               waiting,
               response);
    }

    printf("\nMedia WT: %.2f\n", wt / n);
    printf("Media TAT: %.2f\n", tat / n);
    printf("Media RT: %.2f\n", rt / n);
    printf("Throughput: %.2f\n", (float)n / tempo_total);
}

int main() {
    printf("Algoritmo: PRIORIDADE PREEMPTIVO\n\n");

    int n, tempo = 0, concluidos = 0;
    Fila *entrada = criar_fila();
    Fila *prontos = criar_fila();
    Fila *finalizados = criar_fila();

    Processo *executando = NULL;

    printf("Quantidade de processos: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Processo *p = malloc(sizeof(Processo));
        printf("P%d (chegada duracao prioridade): ", i + 1);
        scanf("%d %d %d",
              &p->tempoChegada,
              &p->duracaoOriginal,
              &p->prioridade);

        p->id = i + 1;
        p->tempoRestante = p->duracaoOriginal;
        p->tempoPrimeiroAtendimento = -1;

        No *no = malloc(sizeof(No));
        no->processo = p;
        no->prox = entrada->inicio;
        entrada->inicio = no;
    }

    while (concluidos < n) {

        No *ant = NULL, *atual = entrada->inicio;
        while (atual) {
            if (atual->processo->tempoChegada <= tempo) {
                enfileirar_prioridade(prontos, atual->processo);

                if (!ant) entrada->inicio = atual->prox;
                else ant->prox = atual->prox;

                No *rem = atual;
                atual = atual->prox;
                free(rem);
            } else {
                ant = atual;
                atual = atual->prox;
            }
        }

        if (executando && prontos->inicio &&
            prontos->inicio->processo->prioridade < executando->prioridade) {

            enfileirar_prioridade(prontos, executando);
            executando = desenfileirar(prontos);
        }

        if (!executando && prontos->inicio)
            executando = desenfileirar(prontos);

        if (executando) {
            if (executando->tempoPrimeiroAtendimento == -1)
                executando->tempoPrimeiroAtendimento = tempo;

            executando->tempoRestante--;
            tempo++;

            if (executando->tempoRestante == 0) {
                executando->tempoTermino = tempo;
                concluidos++;

                No *no = malloc(sizeof(No));
                no->processo = executando;
                no->prox = finalizados->inicio;
                finalizados->inicio = no;

                executando = NULL;
            }
        } else {
            tempo++;
        }
    }

    calcular_metricas(finalizados, n, tempo);
    return 0;
}
