#include <string.h>
#include <ctype.h>
#include "validaciones.h"

int cadenaVacia(const char *cadena) {
    if (cadena == NULL) return 1;
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (!isspace((unsigned char)cadena[i])) return 0;
    }
    return 1;
}

int contieneComa(const char *cadena) {
    return strchr(cadena, ',') != NULL;
}

int codigoValido(const char *codigo) {
    int len = strlen(codigo);
    if (len < 1 || len > 15) return 0;
    for (int i = 0; i < len; i++) {
        if (!isalnum((unsigned char)codigo[i])) return 0;
    }
    return 1;
}

int existeCodigo(const Libreria *lib, const char *codigo, int excluir) {
    for (int i = 0; i < lib->cantidad; i++) {
        if (i != excluir && strcmp(lib->libros[i].codigo, codigo) == 0) return 1;
    }
    return 0;
}

int existeISBN(const Libreria *lib, const char *isbn, int excluir) {
    for (int i = 0; i < lib->cantidad; i++) {
        if (i != excluir && strcmp(lib->libros[i].isbn, isbn) == 0) return 1;
    }
    return 0;
}
