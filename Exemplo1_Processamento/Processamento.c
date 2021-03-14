#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUMERO_ARQUIVOS 10000000

int main()
{
  clock_t start = clock();

  for(int i = 0; i < NUMERO_ARQUIVOS; i++){
    int processamento = sqrt(exp(i));
  }

  clock_t end = clock();
  int tempo = ((int) (end - start));
  printf("Tempo de execução: %d", tempo);
  return 0;
}