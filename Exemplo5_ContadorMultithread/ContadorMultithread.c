#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

typedef unsigned(WINAPI *CAST_FUNCTION)(LPVOID);
typedef unsigned *CAST_LPDWORD;

typedef struct parametros_thread
{
  int contagemThread;
  int index;
} parametros_thread;

#define NUMERO_THREADS 2
#define CONTAGEM_ESPERADA 10000000

DWORD WINAPI Contar(LPVOID parametros_thread);

unsigned int contador = 0;

int main()
{
  clock_t start = clock();

  parametros_thread parametros[NUMERO_THREADS];
  HANDLE threads[NUMERO_THREADS];
  DWORD id_thread;

  for (int i = 0; i < NUMERO_THREADS; i++)
  {
    parametros[i].index = i;
    parametros[i].contagemThread = CONTAGEM_ESPERADA / NUMERO_THREADS;

    threads[i] = (HANDLE)_beginthreadex(
        NULL,
        0,
        (CAST_FUNCTION)Contar,
        (void *)(&parametros[i]),
        0,
        (CAST_LPDWORD)&id_thread);
  }

  DWORD status_espera = WaitForMultipleObjects(NUMERO_THREADS, threads, TRUE, INFINITE);
  if (status_espera != WAIT_OBJECT_0)
  {
    printf("Erro em WaitForMultipleObjects! Codigo = %d\n", GetLastError());
    return 0;
  }

  printf("Contagem finalizada!\n");

  DWORD codigo_saida_thread;
  for (int i = 0; i < NUMERO_THREADS; ++i)
  {
    CloseHandle(threads[i]);
  }

  clock_t end = clock();
  int tempo = ((int)(end - start));
  printf("Valor final do contador: %d\n", contador);
  printf("Diferença em relação ao esperado: %d\n", CONTAGEM_ESPERADA - contador);
  printf("Tempo de execução: %d", tempo);
  return 0;
}

DWORD WINAPI Contar(LPVOID params)
{
  parametros_thread *parametros = (parametros_thread *)params;

  for (int i = 0; i < parametros->contagemThread; i++)
  {
    contador++;
  }
  return 0;
}
