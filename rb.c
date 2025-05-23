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
    fprintf(stderr, "%d,%d,%d\n", raiz->chave, level(raiz), raiz->color);
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
    if ((!raiz) || (!n))
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
    if ((!raiz) || (!n))
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
    struct rbno *prox;
    int cor = n->color;

    if (n->esq == NULL)
        raiz = transplante(raiz, n, n->dir);
    else if (n->dir == NULL)
        raiz = transplante(raiz, n, n->esq);
    else
    {
        prox = min_Tree(n->dir);
        if (n->dir != prox)
        {
            raiz = transplante(raiz, prox, prox->dir);
            prox->dir = n->dir;
            prox->dir->pai = prox;
        }
        if ((cor == RED) && (prox->color == BLACK) && (prox->dir == NULL) && (prox->esq == NULL))
            n->esq->color = RED;
        else
            cor = prox->color;
        raiz = transplante(raiz, n, prox);
        prox->esq = n->esq;
        prox->esq->pai = prox;
    }
    free(n);
    if (cor == BLACK)
        raiz = rb_Delete_Fix(raiz, prox);
    return raiz;
}

struct rbno *rb_Insert_Fix(struct rbno *raiz, struct rbno *n)
{
    struct rbno *tio;
    while ((n != raiz) && ((n != NULL) && (n->pai->color == RED)))
    {
        if (n->pai != raiz)
        {
            if (n->pai == n->pai->pai->esq)
            {
                tio = n->pai->pai->dir;
                if ((tio != NULL) && (tio->color == RED))
                {
                    tio->color = BLACK;
                    n->pai->color = BLACK;
                    n->pai->pai->color = RED;
                    n = n->pai->pai;
                }
                else
                {
                    if (n == n->pai->dir)
                    {
                        n = n->pai;
                        raiz = rot_Esq(raiz, n);
                    }
                    n->pai->color = BLACK;
                    n->pai->pai->color = RED;
                    n = n->pai->pai;
                    raiz = rot_Dir(raiz, n);
                }
            }
            else
            {
                tio = n->pai->pai->esq;
                if ((tio != NULL) && (tio->color = RED))
                {
                    tio->color = BLACK;
                    n->pai->color = BLACK;
                    n->pai->pai->color = RED;
                    n = n->pai->pai;
                }
                else
                {
                    if (n == n->pai->esq)
                    {
                        n = n->pai;
                        raiz = rot_Dir(raiz, n);
                    }
                    n->pai->color = BLACK;
                    n->pai->pai->color = RED;
                    n = n->pai->pai;
                    raiz = rot_Esq(raiz, n);
                }
            }
        }
        else
            n = n->pai;
    }
    raiz->color = BLACK;
    return raiz;
}

struct rbno *rb_Insert(struct rbno *raiz, struct rbno *n)
{
    if ((!raiz) || (!n))
        return n;
    struct rbno *aux, *pai = NULL;
    aux = raiz;
    while (aux != NULL)
    {
        pai = aux;
        if (n->chave > aux->chave)
            aux = aux->dir;
        else
            aux = aux->esq;
    }
    n->pai = pai;
    if (n->chave > pai->chave)
        pai->dir = n;
    else
        pai->esq = n;
    raiz = rb_Insert_Fix(raiz, n);
    return raiz;
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
            irmao = n->pai->dir;
            if ((irmao != NULL) && (irmao->color == RED))
            {
                irmao->color = BLACK;
                irmao->pai->color = RED;
                raiz = rot_Esq(raiz, n->pai);
                irmao = n->pai->dir;
            }
            if ((irmao != NULL) && (((irmao->esq == NULL) || (irmao->esq->color == BLACK)) && ((irmao->dir == NULL) || (irmao->dir->color == BLACK))))
            {
                irmao->color = RED;
                n = irmao->pai;
                if (n != raiz)
                {
                    if (n == n->pai->dir)
                        irmao = n->pai->esq;
                    else
                        irmao = n->pai->dir;
                }
                else
                    irmao = NULL;
            }
            else
            {
                if ((irmao != NULL) && ((irmao->dir == NULL) || (irmao->dir->color == BLACK)))
                {
                    irmao->esq->color = RED;
                    irmao->color = BLACK;
                    raiz = rot_Dir(raiz, irmao);
                    irmao = n->pai->dir;
                }
                irmao->color = n->pai->color;
                n->pai->color = BLACK;
                irmao->dir->color = BLACK;
                raiz = rot_Esq(raiz, n->pai);
                n = raiz;
            }
        }
        else if (n == n->pai->dir)
        {
            irmao = n->pai->esq;
            if ((irmao != NULL) && (irmao->color == RED))
            {
                irmao->color = BLACK;
                n->pai->color = RED;
                raiz = rot_Dir(raiz, n->pai);
                irmao = n->pai->esq;
            }
            if ((irmao != NULL) && (((irmao->esq == NULL) || (irmao->esq->color == BLACK)) && ((irmao->dir == NULL) || (irmao->dir->color == BLACK))))
            {
                irmao->color = RED;
                n = n->pai;
                if (n != raiz)
                {
                    if (n == n->pai->dir)
                        irmao = n->pai->esq;
                    else
                        irmao = n->pai->dir;
                }
                else
                    irmao = NULL;
            }
            else
            {
                if ((irmao != NULL) && ((irmao->esq == NULL) || (irmao->esq->color == BLACK)))
                {
                    irmao->dir->color = BLACK;
                    irmao->color = RED;
                    raiz = rot_Esq(raiz, irmao);
                    irmao = n->pai->esq;
                }
                irmao->color = n->pai->color;
                n->pai->color = BLACK;
                irmao->esq->color = BLACK;
                raiz = rot_Dir(raiz, n->pai);
                n = raiz;
            }
        }
    }
    n->color = BLACK;
    return raiz;
}