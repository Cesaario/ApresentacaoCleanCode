#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>

typedef unsigned(WINAPI *CAST_FUNCTION)(LPVOID);
typedef unsigned *CAST_LPDWORD;

typedef struct parametros_thread
{
  int numeroArquivos;
  int index;
} parametros_thread;

#define NUMERO_THREADS 10
#define NUMERO_ARQUIVOS 10000000

DWORD WINAPI ProcessarArquivos(LPVOID parametros_thread);

int main()
{
  clock_t start = clock();

  parametros_thread parametros[NUMERO_THREADS];
  HANDLE threads[NUMERO_THREADS];
  DWORD id_thread;

  for (int i = 0; i < NUMERO_THREADS; i++)
  {
    parametros[i].index = i;
    parametros[i].numeroArquivos = NUMERO_ARQUIVOS/NUMERO_THREADS;

    threads[i] = (HANDLE)_beginthreadex(
        NULL,
        0,
        (CAST_FUNCTION)ProcessarArquivos,
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

  printf("Processamento finalizado!\n");

  DWORD codigo_saida_thread;
  for (int i = 0; i < NUMERO_THREADS; ++i)
  {
    CloseHandle(threads[i]);
  }

  clock_t end = clock();
  int tempo = ((int)(end - start));
  printf("Tempo de execução: %d", tempo);
  return 0;
}

DWORD WINAPI ProcessarArquivos(LPVOID params)
{
  parametros_thread *parametros = (parametros_thread *)params;

  for (int i = 0; i < parametros->numeroArquivos; i++)
  {
    int processamento = sqrt(exp(i));
  }
  return 0;
}