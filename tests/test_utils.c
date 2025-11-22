#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"
#include "../include/database.h"
#include "../include/estudiante.h"
#include "test_utils.h"

Estudiante* crear_estudiante_con_promedio(float promedio) {
    Estudiante* e = (Estudiante*)malloc(sizeof(Estudiante));
    e->promedio = promedio;
    return e;
}

MateriaGlobal* crear_materia_dummy(const char* nombre, int cursantes) {
    MateriaGlobal* m = (MateriaGlobal*)malloc(sizeof(MateriaGlobal));
    strcpy(m->nombre, nombre);
    strcpy(m->identificador, "TST");
    m->cursantes = cursantes;
    return m;
}

Estudiante* crear_estudiante_dummy(const char* nombre, int n_cursadas) {
    Estudiante* e = (Estudiante*)malloc(sizeof(Estudiante));
    strcpy(e->nombre, nombre);
    e->legajo = 123;
    e->edad = 20;
    e->promedio = 0.0;
    e->cursadas = NULL;
    e->regulares = NULL;

    for (int i = 0; i < n_cursadas; i++) {
        Cursada* c = (Cursada*)malloc(sizeof(Cursada));
        c->estado = REGULAR_APROBADA;
        ListadoCursadas* nodo = (ListadoCursadas*)malloc(sizeof(ListadoCursadas));
        nodo->data = c;
        nodo->siguiente = e->regulares;
        e->regulares = nodo;
    }
    return e;
}

void test_min_heap() {
    Heap* h = crearHeap(10);
    
    insertar_min_heap(h, crear_estudiante_con_promedio(5.0));
    insertar_min_heap(h, crear_estudiante_con_promedio(3.0));
    insertar_min_heap(h, crear_estudiante_con_promedio(8.0));
    
    Estudiante* min = extraer_minimo_min_heap(h);
    ASSERT("El mínimo debería ser 3.0", min->promedio == 3.0);
    free(min);
    
    min = extraer_minimo_min_heap(h);
    ASSERT("El siguiente mínimo debería ser 5.0", min->promedio == 5.0);
    free(min);
    
    min = extraer_minimo_min_heap(h);
    ASSERT("El último mínimo debería ser 8.0", min->promedio == 8.0);
    free(min);
    
    liberarHeap(h);
}

void test_max_heap() {
    Heap* h = crearHeap(10);
    
    insertar_max_heap(h, crear_estudiante_con_promedio(5.0));
    insertar_max_heap(h, crear_estudiante_con_promedio(3.0));
    insertar_max_heap(h, crear_estudiante_con_promedio(8.0));
    
    Estudiante* max = extraer_maximo_max_heap(h);
    ASSERT("El máximo debería ser 8.0", max->promedio == 8.0);
    free(max);
    
    max = extraer_maximo_max_heap(h);
    ASSERT("El siguiente máximo debería ser 5.0", max->promedio == 5.0);
    free(max);
    
    max = extraer_maximo_max_heap(h);
    ASSERT("El último máximo debería ser 3.0", max->promedio == 3.0);
    free(max);
    
    liberarHeap(h);
}

void test_heap_materias() {
    ListadoMaterias* lista = crear_listado_materias();
    
    MateriaGlobal* m1 = crear_materia_dummy("Matematica", 100);
    MateriaGlobal* m2 = crear_materia_dummy("Fisica", 50);
    MateriaGlobal* m3 = crear_materia_dummy("Quimica", 150);
    MateriaGlobal* m4 = crear_materia_dummy("Biologia", 20);
    
    ListadoMaterias* n1 = malloc(sizeof(ListadoMaterias)); n1->data = m1;
    ListadoMaterias* n2 = malloc(sizeof(ListadoMaterias)); n2->data = m2;
    ListadoMaterias* n3 = malloc(sizeof(ListadoMaterias)); n3->data = m3;
    ListadoMaterias* n4 = malloc(sizeof(ListadoMaterias)); n4->data = m4;
    
    n1->siguiente = n2;
    n2->siguiente = n3;
    n3->siguiente = n4;
    n4->siguiente = NULL;
    
    lista = n1;
    
    MateriaGlobal** mas_cursadas = encontrar_k_materias_mas_cursadas(lista, 2);
    ASSERT("La más cursada 1 debería ser Quimica", strcmp(mas_cursadas[0]->nombre, "Quimica") == 0);
    ASSERT("La más cursada 2 debería ser Matematica", strcmp(mas_cursadas[1]->nombre, "Matematica") == 0);
    free(mas_cursadas);
    
    MateriaGlobal** menos_cursadas = encontrar_k_materias_menos_cursadas(lista, 2);
    ASSERT("La menos cursada 1 debería ser Biologia", strcmp(menos_cursadas[0]->nombre, "Biologia") == 0);
    ASSERT("La menos cursada 2 debería ser Fisica", strcmp(menos_cursadas[1]->nombre, "Fisica") == 0);
    free(menos_cursadas);
    
    free(n1); free(n2); free(n3); free(n4);
    free(m1); free(m2); free(m3); free(m4);
}

void test_heap_estudiantes_cursadas() {
    ListadoEstudiantes* lista = NULL;
    
    Estudiante* e1 = crear_estudiante_dummy("Juan", 5);
    Estudiante* e2 = crear_estudiante_dummy("Maria", 10);
    Estudiante* e3 = crear_estudiante_dummy("Pedro", 2);
    
    ListadoEstudiantes* n1 = malloc(sizeof(ListadoEstudiantes)); n1->data = e1;
    ListadoEstudiantes* n2 = malloc(sizeof(ListadoEstudiantes)); n2->data = e2;
    ListadoEstudiantes* n3 = malloc(sizeof(ListadoEstudiantes)); n3->data = e3;
    
    n1->siguiente = n2;
    n2->siguiente = n3;
    n3->siguiente = NULL;
    
    lista = n1;
    
    Estudiante** mas_cursadas = encontrar_k_estudiantes_mas_cursadas(lista, 2);
    ASSERT("El estudiante con más cursadas 1 debería ser Maria", strcmp(mas_cursadas[0]->nombre, "Maria") == 0);
    ASSERT("El estudiante con más cursadas 2 debería ser Juan", strcmp(mas_cursadas[1]->nombre, "Juan") == 0);
    free(mas_cursadas);
    
    free(n1); free(n2); free(n3);
    free(e1); free(e2); free(e3);
}

int main() {
    printf("Ejecutando tests para utils.c...\n");
    RUN_TEST(test_min_heap);
    RUN_TEST(test_max_heap);
    RUN_TEST(test_heap_materias);
    RUN_TEST(test_heap_estudiantes_cursadas);
    print_test_summary();
    return tests_failed != 0;
}
