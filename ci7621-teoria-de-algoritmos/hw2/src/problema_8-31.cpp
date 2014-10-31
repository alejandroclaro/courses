//
// problema_8-31.cpp : Problema 3.31 Brassard
//

#include <cstdio>
#include <cstdlib>

int ordenaciones(int n)
{
	int *pBuffer = (int*)malloc((n)*sizeof(int));
	int nRet, x, y, j, k;

	if(n < 2)
		return n;

	// Inicializa el arreglo.
	for( j = 0; j < n; ++j)
		pBuffer[j] = 0;

	// Construye la tabla por programacion dinamica.
	pBuffer[0] = 2;
	pBuffer[1] = 1;

	for(k = 3; k <= n; ++k)
	{
		x = 0;

		for(j = 0; j < k; ++j)
		{
			y          = pBuffer[j];
			pBuffer[j] = (k-j)*(pBuffer[j] + x);
			x          = y;
		}
	}

	// Suma las combinaciones. (solucion)
	nRet = 0;
	for(j = 0; j < n; ++j)
		nRet += pBuffer[j];

	free(pBuffer);
	return nRet;
}

int main(int argc, char* argv[])
{
	int ret = ordenaciones(3);

	printf("%d", ret);

	getchar();
	return 0;
}

