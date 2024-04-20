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

    no->anterior = d->cauda;

    if (deque_vazio(d)) {
        d->cabeca = no;
    } else {
        d->cauda->proximo = no;
    }

    d->cauda = no;
}

void deque_unshift(Deque* d, int valor) {
    No* no = novo_no(valor);

    no->proximo = d->cabeca;

    if (deque_vazio(d)) {
        d->cauda = no;
    } else {
        d->cabeca->anterior = no;
    }

    d->cabeca = no;
}

int deque_pop(Deque* d) {
    if (deque_vazio(d)) {
        return -1;
    }

    int valor = d->cauda->valor;
    No* anterior = d->cauda->anterior;

    if (anterior != NULL) {
        anterior->proximo = NULL;
    }

    free(d->cauda);
    d->cauda = anterior;

    if (anterior == NULL) {
        d->cabeca = NULL;
    }

    return valor;
}

int deque_shift(Deque* d) {
    if (deque_vazio(d)) {
        return -1;
    }

    int valor = d->cabeca->valor;
    No* proximo = d->cabeca->proximo;

    if (proximo != NULL) {
        proximo->anterior = NULL;
    }

    free(d->cabeca);
    d->cabeca = proximo;

    if (proximo == NULL) {
        d->cauda = NULL;
    }

    return valor;
}

void imprimir_deque(Deque* d) {
    No* atual = d->cabeca;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

void imprimir_deque_inverso(Deque* d) {
    No* atual = d->cauda;
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->anterior;
    }
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