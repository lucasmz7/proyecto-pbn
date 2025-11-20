#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/database.h"
#include "../include/persistencia.h"
#include "test_utils.h"

void test_persistencia() {
    const char* filename = "test_data.json";
    
    // Crear datos
    ListadoEstudiantes* estudiantes = crear_listado_estudiantes();
    agregar_estudiante(&estudiantes, 111111, 20, "Test User");
    
    ListadoMaterias* materias = crear_listado_materias();
    agregar_materia(&materias, "TST101", "Test Subject");
    
    // Guardar
    guardar_datos(materias, estudiantes, filename);
    
    // Cargar
    ListadoEstudiantes* estudiantes_loaded = NULL;
    ListadoMaterias* materias_loaded = NULL;
    
    cargar_datos(filename, &materias_loaded, &estudiantes_loaded);
    
    // Verificar
    ASSERT("Los estudiantes cargados no deberían ser NULL", estudiantes_loaded != NULL);
    ASSERT("Las materias cargadas no deberían ser NULL", materias_loaded != NULL);
    
    ASSERT("Debería haber 1 estudiante", cantidad_estudiantes(estudiantes_loaded) == 1);
    ASSERT("Debería haber 1 materia", cantidad_materias(materias_loaded) == 1);
    
    Estudiante* e = buscar_por_legajo(estudiantes_loaded, 111111);
    ASSERT("Debería encontrar el estudiante cargado", e != NULL);
    ASSERT("El nombre del estudiante cargado coincide", strcmp(e->nombre, "Test User") == 0);
    
    MateriaGlobal* m = buscar_por_identificador(materias_loaded, "TST101");
    ASSERT("Debería encontrar la materia cargada", m != NULL);
    ASSERT("El nombre de la materia cargada coincide", strcmp(m->nombre, "Test Subject") == 0);
    
    // Limpieza
    remove(filename);
    // Liberar listas...
}

int main() {
    printf("Ejecutando tests para persistencia.c...\n");
    RUN_TEST(test_persistencia);
    print_test_summary();
    return tests_failed != 0;
}
