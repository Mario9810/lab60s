// mario sarmientos 17055
//referencia: https://linuxhint.com/posix-semaphores-with-c-programming/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define nthreads 4
sem_t mut;
int recursos = 1000;
void* accionh(void* arg){
	
	pid_t pid = syscall(SYS_gettid);
	sem_wait(&mut);
	printf("Entrando al thread(tomando recurso)");
	recursos--;
	sleep(1);
	
	recursos++;
	printf("saliendo del thread(devolviendo recurso) :)");
	sem_post(&mut);
	
}

int main(){
	int i;
	FILE *filepointer;
	filepointer = fopen("inciso1.txt","w");
	pthread_t *hilos;
	if(fptr == NULL){
		printf("error en el archivo");
		exit(1);
	}
	
	fprint(filepointer,"Iniciando programa\n");
	sem_init(&mut,0,1);
	fprint(filepointer,"Creando threads");
	
	for(i = 0; i<nthreads;i++){
		pthread_create(&hilos[i],NULL,accionh,NULL);
	}
	
	fprintf(filepointer,"Esperando threads");
	for(i = 0;i<nthreads, i++){
		pthread_join(hilos[i],NULL);
	}
	fclose(filepointer);
	return 0;
}
