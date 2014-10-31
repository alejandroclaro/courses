//
// problema 7-40 del Brassard
// Alejandro Claro Mosqueda
//

#include <stdio.h>

#define N 20

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void remplazar(int T[N+1], int k, int i)
{
	int kp = MIN(k - i + 1, N - k);

	for(int j = 0; j < kp; ++j)
	{
		int swp      = T[i + j];
		T[i + j]     = T[k + 1 + j];
		T[k + 1 + j] = swp;
	}

	i = i + kp;

	if(k < i)
		k = k + kp;

	if(k < N)
		remplazar(T, k, i);
}

int main(int argc, char* argv[])
{
	int T[N+1];

	printf("{ ");
	for(int i = 1; i <= N; ++i)
	{
		T[i] = i;
		printf("%d, ", T[i]);
	}
	printf("}\n\n");

	remplazar(T, 15, 1);

	printf("{ ");
	for(int i = 1; i <= N; ++i)
	{
		printf("%d, ", T[i]);
	}
	printf("}\n\n");

	getchar();
	return 0;
}

