#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int aleat(int min, int max)
{
    return ((rand() % (max - min + 1)) + min);
}

int main()
{
    int command, chave;
    struct rbno *n, *raiz = NULL;
    do
    {
        command = getchar();
        fscanf(stdin, " %d", &chave);
        if (command == 105)
        {
            n = cria_No(chave);
            if (!raiz)
            {
                raiz = n;
                raiz->color = BLACK;
            }
            else
                raiz = rb_Insert(raiz, n);
            printTree(raiz);
            printf("\n");
        }
        else if (command == 114)
        {
            n = busca(raiz, chave);
            if (n)
                raiz = tree_Remove(raiz, n);
            printTree(raiz);
            printf("\n");
        }
    } while (command != EOF);
    printTree(raiz);
    destroi_Arvore(raiz);
}