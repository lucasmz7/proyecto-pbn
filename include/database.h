#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include "materia.h"
#include <string.h>

typedef struct Estudiante Estudiante;

typedef struct ListadoEstudiantes
{
    Estudiante *data;
    struct ListadoEstudiantes *siguiente;
} ListadoEstudiantes;

typedef struct ListadoMaterias
{
    MateriaGlobal *data;
    struct ListadoMaterias *siguiente;
} ListadoMaterias;

typedef struct ListadoCorrelativa
{
    MateriaGlobal *data;
    struct ListadoCorrelativa *siguiente;
} ListadoCorrelativa;

typedef struct ListadoCursadas
{
    Cursada *data;
    struct ListadoCursadas *siguiente;
} ListadoCursadas;

ListadoEstudiantes *crear_listado_estudiantes();
ListadoMaterias *crear_listado_materias();

int agregar_estudiante(ListadoEstudiantes **lista, int legajo, int edad, const char *nombre);
int agregar_materia(ListadoMaterias **lista, const char *identificador, const char *nombre);

int eliminar_estudiante(ListadoEstudiantes **lista, int legajo);
int eliminar_materia(ListadoMaterias **lista, const char *nombre);

int cantidad_estudiantes(ListadoEstudiantes *lista);
int cantidad_materias(ListadoMaterias *lista);

void listar_estudiantes(ListadoEstudiantes *lista);
void listar_materias(ListadoMaterias *lista);

void buscar_por_nombre(ListadoEstudiantes *lista, const char *nombre);
void buscar_por_rango_edad(ListadoEstudiantes *lista, int edad_min, int edad_max);

Estudiante *buscar_por_legajo(ListadoEstudiantes *lista, int legajo);
MateriaGlobal *buscar_por_identificador(ListadoMaterias *lista, const char *id);

void print_detalle(Estudiante *estudiante);
void print_estudiante(Estudiante *estudiante);
void print_materia(MateriaGlobal *materia);
void print_cursada(Cursada *cursada);

#endif
