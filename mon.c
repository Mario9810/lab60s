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
spthread_mutex_t mut;
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

void* monitor(void){
	pid_t pid;
	pid = syscall(SYS_gettid);
	printf("hilo: %d usa %d recursos", pid,tcost);
	printf
	while(decresase_count(tcost)!=0){
		NULL;
	}
	decrease_count(tcost);
	sleep(2);
	increase_count(tcost);
	printf("hilo: %d devuelve %d recursos",pid,tcost);
	
}

int main(){
	int i;
	FILE *filepointer;
	pthread *hilos;
	filepointer = fopen("inciso2.txt","w");
	if(filepointer==NULL){
		printf("error en archivo"){
			exit(1);
		}
	}
	fprintf(filepointer,"Iniciando programa\n");
	for(i =0;i<nthreads;i++){
		pthread(&hilos[i],NULL,monitor,NULL);
		sleep(1);
	}
	fprintf(filepointer,"Esperando hilos");
	for(i=0;i<nthreads,i++){
		pthread_join(hilos[i],NULL);
	}
	fclose(filepointer);
	return 0;
}
