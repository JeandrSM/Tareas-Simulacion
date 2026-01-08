#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *archivo;
    int i;

    // Inicializar la semilla del generador aleatorio
    srand(time(NULL));

    // Abrir archivo en modo escritura
    archivo = fopen("num_1a4.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Generar números aleatorios entre 1 y 20
    for (i = 0; i < 1000000; i++) {
        int numero = (rand() % 4) + 1;  // Genera números del 1 al 20
        fprintf(archivo, "%d\n", numero);
    }

    // Cerrar archivo
    fclose(archivo);

    printf("Se generaron los numeros aleatorios entre 1 y 20 en 'numeros_aleatorios.txt'\n");
    return 0;
}