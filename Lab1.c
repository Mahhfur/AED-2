#include <stdio.h>
#include <stdlib.h> 


int busca (int vet[], int tamanho, int n){
	int i, j=0, cont=0;
	for (i=1; i<tamanho; i++){
		if (vet[j]+vet[i]>=n) return i;
	}
	return tamanho-1;
}

int buscaBinaria(int arr[], int tamanho, int n) {
	int esquerda = 0;
	int direita = tamanho - 1;
	int indiceEncontrado = - 1;

	while (esquerda <= direita) {
			int meio = (esquerda + direita) / 2;

		if (arr[meio] == n) {
			return meio; // Encontrou o número exato
		} else if (arr[meio] < n) {
				esquerda = meio + 1;
				} else {
					indiceEncontrado = meio;
						direita = meio - 1;
				}
	}
	return indiceEncontrado;
}

void countingSort(int arr[], int n) {
	int min = arr[0];
	int max = arr[0];

	for (int i = 1; i < n; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
		if (arr[i] > max) {
			max = arr[i];
		}
	}

	int range = max - min + 1;
	int count[range];
	int output[n];

	for (int i = 0; i < range; i++) {
		count[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		count[arr[i] - min]++;
	}

	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}

	for (int i = n - 1; i >= 0; i--) {
		output[count[arr[i] - min] - 1] = arr[i];
		count[arr[i] - min]--;
	}

	for (int i = 0; i < n; i++) {
		arr[i] = output[i];
	}
}

int verificadordesoma(int vet[], int ind, int n) {
	int i = 0, j = ind, cont = 0, par = 0;

		while(i < j){
				cont = vet[i] + vet[j];
				if(cont == n){
						par++;
						i++;
						j--;
				} else if(cont < n) {
								i++;
						} else{
										j--;
								}
		}
	return par;
}

int main(void) {
		int s, n, i, ind;
	scanf("%d %d", &s, &n);

	int *vet = (int *)malloc(s * sizeof(int));
	for (i = 0; i < s; i++) scanf("%d", &vet[i]);

	countingSort(vet, s);    

	if (vet[0] < 0){
		ind=busca(vet, s, n);     
		printf("%d", verificadordesoma(vet, ind, n));
	}

	if (vet[0] >= 0){
		ind = buscaBinaria(vet, s, n);
		printf("%d", verificadordesoma(vet, ind, n));         
	}

	free(vet);
	return 0; 
}
