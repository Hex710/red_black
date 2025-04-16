#include <stdio.h>
#include <stdlib.h>

// tad que representa um noh em uma arvore
struct no
{
    int chave;      // guarda um valor inteiro dentro do noh
    struct no *esq; // aponta para o filho esquerdo
    struct no *dir; // aponta para o filho direito
    struct no *pai; // aponta para o noh pai
};

// aloca o espaco para o noh e insere o valor dado como sua chave, retorna o noh criado
struct no *cria_No(int chave);

// faz a busca e insercao na arvore, mantendo ela como uma arvore de busca binaria, retorna o noh encontrado ou inserido
struct no *binary(struct no *n, struct no *pai, int chave);

// destroi cada noh utilizando a pos-ordem
void destroi_Arvore(struct no *n);

// imprime todos os nohs utilizando a pre-ordem
void printTree(struct no *n);

// acha o noh com a chave de menor valor em uma arvore
struct no *min_Tree(struct no *n);

// acha o noh com a chave de maior valor em uma arvore
struct no *max_Tree(struct no *n);

// rotaciona o noh recebido para a esquerda, retorna a raiz da arvore
struct no *rot_Esq(struct no *raiz, struct no *n);

// rotaciona o noh recebido para a direita, retorna a raiz da arvore
struct no *rot_Dir(struct no *raiz, struct no *n);

// busca binaria por um no com chave correspondente, retorna um pointer para o noh ou para NULL se o noh nao existir
struct no *busca(struct no *n, int chave);

// retira o noh indicado em n e coloca seu filho no lugar, retorna um pointer para a raiz
struct no *transplante(struct no *raiz, struct no *n, struct no *filho);

// remove qualquer noh, seja ele folha, raiz ou intermediario
struct no *tree_Remove(struct no *raiz, struct no *n);