#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"
#include "database.h"
#include <string.h>

int estudiante_modificar_legajo(Estudiante *estudiante, int nuevo_legajo)
{
    if (estudiante == NULL)
    {
        printf("[ERROR]: Struct 'Estudiante' invalido\n");
        return 1;
    }

    if (nuevo_legajo < 10000 || nuevo_legajo > 99999)
    {
        printf("[ERROR]: Legajo invalido\n");
        return 1;
    }

    estudiante->legajo = nuevo_legajo;
    return 0;
}

int estudiante_modificar_edad(Estudiante *estudiante, int nueva_edad)
{
    if (estudiante == NULL)
    {
        printf("[ERROR]: Struct 'Estudiante' invalido\n");
        return 1;
    }

    if (nueva_edad < 18 || nueva_edad > 100)
    {
        printf("[ERROR]: Edad invalida\n");
        return 1;
    }

    estudiante->edad = nueva_edad;
    return 0;
}

int estudiante_modificar_nombre(Estudiante *estudiante, const char *nuevo_nombre)
{
    if (estudiante == NULL)
    {
        printf("[ERROR]: Struct 'Estudiante' invalido\n");
        return 1;
    }

    if (strlen(nuevo_nombre) < 1 || strlen(nuevo_nombre) > 50)
    {
        printf("[ERROR]: Nombre de estudiante invalido\n");
        return 1;
    }

    strcpy(estudiante->nombre, nuevo_nombre);
    return 0;
}

int estudiante_actualizar_promedio(Estudiante *estudiante)
{
    if (estudiante == NULL)
    {
        printf("[ERROR]: Struct 'Estudiante' invalido\n");
        return 1;
    }

    double suma = 0.0;
    int cantidad = 0;
    ListadoCursadas *lista = estudiante->regulares;

    while (lista != NULL)
    {
        if (lista->data != NULL)
        {
            suma += lista->data->nota;
            cantidad++;
        }
        lista = lista->siguiente;
    }

    if (cantidad > 0)
    {
        estudiante->promedio = (float)(suma / cantidad);
    }
    else
    {
        estudiante->promedio = 0.0f;
    }
    return 0;
}

int anotar(Estudiante *estudiante, ListadoMaterias *lista_materias, const char *nombre_materia)
{
    if (estudiante == NULL)
    {
        printf("[ERROR]: Struct 'Estudiante' invalido\n");
        return 1;
    }

    if (lista_materias == NULL)
    {
        printf("[ERROR]: Struct 'ListadoMaterias' invalido\n");
        return 1;
    }

    if (strlen(nombre_materia) < 1 || strlen(nombre_materia) > 50)
    {
        printf("[ERROR]: Nombre de materia invalido\n");
        return 1;
    }

    // Buscar la materia global en la lista
    ListadoMaterias *actual = lista_materias;
    MateriaGlobal *materia_encontrada = NULL;

    while (actual != NULL)
    {
        if (actual->data != NULL && strcmp(actual->data->nombre, nombre_materia) == 0)
        {
            materia_encontrada = actual->data;
            break;
        }
        actual = actual->siguiente;
    }

    // Si no se encontró la materia
    if (materia_encontrada == NULL)
    {
        printf("[ERROR]: No existe una materia con ese nombre\n");
        return 1;
    }

    // TODO: Buscar si ya esta anotado

    materia_encontrada->cursantes += 1;

    // Crear la cursada
    Cursada *c = malloc(sizeof(Cursada));
    c->referencia = materia_encontrada;
    c->estado = CURSANDO;
    c->nota = 0.0f;

    // Crear el nodo de lista
    ListadoCursadas *nodo = malloc(sizeof(ListadoCursadas));
    nodo->data = c;
    nodo->siguiente = NULL;

    // Insertar en la lista de cursadas del estudiante
    if (estudiante->cursadas == NULL)
    {
        estudiante->cursadas = nodo;
        return 0;
    }

    // Recorrer hasta el final e insertar
    ListadoCursadas *iter = estudiante->cursadas;
    while (iter->siguiente != NULL)
        iter = iter->siguiente;
    iter->siguiente = nodo;
    return 0;
}

// TODO: deberia comprobar si no esta anotado a ninguna materia con ese nombrE?
int bajar(Estudiante *estudiante, const char *nombre_materia)
{
    if (estudiante == NULL)
    {
        printf("[ERROR]: Struct 'Estudiante' invalido\n");
        return 1;
    }

    if (strlen(nombre_materia) < 1 || strlen(nombre_materia) > 50)
    {
        printf("[ERROR]: Nombre de materia invalido\n");
        return 1;
    }

    ListadoCursadas **lista = &estudiante->cursadas;
    if (lista == NULL || *lista == NULL)
        return 1;

    ListadoCursadas *actual = *lista;
    ListadoCursadas *previo = NULL;

    // Si la materia a eliminar es la primera
    if (actual != NULL && actual->data != NULL && strcmp(actual->data->referencia->nombre, nombre_materia) == 0)
    {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return 0;
    }

    // Recorremos hasta llegar encontrar el nodo a eliminar
    while (actual != NULL && (actual->data == NULL || strcmp(actual->data->referencia->nombre, nombre_materia) != 0))
    {
        previo = actual;
        actual = actual->siguiente;
    }

    // Si no se encontrro
    if (actual == NULL)
    {
        printf("[ERROR]: No existe una materia con ese nombre\n");
        return 1;
    }

    actual->data->referencia->cursantes -= 1;

    // Eliminamos el nodo y reconectamos la lista
    previo->siguiente = actual->siguiente;
    if (actual->data)
        free(actual->data);
    free(actual);
    return 0;
}

// TODO: comprobar que no la aprobo todavia
int rendir_final(Estudiante *estudiante, const char *nombre_materia, float nota)
{
    if (estudiante == NULL)
    {
        printf("[ERROR]: Struct 'Estudiante' invalido\n");
        return 1;
    }

    if (strlen(nombre_materia) < 1 || strlen(nombre_materia) > 50)
    {
        printf("[ERROR]: No existe una materia con ese nombre\n");
        return 1;
    }

    if (nota > 10 || nota < 1)
    {
        printf("[ERROR]: Nota invalida");
        return 1;
    }

    EstadoMateria estado;
    if (nota >= 4)
    {
        estado = REGULAR_APROBADA;
    }
    else
    {
        estado = REGULAR_DESAPROBADA;
    }

    ListadoCursadas *lista = estudiante->regulares;

    while (lista != NULL)
    {
        if (strcmp(lista->data->referencia->nombre, nombre_materia) == 0)
        {
            lista->data->estado = estado;
            lista->data->nota = nota;
            estudiante_actualizar_promedio(estudiante);
            break;
        }
        lista = lista->siguiente;
    }

    if (nota >= 4)
    {
        lista->data->referencia->aprobados += 1;
    }
    else
    {
        lista->data->referencia->desaprobados += 1;
    }

    bajar(estudiante, nombre_materia);
    return 0;
}