#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a estrutura para um nó da árvore treap
typedef struct NoTreap {
    int chave;
    int prioridade;
    struct NoTreap* esquerdo;
    struct NoTreap* direito;
} NoTreap;

// Função para criar um novo nó da árvore treap
NoTreap* criarNovoNo(int chave) {
    NoTreap* no = (NoTreap*)malloc(sizeof(NoTreap));
    no->chave = chave;
    no->prioridade = rand() % 100 + 1; // Prioridade aleatória entre 1 e 100
    no->esquerdo = NULL;
    no->direito = NULL;
    return no;
}

// Função para rotacionar à direita
NoTreap* rotacionarDireita(NoTreap* raiz) {
    NoTreap* novaRaiz = raiz->esquerdo;
    NoTreap* temp = novaRaiz->direito;

    novaRaiz->direito = raiz;
    raiz->esquerdo = temp;

    return novaRaiz;
}

// Função para rotacionar à esquerda
NoTreap* rotacionarEsquerda(NoTreap* raiz) {
    NoTreap* novaRaiz = raiz->direito;
    NoTreap* temp = novaRaiz->esquerdo;

    novaRaiz->esquerdo = raiz;
    raiz->direito = temp;

    return novaRaiz;
}

// Função para inserir um novo nó
NoTreap* inserir(NoTreap* raiz, int chave) {
    // Caso base: árvore vazia
    if (raiz == NULL) {
        return criarNovoNo(chave);
    }

    // Insere na subárvore esquerda se o chave for menor
    if (chave < raiz->chave) {
        raiz->esquerdo = inserir(raiz->esquerdo, chave);

        // Verifica e rotaciona se necessário
        if (raiz->esquerdo->prioridade > raiz->prioridade) {
            raiz = rotacionarDireita(raiz);
        }
    } else {
        // Chave é maior ou igual à chave atual do nó
        raiz->direito = inserir(raiz->direito, chave);

        // Verifica e rotaciona se necessário
        if (raiz->direito->prioridade > raiz->prioridade) {
            raiz = rotacionarEsquerda(raiz);
        }
    }

    return raiz;
}

// Função para buscar uma chave
NoTreap* buscar(NoTreap* raiz, int chave) {
    // Caso base: árvore vazia ou nó encontrado
    if (raiz == NULL || raiz->chave == chave) {
        return raiz;
    }

    // Chave é maior que a chave do nó atual
    if (raiz->chave < chave) {
        return buscar(raiz->direito, chave);
    }

    // Chave é menor que a chave do nó atual
    return buscar(raiz->esquerdo, chave);
}

// Função para remover um nó
NoTreap* remover(NoTreap* raiz, int chave) {
    if (raiz == NULL) {
        return raiz;
    }

    if (chave < raiz->chave) {
        raiz->esquerdo = remover(raiz->esquerdo, chave);
    } else if (chave > raiz->chave) {
        raiz->direito = remover(raiz->direito, chave);
    } else {
        // Nó encontrado, manipula diferentes casos
        if (raiz->esquerdo == NULL && raiz->direito == NULL) {
            // Nó folha, simplesmente o exclui
            free(raiz);
            return NULL;
        }

        if (raiz->esquerdo == NULL) {
            NoTreap* temp = raiz->direito;
            free(raiz);
            return temp;
        }

        if (raiz->direito == NULL) {
            NoTreap* temp = raiz->esquerdo;
            free(raiz);
            return temp;
        }

        // Nó tem dois filhos, encontre o menor nó na subárvore direita
        NoTreap* menorDireita = raiz->direito;
        while (menorDireita->esquerdo != NULL) {
            menorDireita = menorDireita->esquerdo;
        }

        // Substitua o nó pelo seu menor filho
        raiz->chave = menorDireita->chave;
        raiz->prioridade = menorDireita->prioridade;

        // Remova o menor nó da subárvore direita
        raiz->direito = remover(raiz->direito, menorDireita->chave);
    }

    // Verifica e rotaciona se necessário
    if (raiz != NULL) {
        if (raiz->esquerdo != NULL && raiz->esquerdo->prioridade > raiz->prioridade) {
            raiz = rotacionarEsquerda(raiz);
        }
        if (raiz->direito != NULL && raiz->direito->prioridade > raiz->prioridade) {
            raiz = rotacionarDireita(raiz);
        }
    }

    return raiz;
}

// Função para imprimir a árvore treap em ordenada
void imprimirTreap(NoTreap* raiz) {
    if (raiz == NULL) {
        return;
    }

    imprimirTreap(raiz->esquerdo);

    printf("%d (%d)\n", raiz->chave, raiz->prioridade);

    imprimirTreap(raiz->direito);
}

int main() {
    srand(time(NULL)); // Semeia o gerador de números aleatórios

    NoTreap* raiz = NULL;

    // Insere nós
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    // Imprime a árvore inicial
    printf("Árvore inicial:\n");
    imprimirTreap(raiz);
    printf("\n");

    // Busca por um nó
    NoTreap* buscado = buscar(raiz, 60);
    if (buscado != NULL) {
        printf("Chave %d encontrada\n", buscado->chave);
    } else {
        printf("Chave não encontrada```
