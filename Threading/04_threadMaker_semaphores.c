#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#define NUM_THREADS 3

sem_t semone, semtwo, semthree, semfour, semfive, semsix;
pthread_t threads[NUM_THREADS];
//Various procedures for printing thread #s and exiting said threads
void *ProcA(void *threadid){
	long tid;
	tid = (long)threadid;
	pthread_t id = pthread_self();  //Returns the thread id

	// Using if statements was the only way that I got semaphores to work, based after OBC solution code
	// Im guessing this will make sure that the process doesn't print 2 threads in one go
	if (pthread_equal(id,threads[1])){  //If the id is equal to the thread, then it will print that thread
	sem_wait(&semtwo);
		printf("\n+thread %ld ", tid);
		printf("from ProcA\n");
	sem_post(&semone);
	} else{
	sem_wait(&semone);

		printf("\n+thread %ld ", tid);
		printf("from ProcA\n");
	sem_post(&semtwo);
	}


}

void *ProcB(void *threadid){
	long tid;
	tid = (long)threadid;
	pthread_t id = pthread_self();

	if (pthread_equal(id,threads[1])){
	sem_wait(&semtwo);
		printf("\n+thread %ld ", tid);
		printf("from ProcB\n");
	sem_post(&semone);
	} else{
	sem_wait(&semone);

		printf("\n+thread %ld ", tid);
		printf("from ProcB\n");
	sem_post(&semtwo);
	}


}


void *ProcC(void *threadid){
	long tid;
	tid = (long)threadid;
	pthread_t id = pthread_self();

	if (pthread_equal(id,threads[1])){
	sem_wait(&semtwo);
		printf("\n+thread %ld ", tid);
		printf("from ProcC\n");
	sem_post(&semone);
	} else{
	sem_wait(&semone);

		printf("\n+thread %ld ", tid);
		printf("from ProcC\n");
	sem_post(&semtwo);
	}


}

int main() {
	printf("\nBegin thread maker.\n");
	sem_init(&semone, 0, 0);
	sem_init(&semtwo, 0, 1);
	int th; // Temporary thread
	long t;

	//For loops to make threads
	printf("\tRunning: ProcA:\n");
	for(t = 1; t<NUM_THREADS;t++){
		sleep(1);
		th = pthread_create(&threads[t], NULL, ProcA, (void *)t);
		sleep(1);
	}

	printf("\tRunning: ProcB:\n");
	for(t = 1; t<NUM_THREADS;t++){
		sleep(1);
		th = pthread_create(&threads[t], NULL, ProcB,(void *)t);
		sleep(1);
	}

	printf("\tRunning: ProcC:\n");
	for(t = 1; t<NUM_THREADS;t++){
		sleep(1);
		th = pthread_create(&threads[t], NULL, ProcC,(void *)t);
		sleep(1);
	}

	//Necessary to make it print the terminated line
	sleep(1);
	printf("Program terminated.\n");


}
