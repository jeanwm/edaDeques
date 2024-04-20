#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no {
    struct no *anterior;
    struct no *proximo;
    int valor;
} No;

typedef struct {
    No* cabeca;
    No* cauda;
} Deque;

No* novo_no(int valor) {
    No* no = (No*) malloc(sizeof(No));
    no->valor = valor;
    no->anterior = no->proximo = NULL;

    return no;
}

Deque* novo_deque() {
    Deque* d = (Deque*) malloc(sizeof(Deque));
    d->cabeca = d->cauda = NULL;

    return d;
}

bool deque_vazio(Deque* d) {
    return d->cabeca == NULL && d->cauda == NULL;
}

void deque_push(Deque* d, int valor) {
    No* no = novo_no(valor);

    if (deque_vazio(d)) {
        d->cabeca = no;
        d->cauda = no;
        no->proximo = no->anterior = no;
    } else {
        no->anterior = d->cauda;
        no->proximo = d->cabeca;
        d->cauda->proximo = no;
        d->cabeca->anterior = no;
        d->cauda = no;
    }
}

void deque_unshift(Deque* d, int valor) {
    No* no = novo_no(valor);

    if (deque_vazio(d)) {
        d->cabeca = no;
        d->cauda = no;
        no->proximo = no->anterior = no;
    } else {
        no->proximo = d->cabeca;
        no->anterior = d->cauda;
        d->cabeca->anterior = no;
        d->cauda->proximo = no;
        d->cabeca = no;
    }
}

int deque_pop(Deque* d) {
    if (deque_vazio(d)) {
        return -1;
    }

    int valor = d->cauda->valor;
    No* anterior = d->cauda->anterior;
    No* proximo = d->cauda->proximo;

    anterior->proximo = d->cabeca;
    d->cabeca->anterior = anterior;
    free(d->cauda);
    d->cauda = anterior;

    if (d->cauda == d->cabeca) {
        d->cabeca = NULL;
        d->cauda = NULL;
    }

    return valor;
}

int deque_shift(Deque* d) {
    if (deque_vazio(d)) {
        return -1;
    }

    int valor = d->cabeca->valor;
    No* anterior = d->cabeca->anterior;
    No* proximo = d->cabeca->proximo;

    anterior->proximo = proximo;
    proximo->anterior = anterior;
    free(d->cabeca);
    d->cabeca = proximo;

    if (d->cauda == d->cabeca) {
        d->cabeca = NULL;
        d->cauda = NULL;
    }

    return valor;
}

void imprimir_deque(Deque* d) {
    if (deque_vazio(d)) {
        printf("Deque vazio\n");
        return;
    }
    No* atual = d->cabeca;
    do {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    } while (atual != d->cabeca);
    printf("\n");
}

void imprimir_deque_inverso(Deque* d) {
    if (deque_vazio(d)) {
        printf("Deque vazio\n");
        return;
    }
    No* atual = d->cauda;
    do {
        printf("%d ", atual->valor);
        atual = atual->anterior;
    } while (atual != d->cauda);
    printf("\n");
}

int main(void) {
    int n, valor;
    printf("Digite o tamanho do conjunto: ");
    scanf("%d", &n);

    Deque* d = novo_deque();

    printf("Digite os %d números:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &valor);
        deque_push(d, valor);
    }

    printf("Ordem de inserção: ");
    imprimir_deque(d);

    printf("Ordem inversa à inserção: ");
    imprimir_deque_inverso(d);

    return 0;
}