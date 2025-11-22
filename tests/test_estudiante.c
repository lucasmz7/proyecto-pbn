#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/estudiante.h"
#include "../include/database.h" 
#include "test_utils.h"

Estudiante* crear_estudiante_dummy() {
    Estudiante* e = (Estudiante*)malloc(sizeof(Estudiante));
    strcpy(e->nombre, "Juan Perez");
    e->legajo = 123456;
    e->edad = 20;
    e->cursadas = NULL;
    e->regulares = NULL;
    e->promedio = 0.0;
    return e;
}

void test_estudiante_modificar_datos() {
    Estudiante* e = crear_estudiante_dummy();
    
    estudiante_modificar_nombre(e, "Maria Lopez");
    ASSERT("El nombre debería ser Maria Lopez", strcmp(e->nombre, "Maria Lopez") == 0);
    
    estudiante_modificar_legajo(e, 654321);
    ASSERT("El legajo debería ser 654321", e->legajo == 654321);
    
    estudiante_modificar_edad(e, 21);
    ASSERT("La edad debería ser 21", e->edad == 21);
    
    free(e);
}

void test_anotar_y_bajar() {
    Estudiante* e = crear_estudiante_dummy();
    ListadoMaterias* materias = crear_listado_materias();
    agregar_materia(&materias, "MAT1", "Matematica I", 0);
    
    int res = anotar(e, materias, "Matematica I");
    ASSERT("anotar() debería retornar 0 (éxito)", res == 0);
    ASSERT("ListadoCursadas no debería ser NULL", e->cursadas != NULL);
    ASSERT("El nombre de la materia cursada debería ser Matematica I", strcmp(e->cursadas->data->referencia->nombre, "Matematica I") == 0);
    
    res = bajar(e, "Matematica I");
    ASSERT("bajar() debería retornar 0 (éxito)", res == 0);
    ASSERT("ListadoCursadas debería ser NULL después de bajar", e->cursadas == NULL);
    
    free(e);
}

void test_rendir_final() {
    Estudiante* e = crear_estudiante_dummy();
    ListadoMaterias* materias = crear_listado_materias();
    agregar_materia(&materias, "MAT1", "Matematica I", 0);
    
    anotar(e, materias, "Matematica I");
    
    int res = rendir_final(e, "Matematica I", 8.0);
    ASSERT("rendir_final() debería retornar 0", res == 0);
    ASSERT("El promedio debería ser 8.0", e->promedio == 8.0);
    ASSERT("ListadoCursadas no debería ser NULL", e->regulares != NULL);
    ASSERT("La nota debería ser 8.0", e->regulares->data->nota == 8.0);
    
    agregar_materia(&materias, "FIS1", "Fisica I", 0);
    anotar(e, materias, "Fisica I");
    rendir_final(e, "Fisica I", 6.0);
    
    ASSERT("El promedio debería ser 7.0", e->promedio == 7.0);
    
    free(e);
}

int main() {
    printf("Ejecutando tests para estudiante.c...\n");
    RUN_TEST(test_estudiante_modificar_datos);
    RUN_TEST(test_anotar_y_bajar);
    RUN_TEST(test_rendir_final);
    print_test_summary();
    return tests_failed != 0;
}
