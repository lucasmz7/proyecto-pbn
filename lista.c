#include <stdio.h>
#include <stdlib.h>
#include <materia.c>


typedef struct Estudiante{
    char nombre[50];
    int legajo;
    int edad;
    Materia materias_cursando[5];
    Materia materias_aprobadas[50];
    struct Estudiante *siguiente;
    float promedio;
} Estudiante;

// Lista enlazada simple
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Estudiante* list_create() {
    return NULL;
}

void alta_estudiante(Estudiante **lista, int legajo) {
    Estudiante *nuevo_estudiante = malloc(sizeof(Estudiante));
    nuevo_estudiante->legajo = legajo;
    nuevo_estudiante->siguiente = NULL;

    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (*lista == NULL) {
        *lista = nuevo_estudiante;    
    } else // Si no, recorremos la lista hasta el final y añadimos el nuevo nodo 
    {
        Estudiante *actual = *lista;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_estudiante;
    }
}

void modificar_estudiante(Estudiante **lista) {

}

int list_length(Estudiante *lista) {
    int count = 0;
    Estudiante *actual = lista;
    while (actual != NULL) {
        count++;
        actual = actual->siguiente;
    }
    return count;
}

void list_getByIndex(Estudiante **lista, int index) {
    if (*lista == NULL) return;

    Estudiante *actual = *lista;
    int count = 0;
    while (actual != NULL) {
        if (count == index) {
            return actual;
        }
        count++;
        actual = actual->siguiente;
    }
    return; // Si el índice es inválido
}

void baja_estudiante(Estudiante **lista, int legajo) {
    if (*lista == NULL) return;  // lista vacía

    Estudiante *actual = *lista;
    Estudiante *previous = NULL;

    // Si el índice a borrar es 0 (el primer elemento)
    if (index == 0) {
        *lista = actual->siguiente;  // mover cabeza
        free(actual);                 // liberar nodo original
        return;
    }

    // Recorremos hasta llegar al nodo a eliminar
    for (int i = 0; actual != NULL && i < index; i++) {
        previous = actual;
        actual = actual->siguiente;
    }

    // Si el índice es inválido
    if (actual == NULL) return;

    // Eliminamos el nodo y reconectamos la lista
    previous->siguiente = actual->siguiente;
    free(actual); 
}


void list_print(Estudiante *lista) {
    Estudiante *actual = lista;
    while (actual != NULL) {
        printf("%d ->", actual->legajo);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

Estudiante *buscar_por_edad() {

}

Estudiante *buscar_por_nombre() {
    
}
