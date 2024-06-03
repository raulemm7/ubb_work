#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/*
 * se dau datele unei matrici in fisier
 * pentru fiecare rand se creeaza un thread care calculeaza suma pe randul respectiv
 * la final se afiseaza suma totala
 */

int MAX_ROW = 10;
int MAX_COL = 10;

int sum;
int mat[10003][10003];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* do_sum(void* arg) {
    int row = *(int*)arg;

    int thread_sum = 0;
    for(int i = 0; i < MAX_COL; i++) {
        thread_sum += mat[row][i];
    }

    pthread_mutex_lock(&mtx);
    sum += thread_sum;
    pthread_mutex_unlock(&mtx);

    return NULL;
}

int main() {
    FILE* fd = fopen("test_matrix.txt", "r+");
    fscanf(fd, "%d", &MAX_ROW);
    fscanf(fd, "%d", &MAX_COL);

    for(int i = 0; i < MAX_ROW; i++) {
        for(int j = 0; j < MAX_COL; j++) {
            fscanf(fd, "%d", &mat[i][j]);
        }
    }

    pthread_t tid[MAX_ROW];

    for(int i = 0; i < MAX_ROW; i++) {
        int* id = (int*)malloc(sizeof(int));
        *id = i;
        pthread_create(&tid[i], NULL, do_sum, id);
    }

    for(int i = 0; i < MAX_ROW; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("%d\n", sum);

    return 0;
}

