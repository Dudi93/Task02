#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* write_ping(void* iterations);
void* write_pong(void* iterations);
void ping(void);
void pong(void);
pthread_mutex_t MTX;
pthread_cond_t COND;
int test = 0;

int main(int argc, char* argv[])
{
	pthread_t thread1, thread2;
	thread1 = thread2 = 0;
	pthread_mutex_init(&MTX, 0);
	pthread_cond_init(&COND, 0);
	int* number_of_iterations = malloc(sizeof(int));
	*number_of_iterations = atoi(argv[1]) / 2;
	
	pthread_create(&thread1, NULL, write_ping, (void*) number_of_iterations);
	pthread_create(&thread2, NULL, write_ping, (void*) number_of_iterations);

	pthread_join(thread1, 0);
	pthread_join(thread2, 0);

	return 0;
}

void* write_ping(void* iterations)
{
	int* number = (void*) iterations;
	int i;
	for (i = 0; i < *number; ++i)
	{
		ping();
		pong();
	}	

	return NULL;
}

/*void* write_pong(void* iterations)
{
	int* number = (void*) iterations;
	int i;
	for (i = 0; i < *number; ++i)
	{
		pong();
	}	

	return NULL;
}*/
void ping(void)
{
	pthread_mutex_lock(&MTX);
	//printf("%s\n", "PING");
	if(test == 0)
	{
		printf("%s\n", "PING");
		test = 1;
		pthread_cond_signal(&COND);
	}
	else
		pthread_cond_wait(&COND, &MTX);
	pthread_mutex_unlock(&MTX);


}

void pong(void)
{
	pthread_mutex_lock(&MTX);
	//printf("%s\n", "PONG");
	if (test == 1)
	{
		printf("%s\n", "PONG");
		test = 0;
		pthread_cond_signal(&COND);
	}
	else
		pthread_cond_wait(&COND, &MTX);
	pthread_mutex_unlock(&MTX);

}
