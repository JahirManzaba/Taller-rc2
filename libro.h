#ifndef LIBRO_H
#define LIBRO_H

#define MAX_LIBROS 1000
#define TAM_CODIGO 16
#define TAM_TITULO 120
#define TAM_CLASIFICACION 50
#define TAM_AUTOR 120
#define TAM_ISBN 25

typedef struct {
    char codigo[TAM_CODIGO];
    char titulo[TAM_TITULO];
    char clasificacion[TAM_CLASIFICACION];
    char autor[TAM_AUTOR];
    char isbn[TAM_ISBN];
    int stock;
} Libro;

typedef struct {
    Libro libros[MAX_LIBROS];
    int cantidad;
} Libreria;

int buscarPorCodigo(const Libreria *lib, const char *codigo);
void registrarLibro(Libreria *lib);
void listarLibros(const Libreria *lib);
void buscarLibro(const Libreria *lib);
void actualizarLibro(Libreria *lib);
void eliminarLibro(Libreria *lib);
void imprimirEncabezado(void);
void imprimirLibro(const Libro *l);

#endif
