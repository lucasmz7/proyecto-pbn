#include <stdio.h>
#include <string.h>
#include "../include/materia.h"
#include "test_utils.h"

void test_materia_modificar_nombre() {
    MateriaGlobal m;
    strcpy(m.nombre, "Matematica");
    
    materia_modificar_nombre(&m, "Fisica");
    ASSERT("El nombre de la materia debería ser Fisica", strcmp(m.nombre, "Fisica") == 0);
}

void test_materia_modificar_identificador() {
    MateriaGlobal m;
    strcpy(m.identificador, "MAT101");
    
    materia_modificar_identificador(&m, "FIS101");
    ASSERT("El identificador de la materia debería ser FIS101", strcmp(m.identificador, "FIS101") == 0);
}

int main() {
    printf("Ejecutando tests para materia.c...\n");
    RUN_TEST(test_materia_modificar_nombre);
    RUN_TEST(test_materia_modificar_identificador);
    print_test_summary();
    return tests_failed != 0;
}
