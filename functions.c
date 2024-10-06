#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "functions.h"

#define TAMANHO_MATRIX 30

char floresta[TAMANHO_MATRIX][TAMANHO_MATRIX];
pthread_mutex_t mutex[TAMANHO_MATRIX][TAMANHO_MATRIX];
pthread_cond_t cond[TAMANHO_MATRIX][TAMANHO_MATRIX];

void inicializar_floresta() {
    for (int i = 0; i < TAMANHO_MATRIX; i++) {
        for (int j = 0; j < TAMANHO_MATRIX; j++) {
            floresta[i][j] = '-';
            pthread_mutex_init(&mutex[i][j], NULL);
            pthread_cond_init(&cond[i][j], NULL);
        }
    }
}

void* sensor_thread(void* args) {
    SensorInfo *info = (SensorInfo *)args;
    int x = info->x;
    int y = info->y; 

    while (1) {
        pthread_mutex_lock(&mutex[x][y]);
        if (floresta[x][y] == '@') {

            if (x > 0) pthread_cond_signal(&cond[x - 1][y]);
            if (x < TAMANHO_MATRIX - 1) pthread_cond_signal(&cond[x + 1][y]);
            if (y > 0) pthread_cond_signal(&cond[x][y - 1]);
            if (y < TAMANHO_MATRIX - 1) pthread_cond_signal(&cond[x][y + 1]);


            if (x == 0 || x == TAMANHO_MATRIX - 1 || y == 0 || y == TAMANHO_MATRIX - 1) {
            }
        }
        pthread_mutex_unlock(&mutex[x][y]);
        sleep(1);
    }
    return NULL;
}

void* gerar_incendio(void* args) {
    while (1) {
        int x = rand() % TAMANHO_MATRIX;
        int y = rand() % TAMANHO_MATRIX;

        pthread_mutex_lock(&mutex[x][y]);
        if (floresta[x][y] == '-') {
            floresta[x][y] = '@'; 
            pthread_cond_signal(&cond[x][y]);
        }
        pthread_mutex_unlock(&mutex[x][y]);

        sleep(3);
    }
    return NULL;
}

void* cen;