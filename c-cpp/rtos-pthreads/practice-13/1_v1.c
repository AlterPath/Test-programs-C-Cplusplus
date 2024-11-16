#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAX 9999

void* thread_1 (void* num);
void* thread_2 (void* num);
void handler ();

int main() {
	srand(time(NULL));
	int num = 0;
	signal(SIGINT, handler);

	int			rc;
	pthread_t	tid;

	while (1) {
		num = rand()%MAX-(MAX/2);
		if (num%2 == 0) {
			rc = pthread_create(&tid, NULL, thread_1, (void*)&num);
		} else {
			rc = pthread_create(&tid, NULL, thread_2, (void*)&num);
		}
		if (rc) {
			fprintf(stderr, "\e[91mОшибка создания потока для числа %d\e[0m\n", num);
		} 
		sleep(1);
	}
	exit(0);
}

void* thread_1(void* num) {
	int local = *(int*)num;
	printf("\e[92mСообщение из потока \e[95m2\e[0m: Квадрат числа \e[95m%4d\e[0m равен \e[93m%lld\e[0m\n", local, (long long)local*local);
	pthread_exit(NULL);
}

void* thread_2(void* num) {
	int local = *(int*)num;
	printf("\e[92mСообщение из потока \e[96m3\e[0m: Куб числа \e[96m%4d\e[0m равен \e[93m%lld\e[0m\n", local, (long long)local*local*local);
	pthread_exit(NULL);
}

void handler() {
	fprintf(stdout, "\e[0m");
	fprintf(stderr, "\n\e[37;41mВыход\e[0m\n");
	exit(1);
}
