#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "persistencia.h"

int cargarLibros(Libreria *lib, const char *archivo) {
    FILE *f = fopen(archivo, "r");
    if (f == NULL) return 0;

    char linea[512];
    lib->cantidad = 0;
    int primera = 1;

    while (fgets(linea, sizeof(linea), f) != NULL && lib->cantidad < MAX_LIBROS) {
        size_t len = strlen(linea);
        if (len > 0 && linea[len - 1] == '\n') linea[len - 1] = '\0';
        if (strlen(linea) == 0) continue;

        if (primera) {
            primera = 0;
            if (strncmp(linea, "codigo_libro", 12) == 0) continue;
        }

        Libro l;
        char *campo;

        campo = strtok(linea, ",");
        if (!campo) continue;
        strncpy(l.codigo, campo, TAM_CODIGO - 1); l.codigo[TAM_CODIGO - 1] = '\0';

        campo = strtok(NULL, ",");
        if (!campo) continue;
        strncpy(l.titulo, campo, TAM_TITULO - 1); l.titulo[TAM_TITULO - 1] = '\0';

        campo = strtok(NULL, ",");
        if (!campo) continue;
        strncpy(l.clasificacion, campo, TAM_CLASIFICACION - 1); l.clasificacion[TAM_CLASIFICACION - 1] = '\0';

        campo = strtok(NULL, ",");
        if (!campo) continue;
        strncpy(l.autor, campo, TAM_AUTOR - 1); l.autor[TAM_AUTOR - 1] = '\0';

        campo = strtok(NULL, ",");
        if (!campo) continue;
        strncpy(l.isbn, campo, TAM_ISBN - 1); l.isbn[TAM_ISBN - 1] = '\0';

        campo = strtok(NULL, ",");
        if (!campo) continue;
        l.stock = atoi(campo);

        lib->libros[lib->cantidad++] = l;
    }

    fclose(f);
    return lib->cantidad;
}

int guardarLibros(const Libreria *lib, const char *archivo) {
    FILE *f = fopen(archivo, "w");
    if (f == NULL) return -1;

    fprintf(f, "codigo_libro,titulo,clasificacion,autor_principal,isbn,stock\n");
    for (int i = 0; i < lib->cantidad; i++) {
        const Libro *l = &lib->libros[i];
        fprintf(f, "%s,%s,%s,%s,%s,%d\n",
                l->codigo, l->titulo, l->clasificacion, l->autor, l->isbn, l->stock);
    }

    fclose(f);
    return lib->cantidad;
}
