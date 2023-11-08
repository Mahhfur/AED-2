#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPRIMENTO_NOME 15

// Estrutura da lista de projetos
typedef struct Projeto {
				int numero;
				struct Projeto* proximo;
				struct Projeto* anterior;
} Projeto;

// Estrutura do nó
typedef struct No {
				int altura;
				char nome[MAX_COMPRIMENTO_NOME + 1];
				Projeto* projetos;
				struct No* esquerda;
				struct No* direita;
} No;

// Cria um nó
No* criarNo(char* nome, int num) {
				No* novoNo = malloc(sizeof(No));
				strncpy(novoNo->nome, nome, MAX_COMPRIMENTO_NOME);
				novoNo->nome[MAX_COMPRIMENTO_NOME] = '\0';
				novoNo->esquerda = NULL;
				novoNo->direita = NULL;
				novoNo->altura = 1;
				novoNo->projetos = NULL;
				return novoNo;
}

// Calcula a altura do nó
int alturaNo(No* no) {
				if (no == NULL) {
								return 0;
				}
				return no->altura;
}

// Calcula o fator de balanceamento da árvore
int fatorBalanceamento(No* no) {
				if (no == NULL) {
								return 0;
				}
				return alturaNo(no->esquerda) - alturaNo(no->direita);
}

// Atualiza a altura da árvore após o balanceamento
void atualizarAltura(No* no) {
				if (no != NULL) {
								int alturaEsquerda = alturaNo(no->esquerda);
								int alturaDireita = alturaNo(no->direita);

								if (alturaEsquerda > alturaDireita) {
												no->altura = alturaEsquerda + 1;
								} else {
												no->altura = alturaDireita + 1;
								}
				}
}

// Rotações da árvore
No* rotacaoDireita(No* y) {
				No* x = y->esquerda;
				No* T2 = x->direita;

				x->direita = y;
				y->esquerda = T2;

				atualizarAltura(y);
				atualizarAltura(x);

				return x;
}

No* rotacaoEsquerda(No* x) {
				No* y = x->direita;
				No* T2 = y->esquerda;

				y->esquerda = x;
				x->direita = T2;

				atualizarAltura(x);
				atualizarAltura(y);

				return y;
}

No* rotacaoDireitaEsquerda(No* z) {
				z->direita = rotacaoDireita(z->direita);
				return rotacaoEsquerda(z);
}

No* rotacaoEsquerdaDireita(No* z) {
				z->esquerda = rotacaoEsquerda(z->esquerda);
				return rotacaoDireita(z);
}

// Insere na lista de projetos
void inserirProjeto(Projeto** lista, int num) {
				Projeto* novoProjeto = malloc(sizeof(Projeto));
				novoProjeto->numero = num;
				novoProjeto->proximo = NULL;

				if (*lista == NULL) {
								novoProjeto->anterior = NULL;
								*lista = novoProjeto;
				} else {
								Projeto* ultimo = *lista;
								while (ultimo->proximo != NULL) {
												ultimo = ultimo->proximo;
								}
								ultimo->proximo = novoProjeto;
								novoProjeto->anterior = ultimo;
				}
}

// Insere nó na árvore
No* inserirNo(No* raiz, char* nome, int numeroProjeto) {
				if (raiz == NULL) {
								No* novoNo = criarNo(nome, numeroProjeto);
								inserirProjeto(&(novoNo->projetos), numeroProjeto);
								return novoNo;
				}

				if (strcmp(nome, raiz->nome) < 0) {
								raiz->esquerda = inserirNo(raiz->esquerda, nome, numeroProjeto);
				} else if (strcmp(nome, raiz->nome) > 0) {
								raiz->direita = inserirNo(raiz->direita, nome, numeroProjeto);
				} else if (strcmp(nome, raiz->nome) == 0) {
								inserirProjeto(&(raiz->projetos), numeroProjeto);
								return raiz;
				}

				atualizarAltura(raiz);

				int fatorBalanc = fatorBalanceamento(raiz);

				if (fatorBalanc > 1 && strcmp(nome, raiz->esquerda->nome) < 0) {
								return rotacaoDireita(raiz);
				}

				if (fatorBalanc < -1 && strcmp(nome, raiz->direita->nome) > 0) {
								return rotacaoEsquerda(raiz);
				}

				if (fatorBalanc > 1 && strcmp(nome, raiz->esquerda->nome) > 0) {
								raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
								return rotacaoDireita(raiz);
				}

				if (fatorBalanc < -1 && strcmp(nome, raiz->direita->nome) < 0) {
								raiz->direita = rotacaoDireita(raiz->direita);
								return rotacaoEsquerda(raiz);
				}

				return raiz;
}

// Busca nó na árvore
No* buscarNo(No* raiz, char* nome) {
				if (raiz == NULL || strcmp(nome, raiz->nome) == 0) {
								return raiz;
				}

				if (strcmp(nome, raiz->nome) < 0) {
								return buscarNo(raiz->esquerda, nome);
				} else {
								return buscarNo(raiz->direita, nome);
				}
}

void imprimirProjetos(Projeto* projeto) {
				while (projeto != NULL) {
								printf(" %d", projeto->numero);
								projeto = projeto->proximo;
				}
				printf("\n");
}

int main(void) {
				int opcao, projeto;
				char nome[MAX_COMPRIMENTO_NOME + 1];

				scanf("%d", &opcao);

				No* raizArvore = NULL;

				do {
								scanf("%s", nome);
								if (opcao == 1) {
												scanf("%d", &projeto);
												if (buscarNo(raizArvore, nome) == NULL) {
																raizArvore = inserirNo(raizArvore, nome, projeto);
												} else {
																No* aux = buscarNo(raizArvore, nome);
																inserirProjeto(&(aux->projetos), projeto);
												}
								} else if (opcao == 2) {
												No* noEncontrado = buscarNo(raizArvore, nome);

												if (noEncontrado == NULL) {
																printf("0\n");
												} else {
																printf("%d", noEncontrado->altura);
																imprimirProjetos(noEncontrado->projetos);
												}
								}
								scanf("%d", &opcao);
				} while (opcao != 0);

				return 0;
}