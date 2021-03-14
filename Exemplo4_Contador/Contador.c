#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CONTAGEM_ESPERADA 10000000

unsigned int contador = 0;

int main()
{
  clock_t start = clock();

  for(int i = 0; i < CONTAGEM_ESPERADA; i++){
    contador++;
  }

  clock_t end = clock();
  int tempo = ((int) (end - start));
  printf("Valor final do contador: %d\n", contador);
  printf("Diferença em relação ao esperado: %d\n", CONTAGEM_ESPERADA - contador);
  printf("Tempo de execução: %d", tempo);
  return 0;
}