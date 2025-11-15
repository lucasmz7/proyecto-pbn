#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"
#include "database.h"
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
    
    double suma = 0.0;
    int cantidad = 0;
    ListadoCursadas *lista = estudiante->regulares;

    while (lista != NULL) {
        if (lista->data != NULL) {
            suma += lista->data->nota;
            cantidad++;
        }
        lista = lista->siguiente;
    }

    if (cantidad > 0) {
        estudiante->promedio = (float)(suma / cantidad);
    } else {
        estudiante->promedio = 0.0f;
    }
    return 0;
}

int anotar(Estudiante *estudiante, ListadoMaterias *lista_materias, const char *nombre_materia) {
    // Validar parámetros
    if (estudiante == NULL || lista_materias == NULL || nombre_materia == NULL) {
        return 1;
    }
     
    // Buscar la materia global en la lista
    ListadoMaterias *actual = lista_materias;
    MateriaGlobal *materia_encontrada = NULL;
    
    while (actual != NULL) {
        if (actual->data != NULL && strcmp(actual->data->nombre, nombre_materia) == 0) {
            materia_encontrada = actual->data;
            break;
        }
        actual = actual->siguiente;
    }
    
    // Si no se encontró la materia
    if (materia_encontrada == NULL) {
        printf("ERROR: Materia '%s' no existe en el sistema.\n", nombre_materia);
        return 1;
    }
    
    // Crear la cursada
    Cursada *c = malloc(sizeof(Cursada));
    if (c == NULL) return 1;
    c->referencia = materia_encontrada;
    c->estado = CURSANDO;
    c->nota = 0.0f;

    // Crear el nodo de lista
    ListadoCursadas *nodo = malloc(sizeof(ListadoCursadas));
    if (nodo == NULL) { free(c); return 1; }
    nodo->data = c;
    nodo->siguiente = NULL;

    // Insertar en la lista de cursadas del estudiante
    if (estudiante->cursadas == NULL) {
        estudiante->cursadas = nodo;
        return 0;
    }

    // Recorrer hasta el final e insertar
    ListadoCursadas *iter = estudiante->cursadas;
    while (iter->siguiente != NULL) iter = iter->siguiente;
    iter->siguiente = nodo;
    return 0;
}

int bajar(Estudiante *estudiante, const char *nombre_materia) {
    if (estudiante == NULL) return 1;

    ListadoCursadas **lista = &estudiante->cursadas;
    if (lista == NULL || *lista == NULL) return 1;

    ListadoCursadas *actual = *lista;
    ListadoCursadas *previo = NULL;

    // Si la correlativa a eliminar es la primera
    if (actual != NULL && actual->data != NULL && strcmp(actual->data->referencia->nombre, nombre_materia) == 0) {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return 0;
    }

    // Recorremos hasta llegar encontrar el nodo a eliminar
    while (actual != NULL && (actual->data == NULL || strcmp(actual->data->referencia->nombre, nombre_materia) != 0)) {
        previo = actual;
        actual = actual->siguiente;
    }
    
    // Si no se encontrro
    if (actual == NULL) return 1;

    // Eliminamos el nodo y reconectamos la lista
    previo->siguiente = actual->siguiente;
    if (actual->data) free(actual->data);
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