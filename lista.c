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
    PONT anterior = NULL; // cria elemento anterior = null
    PONT atual = l->inicio;

    // Percorre a lista até achar a posição correta
    // (anterior fica logo antes de atual, sempre)
    while (atual != NULL && atual->reg.chave < reg.chave) {
        anterior = atual;
        atual = atual->prox;
    }

    // Verifica duplicidade: se achou elemento com mesma chave
    if (atual != NULL && atual->reg.chave == reg.chave) {
        return 0;
    }

    // Cria o novo elemento
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) {
        return 0; // falha de alocação
    }
    novo->reg = reg;

    // Liga o novo elemento aos seus vizinhos
    novo->prox = atual;      // pode ser NULL (fim da lista)
    novo->ant  = anterior;   // pode ser NULL (início da lista)

    // Atualiza o vizinho ANTERIOR (se existir) para apontar pro novo
    if (anterior != NULL) {
        anterior->prox = novo;
    } else {
        // não havia anterior -> novo é o primeiro da lista
        l->inicio = novo;
    }

    // Atualiza o vizinho POSTERIOR (se existir) para apontar pro novo
    if (atual != NULL) {
        atual->ant = novo;
    }

    return 1;
}



int main(){

    printf("Hello World!");

    return 0;
}
