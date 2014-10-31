//
// problema_8-30.c: Problema 8.30 Brassard
//

#include <cstdio>
#include <cstdlib>
#include <vector>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int distance(const char* source, const char* target)
{
	int cost, i, j;
	int above, left, diagonal, value;

	int n = (int)strlen(source);
	int m = (int)strlen(target);

	if(n == 0)
		return m;

	if(m == 0)
		return n;

	std::vector< std::vector<int> >  matrix(n+1);

	for(i = 0; i < n+1; ++i)
		matrix[i].resize(m+1, 0);

	// Primera fila y primera columna
	for(i = 0; i <= n; i++)
		matrix[i][0] = i;

	for(j = 0; j <= m; j++)
		matrix[0][j] = j;

	// recorre todo los caracteres de la cadena original.
	for(i = 1; i < n+1; ++i)
	{
		char si = source[i-1];

		// recorre todo los caracteres de la cadena destino.
		for(int j = 1; j < m+1; ++j)
		{
			char tj = target[j-1];

			// Transformar un caracter cuesta 1
			if (si == tj)
				cost = 0;
			else
				cost = 1;

			// Calcula los elementos de la matrix correspondiente a i,j
			above    = matrix[i-1][j];
			left     = matrix[i][j-1];
			diagonal = matrix[i-1][j-1];
			value    = MIN(above + 1, MIN(left + 1, diagonal + cost));

			if(i > 2 && j > 2)
			{
				int trans = matrix[i-2][j-2] + 1;

				if(source[i-2] != tj)
					trans++;

				if(si != target[j-2])
					trans++;

				if(value > trans)
					value = trans;
			}

			matrix[i][j] = value;
		}
	}

	return matrix[n][m];
}

int main(int argc, char* argv[])
{
	char source[] = "abcde";
	char target[] = "abce";

	int ret = distance(source, target);

	printf("%d", ret);

	getchar();
	return 0;
}
