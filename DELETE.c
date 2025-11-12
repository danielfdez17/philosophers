#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Orden a cumplir en el tablon
int tablon;

// E2. Variables para sincronizacion
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex
pthread_cond_t cond_capataz = PTHREAD_COND_INITIALIZER; // VC para el capataz
pthread_cond_t* cond_obreros; // Array de VCs para todos los obreros.

// E2. Variables globales.
int* obreros_leidos; // Array de enteros que indica si cada obrero ha leído (1) o no (0) la orden actual.
int obreros_pendientes; // Variable para contar el número de obreros pendientes de leer la orden actual.

typedef struct {
    int id;         // Identificador del obrero.
    int nordenes;   // Numero de ordenes a leer/ejecutar.
} obrero_t;

typedef struct {
    int nobreros;   // Numero de obreros a cargo.
    int nordenes;   // Numero de ordenes a colgar.
} capataz_t;

void escribeOrden(int Norden, int Nobreros) {
    int i;

    printf("[Capataz ] Esperando para escribir nueva orden\n");

    pthread_mutex_lock(&mutex);

    // E2. Espera si hay obreros pendientes de leer orden
    while (obreros_pendientes > 0) {
        pthread_cond_wait(&cond_capataz, &mutex);
    }

    // Escribir siguiente orden en el tablon.
    tablon = Norden;

    printf("[Capataz ] Nueva orden escrita (%d)\n", tablon);

    // E2. Avisa a los obreros porque hay una nueva orden en el tablón.
    for (i = 0; i < Nobreros; i++) {
        obreros_leidos[i] = 0;
        pthread_cond_signal(&cond_obreros[i]);
    }
    obreros_pendientes = Nobreros;
    pthread_mutex_unlock(&mutex);
}

// Funcion de entrada para hilo capataz
void* capataz(void* arg) {
    capataz_t* capataz_info = (capataz_t*)arg; // E1. Recogida de argumentos.
    int Nobreros = capataz_info->nobreros; // E1. Número de obreros a cargo.
    int Nordenes = capataz_info->nordenes; // E1. Número de ordenes a colgar.
    int Norden = 0;

    while (Norden++ < Nordenes)
        escribeOrden(Norden, Nobreros);
}

int leeorden(int id) {
    int orden;

    printf("[Obrero %d] Esperando orden\n", id);

    // E2. Espera si el tablon esta vacio, o si lo que hay en el tablon no lo leyo ya este mismo obrero.
    pthread_mutex_lock(&mutex);
    while (tablon == -1 || obreros_leidos[id] == 1) {
        pthread_cond_wait(&cond_obreros[id], &mutex);
    }

    // Recoge la orden del tablon.
    orden = tablon;

    obreros_leidos[id] = 1;
    obreros_pendientes--;

    // E2. Informa de que ya ha leido el tablon y avisa si es necesario para que el capaz cuelgue una nueva orden.
    if (obreros_pendientes == 0) {
        pthread_cond_signal(&cond_capataz);
    }

    printf("[Obrero %d] Orden leída (%d)\n", id, orden);

    pthread_mutex_unlock(&mutex);

    return orden;
}

void trabaja(int id, int orden) {
    printf("[Obrero %d] Trabajando (%d)\n", id, orden);
    sleep(rand() % 10);
    printf("[Obrero %d] Finaliza orden (%d)\n", id, orden);

    // Escribe en el archivo ordenes_ejecutadas.txt
    FILE* file = fopen("ordenes_ejecutadas.txt", "a");
    if (file != NULL) {
        fprintf(file, "%d %d\n", id, orden);
        fclose(file);
    } else {
        printf("[Obrero %d] Error al abrir el archivo ordenes_ejecutadas.txt\n", id);
    }
}

// Funcion de entrada para hilo obrero
void* obrero(void* arg) {
    obrero_t* obrero_info = (obrero_t*)arg; // E1. Recogida de argumentos.
    int id = obrero_info->id;               // E1. Identificador de obrero.
    int Nordenes = obrero_info->nordenes;   // E1. Número de ordenes a ejecutar.

    int Norden = 0;
    int orden;

    while (Norden++ < Nordenes) {
        orden = leeorden(id);
        trabaja(id, orden);
    }

}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <ordenes_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error al abrir el archivo %s\n", argv[1]);
        return 1;
    }

    int Nobreros = 0;
    int Nordenes = 0;
    int i;

    if (fscanf(file, "%d", &Nobreros) != 1) {
        printf("Error reading number of workers\n");
        fclose(file);
        return 1;
    }

    if (fscanf(file, "%d", &Nordenes) != 1) {
        printf("Error reading number of orders\n");
        fclose(file);
        return 1;
    }

    tablon = -1;

    pthread_t capataz_thread;
    pthread_t* obreros_threads = malloc(Nobreros * sizeof(pthread_t));
    obrero_t* obreros_info = malloc(Nobreros * sizeof(obrero_t));

    for (i = 0; i < Nobreros; i++) {
        obreros_info[i].id = i;
        obreros_info[i].nordenes = Nordenes;

        if (pthread_create(&obreros_threads[i], NULL, obrero, &obreros_info[i]) != 0) {
            printf("Error al crear el hilo del obrero %d\n", i + 1);
            fclose(file);
            free(obreros_threads);
            free(obreros_info);
            return 1;
        }
    }

    capataz_t capataz_info;
    capataz_info.nobreros = Nobreros;
    capataz_info.nordenes = Nordenes;

    if (pthread_create(&capataz_thread, NULL, capataz, &capataz_info) != 0) {
        printf("Error al crear el hilo del capataz\n");
        fclose(file);
        free(obreros_threads);
        free(obreros_info);
        return 1;
    }

    fclose(file);

    pthread_join(capataz_thread, NULL);
    for (i = 0; i < Nobreros; i++) {
        pthread_join(obreros_threads[i], NULL);
    }

    free(obreros_threads);
    free(obreros_info);

    return 0;
}
