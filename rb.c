#include <stdio.h>
#include <stdlib.h>

#include "rb.h"

int level(struct rbno *n)
{
    if (!n)
        return 0;

    int h = 0;

    while (n->pai != NULL)
    {
        n = n->pai;
        h++;
    }
    return h;
}

struct rbno *cria_No(int chave)
{
    struct rbno *n;
    if (!(n = malloc(sizeof(struct rbno))))
        return NULL;

    n->chave = chave;
    n->dir = n->esq = n->pai = NULL;
    n->color = RED;
    return n;
}

struct rbno *binary(struct rbno *n, struct rbno *pai, int chave)
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

void destroi_Arvore(struct rbno *raiz)
{
    if (raiz == NULL)
        return;

    destroi_Arvore(raiz->esq);
    destroi_Arvore(raiz->dir);
    free(raiz);
    return;
}

void printTree(struct rbno *raiz)
{
    if (raiz == NULL)
        return;

    printTree(raiz->esq);
    printf("%d,%d,%d\n", raiz->chave, level(raiz), raiz->color);
    printTree(raiz->dir);
}

struct rbno *min_Tree(struct rbno *n)
{
    while (n->esq != NULL)
        n = n->esq;
    return n;
}

struct rbno *max_Tree(struct rbno *n)
{
    while (n->dir != NULL)
        n = n->dir;
    return n;
}

struct rbno *rot_Esq(struct rbno *raiz, struct rbno *n)
{
    if (!n)
        return NULL;

    struct rbno *aux = n->dir;
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

struct rbno *rot_Dir(struct rbno *raiz, struct rbno *n)
{
    if (!n)
        return NULL;

    struct rbno *aux = n->esq;
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

struct rbno *busca(struct rbno *n, int chave)
{
    if (!n)
        return NULL;
    if (chave == n->chave)
        return n;
    if (chave < n->chave)
        return busca(n->esq, chave);
    return busca(n->dir, chave);
}

struct rbno *transplante(struct rbno *raiz, struct rbno *n, struct rbno *filho)
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

struct rbno *tree_Remove(struct rbno *raiz, struct rbno *n)
{
    struct rbno *ant;
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

void recolorir(struct rbno *n)
{
    if (!n)
        return;
    if (n->color == RED)
        n->color = BLACK;
    else
        n->color == RED;
}

struct rbno *rb_Insert(struct rbno *raiz, int chave)
{
    struct rbno *tio, *n = binary(raiz, NULL, chave);
    while ((n != raiz) && (n->color == RED))
    {
        if (n->pai == n->pai->pai->esq)
        {
            tio = n->pai->pai->dir;
            if (tio->color == RED)
            {
                recolorir(tio);
                recolorir(n->pai);
                recolorir(n->pai->pai);
                n = n->pai->pai;
            }
            else
            {
                if (n == n->pai->dir)
                {
                    raiz = rot_Esq(raiz, n->pai);
                    if (n == n->pai->dir)
                    {
                        raiz = rot_Esq(raiz, n->pai);
                        recolorir(n);
                        recolorir(n->esq);
                        n = n->esq;
                    }
                    else
                    {
                        raiz = rot_Dir(raiz, n->pai);
                        recolorir(n);
                        recolorir(n->dir);
                        n = n->dir;
                    }
                }
                if (n->pai == n->pai->pai->dir)
                {
                    raiz = rot_Esq(raiz, n->pai->pai);
                    recolorir(n->pai);
                    recolorir(n->pai->esq);
                    n = n->pai->esq;
                }
                else
                {
                    raiz = rot_Dir(raiz, n->pai->pai);
                    recolorir(n->pai);
                    recolorir(n->pai->dir);
                    n = n->pai->dir;
                }
            }
        }
        else
        {
            tio = n->pai->pai->esq;
            if (tio->color == RED)
            {
                recolorir(tio);
                recolorir(n->pai);
                recolorir(n->pai->pai);
                n = n->pai->pai;
            }
            else
            {
                if (n == n->pai->esq)
                {
                    raiz = rot_Dir(raiz, n->pai);
                    if (n == n->pai->esq)
                    {
                        raiz = rot_Dir(raiz, n->pai);
                        recolorir(n);
                        recolorir(n->dir);
                        n = n->dir;
                    }
                    else
                    {
                        raiz = rot_Esq(raiz, n->pai);
                        recolorir(n);
                        recolorir(n->esq);
                        n = n->esq;
                    }
                }
                if (n->pai == n->pai->pai->esq)
                {
                    raiz = rot_Dir(raiz, n->pai->pai);
                    recolorir(n->pai);
                    recolorir(n->pai->dir);
                }
                else
                {
                    raiz = rot_Esq(raiz, n->pai->pai);
                    recolorir(n->pai);
                    recolorir(n->pai->esq);
                }
            }
        }
    }
    raiz->color = BLACK;
}

struct rbno *rb_Delete_Fix(struct rbno *raiz, struct rbno *n)
{
    if (!raiz)
        return NULL;
    struct rbno *irmao;
    while ((n != raiz) && (n->color == BLACK))
    {
        if (n == n->pai->esq)
        {
            irmao = n->pai->dir; // e se o irmao for nulo?
            if (irmao != NULL)
            {
                if (irmao->color == RED)
                {
                    raiz = rot_Esq(raiz, n->pai);
                    recolorir(irmao);
                    recolorir(irmao->esq); // checar se o n e o irmao mudam
                }
                if (((irmao->esq == NULL) || (irmao->esq->color == BLACK)) && ((irmao->dir == NULL) || (irmao->dir->color == BLACK)))
                {
                    raiz = tree_Remove(raiz, n);
                    recolorir(irmao);
                    recolorir(irmao->pai);
                }
                else
                {
                    if ((irmao->dir == NULL) || (irmao->dir->color == BLACK))
                    {
                        raiz = rot_Dir(raiz, irmao);
                        recolorir(irmao);
                        recolorir(irmao->pai);
                    }
                    raiz = tree_Remove(raiz, n);
                    raiz = rot_Esq(raiz, n->pai);
                    recolorir(irmao->dir);
                }
            }
        }
        else if (n == n->pai->dir)
        {
            irmao = n->pai->esq;
            if (irmao != NULL)
            {
                if (irmao->color == RED)
                {
                    raiz = rot_Dir(raiz, n->pai);
                    recolorir(irmao);
                    recolorir(n->pai); // checar se o n muda
                }
                if (((irmao->esq == NULL) || (irmao->esq->color == BLACK)) && ((irmao->dir == NULL) || (irmao->dir->color == BLACK)))
                {
                    raiz = tree_Remove(raiz, n);
                    recolorir(irmao);
                    recolorir(irmao->pai);
                }
                else
                {
                    if ((irmao->esq == NULL) || (irmao->esq->color == BLACK))
                    {
                        raiz = rot_Esq(raiz, irmao);
                        recolorir(irmao);
                        recolorir(irmao->pai);
                    }
                    raiz = tree_Remove(raiz, n);
                    raiz = rot_Dir(raiz, n->pai);
                    recolorir(irmao->dir);
                }
            }
        }
    }
    n->color == BLACK;
}