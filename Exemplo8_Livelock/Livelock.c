#include "stdlib.h"
#include "stdio.h"
#include "windows.h"

typedef unsigned(WINAPI *CAST_FUNCTION)(LPVOID);
typedef unsigned *CAST_LPDWORD;

HANDLE Mutex1;
HANDLE Mutex2;

DWORD WINAPI ExecucaoThread1(LPVOID params);
DWORD WINAPI ExecucaoThread2(LPVOID params);

//https://www.baeldung.com/java-deadlock-livelock

int main()
{

  Mutex1 = CreateMutex(NULL, FALSE, "Mutex1");
  Mutex2 = CreateMutex(NULL, FALSE, "Mutex2");

  DWORD id_thread;

  HANDLE Thread1 = (HANDLE)_beginthreadex(
      NULL,
      0,
      (CAST_FUNCTION)ExecucaoThread1,
      0,
      0,
      (CAST_LPDWORD)&id_thread);

  HANDLE Thread2 = (HANDLE)_beginthreadex(
      NULL,
      0,
      (CAST_FUNCTION)ExecucaoThread2,
      0,
      0,
      (CAST_LPDWORD)&id_thread);

  HANDLE Threads[2] = {Thread1, Thread2};

  printf("Executando...\n");
  WaitForMultipleObjects(2, Threads, TRUE, INFINITE);
  printf("Execução finalizada...\n");

  return 0;
}

DWORD WINAPI ExecucaoThread1(LPVOID params)
{
  while (1)
  {
    WaitForSingleObject(Mutex1, 1000);
    printf("T1: Mutex1 conquistado, tentando conquistar Mutex2\n");
    Sleep(1);

    int status = WaitForSingleObject(Mutex2, 0);
    if(status == WAIT_TIMEOUT){
      printf("T1: Mutex2 ocupado, liberando Mutex1\n");
      ReleaseMutex(Mutex1);
      continue;
    }else{
      printf("T1: Mutex2 conquistado\n");
    }

    printf("T1 executando operação...\n");
    break;
  }
  ReleaseMutex(Mutex1);
  ReleaseMutex(Mutex2);
}

DWORD WINAPI ExecucaoThread2(LPVOID params)
{
  while (1)
  {
    WaitForSingleObject(Mutex2, 1000);
    printf("T2: Mutex2 conquistado, tentando conquistar Mutex1\n");
    Sleep(1);

    int status = WaitForSingleObject(Mutex1, 0);
    if(status == WAIT_TIMEOUT){
      printf("T2: Mutex1 ocupado, liberando Mutex2\n");
      ReleaseMutex(Mutex2);
      continue;
    }else{
      printf("T2: Mutex1 conquistado\n");
    }

    printf("T2 executando operação...\n");
    break;
  }
  ReleaseMutex(Mutex2);
  ReleaseMutex(Mutex1);
}
