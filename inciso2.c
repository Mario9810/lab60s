// mario sarmientos 17055
//referencia: https://docs.oracle.com/cd/E19120-01/open.solaris/816-5137/sync-12/index.html
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#define nthreads 4
#define tcost 25
pthread_mutex_t mut;
int recursos = 1000;

int decrease_count(int count){
	if(recursos < count){
		return -1;
	}
	else{
		pthread_mutex_lock(&mut);
		printf("se consumiran %d recursos\n",count);
		recursos -= count;
		pthread_mutex_unlock(&mut);
		return 0;
		}
}

int increase_count(int count){
	pthread_mutex_lock(&mut);
	printf("se devolverán %d recursos\n", count);
	recursos += count;
	pthread_mutex_unlock(&mut);
	return 0;
}

void* monitor(){
	pid_t pid;
	pid = syscall(SYS_gettid);
	printf("hilo: %d usa %d recursos", pid,tcost);
	while(decrease_count(tcost)!=0){
		NULL;
	}
	decrease_count(tcost);
	sleep(2);
	increase_count(tcost);
	printf("hilo: %d devuelve %d recursos",pid,tcost);
	
}

int main() {
	FILE *filepointer;
	filepointer = fopen("inciso2.txt", "w");

	if (filepointer == NULL)
	{
		printf("Error!");
		exit(1);
	}

	fprintf(filepointer, "Iniciando programa\n");
	int j;
	pthread_t *hilos;


	fprintf(filepointer, "Creando %d threads\n", nthreads);
	for (j = 0; j < nthreads; j++) {
		pthread_create(&hilos[j], NULL, monitor, NULL);
	}

	fprintf(filepointer, "Esperando threads \n");
	for (j = 0; j < nthreads; j++) {
		pthread_join(hilos[j], NULL);
	}
	fclose(filepointer);
	return 0;
}
