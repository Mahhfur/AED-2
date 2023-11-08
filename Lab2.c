#include <stdio.h>
#include <stdlib.h>

struct No {
		int preco;
		struct No* esq;
		struct No* dir;
		int num;
};

typedef struct No no;

no* insere(no** r, int valor, int x) {
		if (*r == NULL) {
				no* novo = malloc(sizeof(no));
				novo->preco = valor;
				novo->dir = novo->esq = NULL;
				novo->num = x;
				*r = novo;
				return *r;
		}

		if (valor > (*r)->preco) {
				(*r)->dir = insere(&(*r)->dir, valor, x);
		} else {
				(*r)->esq = insere(&(*r)->esq, valor, x);
		}
		return *r;
}

no* removerMaiorPrecoEImprimir(no* raiz) {
		if (raiz == NULL) {
								printf("0\n");
				return NULL;
		}

		if (raiz->dir != NULL) {
				raiz->dir = removerMaiorPrecoEImprimir(raiz->dir);
				return raiz;
		}

		printf("%d\n", raiz->num);

		no* temp = raiz->esq;
		free(raiz);
		return temp;
}

int main() {
		no* raiz = NULL;
		char op;
		int valor;
		int i = 0;

		for (int j = 0; j < 1000000; j++) {
				scanf(" %c", &op);
				if (op == 'c') {
						i++;
						scanf("%d", &valor);
						insere(&raiz, valor, i);
				}

				if (op == 'v') {
						raiz = removerMaiorPrecoEImprimir(raiz);
				}

				if (op == 'f') {
						// Liberar a memória dos nós individuais
						free(raiz);
						break;
				}
		}


		return 0;
}
