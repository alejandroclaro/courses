//
// problema 7.38 : caso en que n es par o impar
//

#include <stdio.h>

#define N 5

void planificar(int T[N + 2][N + 2])
{
  int nPlayers = N%2 != 0 ? N + 1 : N;

  int m = nPlayers/2;

  for(int d = 0; d < (nPlayers-1); d++)
  {
    for(int i = 0; i < m; i++)
    {
      int ip, jp;

      if(i == 0)
        ip = 0;
      else
        ip = 1 + (i + d-1)%(nPlayers-1);

      jp = 1 + (nPlayers-1 - i + d-1)%(nPlayers-1);

      T[d+1][ip + 1] = jp == N ? -1 : jp + 1;
      T[d+1][jp + 1] = ip == N ? -1 : ip + 1;
    }
  }
}

int main(int argc, char* argv[])
{
  int T[N + 2][N + 2];

  int nPlayers = N%2 != 0 ? N + 1 : N;

  planificar(T);

  for(int i = 1; i <= nPlayers - 1; i++)
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

