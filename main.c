#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "functions.h"

int main() {
    pthread_t sensores[TAMANHO_MATRIX][TAMANHO_MATRIX];
    pthread_t gerador_incendios;
    pthread_t central;

    inicializar_floresta();

    for (int i = 0; i < TAMANHO_MATRIX; i++) {
        for (int j = 0; j < TAMANHO_MATRIX; j++) {
            SensorInfo *info = malloc(sizeof(SensorInfo));
            info->x = i;
            info->y = j;
            pthread_create(&sensores[i][j], NULL, sensor_thread, (void *)info);
        }
    }

    pthread_create(&gerador_incendios, NULL, gerar_incendio, NULL);

    pthread_create(&central, NULL, central_controle, NULL);

    while (1) {
        imprimir_floresta();
        sleep(1);
    }

    return 0;
}
