#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int array[MAX_SIZE];
    int inicio;
    int fim;
} Deque;

void inicializar_deque(Deque* d) {
    d->inicio = -1;
    d->fim = -1;
}

bool deque_vazio(Deque* d) {
    return d->inicio == -1;
}

bool deque_cheio(Deque* d) {
    return (d->fim + 1) % MAX_SIZE == d->inicio;
}

void deque_push(Deque* d, int valor) {
    if (deque_cheio(d)) {
        printf("Erro: deque cheio\n");
        return;
    }
    if (deque_vazio(d)) {
        d->inicio = 0;
        d->fim = 0;
    } else {
        d->fim = (d->fim + 1) % MAX_SIZE;
    }
    d->array[d->fim] = valor;
}

void deque_unshift(Deque* d, int valor) {
    if (deque_cheio(d)) {
        printf("Erro: deque cheio\n");
        return;
    }
    if (deque_vazio(d)) {
        d->inicio = 0;
        d->fim = 0;
    } else {
        d->inicio = (d->inicio - 1 + MAX_SIZE) % MAX_SIZE;
    }
    d->array[d->inicio] = valor;
}

int deque_pop(Deque* d) {
    if (deque_vazio(d)) {
        printf("Erro: deque vazio\n");
        return -1;
    }
    int valor = d->array[d->fim];
    if (d->inicio == d->fim) {
        d->inicio = -1;
        d->fim = -1;
    } else {
        d->fim = (d->fim - 1 + MAX_SIZE) % MAX_SIZE;
    }
    return valor;
}

int deque_shift(Deque* d) {
    if (deque_vazio(d)) {
        printf("Erro: deque vazio\n");
        return -1;
    }
    int valor = d->array[d->inicio];
    if (d->inicio == d->fim) {
        d->inicio = -1;
        d->fim = -1;
    } else {
        d->inicio = (d->inicio + 1) % MAX_SIZE;
    }
    return valor;
}

void imprimir_deque(Deque* d) {
    if (deque_vazio(d)) {
        printf("Deque vazio\n");
        return;
    }
    int atual = d->inicio;
    while (atual != d->fim) {
        printf("%d ", d->array[atual]);
        atual = (atual + 1) % MAX_SIZE;
    }
    printf("%d\n", d->array[d->fim]);
}

void imprimir_deque_inverso(Deque* d) {
    if (deque_vazio(d)) {
        printf("Deque vazio\n");
        return;
    }
    int atual = d->fim;
    while (atual != d->inicio) {
        printf("%d ", d->array[atual]);
        atual = (atual - 1 + MAX_SIZE) % MAX_SIZE;
    }
    printf("%d\n", d->array[d->inicio]);
}

int main(void) {
    int n, valor;
    printf("Digite o tamanho do conjunto: ");
    scanf("%d", &n);

    Deque d;
    inicializar_deque(&d);

    printf("Digite os %d números:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &valor);
        deque_push(&d, valor);
    }

    printf("Ordem de inserção: ");
    imprimir_deque(&d);

    printf("Ordem inversa à inserção: ");
    imprimir_deque_inverso(&d);

    return 0;
}