#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "libro.h"
#include "validaciones.h"
#include "util.h"

static int contieneIgnoreCase(const char *texto, const char *patron) {
    size_t lt = strlen(texto);
    size_t lp = strlen(patron);
    if (lp == 0) return 1;
    if (lp > lt) return 0;
    for (size_t i = 0; i + lp <= lt; i++) {
        size_t j = 0;
        while (j < lp && tolower((unsigned char)texto[i + j]) == tolower((unsigned char)patron[j])) {
            j++;
        }
        if (j == lp) return 1;
    }
    return 0;
}

void imprimirEncabezado(void) {
    printf("\n%-15s %-30s %-15s %-25s %-15s %-6s\n",
           "CODIGO", "TITULO", "CLASIFICACION", "AUTOR", "ISBN", "STOCK");
    printf("--------------------------------------------------------------------------------------------------------------\n");
}

void imprimirLibro(const Libro *l) {
    printf("%-15s %-30s %-15s %-25s %-15s %-6d\n",
           l->codigo, l->titulo, l->clasificacion, l->autor, l->isbn, l->stock);
}

int buscarPorCodigo(const Libreria *lib, const char *codigo) {
    for (int i = 0; i < lib->cantidad; i++) {
        if (strcmp(lib->libros[i].codigo, codigo) == 0) return i;
    }
    return -1;
}

void registrarLibro(Libreria *lib) {
    if (lib->cantidad >= MAX_LIBROS) {
        printf("Capacidad maxima alcanzada.\n");
        return;
    }

    Libro nuevo;

    while (1) {
        leerLinea("Codigo (1-15 alfanumerico, sin espacios): ", nuevo.codigo, TAM_CODIGO);
        if (!codigoValido(nuevo.codigo)) {
            printf("Codigo invalido. Use solo letras/numeros, longitud 1-15.\n");
            continue;
        }
        if (existeCodigo(lib, nuevo.codigo, -1)) {
            printf("El codigo ya existe. Ingrese otro.\n");
            continue;
        }
        break;
    }

    while (1) {
        leerLinea("Titulo: ", nuevo.titulo, TAM_TITULO);
        if (cadenaVacia(nuevo.titulo)) { printf("El titulo no puede estar vacio.\n"); continue; }
        if (contieneComa(nuevo.titulo)) { printf("No use comas.\n"); continue; }
        break;
    }

    while (1) {
        leerLinea("Clasificacion: ", nuevo.clasificacion, TAM_CLASIFICACION);
        if (cadenaVacia(nuevo.clasificacion)) { printf("La clasificacion no puede estar vacia.\n"); continue; }
        if (contieneComa(nuevo.clasificacion)) { printf("No use comas.\n"); continue; }
        break;
    }

    while (1) {
        leerLinea("Autor principal: ", nuevo.autor, TAM_AUTOR);
        if (cadenaVacia(nuevo.autor)) { printf("El autor no puede estar vacio.\n"); continue; }
        if (contieneComa(nuevo.autor)) { printf("No use comas.\n"); continue; }
        break;
    }

    while (1) {
        leerLinea("ISBN: ", nuevo.isbn, TAM_ISBN);
        if (cadenaVacia(nuevo.isbn)) { printf("El ISBN es obligatorio.\n"); continue; }
        if (contieneComa(nuevo.isbn)) { printf("No use comas.\n"); continue; }
        if (existeISBN(lib, nuevo.isbn, -1)) { printf("El ISBN ya existe.\n"); continue; }
        break;
    }

    while (1) {
        nuevo.stock = leerEntero("Stock (>= 0): ");
        if (nuevo.stock < 0) { printf("El stock no puede ser negativo.\n"); continue; }
        break;
    }

    lib->libros[lib->cantidad] = nuevo;
    lib->cantidad++;
    printf("Libro registrado correctamente.\n");
}
