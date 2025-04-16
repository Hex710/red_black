#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

struct no *cria_No(int chave)
{
    struct no *n;
    if (!(n = malloc(sizeof(struct no))))
        return NULL;

    n->chave = chave;
    n->dir = n->esq = n->pai = NULL;
    return n;
}

struct no *binary(struct no *n, struct no *pai, int chave)
{
    if (n == NULL)
    {
        n = cria_No(chave);
        n->pai = pai;

        if (n->chave > pai->chave)
            pai->dir = n;
        else if (n->chave < pai->chave)
            pai->esq = n;

        return n;
    }

    if (n->chave > chave)
        return binary(n->esq, n, chave);

    if (n->chave < chave)
        return binary(n->dir, n, chave);

    return n;
}

void destroi_Arvore(struct no *n)
{
    if (n == NULL)
        return;

    destroi_Arvore(n->esq);
    destroi_Arvore(n->dir);
    free(n);
    return;
}

void printTree(struct no *n)
{
    if (n == NULL)
        return;

    printTree(n->esq);
    printf("%d ", n->chave);
    printTree(n->dir);
}

struct no *min_Tree(struct no *n)
{
    while (n->esq != NULL)
        n = n->esq;
    return n;
}

struct no *max_Tree(struct no *n)
{
    while (n->dir != NULL)
        n = n->dir;
    return n;
}

struct no *rot_Esq(struct no *raiz, struct no *n)
{
    if (!n)
        return NULL;

    struct no *aux = n->dir;
    n->dir = aux->esq;

    if (aux->esq != NULL)
        aux->esq->pai = n;
    aux->pai = n->pai;
    if (n->pai == NULL)
        raiz = aux;
    else if (n == n->pai->esq)
        n->pai->esq = aux;
    else
        n->pai->dir = aux;
    aux->esq = n;
    n->pai = aux;
    return raiz;
}

struct no *rot_Dir(struct no *raiz, struct no *n)
{
    if (!n)
        return NULL;

    struct no *aux = n->esq;
    n->esq = aux->dir;

    if (aux->dir != NULL)
        aux->dir->pai = n;
    aux->pai = n->pai;
    if (n->pai == NULL)
        raiz = aux;
    else if (n == n->pai->esq)
        n->pai->esq = aux;
    else
        n->pai->dir = aux;
    aux->dir = n;
    n->pai = aux;
    return raiz;
}

struct no *busca(struct no *n, int chave)
{
    if (!n)
        return NULL;
    if (chave == n->chave)
        return n;
    if (chave < n->chave)
        return busca(n->esq, chave);
    return busca(n->dir, chave);
}

struct no *transplante(struct no *raiz, struct no *n, struct no *filho)
{
    if (n->pai == NULL)
        raiz = filho;
    else if (n == n->pai->esq)
        n->pai->esq = filho;
    else
        n->pai->dir = filho;
    if (filho != NULL)
        filho->pai = n->pai;
    return raiz;
}

struct no *tree_Remove(struct no *raiz, struct no *n)
{
    struct no *ant;
    if (n->esq == NULL)
        raiz = transplante(raiz, n, n->dir);
    else if (n->dir == NULL)
        raiz = transplante(raiz, n, n->esq);
    else
    {
        ant = min_Tree(n->dir);
        if (ant->pai != n)
        {
            raiz = transplante(raiz, ant, ant->dir);
            ant->dir = n->dir;
            ant->dir->pai = ant;
        }
        raiz = transplante(raiz, n, ant);
        ant->esq = n->esq;
        ant->esq->pai = ant;
    }
    return raiz;
}
