#ifndef FUNCOES_H
#define FUNCOES_H

#define TAMANHO_MATRIX 30

typedef struct {
    int x;
    int y;
} SensorInfo;


void inicializar_floresta();

void* sensor_thread(void* args);

void* gerar_incendio(void* args);

void* central_controle(void* args);

void imprimir_floresta();

#endif;
