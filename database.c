#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"
#include "materia.h"
#include <string.h>
#include "database.h"

Estudiante *buscar_por_legajo(ListadoEstudiantes *lista, int legajo);
MateriaGlobal *buscar_por_identificador(ListadoMaterias *lista, const char *id);

ListadoEstudiantes *crear_listado_estudiantes()
{
    return NULL;
}

ListadoMaterias *crear_listado_materias()
{
    return NULL;
}

ListadoCursadas *crear_listado_cursadas()
{
    return NULL;
}

int agregar_estudiante(ListadoEstudiantes **lista, int legajo, int edad, const char *nombre)
{

    if (edad < 18 || edad > 100)
    {
        printf("[ERROR]: Edad invalida\n");
        return 1;
    }

    if (legajo < 100000 || legajo > 999999)
    {
        printf("[ERROR]: Legajo invalido\n");
        return 1;
    }

    if (strlen(nombre) < 1 || strlen(nombre) > 50)
    {
        printf("[ERROR]: Nombre de estudiante invalido\n");
        return 1;
    }

    if (buscar_por_legajo(*lista, legajo) != NULL)
    {
        printf("Ya existe un estudiante con ese legajo");
        return 1;
    }

    // Inicializamos Estudiante
    Estudiante *nuevo_estudiante = malloc(sizeof(Estudiante));
    nuevo_estudiante->legajo = legajo;
    nuevo_estudiante->edad = edad;
    strcpy(nuevo_estudiante->nombre, nombre);
    nuevo_estudiante->promedio = 0.0f;
    nuevo_estudiante->cursadas = NULL;
    nuevo_estudiante->regulares = NULL;

    // Incializamos nuevo nodo de la lista
    ListadoEstudiantes *nuevo_nodo = malloc(sizeof(ListadoEstudiantes));
    nuevo_nodo->data = nuevo_estudiante;
    nuevo_nodo->siguiente = NULL;

    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (*lista == NULL)
    {
        *lista = nuevo_nodo;
    }
    else // Si no, recorremos la lista hasta el final y añadimos el nuevo nodo
    {
        ListadoEstudiantes *actual = *lista;
        while (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_nodo;
    }
    return 0;
}

int agregar_materia(ListadoMaterias **lista, const char *identificador, const char *nombre)
{

    if (strlen(identificador) > 6 || strlen(identificador) < 1)
    {
        printf("[ERROR]: Identificador de materia invalido\n");
        return 1;
    }

    if (strlen(nombre) > 50 || strlen(nombre) < 1)
    {
        printf("[ERROR]: Nombre de materia invalido\n");
        return 1;
    }

    if (buscar_por_identificador(*lista, identificador) != NULL)
    {
        printf("Ya existe una materia con ese identificador");
        return 1;
    }

    if (buscar_materia_por_nombre(*lista, nombre) != NULL)
    {
        printf("Ya existe una materia con ese nombre");
        return 1;
    }

    // Inicializamos Materia
    MateriaGlobal *nueva_materia = malloc(sizeof(MateriaGlobal));
    strcpy(nueva_materia->identificador, identificador);
    strcpy(nueva_materia->nombre, nombre);
    nueva_materia->cursantes = 0;
    nueva_materia->aprobados = 0;
    nueva_materia->desaprobados = 0;

    // Incializamos nuevo nodo de la lista
    ListadoMaterias *nuevo_nodo = malloc(sizeof(ListadoMaterias));
    nuevo_nodo->data = nueva_materia;
    nuevo_nodo->siguiente = NULL;

    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (*lista == NULL)
    {
        *lista = nuevo_nodo;
    }
    else // Si no, recorremos la lista hasta el final y añadimos el nuevo nodo
    {
        ListadoMaterias *actual = *lista;
        while (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_nodo;
    }
    return 0;
}

int eliminar_estudiante(ListadoEstudiantes **lista, int legajo)
{
    if (*lista == NULL)
    {
        printf("No hay estudiantes en la lista\n");
        return 1;
    }

    if (legajo < 10000 || legajo >= 99999)
    {
        printf("[ERROR]: Legajo invalido\n");
        return 1;
    }

    ListadoEstudiantes *actual = *lista;
    ListadoEstudiantes *previo = NULL;

    // Si el estudiante a eliminar es el primero
    if (actual->data->legajo == legajo)
    {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return 0;
    }

    // Recorremos hasta llegar encontrar el nodo a eliminar
    while (actual != NULL && (actual->data->legajo == legajo))
    {
        previo = actual;
        actual = actual->siguiente;
    }

    // Si no se encontrro
    if (actual == NULL)
    {
        printf("No existe ningun estudiante con ese legajo\n");
        return 1;
    }
    // Eliminamos el nodo y reconectamos la lista
    previo->siguiente = actual->siguiente;
    free(actual->data);
    free(actual);
    return 0;
}

int eliminar_materia(ListadoMaterias **lista, const char *nombre)
{
    if (*lista == NULL)
    {
        printf("No hay materias en la lista\n");
        return 1;
    }

    if (strlen(nombre) < 1 || strlen(nombre) > 50)
    {
        printf("[ERROR]: Nombre de materia invalido\n");
        return 1;
    }

    ListadoMaterias *actual = *lista;
    ListadoMaterias *previo = NULL;

    // Si la materia a eliminar es la primera
    if (strcmp(actual->data->nombre, nombre) == 0)
    {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return 0;
    }

    // Recorremos hasta llegar encontrar el nodo a eliminar
    while (actual != NULL && strcmp(actual->data->nombre, nombre) != 0)
    {
        previo = actual;
        actual = actual->siguiente;
    }

    // Si no se encontrro
    if (actual == NULL)
    {
        printf("No existe una materia con ese nombre\n");
        return 1;
    }

    // Eliminamos el nodo y reconectamos la lista
    previo->siguiente = actual->siguiente;
    free(actual->data);
    free(actual);
    return 0;
}

int cantidad_estudiantes(ListadoEstudiantes *lista)
{
    int cantidad = 0;
    ListadoEstudiantes *actual = lista;
    while (actual != NULL)
    {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}

int cantidad_materias(ListadoMaterias *lista)
{
    int cantidad = 0;
    ListadoMaterias *actual = lista;
    while (actual != NULL)
    {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}

int cantidad_cursadas(ListadoCursadas *lista)
{
    int cantidad = 0;
    ListadoCursadas *actual = lista;
    while (actual != NULL)
    {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}

void listar_estudiantes(ListadoEstudiantes *lista)
{
    if (lista == NULL)
    {
        printf("No hay estudiantes\n");
        return;
    }

    ListadoEstudiantes *actual = lista;

    printf("|%-50s|%-6s|%-4s|%-10s|\n", "Nombre", "Legajo", "Edad", "Promedio");
    printf("|==================================================|======|====|==========|\n");

    while (actual != NULL)
    {
        print_estudiante(actual->data);
        actual = actual->siguiente;
    }
}

void listar_materias(ListadoMaterias *lista)
{
    if (lista == NULL)
    {
        printf("No hay materias en la lista\n");
        return;
    }

    ListadoMaterias *actual = lista;

    printf("|%-50s|%-6s|%-9s|%-9s|%-12s|\n", "Materias", "ID", "Cursantes", "Aprobados", "Desaprobados");
    printf("|==================================================|======|=========|=========|============|\n");

    while (actual != NULL)
    {
        print_materia(actual->data);
        actual = actual->siguiente;
    }
}

void buscar_por_nombre(ListadoEstudiantes *lista, const char *nombre)
{
    if (lista == NULL)
    {
        printf("No hay estudiantes en la lista\n");
        return;
    }

    if (strlen(nombre) > 50)
    {
        printf("[ERROR]: nombre demasiado largo (máximo 50 chars)\n");
        return;
    }

    ListadoEstudiantes *actual = lista;
    int encontrado = 0;

    // Recorremos la lista
    while (actual != NULL)
    {
        if (strcmp(actual->data->nombre, nombre) == 0)
        {
            // Mostrar encabezado solo la primera vez
            if (!encontrado)
            {
                printf("|%-50s|%-6s|%-4s|%-10s|\n",
                       "Nombre", "Legajo", "Edad", "Promedio");
                printf("|==================================================|======|====|==========|\n");
            }

            print_estudiante(actual->data);
            encontrado = 1;
        }

        actual = actual->siguiente;
    }

    if (!encontrado)
    {
        printf("No existe ningún estudiante con ese nombre\n");
    }
}

// Tanto edad_min como edad_max son incluyentes
void buscar_por_rango_edad(ListadoEstudiantes *lista, int edad_min, int edad_max)
{
    if (lista == NULL)
    {
        printf("No hay estudiantes en la lista\n");
        return;
    }

    if (edad_min < 18 || edad_min > 100)
    {
        printf("[ERROR]: Edad mínima inválida\n");
        return;
    }

    if (edad_max < 18 || edad_max > 100)
    {
        printf("[ERROR]: Edad máxima inválida\n");
        return;
    }

    if (edad_max < edad_min)
    {
        printf("[ERROR]: El rango es inválido (edad_max < edad_min)\n");
        return;
    }

    ListadoEstudiantes *actual = lista;
    int encontrado = 0;

    while (actual != NULL)
    {
        if (actual->data->edad >= edad_min && actual->data->edad <= edad_max)
        {
            if (!encontrado)
            {
                printf("Estudiantes en el rango %d - %d\n", edad_min, edad_max);
                printf("\n");
                printf("|%-50s|%-6s|%-4s|%-10s|\n",
                       "Nombre", "Legajo", "Edad", "Promedio");
                printf("|==================================================|======|====|==========|\n");
            }

            print_estudiante(actual->data);
            encontrado = 1;
        }

        actual = actual->siguiente;
    }

    if (!encontrado)
    {
        printf("No se encontraron estudiantes entre %d y %d años.\n",
               edad_min, edad_max);
    }
}

Estudiante *buscar_por_legajo(ListadoEstudiantes *lista, int legajo)
{
    if (lista == NULL)
    {
        printf("No hay estudiantes en la lista\n");
        return NULL;
    }

    if (legajo < 100000 || legajo >= 999999)
    {
        printf("[ERROR]: numero de legajo invalido (debe ser de 6 digitos)\n");
        return NULL;
    }

    ListadoEstudiantes *actual = lista;
    while (actual != NULL)
    {
        if (actual->data->legajo == legajo)
        {
            return actual->data;
        }
        actual = actual->siguiente;
    }

    // No encontrado
    printf("No existe un estudiante con ese legajo\n");
    return NULL;
}

MateriaGlobal *buscar_por_identificador(ListadoMaterias *lista, const char *id)
{
    if (lista == NULL)
    {
        printf("No hay materias en la lista\n");
        return NULL;
    }

    if (strlen(id) < 1 || strlen(id) > 6)
    {
        printf("[ERROR]: Identificador invalido\n");
        return NULL;
    }

    while (lista)
    {
        if (strcmp(lista->data->identificador, id) == 0)
            return lista->data;
        lista = lista->siguiente;
    }
    printf("No existe una materia con ese identificador\n");
    return NULL;
}

MateriaGlobal *buscar_materia_por_nombre(ListadoMaterias *lista, const char *nombre)
{
    ListadoMaterias *actual = lista;
    while (actual != NULL)
    {
        if (strcmp(actual->data->nombre, nombre) == 0)
            return actual->data;

        actual = actual->siguiente;
    }
    return NULL;
}

const char *estado_a_string(EstadoMateria e)
{
    switch (e)
    {
    case CURSANDO:
        return "CURSANDO";
    case REGULAR_PENDIENTE:
        return "REGULAR PENDIENTE";
    case REGULAR_DESAPROBADA:
        return "REGULAR DESAPROBADA";
    case REGULAR_APROBADA:
        return "REGULAR APROBADA";
    case LIBRE:
        return "LIBRE";
    }
    return "DESCONOCIDO";
}

void print_estudiante(Estudiante *estudiante)
{
    if (estudiante == NULL)
    {
        printf("[ERROR]: Struct 'Estudiante' invalido\n");
    }

    estudiante_actualizar_promedio(estudiante);
    printf("|%-50s|%-6d|%-4d|%-10.2f|\n", estudiante->nombre, estudiante->legajo, estudiante->edad, estudiante->promedio);
}

void print_materia(MateriaGlobal *materia)
{
    if (materia == NULL)
    {
        printf("[ERROR]: Struct 'MateriaGlobal' invalido\n");
    }

    printf("|%-50s|%-6s|%-9d|%-9d|%-12d|\n", materia->nombre, materia->identificador, materia->cursantes, materia->aprobados, materia->desaprobados);
}

void print_cursada(Cursada *cursada)
{
    if (cursada == NULL)
    {
        printf("[ERROR]: Struct 'Cursada' invalido\n");
    }

    const char *estado = estado_a_string(cursada->estado);

    printf("|   %-47s|%-6s|%-2.2f|%-20s|\n", cursada->referencia->nombre, cursada->referencia->identificador, cursada->nota, estado);
}

void print_detalle(Estudiante *estudiante)
{
    print_estudiante(estudiante);

    ListadoCursadas *actual_cursadas = estudiante->cursadas;
    ListadoCursadas *actual_regulares = estudiante->regulares;

    printf("|   %-47s|%-6s|%-4s|%-20s|\n", "Materias en curso:", "ID", "Nota", "Estado");
    while (actual_cursadas != NULL)
    {
        print_cursada(actual_cursadas->data);
        actual_cursadas = actual_cursadas->siguiente;
    }
    printf("|   %-47s|%-6s|%-4s|%-20s|\n", "Materias regulares:", "ID", "Nota", "Estado");
    while (actual_regulares != NULL)
    {
        print_cursada(actual_regulares->data);
        actual_regulares = actual_regulares->siguiente;
    }
}
