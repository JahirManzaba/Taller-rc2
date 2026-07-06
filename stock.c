#include <stdio.h>
#include "stock.h"
#include "util.h"

void consultarStock(const Libreria *lib) {
    if (lib->cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }
    printf("\n%-15s %-30s %-6s\n", "CODIGO", "TITULO", "STOCK");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < lib->cantidad; i++) {
        printf("%-15s %-30s %-6d\n",
               lib->libros[i].codigo, lib->libros[i].titulo, lib->libros[i].stock);
    }
}

void actualizarStock(Libreria *lib) {
    if (lib->cantidad == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    char codigo[TAM_CODIGO];
    leerLinea("Codigo del libro: ", codigo, TAM_CODIGO);
    int idx = buscarPorCodigo(lib, codigo);
    if (idx == -1) {
        printf("No existe un libro con ese codigo.\n");
        return;
    }

    printf("Stock actual: %d\n", lib->libros[idx].stock);
    printf("1. Incrementar\n");
    printf("2. Disminuir\n");
    int op = leerEntero("Opcion: ");
    int cant = leerEntero("Cantidad: ");
    if (cant < 0) {
        printf("Cantidad invalida.\n");
        return;
    }

    if (op == 1) {
        lib->libros[idx].stock += cant;
    } else if (op == 2) {
        if (cant > lib->libros[idx].stock) {
            printf("No puede disminuir mas del stock disponible.\n");
            return;
        }
        lib->libros[idx].stock -= cant;
    } else {
        printf("Opcion invalida.\n");
        return;
    }

    printf("Stock actualizado: %d\n", lib->libros[idx].stock);
}