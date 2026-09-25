#include <stdio.h>
#include <stdlib.h>

typedef int TIPOCHAVE;
typedef int bool;

typedef struct {
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

typedef struct aux{
    REGISTRO reg; //valor
    struct aux *ant, *prox; //& do elem ant e o prox
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
} LISTA;

bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
    PONT anterior = NULL;
    PONT atual = l->inicio;

    // Encontra a posição de inserção mantendo a ordem
    while (atual != NULL && atual->reg.chave < reg.chave) {
        anterior = atual;
        atual = atual->prox;
    }

    // Aloca o novo nó e valida a alocação
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) return 0;

    novo->reg = reg;
    novo->ant = anterior;
    novo->prox = atual;

    // Trata a ligação do ponteiro anterior (ou o início da lista)
    if (anterior == NULL) {
        l->inicio = novo;
    } else {
        anterior->prox = novo;
    }

    // Trata a ligação do ponteiro próximo (caso não seja o fim da lista)
    if (atual != NULL) {
        atual->ant = novo;
    }

    return 1;
}