#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"
#include "utils.h"
#include <string.h>

int estudiante_modificar_legajo(Estudiante *estudiante, int nuevo_legajo) {
    if (estudiante == NULL) {
        return 1;
    }

    if (verificar_legajo(nuevo_legajo) != 0) {
        printf("No se pudo modificar el legajo. Legajo invalido");
        return 1;
    }

    estudiante->legajo = nuevo_legajo;
    return 0;
}

int estudiante_modificar_edad(Estudiante *estudiante, int nueva_edad) {
    if (estudiante == NULL) {
        return 1;
    }

    if (verificar_edad(nueva_edad) != 0) {
        printf("No se pudo modificar la edad. Edad invalida");
        return 1;
    }

    estudiante->edad = nueva_edad;
    return 0;
}

int estudiante_modificar_nombre(Estudiante *estudiante, const char *nuevo_nombre) {
    if (estudiante == NULL) {
        return 1;
    }
    
    if (verificar_nombre_estudiante(nuevo_nombre) != 0) {
        printf("No se pudo modificar el nombre del estudiante. Nombre invalido");
        return 1;
    }

    strcpy(estudiante->nombre, nuevo_nombre);
    return 0;
}

int estudiante_actualizar_promedio(Estudiante *estudiante) {
    if (estudiante == NULL) {
        return 1;
    }
    
    int suma = 0;
    int cantidad = 0;
    ListadoCursadas *lista = estudiante->regulares;

    while (lista != NULL) {
        lista = lista->siguiente;
        suma += lista->data->nota;
        cantidad++;
    }

    estudiante->promedio = suma / cantidad;
    return 0;
}

int anotar(Estudiante *estudiante, MateriaGlobal *materia) {
    // TODO: deberia anotarse si ya esta en regulares?
    if (estudiante == NULL || materia == NULL) {
        return 1;
    } 

    ListadoCursadas *lista = estudiante->cursadas;

    while (lista->siguiente != NULL) {
        lista = lista->siguiente;
    }

    lista->siguiente = materia;
    return 0;
}

int bajar(Estudiante *estudiante, const char *nombre_materia) {
    ListadoCursadas **lista = estudiante->cursadas;
    
    if (estudiante == NULL) {
        return 1;
    }

    ListadoCursadas *actual = *lista;
    ListadoCursadas *previo = NULL;

    // Si la correlativa a eliminar es la primera
    if (strcmp(actual->data->referencia->nombre, nombre_materia) == 0) {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return 0;
    }

    // Recorremos hasta llegar encontrar el nodo a eliminar
    while (actual != NULL && strcmp(actual->data->referencia->nombre, nombre_materia) != 0) {
        previo = actual;
        actual = actual->siguiente;
    }
    
    // Si no se encontrro
    if (actual == NULL) return 1;

    // Eliminamos el nodo y reconectamos la lista
    previo->siguiente = actual->siguiente;
    free(actual->data);
    free(actual);
    return 0; 
}

int rendir_final(Estudiante *estudiante, const char *nombre_materia, float nota) {
    if (estudiante == NULL) {
        return 1;
    }

    if (verificar_nota(nota) != 0) {
        return 1;
    }
    
    EstadoMateria estado;
    if (nota >= 4) {
        estado = REGULAR_APROBADA; 
    } else {
        estado = REGULAR_DESAPROBADA;
    }

    ListadoCursadas *lista = estudiante->regulares;

    while (lista != NULL) {
        if (strcmp(lista->data->referencia->nombre, nombre_materia) == 0) {
            lista->data->estado = estado;
            lista->data->nota = nota;
            break;
        }
        lista = lista->siguiente;
    }
    bajar(estudiante, nombre_materia);
    return 0;
}