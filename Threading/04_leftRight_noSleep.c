#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//compile on linux: gcc -pthread 04_leftRight_noSleep.c
//

sem_t leftsem, rightsem;


void *left(void *arg)
{

    for (;;) {
        sem_wait(&leftsem);
        sleep(1); // allows to see the individual print lines
        printf("  Left        \n");
        sem_post(&rightsem);
	}
}

void *right(void *arg)
{

	for (;;){
        	sem_wait(&rightsem);
          sleep(1); // allows to see the individual print lines
        	printf("          Right\n");
        	sem_post(&leftsem);
	}
}

int main(void)
{

	sem_init(&leftsem, 0, 0);
	sem_init(&rightsem, 0, 1);
	pthread_t left_thread, right_thread;
	pthread_create(&left_thread, NULL, left, NULL);
	pthread_create(&right_thread, NULL, right, NULL);
	pthread_join(left_thread, NULL);
	pthread_join(right_thread, NULL);
	printf("\n");
	return 0;

}
