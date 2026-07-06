#include <stdio.h>
#include "libro.h"
#include "stock.h"
#include "reportes.h"
#include "persistencia.h"
#include "util.h"

#define ARCHIVO "libros.csv"

static void menuStock(Libreria *lib) {
    printf("\n--- CONTROL DE STOCK ---\n");
    printf("1. Consultar stock\n");
    printf("2. Actualizar stock\n");
    int op = leerEntero("Opcion: ");
    if (op == 1) consultarStock(lib);
    else if (op == 2) actualizarStock(lib);
    else printf("Opcion invalida.\n");
}

static void menuReportes(const Libreria *lib) {
    printf("\n--- REPORTES ---\n");
    printf("1. Libros agotados\n");
    printf("2. Libros con stock bajo\n");
    int op = leerEntero("Opcion: ");
    if (op == 1) librosAgotados(lib);
    else if (op == 2) librosStockBajo(lib);
    else printf("Opcion invalida.\n");
}

int main(void) {
    Libreria lib;
    lib.cantidad = 0;

    int cargados = cargarLibros(&lib, ARCHIVO);
    if (cargados > 0) {
        printf("Se cargaron %d libro(s) desde %s\n", cargados, ARCHIVO);
    }

    int opcion;
    do {
        printf("\n===== GESTION DE LIBROS =====\n");
        printf("1. Registrar libro\n");
        printf("2. Listar libros\n");
        printf("3. Buscar libro\n");
        printf("4. Actualizar libro\n");
        printf("5. Eliminar libro\n");
        printf("6. Consultar stock\n");
        printf("7. Reportes\n");
        printf("8. Guardar cambios\n");
        printf("9. Salir\n");
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: registrarLibro(&lib); break;
            case 2: listarLibros(&lib); break;
            case 3: buscarLibro(&lib); break;
            case 4: actualizarLibro(&lib); break;
            case 5: eliminarLibro(&lib); break;
            case 6: menuStock(&lib); break;
            case 7: menuReportes(&lib); break;
            case 8:
                if (guardarLibros(&lib, ARCHIVO) >= 0) printf("Cambios guardados en %s\n", ARCHIVO);
                else printf("Error al guardar.\n");
                break;
            case 9:
                if (guardarLibros(&lib, ARCHIVO) >= 0) printf("Cambios guardados. Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 9);

    return 0;
}
