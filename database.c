#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"
#include "materia.h"
#include <string.h>
#include "database.h"
#include "utils.h"

ListadoEstudiantes *crear_listado_estudiantes() {
    return NULL;
}

ListadoMaterias *crear_listado_materias() {
    return NULL;
}

ListadoCorrelativa *crear_listado_correlativa() {
    return NULL;
}

ListadoCursadas *crear_listado_cursadas() {
    return NULL;
}

void agregar_estudiante(ListadoEstudiantes **lista, int legajo, int edad, const char* nombre) {
    // Inicializamos Estudiante
    Estudiante *nuevo_estudiante = malloc(sizeof(Estudiante));
    nuevo_estudiante->legajo = legajo;
    nuevo_estudiante->edad = edad;
    strcpy(nuevo_estudiante->nombre, nombre);
    nuevo_estudiante->promedio = 0;
    nuevo_estudiante->cursadas = NULL;
    nuevo_estudiante->regulares = NULL;

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

void agregar_materia(ListadoMaterias **lista, const char *identificador, const char *nombre) {
    // Inicializamos Materia
    MateriaGlobal *nueva_materia = malloc(sizeof(MateriaGlobal));
    strcpy(nueva_materia->identificador, identificador);
    strcpy(nueva_materia->nombre, nombre);

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


void eliminar_estudiante(ListadoEstudiantes **lista, int legajo) {
    if (*lista == NULL) {
        return;
    }

    ListadoEstudiantes *actual = *lista;
    ListadoEstudiantes *previo = NULL;

    // Si el estudiante a eliminar es el primero
    if (actual->data->legajo == legajo) {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return;
    }

    // Recorremos hasta llegar encontrar el nodo a eliminar
    while (actual != NULL && (actual->data->legajo == legajo)) {
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


void eliminar_materia(ListadoMaterias **lista, const char *nombre) {
    if (*lista == NULL) {
        return;
    }

    ListadoMaterias *actual = *lista;
    ListadoMaterias *previo = NULL;

    // Si la materia a eliminar es la primera
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
    if (lista == NULL) {
        printf("No hay estudiantes\n");
        return;
    }

    ListadoEstudiantes *actual = lista;
    Estudiante *estudiante = actual->data;

    printf("|%-50s|%-6s|%-4s|%-20s|\n", "Nombre", "Legajo", "Edad", "Promedio");
    while (actual != NULL) {
        print_estudiante(estudiante);

        actual = actual->siguiente;
    }
}


void listar_materias(ListadoMaterias *lista) {
    if (lista == NULL) {
        printf("No hay materias\n");
        return;
    }

    ListadoMaterias *actual = lista;
    MateriaGlobal *materia = actual->data;

    while (actual != NULL) {
        print_materia(materia);
        actual = actual->siguiente;
    }
}

void buscar_por_nombre(ListadoEstudiantes *lista, const char *nombre) {
    if (lista == NULL) {
        printf("ERROR: base de datos vacia\n");
        return;
    }

    // TODO: verificar nombre
    if (strlen(nombre) > 50) {
        printf("ERORR: nombre demasiado largo (el nombre debe ser de como mucho 50 caracteres)\n");
        return;
    }
    
    ListadoEstudiantes *actual = lista;
    Estudiante *estudiante = actual->data;
    ListadoCursadas *actual_cursadas = estudiante->cursadas;
    ListadoCursadas *actual_regulares = estudiante->regulares;    
    
    if (actual == NULL) {
        printf("No existe ningun estudiante con ese nombre\n");
        return;
    }

    printf("|%-50s|%-6s|%-4s|%-20s|\n", "Nombre", "Legajo", "Edad", "Promedio");
    while (actual != NULL ) {
        if (strcmp(actual->data->nombre, nombre) == 0) {
            print_estudiante(estudiante);
            printf("|   %-47s|%-6s|%-4s|%-20s|\n", "Materias en curso:", "ID", "Nota", "Estado");
            while (actual_cursadas != NULL) {
                print_cursada(actual_cursadas->data);
                actual_cursadas = actual_cursadas->siguiente;
            }
            printf("|   %-47s|%-6s|%-4s|%-20s|\n", "Materias regulares:", "ID", "Nota", "Estado");
            while (actual_regulares != NULL) {
                print_cursada(actual_regulares->data);
                actual_regulares = actual_regulares->siguiente;
            }

        }
        actual = actual->siguiente;
    }
}

// Tanto edad_min como edad_max son incluyentes
void buscar_por_rango_edad(ListadoEstudiantes *lista, int edad_min, int edad_max) {
    if (lista == NULL) {
        printf("ERROR: base de datos vacia\n");
        return;
    }

    // TODO: verificar edad
    if (edad_min < 18 || edad_min > 100) {
        printf("ERROR: edad minima invalida (la edad minima debe estar entre [18;100])\n");
        return;
    } 

    if (edad_max < 18 || edad_max > 100) {
        printf("ERROR: edad maxima invalida (la edad maxima debe estar entre [18;100])\n");
        return;
    }
    
    if (edad_max < edad_min) {
        printf("ERROR: rango de edad invalido (la edad minima tiene que ser menor o igual que la edad maxima)\n");
        return;
    }

    ListadoEstudiantes *actual = lista;
    
    printf("Estudiantes en el rango %d-%d\n", edad_min, edad_max);
    printf("|%-50s|%-6s|%-4s|%-20s|\n", "Nombre", "Legajo", "Edad", "Promedio");
    while (actual != NULL) {
        if (actual->data->edad >= edad_min && actual->data->edad <= edad_max) {
            print_estudiante(actual->data);
        }
        actual = actual->siguiente;
    }

}

Estudiante *buscar_por_legajo(ListadoEstudiantes *lista, int legajo) {
    if (lista == NULL) {
        printf("ERROR: base de datos vacia\n");
        return NULL;
    }

    // TODO: verificar legajo
    if (legajo < 10000 || legajo >= 100000) {
        printf("ERROR: numero de legajo invalido (debe ser de 5 digitos)\n");
        return NULL;
    }

    ListadoEstudiantes *actual = lista;
    while (actual != NULL) {
        if (actual->data->legajo == legajo) {
            return actual->data;
        }
        actual = actual->siguiente;
    }

    // No encontrado
    printf("ERROR: legajo no encontrado\n");
    return NULL;
}

