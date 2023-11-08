#include <stdio.h>

typedef struct {
	int voto1;
	int voto2;
	int voto3;
} Voter;

typedef struct {
	int num;
	int votes;
} Candidate;

int main() {
	int numVoters, numCandidates;
	float totalVotes = 0;

	scanf("%d %d", &numVoters, &numCandidates);

	Voter voters[numVoters];
	Candidate candidates[numCandidates];

	// Inicializar candidatos
	for (int i = 0; i < numCandidates; i++) {
		candidates[i].num = i + 1;
		candidates[i].votes = 0;
	}

	// Processar votos
	for (int i = 0; i < numVoters; i++) {
		int vote1, vote2, vote3;
		scanf("%d %d %d", &vote1, &vote2, &vote3);

		if (vote1 >= 1 && vote1 <= numCandidates) {
			voters[i].voto1 = vote1;
			candidates[voters[i].voto1 - 1].votes++;
			totalVotes++;
		}
		if (vote2 >= 1 && vote2 <= numCandidates) {
			voters[i].voto2 = vote2;
		}
		if (vote3 >= 1 && vote3 <= numCandidates) {
			voters[i].voto3 = vote3;
		}
	}

	// Encontrar os dois candidatos mais votados
	int firstMostVoted = -1;
	int secondMostVoted = -1;

	for (int i = 0; i < numCandidates; i++) {
		if (firstMostVoted == -1 ||
				candidates[i].votes > candidates[firstMostVoted].votes) {
			secondMostVoted = firstMostVoted;
			firstMostVoted = i;
		} else if (secondMostVoted == -1 ||
							 candidates[i].votes > candidates[secondMostVoted].votes) {
			secondMostVoted = i;
		}
	}

	// Calcular porcentagem do mais votado
	float percentage = (candidates[firstMostVoted].votes * 100) / totalVotes;

	// Verificar se há um vencedor no primeiro turno
	if (percentage > 50) {
		printf("%d %.2f", candidates[firstMostVoted].num, percentage);
	} else {
		// Se não houver vencedor, calcular votos no segundo turno
		if (totalVotes > 0) {
			printf("%d %.2f\n", candidates[firstMostVoted].num, percentage);
			totalVotes = candidates[firstMostVoted].votes +
									 candidates[secondMostVoted].votes;

			// Contabilizar votos no segundo turno
			for (int i = 0; i < numVoters; i++) {
				if (voters[i].voto1 != candidates[firstMostVoted].num &&
						voters[i].voto1 != candidates[secondMostVoted].num) {

					if (voters[i].voto2 == candidates[firstMostVoted].num) {
						candidates[firstMostVoted].votes++;
						totalVotes++;
					} else if (voters[i].voto2 == candidates[secondMostVoted].num) {
						candidates[secondMostVoted].votes++;
						totalVotes++;
					} else {
						if (voters[i].voto3 == candidates[firstMostVoted].num) {
							candidates[firstMostVoted].votes++;
							totalVotes++;
						} else if (voters[i].voto3 == candidates[secondMostVoted].num) {
							candidates[secondMostVoted].votes++;
							totalVotes++;
						}
					}
				}
			}

			// Verificar resultado do segundo turno
			if (candidates[firstMostVoted].votes ==
					candidates[secondMostVoted].votes) {
				if (candidates[firstMostVoted].num <
						candidates[secondMostVoted].num) {
					percentage =
							(candidates[firstMostVoted].votes * 100) / totalVotes;
					printf("%d %.2f", candidates[firstMostVoted].num, percentage);

				} else {
					percentage =
							(candidates[secondMostVoted].votes * 100) / totalVotes;
					printf("%d %.2f", candidates[secondMostVoted].num, percentage);
				}
			} else {
				if (candidates[firstMostVoted].votes >
						candidates[secondMostVoted].votes) {
					percentage = (candidates[firstMostVoted].votes * 100) / totalVotes;
					printf("%d %.2f", candidates[firstMostVoted].num, percentage);
				} else {
					percentage = (candidates[secondMostVoted].votes * 100) / totalVotes;
					printf("%d %.2f", candidates[secondMostVoted].num, percentage);
				}
			}
		} else {
			// Se não houver votos válidos, imprimir 0
			printf("0\n");
		}
	}

	return 0;
}