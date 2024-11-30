#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>

// Семафоры для управления производственной линией
sem_t sem_A, sem_B, sem_C, sem_Module, sem_Product;

void handler() {
	int count_A, count_B, count_C, count_M, count_P;
	sem_getvalue(&sem_A, &count_A);
	sem_getvalue(&sem_B, &count_B);
	sem_getvalue(&sem_C, &count_C);
	sem_getvalue(&sem_Module, &count_M);
	sem_getvalue(&sem_Product, &count_P);
	printf("\nНа данный момент в запасе осталось:\n\t\e[91m%d\e[0m деталей A\
\t\e[92m%d\e[0m деталей B\t\e[93m%d\e[0m деталей C\n\t\e[94m%d\e[0m модулей\
\t\e[95m%d\e[0m изделий\n", count_A, count_B, count_C, count_M, count_P);
	exit(0);
}

// Функция для изготовления детали A
void *produce_A(void *arg) {
    while (1) {
        sleep(1); // Изготовление детали A занимает 1 секунду
        sem_post(&sem_A);
        printf("\e[91mДеталь A\e[0m изготовлена\n");
    }
    return NULL;
}

// Функция для изготовления детали B
void *produce_B(void *arg) {
    while (1) {
        sleep(2); // Изготовление детали B занимает 2 секунды
        sem_post(&sem_B);
        printf("\e[92mДеталь B\e[0m изготовлена\n");
    }
    return NULL;
}

// Функция для изготовления детали C
void *produce_C(void *arg) {
    while (1) {
        sleep(3); // Изготовление детали C занимает 3 секунды
        sem_post(&sem_C);
        printf("\e[93mДеталь C\e[0m изготовлена\n");
    }
    return NULL;
}

// Функция для сборки модуля (из деталей A и B)
void *assemble_module(void *arg) {
    while (1) {
        sem_wait(&sem_A); // Ожидание готовности детали A
        sem_wait(&sem_B); // Ожидание готовности детали B
        printf("\e[94mМодуль\e[0m собран из деталей \e[91mA\e[0m и \e[92mB\e[0m\n");
        sem_post(&sem_Module);
    }
    return NULL;
}

// Функция для сборки готового изделия (из модуля и детали C)
void *assemble_product(void *arg) {
    while (1) {
        sem_wait(&sem_Module); // Ожидание готовности модуля
        sem_wait(&sem_C);      // Ожидание готовности детали C
        printf("\e[95mИзделие\e[0m собрано из \e[94mмодуля\e[0m и \e[93mдетали C\e[0m\n");
        sem_post(&sem_Product);
    }
    return NULL;
}

int main() {
    pthread_t thread_A, thread_B, thread_C, thread_Module, thread_Product;
	int rc;

	signal(SIGINT, handler);

    // Инициализация семафоров
    sem_init(&sem_A, 0, 0);
    sem_init(&sem_B, 0, 0);
    sem_init(&sem_C, 0, 0);
    sem_init(&sem_Module, 0, 0);
    sem_init(&sem_Product, 0, 0);

    // Создание потоков
    rc = pthread_create(&thread_A, NULL, produce_A, NULL);
	if (rc) {
		fprintf(stderr, "\e[91mОшибка создания потока\e[0m\n");
		exit(1);
	}
    rc = pthread_create(&thread_B, NULL, produce_B, NULL);
	if (rc) {
		fprintf(stderr, "\e[91mОшибка создания потока\e[0m\n");
		exit(2);
	}
    rc = pthread_create(&thread_C, NULL, produce_C, NULL);
	if (rc) {
		fprintf(stderr, "\e[91mОшибка создания потока\e[0m\n");
		exit(3);
	}
    rc = pthread_create(&thread_Module, NULL, assemble_module, NULL);
	if (rc) {
		fprintf(stderr, "\e[91mОшибка создания потока\e[0m\n");
		exit(4);
	}
    rc = pthread_create(&thread_Product, NULL, assemble_product, NULL);
	if (rc) {
		fprintf(stderr, "\e[91mОшибка создания потока\e[0m\n");
		exit(5);
	}

    // Ожидание завершения потоков (теоретически они бесконечны)
    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);
    pthread_join(thread_C, NULL);
    pthread_join(thread_Module, NULL);
    pthread_join(thread_Product, NULL);

    // Освобождение ресурсов
    sem_destroy(&sem_A);
    sem_destroy(&sem_B);
    sem_destroy(&sem_C);
    sem_destroy(&sem_Module);

    return 0;
}
