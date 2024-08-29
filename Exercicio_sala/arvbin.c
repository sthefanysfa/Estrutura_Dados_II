#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//------------------------------------------------------
struct NO{
int info;
struct NO *esq;
struct NO *dir;
};

struct NO *criarno(int info){

  struct NO *novoNo = (struct NO *)malloc(sizeof(struct NO));
  if(novoNo == NULL){
    printf("Algo deu errado.\n");
    return novoNo;
  }
  novoNo->info = info;
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  return novoNo;
}

struct NO *inserir(struct NO *raiz, int info){
  if(raiz == NULL){
    raiz = criarno(info);
  }else{
    if(info <= raiz->info){
      raiz->esq = inserir(raiz->esq, info);
    }else{
      raiz->dir = inserir(raiz->dir, info);
    }
  }
  return raiz;
}

struct NO *encontrarfilho(struct NO *raiz){
  struct NO *filho = raiz;
  while (filho->esq != NULL){
    filho = filho->esq;
  }
  return filho;
}

struct NO *apagar(struct NO *raiz, int valor){
  if(raiz == NULL){
    return raiz;
  }
  if(valor < raiz->info){
    raiz->esq = apagar(raiz->esq, valor);
    
  }else if(valor > raiz->info){
    
    raiz->dir = apagar(raiz->dir, valor);
  }else{
    if(raiz->esq == NULL){
      struct NO *temporario = raiz->dir;
      free(raiz);
      return temporario;
    }
    struct NO *temporario = encontrarfilho(raiz->dir);
    raiz->info = temporario->info;
    raiz->dir = apagar(raiz->dir, temporario->info);
  }
  return raiz;
}

struct NO* buscarx(struct NO* raiz, int info ){
  if(raiz == NULL || raiz-> info == info){
return raiz;
  }
  if(info < raiz->info){
    return buscarx(raiz->esq, info);
  }else{
    return buscarx(raiz->dir, info);
  }
}



int main(void) {

  struct NO *raiz = NULL;

  raiz = inserir(raiz, 1);
  raiz = inserir(raiz, 2);
  raiz = inserir(raiz, 3);
  raiz = inserir(raiz, 4);
  raiz = inserir(raiz, 5);
  raiz = inserir(raiz, 6);
  
  return 0;
}
