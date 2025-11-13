#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"
#include "materia.h"
#include <string.h>
#include "database.h"

ListadoEstudiantes* crear_listado_estudiantes() {
    return NULL;
}

ListadoMaterias* crear_listado_materias() {
    return NULL;
}

void agregar_estudiante(ListadoEstudiantes **lista, int legajo, int edad, const char* nombre) {
    // Inicializamos Estudiante
    Estudiante *nuevo_estudiante = malloc(sizeof(Estudiante));
    nuevo_estudiante->legajo = legajo;
    nuevo_estudiante->edad = edad;
    strcpy(nuevo_estudiante->nombre, nombre);
    nuevo_estudiante->promedio = 0;

    for (int i = 0; i < 5; i++) {
        nuevo_estudiante->materias_cursando[i].id = -1;
    }

    for (int i = 0; i < 60; i++) {
        nuevo_estudiante->materias_aprobadas[i].id = -1;
    }

    // Incializamos nuevo nodo de la lista
    ListadoEstudiantes *nuevo_nodo = malloc(sizeof(ListadoEstudiantes));
    nuevo_nodo->data = nuevo_estudiante;
    nuevo_nodo->siguiente = NULL;

    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (*lista == NULL) {
        *lista = nuevo_nodo;
    } else // Si no, recorremos la lista hasta el final y añadimos el nuevo nodo 
    {
        ListadoEstudiantes *actual = *lista;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_nodo;
    }
}

void agregar_materia(ListadoMaterias **lista, const char* identificador, const char* nombre, int id) {
    // Inicializamos Materia
    Materia *nueva_materia = malloc(sizeof(Materia));
    nueva_materia->id = id;
    strcpy(nueva_materia->identificador, identificador);
    strcpy(nueva_materia->nombre, nombre);
    nueva_materia->nota = 0;
    nueva_materia->estado = PENDIENTE;

    // Incializamos nuevo nodo de la lista
    ListadoMaterias *nuevo_nodo = malloc(sizeof(ListadoMaterias));
    nuevo_nodo->data = nueva_materia;
    nuevo_nodo->siguiente = NULL;

    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (*lista == NULL) {
        *lista = nuevo_nodo;
    } else // Si no, recorremos la lista hasta el final y añadimos el nuevo nodo  
    {
        ListadoMaterias *actual = *lista;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_nodo;
    }
}


void eliminar_estudiante(ListadoEstudiantes **lista, const char* nombre) {
    if (*lista == NULL) {
        return;
    }

    ListadoEstudiantes *actual = *lista;
    ListadoEstudiantes *previo = NULL;

    // Si el estudiante a eliminar es el primero
    if (strcmp(actual->data->nombre, nombre) == 0) {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return;
    }

    // Recorremos hasta llegar encontrar el nodo a eliminar
    while (actual != NULL && strcmp(actual->data->nombre, nombre) != 0) {
        previo = actual;
        actual = actual->siguiente;
    }
    
    // Si no se encontrro
    if (actual == NULL) return;

    // Eliminamos el nodo y reconectamos la lista
    previo->siguiente = actual->siguiente;
    free(actual->data);
    free(actual); 
}


void eliminar_materia(ListadoMaterias **lista, const char* nombre) {
    if (*lista == NULL) {
        return;
    }

    ListadoMaterias *actual = *lista;
    ListadoMaterias *previo = NULL;

    // Si el estudiante a eliminar es el primero
    if (strcmp(actual->data->nombre, nombre) == 0) {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return;
    }

    // Recorremos hasta llegar encontrar el nodo a eliminar
    while (actual != NULL && strcmp(actual->data->nombre, nombre) != 0) {
        previo = actual;
        actual = actual->siguiente;
    }
    
    // Si no se encontrro
    if (actual == NULL) return;

    // Eliminamos el nodo y reconectamos la lista
    previo->siguiente = actual->siguiente;
    free(actual->data);
    free(actual); 
}

int cantidad_estudiantes(ListadoEstudiantes *lista) {
    int cantidad = 0;
    ListadoEstudiantes *actual = lista;
    while (actual != NULL) {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}

int cantidad_materias(ListadoMaterias *lista) {
    int cantidad = 0;
    ListadoMaterias *actual = lista;
    while (actual != NULL) {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}


void listar_estudiantes(ListadoEstudiantes *lista) {
    ListadoEstudiantes *actual = lista;
    Estudiante *estudiante = actual->data;
    
    while (actual != NULL) {
        printf("|%-30s|%-5d|%-2d|%-2d|\n", estudiante->nombre, estudiante->legajo, estudiante->edad, estudiante->promedio);
        actual = actual->siguiente;
    }
}


void listar_materias(ListadoMaterias *lista) {
    ListadoMaterias *actual = lista;
    Materia *materia = actual->data;

    while (actual != NULL) {
        printf("|%-5s|%-40s|\n", materia->nombre, materia->identificador);
        actual = actual->siguiente;
    }
}

Estudiante *buscar_por_nombre(ListadoEstudiantes *lista, const char* nombre) {
    if (lista == NULL) {
        printf("ERROR: base de datos vacia\n");
        return NULL;
    }

    if (strlen(nombre) > 50) {
        printf("ERORR: nombre demasiado largo, el nombre debe ser de como mucho 50 caracteres\n");
        return NULL;
    }
    
    ListadoEstudiantes *actual = lista;
    
    while (actual != NULL && strcmp(actual->data->nombre, nombre) != 0) {
        actual = actual->siguiente;
    }
    
    if (actual == NULL) {
        printf("El estudiante no existe\n");
        return NULL;
    }
    
    return actual->data;
}

// Tanto edad_min como edad_max son incluyentes
void buscar_por_rango_edad(ListadoEstudiantes *lista, int edad_min, int edad_max) {
    if (lista == NULL) {
        printf("ERROR: base de datos vacia\n");
        return;
    }

    if (edad_min < 18 || edad_min > 100) {
        printf("ERROR: edad minima invalida, la edad minima debe estar entre [18;100]\n");
        return;
    } 

    if (edad_max < 18 || edad_max > 100) {
        printf("ERROR: edad maxima invalida, la edad maxima debe estar entre [18;100]\n");
        return;
    }
    
    if (edad_max < edad_min) {
        printf("ERROR: rango de edad invalido, la edad minima tiene que ser menor o igual que la edad maxima\n");
        return;
    }

    ListadoEstudiantes *actual = lista;
    
    printf("Estudiantes en el rango %d-%d", edad_min, edad_max);
    while (actual != NULL) {
        if (actual->data->edad >= edad_min && actual->data->edad <= edad_max) {
            printf("|%-30s|%-5d|%-2d|%-2d|\n", actual->data->nombre, actual->data->legajo, actual->data->edad, actual->data->promedio);
        }
        actual = actual->siguiente;
    }

}