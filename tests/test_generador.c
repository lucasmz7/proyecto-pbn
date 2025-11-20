#include <stdio.h>
#include <stdio.h>
#include "../include/database.h"
#include "../include/generador.h"
#include "test_utils.h"

void test_generador() {
    ListadoEstudiantes* estudiantes = crear_listado_estudiantes();
    ListadoMaterias* materias = crear_listado_materias();
    
    int res = generador(&estudiantes, &materias, 10, 5);
    
    ASSERT("El generador debería retornar 0", res == 0);
    ASSERT("Debería haber 10 estudiantes", cantidad_estudiantes(estudiantes) == 10);
    ASSERT("Debería haber 5 materias", cantidad_materias(materias) == 5);
    
}

int main() {
    printf("Ejecutando tests para generador.c...\n");
    RUN_TEST(test_generador);
    print_test_summary();
    return tests_failed != 0;
}
