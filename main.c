#include <stdio.h>
#include "opc.h"

int main() {
    int opcion;
    do {
        printf("\n--- Sistema de Gestion de Biblioteca ---\n");
        printf("1. Registrar libro\n");
        printf("2. Mostrar lista de libros\n");
        printf("3. Buscar libro (por titulo o ID)\n");
        printf("4. Cambiar estado de un libro\n");
        printf("5. Eliminar libro\n");
        printf("6. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer

        switch (opcion) {
            case 1: registrarLibro(); break;
            case 2: mostrarLibros(); break;
            case 3: buscarLibro(); break;
            case 4: actualizarEstadoLibro(); break;
            case 5: eliminarLibro(); break;
            case 6: printf("Saliendo del programa.\n"); break;
            default: printf("Opcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 6);
    
    return 0;
}
