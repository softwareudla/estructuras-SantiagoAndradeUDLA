#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "opc.h"

struct Libro biblioteca[MAX_LIBROS];
int totalLibros = 0;

void registrarLibro() {
    if (totalLibros >= MAX_LIBROS) {
        printf("No se pueden registrar más libros.\n");
        return;
    }

    struct Libro nuevoLibro;

    // ID unico con validacion
    do {
        printf("Ingrese el ID del libro (mayor a 0): ");
        scanf("%d", &nuevoLibro.id);
        getchar();

        if (nuevoLibro.id <= 0) {
            printf("ID inválido. Debe ser mayor a 0.\n");
        } else if (!validarIDUnico(nuevoLibro.id)) {
            printf("El ID ya existe. Intente con otro.\n");
            nuevoLibro.id = -1; // Forzar repeticion del ciclo
        }
    } while (nuevoLibro.id <= 0);

    // Titulo
    printf("Ingrese el título del libro: ");
    fgets(nuevoLibro.titulo, sizeof(nuevoLibro.titulo), stdin);
    nuevoLibro.titulo[strcspn(nuevoLibro.titulo, "\n")] = '\0';

    // Autor
    printf("Ingrese el autor del libro: ");
    fgets(nuevoLibro.autor, sizeof(nuevoLibro.autor), stdin);
    nuevoLibro.autor[strcspn(nuevoLibro.autor, "\n")] = '\0';

    // Anio de publicacion con validacion
    do {
        printf("Ingrese el año de publicación (0 a 2025): ");
        scanf("%d", &nuevoLibro.publicado);
        getchar();

        if (nuevoLibro.publicado < 0 || nuevoLibro.publicado > 2025) {
            printf("Año inválido. Debe estar entre 0 y 2025.\n");
        }
    } while (nuevoLibro.publicado < 0 || nuevoLibro.publicado > 2025);

    // Estado inicial
    strcpy(nuevoLibro.estado, "Disponible");

    // Registro del libro
    biblioteca[totalLibros] = nuevoLibro;
    totalLibros++;

    printf("Libro registrado exitosamente.\n");
}



void mostrarLibros() {
    if (totalLibros == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\nLista de libros:\n");
    printf("ID           | Titulo                           | Autor               | Anio  | Estado\n");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < totalLibros; i++) {
        printf("%-13d| %-30s | %-20s | %-4d | %-10s\n",
               biblioteca[i].id,
               biblioteca[i].titulo,
               biblioteca[i].autor,
               biblioteca[i].publicado,
               biblioteca[i].estado);
    }
}

void buscarLibro() {
    char criterio[100];
    int esNumero = 1; // Bandera para determinar si el criterio es numrico

    printf("Ingrese el titulo o ID del libro a buscar: ");
    fgets(criterio, sizeof(criterio), stdin);
    criterio[strcspn(criterio, "\n")] = '\0';

    // Verificar si el criterio contiene solo digitos
    for (int j = 0; criterio[j] != '\0'; j++) {
        if (criterio[j] < '0' || criterio[j] > '9') {
            esNumero = 0; // No es un número
            break;
        }
    }

    // Si es un numero, convertir manualmente a entero
    int idBuscado = 0;
    if (esNumero) {
        for (int j = 0; criterio[j] != '\0'; j++) {
            idBuscado = idBuscado * 10 + (criterio[j] - '0');
        }
    }

    for (int i = 0; i < totalLibros; i++) {
        if ((esNumero && biblioteca[i].id == idBuscado) || 
            (!esNumero && strcmp(biblioteca[i].titulo, criterio) == 0)) {
            printf("\nLibro encontrado:\n");
            printf("ID: %d\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n",
                   biblioteca[i].id,
                   biblioteca[i].titulo,
                   biblioteca[i].autor,
                   biblioteca[i].publicado,
                   biblioteca[i].estado);
            return;
        }
    }
    printf("Libro no encontrado.\n");
}


void actualizarEstadoLibro() {
    int id;
    printf("Ingrese el ID del libro para cambiar su estado: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < totalLibros; i++) {
        if (biblioteca[i].id == id) {
            if (strcmp(biblioteca[i].estado, "Disponible") == 0) {
                strcpy(biblioteca[i].estado, "Prestado");
            } else {
                strcpy(biblioteca[i].estado, "Disponible");
            }
            printf("Estado actualizado exitosamente.\n");
            return;
        }
    }
    printf("Libro no encontrado.\n");
}

void eliminarLibro() {
    int id;
    printf("Ingrese el ID del libro a eliminar: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < totalLibros; i++) {
        if (biblioteca[i].id == id) {
            for (int j = i; j < totalLibros - 1; j++) {
                biblioteca[j] = biblioteca[j + 1];
            }
            totalLibros--;
            printf("Libro eliminado exitosamente.\n");
            return;
        }
    }
    printf("Libro no encontrado.\n");
}

int validarIDUnico(int id) {
    for (int i = 0; i < totalLibros; i++) {
        if (biblioteca[i].id == id) {
            return 0; // El ID ya existe
        }
    }
    return 1; // El ID es unico
}
