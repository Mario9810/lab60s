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
		printf("se consumiran %d recursos",count);
		recursos -= count;
		pthread_mutex_unlock(&mut);
		return 0;
		}
}

int increase_count(int count){
	printf("se devolverán %d recursos", count);
	pthread_mutex_lock(&mut);
	recursos += count;
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
	FILE *fptr;
	fptr = fopen("inciso2.txt", "w");

	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}

	fprintf(fptr, "Iniciando programa\n");
	int j;
	pthread_t *thread;

	available_resources = 20;

	fprintf(fptr, "Creando %d threads\n", THREADS);
	for (j = 0; j < THREADS; j++) {
		pthread_create(&thread[j], NULL, threads_to_do, NULL);
	}

	fprintf(fptr, "Esperando threads \n");
	for (j = 0; j < THREADS; j++) {
		pthread_join(thread[j], NULL);
	}

	fprintf(fptr, "Fin del programa \n");
	fclose(fptr);
	return 0;
