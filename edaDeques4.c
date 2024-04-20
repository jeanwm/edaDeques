#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no {
    struct no *proximo;
    int valor;
} No;

typedef struct {
    No* cabeca;
} ListaCircular;

No* novo_no(int valor) {
    No* no = (No*) malloc(sizeof(No));
    no->valor = valor;
    no->proximo = NULL;
    return no;
}

ListaCircular* nova_lista() {
    ListaCircular* lista = (ListaCircular*) malloc(sizeof(ListaCircular));
    lista->cabeca = NULL;
    return lista;
}

void inserir_no(ListaCircular* lista, int valor) {
    No* novo = novo_no(valor);
    if (lista->cabeca == NULL) {
        lista->cabeca = novo;
        novo->proximo = novo;
    } else {
        No* ultimo = lista->cabeca;
        while (ultimo->proximo != lista->cabeca) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novo;
        novo->proximo = lista->cabeca;
    }
}

void imprimir_lista_a_partir_de(No* inicio) {
    No* atual = inicio;
    do {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    } while (atual != inicio);
    printf("\n");
}

bool buscar_e_imprimir(ListaCircular* lista, int valor) {
    No* atual = lista->cabeca;
    bool encontrado = false;
    do {
        if (atual->valor == valor) {
            encontrado = true;
            imprimir_lista_a_partir_de(atual);
            break;
        }
        atual = atual->proximo;
    } while (atual != lista->cabeca);
    return encontrado;
}

int main() {
    int n, valor, novo_valor;
    printf("Digite o tamanho do conjunto: ");
    scanf("%d", &n);

    ListaCircular* lista = nova_lista();

    printf("Digite os %d números:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &valor);
        inserir_no(lista, valor);
    }

    printf("Digite o novo número inteiro: ");
    scanf("%d", &novo_valor);

    if (!buscar_e_imprimir(lista, novo_valor)) {
        printf("O número não foi encontrado na lista.\n");
    }

    return 0;
}
