#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define MAX 9999

typedef struct Data {
	int calculated;
	int number;
} Data;

pthread_mutex_t m1;
pthread_mutex_t m2;

void* thread_1 (void* d);
void* thread_2 (void* d);
void handler ();

int main() {
	srand(time(NULL));
	int num = 0;
	signal(SIGINT, handler);

	int			rc;
	pthread_t	tid;
	
	Data t1, t2;
	t1.calculated = 1;
	t1.number = 0;
	t2.calculated = 1;
	t2.number = 0;
	
	rc = pthread_create(&tid, NULL, thread_1, (void*)&t1);
	if (rc) {
		fprintf(stderr, "\e[91mОшибка создания 2 потока\e[0m\n");
	}
	rc = pthread_create(&tid, NULL, thread_2, (void*)&t2);
	if (rc) {
		fprintf(stderr, "\e[91mОшибка создания 3 потока\e[0m\n");
	} 
			
	while (1) {
		num = rand()%MAX-(MAX/2);
		if (num%2 == 0) {
			pthread_mutex_lock(&m1);
			t1.calculated = 0;
			t1.number = num;
			pthread_mutex_unlock(&m1);
		} else {
			pthread_mutex_lock(&m2);
			t2.calculated = 0;
			t2.number = num;
			pthread_mutex_unlock(&m2);
		}
		sleep(1);
	}
	exit(0);
}

void* thread_1(void* d) {
	Data* data = (Data*)d;
	while (1) {
		if (data->calculated == 0) {
			pthread_mutex_lock(&m1);
			int num = data->number;
			printf("\e[92mСообщение из потока \e[95m2\e[0m: Квадрат числа \e[95m%4d\e[0m равен \e[93m%lld\e[0m\n", num, (long long)num*num);
			data->calculated = 1;
			pthread_mutex_unlock(&m1);
		} /* else {
			usleep(333000);
		} */
	}
	pthread_exit(NULL);
}

void* thread_2(void* d) {
	Data* data = (Data*)d;
	while (1) {
		if (data->calculated == 0) {
			pthread_mutex_lock(&m2);
			int num = data->number;
			printf("\e[92mСообщение из потока \e[96m3\e[0m: Куб числа \e[96m%4d\e[0m равен \e[93m%lld\e[0m\n", num, (long long)num*num*num);
			data->calculated = 1;
			pthread_mutex_unlock(&m2);
		} /* else {
			usleep(333000);
		} */
	}
	pthread_exit(NULL);
}

void handler() {
	fprintf(stdout, "\e[0m");
	fprintf(stderr, "\n\e[37;41mВыход\e[0m\n");
	exit(1);
}
