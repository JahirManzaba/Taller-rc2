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

void listarLibros(const Libreria *lib) {
    if (lib->cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }
    imprimirEncabezado();
    for (int i = 0; i < lib->cantidad; i++) {
        imprimirLibro(&lib->libros[i]);
    }
    printf("\nTotal: %d libro(s).\n", lib->cantidad);
}

void buscarLibro(const Libreria *lib) {
    if (lib->cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\nBuscar por:\n");
    printf("1. Codigo\n");
    printf("2. Titulo\n");
    printf("3. Clasificacion\n");
    printf("4. Autor\n");
    printf("5. ISBN\n");
    int op = leerEntero("Opcion: ");

    if (op < 1 || op > 5) {
        printf("Opcion invalida.\n");
        return;
    }

    char criterio[TAM_TITULO];
    leerLinea("Ingrese el valor a buscar: ", criterio, sizeof(criterio));

    int encontrados = 0;
    imprimirEncabezado();
    for (int i = 0; i < lib->cantidad; i++) {
        const Libro *l = &lib->libros[i];
        int coincide = 0;
        switch (op) {
            case 1: coincide = (strcmp(l->codigo, criterio) == 0); break;
            case 2: coincide = contieneIgnoreCase(l->titulo, criterio); break;
            case 3: coincide = contieneIgnoreCase(l->clasificacion, criterio); break;
            case 4: coincide = contieneIgnoreCase(l->autor, criterio); break;
            case 5: coincide = (strcmp(l->isbn, criterio) == 0); break;
        }
        if (coincide) {
            imprimirLibro(l);
            encontrados++;
        }
    }
    if (encontrados == 0) printf("No se encontraron coincidencias.\n");
    else printf("\n%d coincidencia(s).\n", encontrados);
}

void actualizarLibro(Libreria *lib) {
    if (lib->cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    char codigo[TAM_CODIGO];
    leerLinea("Codigo del libro a actualizar: ", codigo, TAM_CODIGO);
    int idx = buscarPorCodigo(lib, codigo);
    if (idx == -1) {
        printf("No existe un libro con ese codigo.\n");
        return;
    }

    Libro *l = &lib->libros[idx];
    printf("\nDeje el campo vacio para conservar el valor actual.\n");

    char prompt[220];
    char entrada[TAM_TITULO];

    while (1) {
        snprintf(prompt, sizeof(prompt), "Codigo [%s]: ", l->codigo);
        leerLinea(prompt, entrada, TAM_CODIGO);
        if (cadenaVacia(entrada)) break;
        if (!codigoValido(entrada)) { printf("Codigo invalido.\n"); continue; }
        if (existeCodigo(lib, entrada, idx)) { printf("Ese codigo ya existe.\n"); continue; }
        strcpy(l->codigo, entrada);
        break;
    }

    while (1) {
        snprintf(prompt, sizeof(prompt), "Titulo [%s]: ", l->titulo);
        leerLinea(prompt, entrada, TAM_TITULO);
        if (cadenaVacia(entrada)) break;
        if (contieneComa(entrada)) { printf("No use comas.\n"); continue; }
        strcpy(l->titulo, entrada);
        break;
    }

    while (1) {
        snprintf(prompt, sizeof(prompt), "Clasificacion [%s]: ", l->clasificacion);
        leerLinea(prompt, entrada, TAM_CLASIFICACION);
        if (cadenaVacia(entrada)) break;
        if (contieneComa(entrada)) { printf("No use comas.\n"); continue; }
        strcpy(l->clasificacion, entrada);
        break;
    }

    while (1) {
        snprintf(prompt, sizeof(prompt), "Autor [%s]: ", l->autor);
        leerLinea(prompt, entrada, TAM_AUTOR);
        if (cadenaVacia(entrada)) break;
        if (contieneComa(entrada)) { printf("No use comas.\n"); continue; }
        strcpy(l->autor, entrada);
        break;
    }

    while (1) {
        snprintf(prompt, sizeof(prompt), "ISBN [%s]: ", l->isbn);
        leerLinea(prompt, entrada, TAM_ISBN);
        if (cadenaVacia(entrada)) break;
        if (contieneComa(entrada)) { printf("No use comas.\n"); continue; }
        if (existeISBN(lib, entrada, idx)) { printf("Ese ISBN ya existe.\n"); continue; }
        strcpy(l->isbn, entrada);
        break;
    }

    while (1) {
        snprintf(prompt, sizeof(prompt), "Stock [%d] (-1 para conservar): ", l->stock);
        int s = leerEntero(prompt);
        if (s == -1) break;
        if (s < 0) { printf("El stock no puede ser negativo.\n"); continue; }
        l->stock = s;
        break;
    }

    printf("Libro actualizado.\n");
}

void eliminarLibro(Libreria *lib) {
    if (lib->cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    char codigo[TAM_CODIGO];
    leerLinea("Codigo del libro a eliminar: ", codigo, TAM_CODIGO);
    int idx = buscarPorCodigo(lib, codigo);
    if (idx == -1) {
        printf("No existe un libro con ese codigo.\n");
        return;
    }

    imprimirEncabezado();
    imprimirLibro(&lib->libros[idx]);

    char conf[8];
    leerLinea("\nConfirma eliminacion? (s/n): ", conf, sizeof(conf));
    if (conf[0] == 's' || conf[0] == 'S') {
        for (int i = idx; i < lib->cantidad - 1; i++) {
            lib->libros[i] = lib->libros[i + 1];
        }
        lib->cantidad--;
        printf("Libro eliminado.\n");
    } else {
        printf("Operacion cancelada.\n");
    }
}
