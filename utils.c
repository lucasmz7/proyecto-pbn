#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "database.h"
#include "estudiante.h"
#include "utils.h"

Heap *crearHeap(int capacidad)
{
    Heap *nuevoHeap = (Heap *)malloc(sizeof(Heap));
    if (nuevoHeap == NULL)
    {
        perror("Fallo al asignar memoria para Heap");
        exit(EXIT_FAILURE);
    }
    nuevoHeap->capacidad = capacidad;
    nuevoHeap->tamano = 0;

    nuevoHeap->arr = (Estudiante **)malloc(capacidad * sizeof(Estudiante *));
    if (nuevoHeap->arr == NULL)
    {
        perror("Fallo al asignar memoria para arr");
        free(nuevoHeap);
        exit(EXIT_FAILURE);
    }
    return nuevoHeap;
}

void intercambiar_estudiante(Estudiante **a, Estudiante **b)
{
    Estudiante *temp = *a;
    *a = *b;
    *b = temp;
}

void liberarHeap(Heap *heap)
{
    if (heap == NULL)
        return;
    free(heap->arr);
    free(heap);
}

void min_heapify(Heap *heap, int i)
{
    int mas_pequeno = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < heap->tamano && heap->arr[izquierda]->promedio < heap->arr[mas_pequeno]->promedio)
    {
        mas_pequeno = izquierda;
    }

    if (derecha < heap->tamano && heap->arr[derecha]->promedio < heap->arr[mas_pequeno]->promedio)
    {
        mas_pequeno = derecha;
    }

    if (mas_pequeno != i)
    {
        intercambiar_estudiante(&heap->arr[i], &heap->arr[mas_pequeno]);
        min_heapify(heap, mas_pequeno);
    }
}

void insertar_min_heap(Heap *heap, Estudiante *estudiante)
{
    if (heap->tamano == heap->capacidad)
    {
        printf("El Heap está lleno.\n");
        return;
    }

    int i = heap->tamano;
    heap->arr[i] = estudiante;
    heap->tamano++;

    while (i != 0 && heap->arr[(i - 1) / 2]->promedio > heap->arr[i]->promedio)
    {
        intercambiar_estudiante(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Estudiante *extraer_minimo_min_heap(Heap *heap)
{
    if (heap->tamano <= 0)
        return NULL;
    if (heap->tamano == 1)
    {
        heap->tamano--;
        return heap->arr[0];
    }

    Estudiante *raiz = heap->arr[0];
    heap->arr[0] = heap->arr[heap->tamano - 1];
    heap->tamano--;
    min_heapify(heap, 0);

    return raiz;
}

Estudiante *obtener_minimo_min_heap(Heap *heap)
{
    if (heap->tamano <= 0)
        return NULL;
    return heap->arr[0];
}

void max_heapify(Heap *heap, int i)
{
    int mas_grande = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < heap->tamano && heap->arr[izquierda]->promedio > heap->arr[mas_grande]->promedio)
    {
        mas_grande = izquierda;
    }

    if (derecha < heap->tamano && heap->arr[derecha]->promedio > heap->arr[mas_grande]->promedio)
    {
        mas_grande = derecha;
    }

    if (mas_grande != i)
    {
        intercambiar_estudiante(&heap->arr[i], &heap->arr[mas_grande]);
        max_heapify(heap, mas_grande);
    }
}

void insertar_max_heap(Heap *heap, Estudiante *estudiante)
{
    if (heap->tamano == heap->capacidad)
    {
        printf("El Heap está lleno.\n");
        return;
    }

    int i = heap->tamano;
    heap->arr[i] = estudiante;
    heap->tamano++;

    while (i != 0 && heap->arr[(i - 1) / 2]->promedio < heap->arr[i]->promedio)
    {
        intercambiar_estudiante(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Estudiante *extraer_maximo_max_heap(Heap *heap)
{
    if (heap->tamano <= 0)
        return NULL;
    if (heap->tamano == 1)
    {
        heap->tamano--;
        return heap->arr[0];
    }

    Estudiante *raiz = heap->arr[0];
    heap->arr[0] = heap->arr[heap->tamano - 1];
    heap->tamano--;
    max_heapify(heap, 0);

    return raiz;
}

Estudiante *obtener_maximo_max_heap(Heap *heap)
{
    if (heap->tamano <= 0)
        return NULL;
    return heap->arr[0];
}

Estudiante **encontrar_k_mejores_promedios(ListadoEstudiantes *lista, int k)
{
    if (k <= 0)
        return NULL;

    int n_estudiantes = cantidad_estudiantes(lista);

    if (n_estudiantes < k)
        k = n_estudiantes;
    if (n_estudiantes == 0)
    {
        printf("No hay estudiantes");
        return NULL;
    }

    Heap *min_heap = crearHeap(k);
    ListadoEstudiantes *actual = lista;

    while (actual != NULL)
    {
        Estudiante *estudiante_actual = actual->data;

        if (min_heap->tamano < k)
        {
            insertar_min_heap(min_heap, estudiante_actual);
        }
        else if (estudiante_actual->promedio > obtener_minimo_min_heap(min_heap)->promedio)
        {
            extraer_minimo_min_heap(min_heap);
            insertar_min_heap(min_heap, estudiante_actual);
        }

        actual = actual->siguiente;
    }

    Estudiante **array_estudiantes = (Estudiante **)malloc(k * sizeof(Estudiante *));
    if (array_estudiantes == NULL)
    {
        perror("Fallo al asignar memoria para array de retorno");
        liberarHeap(min_heap);
        return NULL;
    }

    for (int i = k - 1; i >= 0; i--)
    {
        array_estudiantes[i] = extraer_minimo_min_heap(min_heap);
    }

    liberarHeap(min_heap);
    return array_estudiantes;
}

Estudiante **encontrar_k_peores_promedios(ListadoEstudiantes *lista, int k)
{
    if (k <= 0)
        return NULL;

    int n_estudiantes = cantidad_estudiantes(lista);
    if (n_estudiantes < k)
        k = n_estudiantes;
    if (n_estudiantes == 0)
    {
        printf("No hay estudiantes");
        return NULL;
    }

    Heap *max_heap = crearHeap(k);
    ListadoEstudiantes *actual = lista;

    while (actual != NULL)
    {
        Estudiante *estudiante_actual = actual->data;

        if (max_heap->tamano < k)
        {
            insertar_max_heap(max_heap, estudiante_actual);
        }
        else if (estudiante_actual->promedio < obtener_maximo_max_heap(max_heap)->promedio)
        {
            extraer_maximo_max_heap(max_heap);
            insertar_max_heap(max_heap, estudiante_actual);
        }

        actual = actual->siguiente;
    }

    Estudiante **array_estudiantes = (Estudiante **)malloc(k * sizeof(Estudiante *));
    if (array_estudiantes == NULL)
    {
        perror("Fallo al asignar memoria para array de retorno");
        liberarHeap(max_heap);
        return NULL;
    }

    for (int i = 0; i < k; i++)
    {
        array_estudiantes[k - 1 - i] = extraer_maximo_max_heap(max_heap);
    }

    liberarHeap(max_heap);
    return array_estudiantes;
}

void min_heapify_cursadas(Heap *heap, int i)
{
    int mas_pequeno = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < heap->tamano && cantidad_materias_aprobadas(heap->arr[izquierda]->regulares) < cantidad_materias_aprobadas(heap->arr[mas_pequeno]->regulares))
    {
        mas_pequeno = izquierda;
    }

    if (derecha < heap->tamano && cantidad_materias_aprobadas(heap->arr[derecha]->regulares) < cantidad_materias_aprobadas(heap->arr[mas_pequeno]->regulares))
    {
        mas_pequeno = derecha;
    }

    if (mas_pequeno != i)
    {
        intercambiar_estudiante(&heap->arr[i], &heap->arr[mas_pequeno]);
        min_heapify_cursadas(heap, mas_pequeno);
    }
}

void insertar_min_heap_cursadas(Heap *heap, Estudiante *estudiante)
{
    if (heap->tamano == heap->capacidad) return;

    int i = heap->tamano;
    heap->arr[i] = estudiante;
    heap->tamano++;

    while (i != 0 && cantidad_materias_aprobadas(heap->arr[(i - 1) / 2]->regulares) > cantidad_materias_aprobadas(heap->arr[i]->regulares))
    {
        intercambiar_estudiante(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Estudiante *extraer_minimo_min_heap_cursadas(Heap *heap)
{
    if (heap->tamano <= 0) return NULL;
    if (heap->tamano == 1)
    {
        heap->tamano--;
        return heap->arr[0];
    }

    Estudiante *raiz = heap->arr[0];
    heap->arr[0] = heap->arr[heap->tamano - 1];
    heap->tamano--;
    min_heapify_cursadas(heap, 0);
    return raiz;
}

Estudiante *obtener_minimo_min_heap_cursadas(Heap *heap)
{
    if (heap->tamano <= 0) return NULL;
    return heap->arr[0];
}

/**
 * @brief Encuentra los K estudiantes con mayor cantidad de cursadas aprobadas (regulares).
 * @param lista Puntero al primer nodo de la lista de estudiantes.
 * @param k El número de estudiantes a encontrar.
 * @return Estudiante** Puntero a un array de punteros a Estudiante*, o NULL si hay error.
 */
Estudiante **encontrar_k_estudiantes_mas_cursadas(ListadoEstudiantes *lista, int k)
{
    if (k <= 0) return NULL;

    int n_estudiantes = cantidad_estudiantes(lista);
    if (n_estudiantes < k) k = n_estudiantes;
    if (n_estudiantes == 0) return NULL;

    Heap *min_heap = crearHeap(k);
    ListadoEstudiantes *actual = lista;

    while (actual != NULL)
    {
        Estudiante *estudiante_actual = actual->data;
        int cursadas_actual = cantidad_materias_aprobadas(estudiante_actual->regulares);

        if (min_heap->tamano < k)
        {
            insertar_min_heap_cursadas(min_heap, estudiante_actual);
        }
        else if (cursadas_actual > cantidad_materias_aprobadas(obtener_minimo_min_heap_cursadas(min_heap)->regulares))
        {
            extraer_minimo_min_heap_cursadas(min_heap);
            insertar_min_heap_cursadas(min_heap, estudiante_actual);
        }
        actual = actual->siguiente;
    }

    Estudiante **array_estudiantes = (Estudiante **)malloc(k * sizeof(Estudiante *));
    if (array_estudiantes == NULL)
    {
        liberarHeap(min_heap);
        return NULL;
    }

    for (int i = k - 1; i >= 0; i--)
    {
        array_estudiantes[i] = extraer_minimo_min_heap_cursadas(min_heap);
    }

    liberarHeap(min_heap);
    return array_estudiantes;
}


HeapMaterias *crearHeapMaterias(int capacidad)
{
    HeapMaterias *nuevoHeap = (HeapMaterias *)malloc(sizeof(HeapMaterias));
    if (nuevoHeap == NULL)
    {
        perror("Fallo al asignar memoria para HeapMaterias");
        exit(EXIT_FAILURE);
    }
    nuevoHeap->capacidad = capacidad;
    nuevoHeap->tamano = 0;

    nuevoHeap->arr = (MateriaGlobal **)malloc(capacidad * sizeof(MateriaGlobal *));
    if (nuevoHeap->arr == NULL)
    {
        perror("Fallo al asignar memoria para arr de materias");
        free(nuevoHeap);
        exit(EXIT_FAILURE);
    }
    return nuevoHeap;
}

void liberarHeapMaterias(HeapMaterias *heap)
{
    if (heap == NULL)
        return;
    free(heap->arr);
    free(heap);
}

void intercambiar_materia(MateriaGlobal **a, MateriaGlobal **b)
{
    MateriaGlobal *temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify_materias(HeapMaterias *heap, int i)
{
    int mas_pequeno = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < heap->tamano && heap->arr[izquierda]->cursantes < heap->arr[mas_pequeno]->cursantes)
        mas_pequeno = izquierda;

    if (derecha < heap->tamano && heap->arr[derecha]->cursantes < heap->arr[mas_pequeno]->cursantes)
        mas_pequeno = derecha;

    if (mas_pequeno != i)
    {
        intercambiar_materia(&heap->arr[i], &heap->arr[mas_pequeno]);
        min_heapify_materias(heap, mas_pequeno);
    }
}

void insertar_min_heap_materias(HeapMaterias *heap, MateriaGlobal *materia)
{
    if (heap->tamano == heap->capacidad) return;

    int i = heap->tamano;
    heap->arr[i] = materia;
    heap->tamano++;

    while (i != 0 && heap->arr[(i - 1) / 2]->cursantes > heap->arr[i]->cursantes)
    {
        intercambiar_materia(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

MateriaGlobal *extraer_minimo_min_heap_materias(HeapMaterias *heap)
{
    if (heap->tamano <= 0) return NULL;
    if (heap->tamano == 1)
    {
        heap->tamano--;
        return heap->arr[0];
    }

    MateriaGlobal *raiz = heap->arr[0];
    heap->arr[0] = heap->arr[heap->tamano - 1];
    heap->tamano--;
    min_heapify_materias(heap, 0);
    return raiz;
}

MateriaGlobal *obtener_minimo_min_heap_materias(HeapMaterias *heap)
{
    if (heap->tamano <= 0) return NULL;
    return heap->arr[0];
}

void max_heapify_materias(HeapMaterias *heap, int i)
{
    int mas_grande = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < heap->tamano && heap->arr[izquierda]->cursantes > heap->arr[mas_grande]->cursantes)
        mas_grande = izquierda;

    if (derecha < heap->tamano && heap->arr[derecha]->cursantes > heap->arr[mas_grande]->cursantes)
        mas_grande = derecha;

    if (mas_grande != i)
    {
        intercambiar_materia(&heap->arr[i], &heap->arr[mas_grande]);
        max_heapify_materias(heap, mas_grande);
    }
}

void insertar_max_heap_materias(HeapMaterias *heap, MateriaGlobal *materia)
{
    if (heap->tamano == heap->capacidad) return;

    int i = heap->tamano;
    heap->arr[i] = materia;
    heap->tamano++;

    while (i != 0 && heap->arr[(i - 1) / 2]->cursantes < heap->arr[i]->cursantes)
    {
        intercambiar_materia(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

MateriaGlobal *extraer_maximo_max_heap_materias(HeapMaterias *heap)
{
    if (heap->tamano <= 0) return NULL;
    if (heap->tamano == 1)
    {
        heap->tamano--;
        return heap->arr[0];
    }

    MateriaGlobal *raiz = heap->arr[0];
    heap->arr[0] = heap->arr[heap->tamano - 1];
    heap->tamano--;
    max_heapify_materias(heap, 0);
    return raiz;
}

MateriaGlobal *obtener_maximo_max_heap_materias(HeapMaterias *heap)
{
    if (heap->tamano <= 0) return NULL;
    return heap->arr[0];
}


/**
 * @brief Encuentra las K materias con más cursantes.
 * @param lista Puntero a la lista de materias.
 * @param k Cantidad de materias a encontrar.
 * @return MateriaGlobal** Array de punteros a las materias encontradas.
 */
MateriaGlobal **encontrar_k_materias_mas_cursadas(ListadoMaterias *lista, int k)
{
    if (k <= 0) return NULL;
    int n_materias = cantidad_materias(lista);
    if (n_materias < k) k = n_materias;
    if (n_materias == 0) return NULL;

    HeapMaterias *min_heap = crearHeapMaterias(k);
    ListadoMaterias *actual = lista;

    while (actual != NULL)
    {
        MateriaGlobal *materia_actual = actual->data;
        if (min_heap->tamano < k)
        {
            insertar_min_heap_materias(min_heap, materia_actual);
        }
        else if (materia_actual->cursantes > obtener_minimo_min_heap_materias(min_heap)->cursantes)
        {
            extraer_minimo_min_heap_materias(min_heap);
            insertar_min_heap_materias(min_heap, materia_actual);
        }
        actual = actual->siguiente;
    }

    MateriaGlobal **array_materias = (MateriaGlobal **)malloc(k * sizeof(MateriaGlobal *));
    if (array_materias == NULL)
    {
        liberarHeapMaterias(min_heap);
        return NULL;
    }

    for (int i = k - 1; i >= 0; i--)
    {
        array_materias[i] = extraer_minimo_min_heap_materias(min_heap);
    }

    liberarHeapMaterias(min_heap);
    return array_materias;
}

/**
 * @brief Encuentra las K materias con menos cursantes.
 * @param lista Puntero a la lista de materias.
 * @param k Cantidad de materias a encontrar.
 * @return MateriaGlobal** Array de punteros a las materias encontradas.
 */
MateriaGlobal **encontrar_k_materias_menos_cursadas(ListadoMaterias *lista, int k)
{
    if (k <= 0) return NULL;
    int n_materias = cantidad_materias(lista);
    if (n_materias < k) k = n_materias;
    if (n_materias == 0) return NULL;

    HeapMaterias *max_heap = crearHeapMaterias(k);
    ListadoMaterias *actual = lista;

    while (actual != NULL)
    {
        MateriaGlobal *materia_actual = actual->data;
        if (max_heap->tamano < k)
        {
            insertar_max_heap_materias(max_heap, materia_actual);
        }
        else if (materia_actual->cursantes < obtener_maximo_max_heap_materias(max_heap)->cursantes)
        {
            extraer_maximo_max_heap_materias(max_heap);
            insertar_max_heap_materias(max_heap, materia_actual);
        }
        actual = actual->siguiente;
    }

    MateriaGlobal **array_materias = (MateriaGlobal **)malloc(k * sizeof(MateriaGlobal *));
    if (array_materias == NULL)
    {
        liberarHeapMaterias(max_heap);
        return NULL;
    }

    for (int i = k - 1; i >= 0; i--)
    {
        array_materias[i] = extraer_maximo_max_heap_materias(max_heap);
    }

    liberarHeapMaterias(max_heap);
    return array_materias;
}




