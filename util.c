#include <stdio.h>
#include <string.h>
#include "Util.h"

void leerLinea(const char *mensaje, char *destino, int tam) {
    printf("%s", mensaje);
    fflush(stdout);
    if (fgets(destino, tam, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } else {
        destino[0] = '\0';
    }
}

int leerEntero(const char *mensaje) {
    char buffer[32];
    int valor;
    while (1) {
        leerLinea(mensaje, buffer, sizeof(buffer));
        if (sscanf(buffer, "%d", &valor) == 1) {
            return valor;
        }
        printf("Entrada invalida. Ingrese un numero entero.\n");
    }
}

void pausar(void) {
    int c;
    printf("\nPresione Enter para continuar...");
    fflush(stdout);
    while ((c = getchar()) != '\n' && c != EOF);
}
