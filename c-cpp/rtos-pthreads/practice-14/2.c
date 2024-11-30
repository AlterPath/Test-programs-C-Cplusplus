#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_mutex_t table_lock; // Мьютекс для доступа к условной переменной
pthread_cond_t table_cond;  // Условная переменная

void *philosopher(void *arg) {
    int id = *(int *)arg;
    free(arg);

    while (1) {
        printf("Философ \e[9%dm%d\e[0m размышляет.\n", id+1, id+1);
        usleep(rand() % 500000);

        // Попытка взять вилки
        pthread_mutex_lock(&table_lock);
        while (1) {
            if (pthread_mutex_trylock(&forks[id]) == 0) {
                if (pthread_mutex_trylock(&forks[(id + 1) % NUM_PHILOSOPHERS]) == 0) {
                    break; // Обе вилки успешно захвачены
                } else {
                    pthread_mutex_unlock(&forks[id]); // Освободить первую вилку, если вторая недоступна
                }
            }
            pthread_cond_wait(&table_cond, &table_lock); // Ждать, пока вилки освободятся
        }
       	printf("Философ \e[9%dm%d\e[0m взял вилки\n", id+1, id+1);
        pthread_mutex_unlock(&table_lock);

        // Еда
        printf("Философ \e[9%dm%d\e[0m ест.\n", id+1, id+1);
        usleep(rand() % 500000);

        // Освобождение вилок
        pthread_mutex_lock(&table_lock);
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Философ \e[9%dm%d\e[0m положил вилки.\n", id+1, id+1);
        pthread_cond_broadcast(&table_cond); // Уведомить остальных философов
        pthread_mutex_unlock(&table_lock);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];

    // Инициализация вилок, мьютекса и условной переменной
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    pthread_mutex_init(&table_lock, NULL);
    pthread_cond_init(&table_cond, NULL);

    // Создание потоков для философов
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher, id);
    }

    // Ожидание завершения потоков (теоретически они бесконечны)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Освобождение ресурсов
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    pthread_mutex_destroy(&table_lock);
    pthread_cond_destroy(&table_cond);

    return 0;
}
