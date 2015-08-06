#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* write_text(void* text_ptr);

int main(int ccount, char** value)
{
	pthread_t thread1, thread2;
	thread1 = thread2 = 0;
	pthread_mutex_t MTX;
	pthread_cond_t COND;
	const char* text_ping = "PING";
	const char* text_pong = "PONG";
	
	pthread_create(&thread1, NULL, write_text, (void*) text_ping);
	pthread_create(&thread2, NULL, write_text, (void*) text_pong);

	

	return 0;
}

void* write_text(void* text_ptr)
{
	const char* text = (char*) text_ptr;
	pthread_mutex_lock(&MTX);
	printf("%s", text);
	pthread_cond_signal(&COND);
	return NULL;
}

