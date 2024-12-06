#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define QUEUE_SIZE 10
#define MSG_MAX_LEN 80
#define N 2

typedef struct {
    char messages[QUEUE_SIZE][MSG_MAX_LEN + 1]; // Очередь сообщений
    int front; // Индекс извлечения
    int rear;  // Индекс вставки
    int count; // Текущий размер очереди
    sem_t empty; // Семафор для отслеживания пустых мест
    sem_t full;  // Семафор для отслеживания заполненных мест
    pthread_mutex_t mutex; // Мьютекс для синхронизации доступа
    int dropped; // Флаг для прекращения работы
} queue;

void mymsginit(queue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
    q->dropped = 0;
    sem_init(&q->empty, 0, QUEUE_SIZE); // Все места свободны
    sem_init(&q->full, 0, 0); // Нет заполненных мест
    pthread_mutex_init(&q->mutex, NULL);
}

void mymsqdrop(queue *q) {
    pthread_mutex_lock(&q->mutex);
    q->dropped = 1;
    sem_post(&q->empty); // Разблокировать возможные ожидания
    sem_post(&q->full);
    pthread_mutex_unlock(&q->mutex);
}

void mymsgdestroy(queue *q) {
    sem_destroy(&q->empty);
    sem_destroy(&q->full);
    pthread_mutex_destroy(&q->mutex);
}

int mymsgput(queue *q, char *msg) {
    sem_wait(&q->empty);
    pthread_mutex_lock(&q->mutex);

    if (q->dropped) {
        pthread_mutex_unlock(&q->mutex);
        sem_post(&q->empty);
        return 0;
    }

    int len = strlen(msg);
    if (len > MSG_MAX_LEN) len = MSG_MAX_LEN;

    strncpy(q->messages[q->rear], msg, len);
    q->messages[q->rear][len] = '\0';
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->count++;

    pthread_mutex_unlock(&q->mutex);
    sem_post(&q->full);
    return len;
}

int mymsgget(queue *q, char *buf, size_t bufsize) {
    sem_wait(&q->full);
    pthread_mutex_lock(&q->mutex);

    if (q->dropped) {
        pthread_mutex_unlock(&q->mutex);
        sem_post(&q->full);
        return 0;
    }

    int len = strlen(q->messages[q->front]);
    if (len > bufsize - 1) len = bufsize - 1;

    strncpy(buf, q->messages[q->front], len);
    buf[len] = '\0';
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->count--;

    pthread_mutex_unlock(&q->mutex);
    sem_post(&q->empty);
    return len;
}

void *producer(void *arg) {
    queue *q = (queue *)arg;
    char msg[MSG_MAX_LEN + 1];
    int id = pthread_self() % 1000;

    for (int i = 0; i < 5; ++i) {
        snprintf(msg, sizeof(msg), "Сообщение от производителя %d: %d", id, i);
        int len = mymsgput(q, msg);
        if (len == 0) {
            printf("Производитель %d: Очередь завершена, выход.\n", id);
            break;
        }
        printf("Производитель %d: Отправка сообщения '%s'\n", id, msg);
        sleep(rand() % 2);
    }
    return NULL;
}

void *consumer(void *arg) {
    queue *q = (queue *)arg;
    char buf[MSG_MAX_LEN + 1];
    int id = pthread_self() % 1000;

    while (1) {
        int len = mymsgget(q, buf, sizeof(buf));
        if (len == 0) {
            printf("Потребитель %d: Очередь завершена, выход.\n", id);
            break;
        }
        printf("Потребитель %d: Получено сообщение '%s'\n", id, buf);
        sleep(rand() % 3);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    queue q;
    mymsginit(&q);

	int i;
    pthread_t producers[2], consumers[2];

	for (i=0; i<N; i++) {
    	pthread_create(&producers[i], NULL, producer, &q);
    	pthread_create(&consumers[i], NULL, consumer, &q);	
	}

    sleep(10); // Дать время на выполнение
    mymsqdrop(&q); // Завершение работы очереди

	for (i=0; i<N; i++) {
	    pthread_join(producers[i], NULL);
	    pthread_join(consumers[i], NULL);	
	}

    mymsgdestroy(&q);
    return 0;
}
