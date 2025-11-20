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

#endif
