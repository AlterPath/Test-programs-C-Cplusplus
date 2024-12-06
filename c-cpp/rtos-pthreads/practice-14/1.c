#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    free(arg);

    while (1) {
        printf("Философ \e[9%dm%d\e[0m размышляет.\n", id+1, id+1);
        usleep(rand() % 500000);

        if (id == NUM_PHILOSOPHERS - 1) {
            // Последний философ берет сначала правую вилку, потом левую
            pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
            printf("Философ \e[9%dm%d\e[0m взял правую вилку.\n", id+1, id+1);
            pthread_mutex_lock(&forks[id]);
            printf("Философ \e[9%dm%d\e[0m взял левую вилку.\n", id+1, id+1);
        } else {
            // Остальные философы берут сначала левую вилку, потом правую
            pthread_mutex_lock(&forks[id]);
            printf("Философ \e[9%dm%d\e[0m взял левую вилку.\n", id+1, id+1);
            pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
            printf("Философ \e[9%dm%d\e[0m взял правую вилку.\n", id+1, id+1);
        }

        printf("Философ \e[9%dm%d\e[0m ест.\n", id+1, id+1);
        usleep(rand() % 500000);

        pthread_mutex_unlock(&forks[id]);
        printf("Философ \e[9%dm%d\e[0m положил левую вилку.\n", id+1, id+1);
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Философ \e[9%dm%d\e[0m положил правую вилку.\n", id+1, id+1);
    }

    return NULL;
}

int main() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher, id);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
