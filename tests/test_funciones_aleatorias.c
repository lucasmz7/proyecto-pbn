#include <stdio.h>
#include <stdlib.h>
#include "include/database.h"
#include "include/generador.h"
#include <time.h>

int main() {
    srand(time(NULL));
    
    ListadoEstudiantes *estudiantes = crear_listado_estudiantes();
    ListadoMaterias *materias = crear_listado_materias();
    
    printf("Generando 5 estudiantes y 10 materias...\n\n");
    generador(&estudiantes, &materias, 5, 10);
    
    printf("\n=== PRUEBA DE FUNCIONES ALEATORIAS ===\n\n");
    
    ListadoEstudiantes *actual = estudiantes;
    int num_estudiante = 1;
    
    while (actual != NULL) {
        Estudiante *e = actual->data;
        printf("--- Estudiante %d: %s (Legajo: %d) ---\n", num_estudiante, e->nombre, e->legajo);
        
        int anotadas = anotar_estudiante_materias_aleatorias(e, materias);
        printf("  ✓ Anotado en %d materias\n", anotadas);
        
        if (e->cursadas != NULL) {
            printf("  Cursadas actuales:\n");
            ListadoCursadas *c = e->cursadas;
            while (c != NULL) {
                printf("    - %s\n", c->data->referencia->nombre);
                c = c->siguiente;
            }
        }
        
        int rendidas = rendir_materias_aleatorias(e);
        printf("  ✓ Rindió %d materias\n", rendidas);
        printf("  Promedio actual: %.2f\n", e->promedio);
        
        if (e->regulares != NULL) {
            printf("  Materias aprobadas:\n");
            ListadoCursadas *r = e->regulares;
            while (r != NULL) {
                printf("    - %s (Nota: %.0f)\n", r->data->referencia->nombre, r->data->nota);
                r = r->siguiente;
            }
        }
        
        printf("\n");
        actual = actual->siguiente;
        num_estudiante++;
    }
    
    printf("=== FIN DE LA PRUEBA ===\n");
    
    return 0;
}
