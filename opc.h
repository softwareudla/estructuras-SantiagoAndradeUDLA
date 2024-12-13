#ifndef OPC_H
#define OPC_H

#define MAX_LIBROS 20

struct Libro {
    int id;                    
    char titulo[100];
    char autor[50];
    int publicado;       
    char estado[20];     
};

extern struct Libro biblioteca[MAX_LIBROS];
extern int totalLibros;

// Prototipos de funciones
void registrarLibro();
void mostrarLibros();
void buscarLibro();
void actualizarEstadoLibro();
void eliminarLibro();
int validarIDUnico(int id);

#endif
