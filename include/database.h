#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"
#include "materia.h"
#include <string.h>

typedef struct ListadoEstudiantes {
    Estudiante *data;
    struct ListadoEstudiantes *siguiente;
} ListadoEstudiantes;

typedef struct ListadoMaterias {
    Materia *data;
    struct ListadoMaterias *siguiente;
} ListadoMaterias;

ListadoEstudiantes* crear_listado_estudiantes();
ListadoMaterias* crear_listado_materias();
void agregar_estudiante(ListadoEstudiantes **lista, int legajo, int edad, const char* nombre);
void agregar_materia(ListadoMaterias **lista, const char* identificador, const char* nombre);
void eliminar_estudiante(ListadoEstudiantes **lista, int legajo);
void eliminar_materia(ListadoMaterias **lista, const char* nombre);
int cantidad_estudiantes(ListadoEstudiantes *lista);
int cantidad_materias(ListadoMaterias *lista);
void listar_estudiantes(ListadoEstudiantes *lista);
void listar_materias(ListadoMaterias *lista);
void buscar_por_nombre(ListadoEstudiantes *lista, const char* nombre);
void buscar_por_rango_edad(ListadoEstudiantes *lista, int edad_min, int edad_max);
Estudiante *buscar_por_legajo(ListadoEstudiantes *lista, int legajo);

#endif // DATABASE_H
