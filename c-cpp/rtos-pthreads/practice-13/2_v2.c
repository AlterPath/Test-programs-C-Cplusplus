#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define KORM_MIN 100
#define KORM_MAX 1000
#define EAT_MAX 100
#define DAY_LENGTH 7 // длительность дня в секундах
#define CAT_SLEEP 1
#define FEED_PROBABILITY 20

int lerp(float min, float max, float this, float total);

void *day_thread();
void *cat1();
void *cat2();
void *cat3();
void *cat4();
void *cat5();

int day = 0;
int korm = KORM_MAX;
pthread_mutex_t m_day;
pthread_mutex_t m_korm;
int low;
int high;

int main() {
  srand(time(NULL));
  int rc;
  pthread_t tid;

  low = lerp(KORM_MIN, KORM_MAX, 2, 4);
  high = lerp(KORM_MIN, KORM_MAX, 3, 4);

  rc = pthread_create(&tid, NULL, cat1, NULL);
  if (rc) {
    fprintf(stderr, "\e[91mОшибка создания 1 котофея((((\e[0m\n");
  }
  rc = pthread_create(&tid, NULL, cat2, NULL);
  if (rc) {
    fprintf(stderr, "\e[91mОшибка создания 2 котофея((((\e[0m\n");
  }
  rc = pthread_create(&tid, NULL, cat3, NULL);
  if (rc) {
    fprintf(stderr, "\e[91mОшибка создания 3 котофея((((\e[0m\n");
  }
  rc = pthread_create(&tid, NULL, cat4, NULL);
  if (rc) {
    fprintf(stderr, "\e[91mОшибка создания 4 котофея((((\e[0m\n");
  }
  rc = pthread_create(&tid, NULL, cat5, NULL);
  if (rc) {
    fprintf(stderr, "\e[91mОшибка создания 5 котофея((((\e[0m\n");
  }

  rc = pthread_create(&tid, NULL, day_thread, NULL);
  if (rc) {
    fprintf(stderr, "\e[91mОшибка создания потока дня\e[0m\n");
  }

  // if (EAT_MAX*5 < (KORM_MAX-KORM_MIN)/2) {
  // 	printf("День 1\n");
  // }
  // обработчик хозяина
  int last_day = day;
  int day_record;
  int added;
  // int day_printed = 0;
  while (1) {
    if (day > last_day) {
      // if (EAT_MAX*5 > (KORM_MAX-KORM_MIN)/2) {
      printf("За %d день было добавлено \e[33m%d\e[0m грам корма\n",
             last_day + 1, day_record);
      // }
      day_record = 0;
      last_day = day;
    }

    pthread_mutex_lock(&m_korm);
    if (korm <= 100) {
      added = KORM_MAX - korm;
      korm = KORM_MAX;
      day_record += added;
      pthread_mutex_lock(&m_day);
      last_day = day;
      pthread_mutex_unlock(&m_day);
    }
    pthread_mutex_unlock(&m_korm);
  }
  exit(0);
}

void *day_thread() {
  while (1) {
    sleep(DAY_LENGTH);
    pthread_mutex_lock(&m_day);
    day++;
    pthread_mutex_unlock(&m_day);
  }
  pthread_exit(NULL);
}

void cat_default(int number) {
  int last_day = day;
  int ate = 0;
  int ate_last = 0;
  while (1) {
    // В начале дня сбрасывается счётчик сожранного
    if (day > last_day) {
      ate = 0;
    }
    int color = 39; // цвет по умолчанию

    int feed = rand() % 101;
    if (feed <= FEED_PROBABILITY) {
      if (ate >= EAT_MAX) {
        sleep(CAT_SLEEP);
      } else {
        // сколько максимально котейка максимально захочет жрать
        int eat = rand() % (EAT_MAX + 1);
        int possible = EAT_MAX - ate;

        pthread_mutex_lock(&m_korm);
        // если меньше или равно норме в день, то всё
        if (eat <= possible && eat > 0) {
          ate_last = eat;
        }
        // иначе - доедать до максимума дневной нормы
        else if (possible > 0 && eat > 0) {
          ate_last = EAT_MAX - ate;
        }
        korm -= ate_last;
        ate += ate_last;

        pthread_mutex_lock(&m_day);
        last_day = day;
        pthread_mutex_unlock(&m_day);

        if (korm >= high) {
          color = 92; // если осталось много - зелёный
        } else if (korm < high && korm >= low) {
          color = 93; // не много, но и не мало - жёлтый
        } else {
          color = 91; // мало - красный
        }
        if (ate_last > 0) {
          printf("Котейка номер \e[%dm%d\e[0m съел \e[96m%d\e[0m грам корма "
                 "(\e[%dm%d\e[0m из \e[96m%d\e[0m). Осталось \e[%dm%d\e[0m\n",
                 90 + number, number, ate_last, 90 + number, ate, EAT_MAX,
                 color, korm);
        }
        pthread_mutex_unlock(&m_korm);
        sleep(CAT_SLEEP);
      }
    }
  }
}

void *cat1() { cat_default(1); }
void *cat2() { cat_default(2); }
void *cat3() { cat_default(3); }
void *cat4() { cat_default(4); }
void *cat5() { cat_default(5); }

int lerp(float min, float max, float this, float total) {
  int ret = (int)(min + (max - min) * ((this - 1) / (total - 1)));
  return ret;
}

