#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "database.h"
#include "estudiante.h"

typedef struct
{
    Estudiante **arr;
    int capacidad;
    int tamano;
} Heap;

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

    // Asigna memoria para el array de punteros a Estudiante
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
    free(heap->arr); // Solo se libera el array de punteros, no las estructuras Estudiante
    free(heap);
}

void min_heapify(Heap *heap, int i)
{
    int mas_pequeno = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    // Compara usando el campo 'promedio'
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

    // Compara usando el campo 'promedio'
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

    // Restaura la propiedad del Max-Heap hacia arriba, comparando promedios
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

    // Conteo y verificación de estudiantes
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

    // Recorrido O(N log k)
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

    // Extracción en un array de Estudiante**
    Estudiante **array_estudiantes = (Estudiante **)malloc(k * sizeof(Estudiante *));
    if (array_estudiantes == NULL)
    {
        perror("Fallo al asignar memoria para array de retorno");
        liberarHeap(min_heap);
        return NULL;
    }

    // Extrae y almacena en orden descendente (mejor a peor)
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

    // Conteo y verificación de estudiantes
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

    // Recorrido O(N log k)
    while (actual != NULL)
    {
        Estudiante *estudiante_actual = actual->data;

        if (max_heap->tamano < k)
        {
            insertar_max_heap(max_heap, estudiante_actual);
        }
        // Condición de reemplazo: Si el promedio actual es menor que la raíz (el más grande de los peores)
        else if (estudiante_actual->promedio < obtener_maximo_max_heap(max_heap)->promedio)
        {
            extraer_maximo_max_heap(max_heap);
            insertar_max_heap(max_heap, estudiante_actual);
        }

        actual = actual->siguiente;
    }

    // Extracción en un array de Estudiante**
    Estudiante **array_estudiantes = (Estudiante **)malloc(k * sizeof(Estudiante *));
    if (array_estudiantes == NULL)
    {
        perror("Fallo al asignar memoria para array de retorno");
        liberarHeap(max_heap);
        return NULL;
    }

    // Extrae y almacena en orden ascendente (peor a mejor)
    for (int i = 0; i < k; i++)
    {
        // El Max-Heap devuelve los elementos del más grande al más pequeño.
        // Los almacenamos de forma inversa para que el índice 0 contenga al peor de los peores.
        array_estudiantes[k - 1 - i] = extraer_maximo_max_heap(max_heap);
    }

    liberarHeap(max_heap);
    return array_estudiantes;
}

void imprimir_k_mejores_estudiantes(ListadoEstudiantes *estudiantes, int k)
{
    Estudiante **mejores_estudiantes = encontrar_k_mejores_promedios(estudiantes, k);

    if (mejores_estudiantes == NULL)
    {
        printf("No se encontraron estudiantes o k es inválido.\n");
        return;
    }

    printf("|%-50s|%-6s|%-4s|%-10s|\n", "Nombre", "Legajo", "Edad", "Promedio");
    printf("|==================================================|======|====|==========|\n");
    for (int i = 0; i < k; i++)
    {
        Estudiante *e = mejores_estudiantes[i];
        if (e != NULL)
        {
            print_estudiante(e);
        }
    }

    printf("\n");
    free(mejores_estudiantes);
}

void imprimir_k_peores_estudiantes(ListadoEstudiantes *estudiantes, int k)
{
    Estudiante **peores_estudiantes = encontrar_k_peores_promedios(estudiantes, k);

    if (peores_estudiantes == NULL)
    {
        printf("No se encontraron estudiantes o k es inválido.\n");
        return;
    }

    printf("|%-50s|%-6s|%-4s|%-10s|\n", "Nombre", "Legajo", "Edad", "Promedio");
    printf("|==================================================|======|====|==========|\n");
    for (int i = 0; i < k; i++)
    {
        Estudiante *e = peores_estudiantes[i];
        if (e != NULL)
        {
            print_estudiante(e);
        }
    }

    printf("\n");
    free(peores_estudiantes);
}
