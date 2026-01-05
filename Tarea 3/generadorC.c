#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *archivo;
    int i;

    // Inicializar la semilla del generador aleatorio
    srand(time(NULL));

    // Abrir archivo en modo escritura
    archivo = fopen("numeros_aleatorios.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Generar números aleatorios en [0,1[
    for (i = 0; i < 1000000; i++) {
        double r = (double) rand() / (RAND_MAX + 1.0);
        fprintf(archivo, "%.4f\n", r);
    }

    // Cerrar archivo
    fclose(archivo);

    printf("Se generaron los num");
    return 0;
}
