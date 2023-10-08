#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct argStruct {
    int size;
    int arr[];
};

struct argStruct args = {
    9, // size
    { 7, 2, 1, 3, 8, 4, -5, 6, 9 } // arr
};

pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

void *addSum(void *args) {
    pthread_mutex_lock(&myMutex);

    struct argStruct *temp_args;
    temp_args = (struct argStruct *)args;

    int new_arr[temp_args->size];
    memcpy(new_arr, temp_args->arr, temp_args->size * sizeof(int));

    int sum = 0;
    for (int i = 0; i < temp_args->size; ++i) {
        sum += temp_args->arr[i];
    }

    printf("{");
    for (int i = 0; i < temp_args->size - 1; ++i) {
        new_arr[i] += sum;
        printf("%d, ", new_arr[i]);
    }
    new_arr[temp_args->size - 1] += sum;
    printf("%d}\n", new_arr[temp_args->size - 1]);

    pthread_mutex_unlock(&myMutex);
}

void *diffSum(void *args) {
    pthread_mutex_lock(&myMutex);

    struct argStruct *temp_args;
    temp_args = (struct argStruct *)args;

    int new_arr[temp_args->size];
    memcpy(new_arr, temp_args->arr, temp_args->size * sizeof(int));

    int sum = 0;
    for (int i = 0; i < temp_args->size; ++i) {
        sum += temp_args->arr[i];
    }

    printf("{");
    for (int i = 0; i < temp_args->size - 1; ++i) {
        new_arr[i] = sum - temp_args->arr[i];
        printf("%d, ", new_arr[i]);
    }
    new_arr[temp_args->size - 1] = sum - temp_args->arr[temp_args->size - 1];
    printf("%d}\n", new_arr[temp_args->size - 1]);

    pthread_mutex_unlock(&myMutex);
}

int main() {
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, addSum, (void *)&args);
    pthread_create(&tid2, NULL, diffSum, (void *)&args);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}