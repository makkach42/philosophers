#include <libc.h>
#include <pthread.h>



void *r(void *ss)
{
	(void )ss;
	printf("done\n");
	return (NULL);
}

typefe

int main()
{
	

	pthread_t thread;

	pthread_create(&thread, NULL, r, NULL);
	pthread_join(thread, NULL);
}