#include <stdio.h>
#include "reportes.h"
#include "util.h"

void librosAgotados(const Libreria *lib) {
    if (lib->cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }
    int cont = 0;
    imprimirEncabezado();
    for (int i = 0; i < lib->cantidad; i++) {
        if (lib->libros[i].stock == 0) {
            imprimirLibro(&lib->libros[i]);
            cont++;
        }
    }
    if (cont == 0) printf("No hay libros agotados.\n");
    else printf("\n%d libro(s) agotado(s).\n", cont);
}

void librosStockBajo(const Libreria *lib) {
    if (lib->cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }
    int limite = leerEntero("Mostrar libros con stock menor a: ");
    int cont = 0;
    imprimirEncabezado();
    for (int i = 0; i < lib->cantidad; i++) {
        if (lib->libros[i].stock < limite) {
            imprimirLibro(&lib->libros[i]);
            cont++;
        }
    }
    if (cont == 0) printf("No hay libros por debajo de ese nivel.\n");
    else printf("\n%d libro(s) con stock bajo.\n", cont);
}