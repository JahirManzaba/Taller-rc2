#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "libro.h"

int cargarLibros(Libreria *lib, const char *archivo);
int guardarLibros(const Libreria *lib, const char *archivo);

#endif
