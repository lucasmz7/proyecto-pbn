#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/database.h"
#include "test_utils.h"

void test_estudiantes_crud() {
    ListadoEstudiantes* lista = crear_listado_estudiantes();
    ASSERT("La lista debería ser NULL inicialmente", lista == NULL);
    
    int res = agregar_estudiante(&lista, 123456, 20, "Juan Perez", 0);
    ASSERT("Agregar estudiante debería retornar 0", res == 0);
    ASSERT("La lista no debería ser NULL", lista != NULL);
    ASSERT("La cantidad de estudiantes debería ser 1", cantidad_estudiantes(lista) == 1);
    
    res = agregar_estudiante(&lista, 654321, 22, "Maria Lopez", 0);
    ASSERT("Agregar estudiante 2 debería retornar 0", res == 0);
    ASSERT("La cantidad de estudiantes debería ser 2", cantidad_estudiantes(lista) == 2);
    
    Estudiante* e = buscar_por_legajo(lista, 123456, 0);
    ASSERT("Debería encontrar el estudiante por legajo", e != NULL);
    ASSERT("El nombre del estudiante debería ser Juan Perez", strcmp(e->nombre, "Juan Perez") == 0);
    
    res = eliminar_estudiante(&lista, 123456);
    ASSERT("Eliminar estudiante debería retornar 0", res == 0);
    ASSERT("La cantidad de estudiantes debería ser 1", cantidad_estudiantes(lista) == 1);
    
    e = buscar_por_legajo(lista, 123456, 0);
    ASSERT("No debería encontrar el estudiante eliminado", e == NULL);
    
    while(lista != NULL) {
        ListadoEstudiantes* next = lista->siguiente;
        free(lista->data);
        free(lista);
        lista = next;
    }
}

void test_materias_crud() {
    ListadoMaterias* lista = crear_listado_materias();
    
    int res = agregar_materia(&lista, "MAT101", "Matematica I", 0);
    ASSERT("Agregar materia debería retornar 0", res == 0);
    ASSERT("La cantidad de materias debería ser 1", cantidad_materias(lista) == 1);
    
    MateriaGlobal* m = buscar_por_identificador(lista, "MAT101", 0);
    ASSERT("Debería encontrar la materia por id", m != NULL);
    ASSERT("El nombre de la materia debería ser Matematica I", strcmp(m->nombre, "Matematica I") == 0);
    
    m = buscar_materia_por_nombre(lista, "Matematica I");
    ASSERT("Debería encontrar la materia por nombre", m != NULL);
    
    res = eliminar_materia(&lista, "Matematica I");
    ASSERT("Eliminar materia debería retornar 0", res == 0);
    ASSERT("La cantidad de materias debería ser 0", cantidad_materias(lista) == 0);
}

int main() {
    printf("Ejecutando tests para database.c...\n");
    RUN_TEST(test_estudiantes_crud);
    RUN_TEST(test_materias_crud);
    print_test_summary();
    return tests_failed != 0;
}
