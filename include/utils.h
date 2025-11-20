#ifndef UTILS_H
#define UTILS_H

#include "estudiante.h"
#include "database.h"

typedef struct
{
    Estudiante **arr;
    int capacidad;
    int tamano;
} Heap;

typedef struct
{
    MateriaGlobal **arr;
    int capacidad;
    int tamano;
} HeapMaterias;

Heap *crearHeap(int capacidad);
void intercambiar_estudiante(Estudiante **a, Estudiante **b);
void liberarHeap(Heap *heap);
void min_heapify(Heap *heap, int i);
void insertar_min_heap(Heap *heap, Estudiante *estudiante);
Estudiante *extraer_minimo_min_heap(Heap *heap);
Estudiante *obtener_minimo_min_heap(Heap *heap);
void max_heapify(Heap *heap, int i);
void insertar_max_heap(Heap *heap, Estudiante *estudiante);
Estudiante *extraer_maximo_max_heap(Heap *heap);
Estudiante *obtener_maximo_max_heap(Heap *heap);
Estudiante **encontrar_k_mejores_promedios(ListadoEstudiantes *lista, int k);
Estudiante **encontrar_k_peores_promedios(ListadoEstudiantes *lista, int k);
void imprimir_k_mejores_estudiantes(ListadoEstudiantes *estudiantes, int k);
void imprimir_k_peores_estudiantes(ListadoEstudiantes *estudiantes, int k);

void min_heapify_cursadas(Heap *heap, int i);
void insertar_min_heap_cursadas(Heap *heap, Estudiante *estudiante);
Estudiante *extraer_minimo_min_heap_cursadas(Heap *heap);
Estudiante *obtener_minimo_min_heap_cursadas(Heap *heap);
Estudiante **encontrar_k_estudiantes_mas_cursadas(ListadoEstudiantes *lista, int k);
void imprimir_k_estudiantes_mas_cursadas(ListadoEstudiantes *estudiantes, int k);

HeapMaterias *crearHeapMaterias(int capacidad);
void liberarHeapMaterias(HeapMaterias *heap);
MateriaGlobal **encontrar_k_materias_mas_cursadas(ListadoMaterias *lista, int k);
MateriaGlobal **encontrar_k_materias_menos_cursadas(ListadoMaterias *lista, int k);
void imprimir_k_materias_mas_cursadas(ListadoMaterias *materias, int k);
void imprimir_k_materias_menos_cursadas(ListadoMaterias *materias, int k);

#endif
