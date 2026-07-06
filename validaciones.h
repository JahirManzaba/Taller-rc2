#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include "libro.h"

int cadenaVacia(const char *cadena);
int contieneComa(const char *cadena);
int codigoValido(const char *codigo);
int existeCodigo(const Libreria *lib, const char *codigo, int excluir);
int existeISBN(const Libreria *lib, const char *isbn, int excluir);

#endif
