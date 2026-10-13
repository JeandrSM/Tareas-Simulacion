#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *archivo;
    int i;

    srand(time(NULL));

    archivo = fopen("numerosC1_4.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    for (i = 0; i < 1000000; i++) {
        int r = (rand() % 4) + 1;  
        fprintf(archivo, "%d\n", r);
    }

    fclose(archivo);

    archivo = fopen("numerosC1_8.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    for (i = 0; i < 1000000; i++) {
        int r = (rand() % 8) + 1;  
        fprintf(archivo, "%d\n", r);
    }

    fclose(archivo);
    printf("Archivo generado correctamente.\n");
    return 0;
}
