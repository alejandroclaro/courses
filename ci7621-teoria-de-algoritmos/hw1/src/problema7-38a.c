//
// problema 7.38 : suponiendo n potencia de 2
//

#include <stdio.h>

#define N 8

void planificar(int T[N + 1][N + 1], int day, int p0, int pf)
{
  int m = (pf - p0 + 1)/2;

  for(int d = 0; d < m; ++d)
  {
    for(int i = 0; i < m; ++i)
    {
      int player1 = p0 + i;
      int player2 = p0 + m + (d + i)%m;

      T[day + d][player1] = player2;
      T[day + d][player2] = player1;
    }
  }

  if(m > 1)
  {
    planificar(T, day + m, p0, p0 + m - 1);
    planificar(T, day + m, p0 + m, pf);
  }
}

int main(int argc, char* argv[])
{
  int T[N + 1][N + 1];

  planificar(T, 1, 1, N);

  for(int i = 1; i <= N - 1; i++)
  {
    for(int j = 1; j <= N; j++)
    {
      printf("%d  ", T[i][j]);
    }

    printf("\n");
  }

  getchar();
  return 0;
}

