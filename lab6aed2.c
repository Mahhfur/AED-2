#include <stdio.h>
#include <stdlib.h>

struct elematriz {
		char sit;
		int passou; // 0=nao passou, 1=passou
};
typedef struct elematriz ele;

int conta(ele **mat, int i, int j, int W, int H);

int main(void) {
		int W, H;
		char m;
		int l, k;
		scanf("%d %d", &W, &H);


		ele **matriz = (ele **)malloc(H * sizeof(ele *));
		for (int i = 0; i < H; i++) {
				matriz[i] = (ele *)malloc(W * sizeof(ele));
		}

		for (int i = 0; i < H; i++) {
				for (int j = 0; j < W; j++) {
						scanf(" %c", &m);
						if (m == '@') {
								l = i;
								k = j;
						}
						matriz[i][j].sit = m;
						matriz[i][j].passou = 0;
				}
		}

		int total = conta(matriz, l, k, W, H);
		printf("%d\n", total);

		for (int i = 0; i < H; i++) {
				free(matriz[i]);
		}
		free(matriz);

		return 0;
}

int conta(ele **mat, int i, int j, int W, int H) {
		if (i < 0 || i >= H || j < 0 || j >= W || mat[i][j].passou==1 || mat[i][j].sit == '#') {
				return 0;
		}

		mat[i][j].passou = 1;
		int count = 1;

		count += conta(mat, i + 1, j, W, H);
		count += conta(mat, i - 1, j, W, H);
		count += conta(mat, i, j + 1, W, H);
		count += conta(mat, i, j - 1, W, H);

		return count;
}