#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct linha {
		char palavra[4];
		char letra;
		struct linha* prox;
};

typedef struct linha traducao;

traducao* vetorDePonteiros[67];

int stringnum(char* str) {
		int length = strlen(str);
		int result = 0;

		for (int i = 0; i < length; i++) {
				char c = str[i];
				if (isalpha(c)) {
						int value = toupper(c) - 'A' + 1;
						result = result * 26 + value;
				} else {
						// Ignora caracteres inválidos
				}
		}
		return result;
}

void hash(int num, char* str, char l) {
		int r;
		r = num % 67;

		if (vetorDePonteiros[r] == NULL) {
				vetorDePonteiros[r] = (traducao*)malloc(sizeof(traducao));
				strcpy(vetorDePonteiros[r]->palavra, str);
				vetorDePonteiros[r]->letra = l;
				vetorDePonteiros[r]->prox = NULL;
		} else {
				traducao* temp = vetorDePonteiros[r];
				while (temp->prox != NULL) {
						temp = temp->prox;
				}
				temp->prox = (traducao*)malloc(sizeof(traducao));
				strcpy(temp->prox->palavra, str);
				temp->prox->letra = l;
				temp->prox->prox = NULL;
		}
}

int main(void) {
		int N, M, i, j, k, a;
		char codon[4];
		char RNA[10001];
		char cod[4];
		char amcod;

		// Inicializar vetorDePonteiros como NULL
		for (i = 0; i < 67; i++) {
				vetorDePonteiros[i] = NULL;
		}

		scanf("%d", &N);
		for (i = 0; i < N; i++) {
				scanf("%s", codon);
				scanf(" %c", &amcod);
				int num = stringnum(codon);
				hash(num, codon, amcod);
		}

		scanf("%d", &M);
		for (i = 0; i < M; i++) {
				scanf("%s", RNA);
				j = 0;
				while (RNA[j] != '\0') {
						j = j + 3;
						a = 0;
						for (k = j - 3; k < j; k++) {
								cod[a] = RNA[k];
								a++;
						}
						cod[a] = '\0'; // Adicione o caractere nulo
						int pcod = stringnum(cod);
						int ncod = pcod % 67;
						traducao* temp = vetorDePonteiros[ncod];
						while (temp != NULL && strcmp(temp->palavra, cod) != 0) {
								temp = temp->prox;
						}
						if (temp != NULL) {
								printf("%c", temp->letra);
						} else {
								printf("*");
						}
				}
				printf("\n");
		}

		return 0;
}
