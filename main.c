#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int aleat(int min, int max)
{
    return ((rand() % (max - min + 1)) + min);
}

int main()
{
    struct no *aux, *n = cria_No(0);
    int i;

    do
    {
        printf("Insira uma chave entre 0 e 100\n");
        scanf("%d", &i);
        printf("\n");
        binary(n, NULL, i);
    } while ((i > 0) && (i < 100));

    for (int j = 0; j < 10; j++)
    {
        aux = busca(n, aleat(1, 100));
        if (aux != NULL)
        {
            int k = aleat(0, 1);
            if (k == 0)
                n = rot_Dir(n, aux);
            else
                n = rot_Esq(n, aux);
        }
    }

    n = tree_Remove(n, n);

    aux = n;

    while ((aux->esq) && (aux->dir))
    {
        if (aux->esq)
            aux = aux->esq;
        else
            aux = aux->dir;
    }

    n = tree_Remove(n, aux);

    printTree(n);

    destroi_Arvore(n);
}