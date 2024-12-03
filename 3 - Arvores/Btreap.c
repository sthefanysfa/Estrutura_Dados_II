#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_ARVORE_B 3

typedef struct NoB {
    int chave;
    struct NoB* filhos[TAMANHO_ARVE_B];
    int quantidadeFilhos;
} NoB;

NoB* criarNovaNoB(int chave) {
    NoB* no = (NoB*)malloc(sizeof(NoB));
    no->chave = chave;
    no->quantidadeFilhos = 0;
    
    for (int i = 0; i < TAMANHO_ARVE_B; i++) {
        no->filhos[i] = NULL;
    }
    
    return no;
}

NoB* inserirNoB(NoB* raiz, int chave) {
    if (raiz == NULL) {
        return criarNovaNoB(chave);
    }

    int posicao = 0;
    while (posicao < raiz->quantidadeFilhos && chave > raiz->filhos[posicao]->chave) {
        posicao++;
    }

    if (raiz->quantidadeFilhos == TAMANHO_ARVE_B - 1) {
        // Árvore cheia, precisa ser dividida
        NoB* novaRaiz = criarNovaNoB(chave);
        
        // Copiar elementos maiores para a nova raiz
        for (int i = 0; i <= TAMANHO_ARVE_B / 2; i++) {
            novaRaiz->filhos[i] = raiz->filhos[i];
        }
        
        // Atualizar a nova raiz
        novaRaiz->quantidadeFilhos = TAMANHO_ARVE_B;
        raiz->quantidadeFilhos = TAMANHO_ARVE_B / 2;
        
        // Colocar o elemento restante na posição correta
        novaRaiz->filhos[raiz->quantidadeFilhos] = raiz;
        novaRaiz->filhos[raiz->quantidadeFilhos + 1] = criarNovaNoB(chave);
        
        return novaRaiz;
    }

    // Inserir o elemento na posição correta
    raiz->filhos[posicao] = inserirNoB(raiz->filhos[posicao], chave);
    raiz->quantidadeFilhos++;

    return raiz;
}

NoB* buscarNoB(NoB* raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave) {
        return raiz;
    }

    for (int i = 0; i < raiz->quantidadeFilhos; i++) {
        if (chave < raiz->filhos[i]->chave) {
            return buscarNoB(raiz->filhos[i], chave);
        }
    }

    return buscarNoB(raiz->filhos[raiz->quantidadeFilhos], chave);
}

NoB* removerNoB(NoB* raiz, int chave) {
    if (raiz == NULL) {
        return raiz;
    }

    if (chave < raiz->chave) {
        raiz->filhos[0] = removerNoB(raiz->filhos[0], chave);
    } else if (chave > raiz->chave) {
        raiz->filhos[raiz->quantidadeFilhos] = removerNoB(raiz->filhos[raiz->quantidadeFilhos], chave);
    } else {
        // Remover o nó atual
        NoB* noRemover = raiz;

        if (raiz->quantidadeFilhos == 1) {
            // Nó folha, simplesmente removê-lo
            free(noRemover);
            return NULL;
        }

        // Encontrar o sucessor ou antecessor
        int posicaoSucessor = encontrarSucessor(raiz->filhos[0]);
        
        raiz->chave = raiz->filhos[0]->filhos[posicaoSucessor]->chave;
        raiz->filhos[0] = removerNoB(raiz->filhos[0], raiz->chave);

        return raiz;
    }

    return raiz;
}

int encontrarSucessor(NoB* no) {
    while (no->filhos[no->quantidadeFilhos - 1] != NULL &&
           no->filhos[no->quantidadeFilhos - 1]->quantidadeFilhos < TAMANHO_ARVE_B - 1) {
        no = no->filhos[no->quantidadeFilhos - 1];
    }
    return no->quantidadeFilhos - 1;
}

void imprimirNoB(NoB* raiz) {
    if (raiz == NULL) {
        return;
    }

    for (int i = 0; i < raiz->quantidadeFilhos; i++) {
        imprimirNoB(raiz->filhos[i]);
    }

    printf("%d ", raiz->chave);
}

int main() {
    srand(time(NULL));

    NoB* raiz = NULL;

    raiz = inserirNoB(raiz, 10);
    raiz = inserirNoB(raiz, 20);
    raiz = inserirNoB(raiz, 5);
    raiz = inserirNoB(raiz, 15);
    raiz = inserirNoB(raiz, 25);

    printf("Árvore B após inserções:\n");
    imprimirNoB(raiz);
    printf("\n");

    NoB* buscado = buscarNoB(raiz, 15);
    if (buscado != NULL) {
        printf("Chave %d encontrada\n", buscado->chave);
    } else {
        printf("Chave não encontrada\n");
    }

    raiz = removerNoB(raiz, 20);

    printf("Árvore B após remoção:\n");
    imprimirNoB(raiz);
    printf("\n");

    return 0;
}
