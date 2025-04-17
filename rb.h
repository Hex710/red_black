#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

struct rbno
{
    int color;
    int chave;        // guarda um valor inteiro dentro do noh
    struct rbno *esq; // aponta para o filho esquerdo
    struct rbno *dir; // aponta para o filho direito
    struct rbno *pai; // aponta para o noh pai
};

// retorna o nivel na arvore do noh dado
int level(struct rbno *n);

// aloca o espaco para o noh e insere o valor dado como sua chave, retorna o noh criado
struct rbno *cria_No(int chave);

// faz a busca e insercao na arvore, mantendo ela como uma arvore de busca binaria, retorna o noh encontrado ou inserido, "pai" recebe NULL quando chamado pela primeira vez
struct rbno *binary(struct rbno *n, struct rbno *pai, int chave);

// destroi cada noh utilizando a pos-ordem
void destroi_Arvore(struct rbno *raiz);

// imprime todos os nohs utilizando a pre-ordem
void printTree(struct rbno *raiz);

// acha o noh com a chave de menor valor em uma arvore
struct rbno *min_Tree(struct rbno *n);

// acha o noh com a chave de maior valor em uma arvore
struct rbno *max_Tree(struct rbno *n);

// rotaciona o noh recebido para a esquerda, retorna a raiz da arvore
struct rbno *rot_Esq(struct rbno *raiz, struct rbno *n);

// rotaciona o noh recebido para a direita, retorna a raiz da arvore
struct rbno *rot_Dir(struct rbno *raiz, struct rbno *n);

// busca binaria por um no com chave correspondente, retorna um pointer para o noh ou para NULL se o noh nao existir
struct rbno *busca(struct rbno *raiz, int chave);

// retira o noh indicado em n e coloca seu filho no lugar, retorna um pointer para a raiz
struct rbno *transplante(struct rbno *raiz, struct rbno *n, struct rbno *filho);

// remove qualquer noh, seja ele folha, raiz ou intermediario
struct rbno *tree_Remove(struct rbno *raiz, struct rbno *n);

// inverte a cor do noh n
void recolorir(struct rbno *n);

// cria e insere um no com a chave dada em uma arvore rubro-negra, jah balanceando a arvore apos a insercao
struct rbno *rb_Insert(struct rbno *raiz, int chave);

// retira e deleta o noh n da arvore rubro-negra, balanceando a arvore apos a remocao
struct rbno *rb_Delete_Fix(struct rbno *raiz, struct rbno *n);