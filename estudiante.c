#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"
#include "database.h"
#include <string.h>

/**
 * @brief Modifica el legajo de un estudiante.
 * @param estudiante Puntero al estudiante.
 * @param nuevo_legajo Nuevo número de legajo.
 * @return int 0 si se modificó correctamente, 1 si hubo error.
 */
int estudiante_modificar_legajo(Estudiante *estudiante, int nuevo_legajo)
{
    if (estudiante == NULL)
    {
        printf("[ERROR]: Struct 'Estudiante' invalido\n");
        return 1;
    }

    if (nuevo_legajo < 100000 || nuevo_legajo > 999999)
    {
        printf("[ERROR]: Legajo invalido\n");
        return 1;
    }

    estudiante->legajo = nuevo_legajo;
    return 0;
}

/**
 * @brief Modifica la edad de un estudiante.
 * @param estudiante Puntero al estudiante.
 * @param nueva_edad Nueva edad.
 * @return int 0 si se modificó correctamente, 1 si hubo error.
 */
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

/**
 * @brief Modifica el nombre de un estudiante.
 * @param estudiante Puntero al estudiante.
 * @param nuevo_nombre Nuevo nombre.
 * @return int 0 si se modificó correctamente, 1 si hubo error.
 */
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

/**
 * @brief Recalcula y actualiza el promedio del estudiante.
 * @param estudiante Puntero al estudiante.
 * @return int 0 si se actualizó correctamente, 1 si hubo error.
 */
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

/**
 * @brief Anota a un estudiante a una materia.
 * @param estudiante Puntero al estudiante.
 * @param lista_materias Puntero a la lista de materias disponibles.
 * @param nombre_materia Nombre de la materia a cursar.
 * @return int 0 si se anotó correctamente, 1 si hubo error.
 */
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

    if (materia_encontrada == NULL)
    {
        printf("[ERROR]: No existe una materia con ese nombre\n");
        return 1;
    }

    materia_encontrada->cursantes += 1;

    Cursada *c = malloc(sizeof(Cursada));
    c->referencia = materia_encontrada;
    c->estado = CURSANDO;
    c->nota = 0.0f;

    ListadoCursadas *nodo = malloc(sizeof(ListadoCursadas));
    nodo->data = c;
    nodo->siguiente = NULL;

    if (estudiante->cursadas == NULL)
    {
        estudiante->cursadas = nodo;
        return 0;
    }

    ListadoCursadas *iter = estudiante->cursadas;
    while (iter->siguiente != NULL)
        iter = iter->siguiente;
    iter->siguiente = nodo;
    return 0;
}

/**
 * @brief Da de baja a un estudiante de una materia en curso.
 * @param estudiante Puntero al estudiante.
 * @param nombre_materia Nombre de la materia.
 * @return int 0 si se dio de baja correctamente, 1 si hubo error.
 */
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

    if (actual != NULL && actual->data != NULL && strcmp(actual->data->referencia->nombre, nombre_materia) == 0)
    {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return 0;
    }

    while (actual != NULL && (actual->data == NULL || strcmp(actual->data->referencia->nombre, nombre_materia) != 0))
    {
        previo = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL)
    {
        printf("[ERROR]: No existe una materia con ese nombre\n");
        return 1;
    }

    actual->data->referencia->cursantes -= 1;

    previo->siguiente = actual->siguiente;
    if (actual->data)
        free(actual->data);
    free(actual);
    return 0;
}

/**
 * @brief Registra la nota final de una materia para un estudiante.
 * @param estudiante Puntero al estudiante.
 * @param nombre_materia Nombre de la materia.
 * @param nota Nota obtenida.
 * @return int 0 si se registró correctamente, 1 si hubo error.
 */
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

    ListadoCursadas *lista = estudiante->cursadas;
    Cursada *cursada_encontrada = NULL;

    while (lista != NULL)
    {
        if (strcmp(lista->data->referencia->nombre, nombre_materia) == 0)
        {
            cursada_encontrada = lista->data;
            break;
        }
        lista = lista->siguiente;
    }

    if (cursada_encontrada == NULL)
    {
        printf("[ERROR]: El estudiante no está cursando esa materia\n");
        return 1;
    }

    EstadoMateria estado;
    if (nota >= 4)
    {
        estado = REGULAR_APROBADA;
        cursada_encontrada->referencia->aprobados += 1;
    }
    else
    {
        estado = REGULAR_DESAPROBADA;
        cursada_encontrada->referencia->desaprobados += 1;
    }

    Cursada *c = malloc(sizeof(Cursada));
    c->referencia = cursada_encontrada->referencia;
    c->estado = estado;
    c->nota = nota;

    ListadoCursadas *nodo = malloc(sizeof(ListadoCursadas));
    nodo->data = c;
    nodo->siguiente = estudiante->regulares;
    estudiante->regulares = nodo;

    estudiante_actualizar_promedio(estudiante);

    bajar(estudiante, nombre_materia);
    
    return 0;
}