#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NB_TOUR 10

typedef struct multi_thread {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} multi_thread;

int compteur = 0;

void* thread_hello_world(multi_thread* mt) {
    printf("Hello World!\n");

    pthread_mutex_lock(&mt->mutex);

    compteur++;
    if (compteur == NB_TOUR) {
        pthread_cond_signal(&mt->cond);
    }

    pthread_mutex_unlock(&mt->mutex);
    return NULL;
}

void* thread_done(multi_thread* mt) {
    pthread_mutex_lock(&mt->mutex);

    while (compteur < NB_TOUR) {
        pthread_cond_wait(&mt->cond, &mt->mutex);
    }

    pthread_mutex_unlock(&mt->mutex);

    printf("Done!\n");
    return NULL;
}

int main(void) {

    pthread_t hellos[NB_TOUR];
    pthread_t done;
    multi_thread* mt = malloc(sizeof(multi_thread));

    pthread_mutex_init(&mt->mutex, NULL);
    pthread_cond_init(&mt->cond, NULL);

    for (int i=0; i<NB_TOUR; i++) {
        pthread_create(&hellos[i], NULL, (void* (*)(void*))thread_hello_world, mt);
        pthread_detach(hellos[i]);
    }

    pthread_create(&done, NULL, (void* (*)(void*))thread_done, mt);

    pthread_join(done, NULL);

    pthread_mutex_destroy(&mt->mutex);
    pthread_cond_destroy(&mt->cond);

    free(mt);

    return 0;
}
