#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h> //só pra não estourar a transposição

/* ----------------------------------------------------------------------
  Estruturas de dados (não altere nomes e ordem de campos)
 ---------------------------------------------------------------------- */

typedef struct celula {
    int linha;
    int coluna;
    int valor;
    struct celula *proxima_linha;
    struct celula *proxima_coluna;
} celula_t;

typedef struct fileira {
    int indice;
    celula_t* primeiro;
    struct fileira *proximo;
} fileira_t;

typedef struct {
    bool transposicao;
    int linha;
    int coluna;
    union {
        int valor_anterior;
        int tamanho;
    };
} operacao_t;

typedef struct elo_pilha {
    operacao_t op;
    struct elo_pilha *proximo;
} elo_pilha_t;

typedef struct {
    elo_pilha_t* topo;
} pilha_t;

typedef struct {
    fileira_t* primeira_linha;
    fileira_t* primeira_coluna;
    int total_celulas;
    pilha_t historico;
} planilha_t;

/* ---------------------------------------------------------------------- *
    Funções auxiliar para leitura das strings dos comandos
 ---------------------------------------------------------------------- */

int igual(char* a, char* b) {
    int i = 0;
    while (a[i] == b[i] && a[i] != '\0') i++;

    return (a[i] == b[i]);
}

/* ---------------------------------------------------------------------- *
    Funções obrigatórias (não altere as assinaturas)
 ---------------------------------------------------------------------- */

void inicializar_planilha(planilha_t *p) {
    // TODO: inicialize primeiraLinha, primeiraColuna, total_celulas e historico.topo
    p->primeira_linha = 0;
    p->primeira_coluna = 0;
    p->total_celulas = 0;
    p->historico.topo = 0;
}

celula_t* buscar_celula(planilha_t *p, int lin, int col,
                      celula_t** cel_ant_linha, celula_t** cel_ant_coluna,
                      fileira_t** fil_ant_linha, fileira_t** fil_ant_coluna) {
    /* TODO: localize a celula (lin,col), preencha os quatro antecessores 
        por referencia, retorne NULL se a celula nao existir */
    fileira_t* linha_atual = p->primeira_linha;
    *fil_ant_linha = NULL;
    *cel_ant_linha = NULL;
    *fil_ant_coluna = NULL;
    *cel_ant_coluna = NULL;

    //espelhando pra achar o fil_ant_coluna e o cel_ant_coluna
    fileira_t* coluna_atual = p->primeira_coluna;

    while (coluna_atual != NULL && coluna_atual->indice < col){
        *fil_ant_coluna = coluna_atual;
        coluna_atual = coluna_atual->proximo;
    }
    if(coluna_atual != NULL && coluna_atual->indice == col){
        celula_t* celula_atual = coluna_atual->primeiro;
        
        while(celula_atual != NULL && celula_atual->linha < lin){
            *cel_ant_coluna = celula_atual;
            celula_atual = celula_atual->proxima_coluna;//É o proximo da mesma coluna! - nome confuso
        }
    }

    while(linha_atual != NULL && linha_atual->indice < lin){
        *fil_ant_linha = linha_atual;
        linha_atual = linha_atual->proximo;
    }
    if (linha_atual != NULL && linha_atual->indice == lin){  
        celula_t* cel_atual = linha_atual->primeiro;
        
        while (cel_atual != NULL && cel_atual->coluna < col){
            *cel_ant_linha = cel_atual;
            cel_atual = cel_atual->proxima_linha; //É o proximo da mesma linha! - nome confuso 
        }
        if(cel_atual != NULL && cel_atual->coluna == col) return cel_atual;
    }
    

    return NULL;
}

int obter_valor(planilha_t *p, int linha, int coluna) {
    celula_t* cel_ant_linha;
    celula_t* cel_ant_coluna;
    fileira_t* fil_ant_linha;
    fileira_t* fil_ant_coluna;

    celula_t* celula_atual = buscar_celula(p, linha, coluna, &cel_ant_linha, &cel_ant_coluna, &fil_ant_linha, &fil_ant_coluna);
    
    if(celula_atual != NULL) return celula_atual->valor;

    return 0;
}

int somar_intervalo(planilha_t* p, int linha_ini, int linha_fim, int coluna_ini, int coluna_fim) {
    // TODO: some os valores das celulas nao nulas no intervalo dado
    //basicamente percorrer todas as linhas até achar as entre o início e o fim

    int super_soma = 0;

    fileira_t* linha_atual = p->primeira_linha;
    while(linha_atual != NULL && linha_atual->indice <= linha_fim){
        if (linha_atual->indice >= linha_ini){
            celula_t* celula_atual = linha_atual->primeiro;
            while(celula_atual != NULL && celula_atual->coluna <= coluna_fim){
                if(celula_atual->coluna >= coluna_ini){
                   super_soma = super_soma + celula_atual->valor; 
                }
                celula_atual = celula_atual->proxima_linha;
            }
        }
        linha_atual = linha_atual->proximo;
    }

    
    return super_soma;
}

int contar_nao_nulas(planilha_t* p) {
    // TODO: retorne a quantidade de celulas nao nulas
    //era só isso:
    return p->total_celulas;
    //mas eu tinha feito o código inteiro percorrendo as celulas -_-
}   
bool definir_celula(planilha_t* p, int lin, int col, int valor) {
    /* TODO: implemente os 4 casos (atualizar/criar/remover/nulo),
       empilhando em p->historico quando houver alteracao efetiva.
       Retorna true se houve alteracao, false se foi operacao nula. */

    celula_t* cel_ant_linha;
    celula_t* cel_ant_coluna;
    fileira_t* fil_ant_linha;
    fileira_t* fil_ant_coluna;

    celula_t* celula_atual = buscar_celula(p, lin, col,
                      &cel_ant_linha, &cel_ant_coluna,
                      &fil_ant_linha, &fil_ant_coluna);

    // Atualizar (acho que é o mais fácil)
    if (celula_atual != NULL && valor != 0) {
        if (celula_atual -> valor == valor){
            return false;
        }
        elo_pilha_t* elo_novo = malloc(sizeof(elo_pilha_t));
        elo_novo->op.transposicao = false;
        elo_novo->op.linha = lin;
        elo_novo->op.coluna = col;
        elo_novo->op.valor_anterior = celula_atual->valor;
        elo_novo->proximo = p->historico.topo;
        p->historico.topo = elo_novo;
        celula_atual->valor = valor;
        return true;
    }

    //Criar - se ainda não existe não dá pra atualizar (OBV)
    if (celula_atual == NULL && valor != 0) {
        celula_atual = malloc(sizeof(celula_t));
        celula_atual->linha = lin;
        celula_atual->coluna = col;
        celula_atual->valor = valor;

        elo_pilha_t* elo_novo = malloc(sizeof(elo_pilha_t));
        elo_novo->op.transposicao = false;
        elo_novo->op.linha = lin;
        elo_novo->op.coluna = col;
        elo_novo->op.valor_anterior = 0;
        elo_novo->proximo = p->historico.topo;
        p->historico.topo = elo_novo;

        //encaixa na lista da LINHA
        fileira_t* fil_linha = (fil_ant_linha == NULL) ? p->primeira_linha : fil_ant_linha->proximo;

        if (cel_ant_linha != NULL) {
            // já existe célula antes na mesma linha -> insere no meio
            celula_atual->proxima_linha = cel_ant_linha->proxima_linha;
            cel_ant_linha->proxima_linha = celula_atual;
        } else if (fil_linha != NULL && fil_linha->indice == lin) {
            // fileira da linha já existe, célula nova vira a primeira
            celula_atual->proxima_linha = fil_linha->primeiro;
            fil_linha->primeiro = celula_atual;
        } else {
            // fileira da linha ainda não existe, precisa criar
            fileira_t* fileira_atual = malloc(sizeof(fileira_t));
            fileira_atual->indice = lin;
            fileira_atual->primeiro = celula_atual;
            fileira_atual->proximo = fil_linha;
            celula_atual->proxima_linha = NULL;

            if (fil_ant_linha == NULL) {
                p->primeira_linha = fileira_atual;
            } else {
                fil_ant_linha->proximo = fileira_atual;
            }
        }

        //encaixa na lista da COLUNA
        fileira_t* fil_coluna = (fil_ant_coluna == NULL) ? p->primeira_coluna : fil_ant_coluna->proximo;

        if (cel_ant_coluna != NULL) {
            celula_atual->proxima_coluna = cel_ant_coluna->proxima_coluna;
            cel_ant_coluna->proxima_coluna = celula_atual;
        } else if (fil_coluna != NULL && fil_coluna->indice == col) {
            celula_atual->proxima_coluna = fil_coluna->primeiro;
            fil_coluna->primeiro = celula_atual;
        } else {
            fileira_t* fileira_atual_coluna = malloc(sizeof(fileira_t));
            fileira_atual_coluna->indice = col;
            fileira_atual_coluna->primeiro = celula_atual;
            fileira_atual_coluna->proximo = fil_coluna;
            celula_atual->proxima_coluna = NULL;

            if (fil_ant_coluna == NULL) {
                p->primeira_coluna = fileira_atual_coluna;
            } else {
                fil_ant_coluna->proximo = fileira_atual_coluna;
            }
        }
        p->total_celulas++;

        return true;
    }

    // Remover (finalmente!)
    if (celula_atual != NULL && valor == 0) {
        elo_pilha_t* elo_novo = malloc(sizeof(elo_pilha_t));
        elo_novo->op.transposicao = false;
        elo_novo->op.linha = lin;
        elo_novo->op.coluna = col;
        elo_novo->op.valor_anterior = celula_atual->valor;
        elo_novo->proximo = p->historico.topo;
        p->historico.topo = elo_novo;

        // desconecta da lista da LINHA!
        fileira_t* fil_linha = (fil_ant_linha == NULL) ? p->primeira_linha : fil_ant_linha->proximo;

        if (cel_ant_linha != NULL) {
            cel_ant_linha->proxima_linha = celula_atual->proxima_linha;
        } else {
            fil_linha->primeiro = celula_atual->proxima_linha;
            if (fil_linha->primeiro == NULL) {
                // linha ficou vazia, remove a fileira
                if (fil_ant_linha == NULL) {
                    p->primeira_linha = fil_linha->proximo;
                } else {
                    fil_ant_linha->proximo = fil_linha->proximo;
                }
                free(fil_linha);
            }
        }

        // desconecta da lista da COLUNA
        fileira_t* fil_coluna = (fil_ant_coluna == NULL) ? p->primeira_coluna : fil_ant_coluna->proximo;

        if (cel_ant_coluna != NULL) {
            cel_ant_coluna->proxima_coluna = celula_atual->proxima_coluna;
        } else {
            fil_coluna->primeiro = celula_atual->proxima_coluna;
            // se ficou vazia exclui tb
            if (fil_coluna->primeiro == NULL) {
                if (fil_ant_coluna == NULL) {
                    p->primeira_coluna = fil_coluna->proximo;
                } else {
                    fil_ant_coluna->proximo = fil_coluna->proximo;
                }
                free(fil_coluna);
            }
        }

        free(celula_atual);
        p->total_celulas--;

        return true;
    }

    return false;
}//#não aguento mais

bool remover_celula(planilha_t* p, int lin, int col) {
    // TODO: remova a celula (lin,col)
    //já não fiz isso no definir? -_- 
    return definir_celula(p, lin, col, 0); // é só isso??
}

bool transpor(planilha_t* p, int lin, int col, int tamanho) {
    /* TODO: transpoe uma matriz quadrada que está localizada entre
       as linhas [lin, lin + tamanho) e colunas [col, col + tamanho). */
       
    elo_pilha_t* base = p->historico.topo;
    bool alterou = false;
    if (tamanho <= 0 || lin > INT_MAX - tamanho || col > INT_MAX - tamanho){
        return false;
    } 

    for (int i = 0; i < tamanho; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            int valor1 = obter_valor(p, lin + i, col + j);
            int valor2 = obter_valor(p, lin + j, col + i);

            if (valor1 != valor2) {
                definir_celula(p, lin + i, col + j, valor2);
                definir_celula(p, lin + j, col + i, valor1);
                alterou = true;
            }
        }
    }

    if (!alterou) return false;

    /* descarta as entradas que os definir_celula acima empilharam */
    while (p->historico.topo != base) {
        elo_pilha_t* lixo = p->historico.topo;
        p->historico.topo = lixo->proximo;
        free(lixo);
    }

    /* empilha UMA unica entrada representando a transposicao inteira */
    elo_pilha_t* elo = malloc(sizeof(elo_pilha_t));
    elo->op.transposicao = true;
    elo->op.linha = lin;
    elo->op.coluna = col;
    elo->op.tamanho = tamanho;
    elo->proximo = base;
    p->historico.topo = elo;

    return alterou;
}

bool desfazer(planilha_t* p) {
    if (p->historico.topo == NULL) return false;

    /* 1. desempilha a operacao a ser desfeita (guardando uma copia) */
    elo_pilha_t* elo = p->historico.topo;
    operacao_t op = elo->op;
    p->historico.topo = elo->proximo;
    free(elo);

    /* 2. marca como ficou o historico depois do pop */
    elo_pilha_t* base = p->historico.topo;

    /* 3. aplica a operacao inversa */
    if (op.transposicao)
        transpor(p, op.linha, op.coluna, op.tamanho);   // transpor eh inversa de si mesma
    else
        definir_celula(p, op.linha, op.coluna, op.valor_anterior);

    /* 4. descarta o que o passo 3 empilhou (desfazer nao pode gerar historico) */
    while (p->historico.topo != base) {
        elo_pilha_t* lixo = p->historico.topo;
        p->historico.topo = lixo->proximo;
        free(lixo);
    }

    return true;
}

void exibir_planilha(planilha_t *p) {
    /* TODO: imprima "linha coluna valor" por linha, em ordem crescente
       de linha e, dentro de cada linha, de coluna. Se vazia, imprima
       "PLANILHA VAZIA" */
    if(p->primeira_linha == NULL){
        printf("PLANILHA VAZIA\n");
        return;
    }
    
    fileira_t* fileira_atual = p->primeira_linha;

    while(fileira_atual != NULL){
        celula_t* celula_atual = fileira_atual->primeiro;
        while(celula_atual != NULL){
        printf("%d %d %d\n", celula_atual->linha, celula_atual->coluna, celula_atual->valor);
            celula_atual = celula_atual->proxima_linha;
        }
        fileira_atual = fileira_atual->proximo;
    }

}

void exibir_historico(planilha_t* p) {
    /* imprime do topo para a base:
       - operacao normal: "linha coluna valor_anterior"
       - transposicao:    "T linha coluna tamanho"
       Se vazio, imprime "HISTORICO VAZIO" */
    if (p->historico.topo == NULL) {
        printf("HISTORICO VAZIO\n");
        return;
    }

    elo_pilha_t* elo_atual = p->historico.topo;

    while (elo_atual != NULL) {
        if (elo_atual->op.transposicao) {
            printf("T %d %d %d\n", elo_atual->op.linha,
                                   elo_atual->op.coluna,
                                   elo_atual->op.tamanho);
        } else {
            printf("%d %d %d\n", elo_atual->op.linha,
                                 elo_atual->op.coluna,
                                 elo_atual->op.valor_anterior);
        }
        elo_atual = elo_atual->proximo;
    }
}

void liberar_tudo(planilha_t* p) {
    // TODO: libere toda a memória alocada por fileira, celula, e pilha.

    // para liberar as células -> por linha igual o mostrar a planilha
    fileira_t* fileira_atual = p->primeira_linha;
    while(fileira_atual != NULL){
        celula_t* celula_atual = fileira_atual->primeiro;
        while(celula_atual != NULL){
            celula_t* proxima = celula_atual->proxima_linha;
            free(celula_atual);
            celula_atual = proxima;
        }
        fileira_atual = fileira_atual->proximo;
    }

    //agr liberar as fileiras
    fileira_t* fileira_atual_linha = p->primeira_linha;
    while(fileira_atual_linha != NULL){
        fileira_t* proxima_fileira_linha = fileira_atual_linha->proximo;
        free(fileira_atual_linha);
        fileira_atual_linha = proxima_fileira_linha;
    }
    fileira_t* fileira_atual_coluna = p->primeira_coluna;
    while(fileira_atual_coluna != NULL){
        fileira_t* proxima_fileira_coluna = fileira_atual_coluna->proximo;
        free(fileira_atual_coluna);
        fileira_atual_coluna = proxima_fileira_coluna;
    }

    //liberar a pilha
    elo_pilha_t* celula_atual = p->historico.topo;
    while(celula_atual != NULL){
        elo_pilha_t* proximo = celula_atual->proximo;
        free(celula_atual);
        celula_atual = proximo;
    }
    
    //zerar os contadores
    p->primeira_linha = NULL;
    p->primeira_coluna = NULL;
    p->historico.topo = NULL;
    p->total_celulas = 0;
}

/* ---------------------------------------------------------------------- *
    Main para leitura de arquivos (já pronta no caso, pode ser que na versão final deixemos sem)
 ---------------------------------------------------------------------- */

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso do comando eh: %s arquivo_entrada.txt arquivo_saida.txt\n", argv[0]);
        return 1;
    }
    
    FILE* entrada = fopen(argv[1], "r");
    FILE* saida = freopen(argv[2], "w", stdout);

    if (!entrada || !saida) {
        fprintf(stderr, "Erro ao tentar abrir os arquivos.\n");
        return 1;
    }

    planilha_t p;
    inicializar_planilha(&p);

    int n;
    fscanf(entrada, "%d", &n);

    char cmd[20];

    while (fscanf(entrada, "%s", cmd) != EOF) {
 
        if (igual(cmd, "DEF")) {
            int lin, col, valor;
            fscanf(entrada, "%d %d %d", &lin, &col, &valor);
            definir_celula(&p, lin, col, valor);
        } else if (igual(cmd, "REM")) {
            int lin, col;
            fscanf(entrada, "%d %d", &lin, &col);
            remover_celula(&p, lin, col);
        } else if (igual(cmd, "GET")) {
            int lin, col;
            fscanf(entrada, "%d %d", &lin, &col);
            fprintf(saida, "GET %d %d %d\n", lin, col, obter_valor(&p, lin, col));
        } else if (igual(cmd, "SOMA")) {
            int li, lf, ci, cf;
            fscanf(entrada, "%d %d %d %d", &li, &lf, &ci, &cf);
            fprintf(saida, "SOMA %d %d %d %d %d\n", li, lf, ci, cf, somar_intervalo(&p, li, lf, ci, cf));
        } else if (igual(cmd, "CONT")) {
            fprintf(saida, "CONT %d\n", contar_nao_nulas(&p));
        } else if (igual(cmd, "DESFAZER")) {
            if (!desfazer(&p)) {
                fprintf(saida, "HISTORICO VAZIO\n");
            }
        } else if (igual(cmd, "EXIBIR")) {
            if (contar_nao_nulas(&p)) {
                printf("PLANILHA\n");
                exibir_planilha(&p);
            } else {
                printf("PLANILHA VAZIA\n");
            }
        } else if (igual(cmd, "HIST")) {
            if (p.historico.topo) {
                printf("HISTORICO\n");
                exibir_historico(&p);
            }
            else {
                printf("HISTORICO VAZIO\n");
            }
        } else if (igual(cmd, "TRANS")) {
            int lin, col, tam;
            fscanf(entrada, "%d %d %d", &lin, &col, &tam);
            transpor(&p, lin, col, tam);
        }
    }

    fclose(entrada);
    fclose(saida);

    liberar_tudo(&p);
    return 0;
}
