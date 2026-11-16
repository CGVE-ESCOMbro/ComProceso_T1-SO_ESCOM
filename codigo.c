#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define LIMITE 10000

// Semaforo para controlar la seccion critica
sem_t sem_bloqueo;

void* imprimir_numeracion(void* arg);

// Funcion principal
int main() {

	pthread_t hilo1, hilo2;
	int id1 = 1;
	int id2 = 2;

	// Inicializar el semaforo en 1
	sem_init(&sem_bloqueo, 0, 1);

	// Crear los dos hilos
	pthread_create(&hilo1, NULL, imprimir_numeracion, &id1);
	pthread_create(&hilo2, NULL, imprimir_numeracion, &id2);

	// Esperar a que ambos hilos terminen
	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);

	// Destruir el semaforo
	sem_destroy(&sem_bloqueo);
	printf("\nAmbos hilos han terminado.\n");
	return 0;
}

// Funcion que ejecutaran ambos hilos
void* imprimir_numeracion(void* arg) {

	int id = *(int*)arg;

	for (int i = 1; i <= LIMITE; i++) {

		// Cuando el hilo llega a 4000,
		// solicita acceso a la seccion critica.
		if (i == 4000) {
			sem_wait(&sem_bloqueo);
			printf("\nHilo %d entra a la seccion critica\n", id);
		}

		// Imprimir el numero correspondiente
		printf("Hilo %d: %d\n", id, i);

		// Cuando llega a 6000, libera el semaforo.
		if (i == 6000) {
			printf("Hilo %d sale de la seccion critica\n\n", id);
			sem_post(&sem_bloqueo);
		}
	}
	return NULL;
}
