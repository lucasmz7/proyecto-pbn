#ifndef DATABASE_H
#define DATABASE_H

#include "estudiante.h"
#include "materia.h"

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

typedef struct ListadoCursadas
{
    Cursada *data;
    struct ListadoCursadas *siguiente;
} ListadoCursadas;

ListadoEstudiantes *crear_listado_estudiantes();
ListadoMaterias *crear_listado_materias();
ListadoCursadas *crear_listado_cursadas();

const char *estado_a_string(EstadoMateria e);

int agregar_estudiante(ListadoEstudiantes **lista, int legajo, int edad, const char *nombre, int modo_silencioso);
int eliminar_estudiante(ListadoEstudiantes **lista, int legajo);
Estudiante *buscar_por_legajo(ListadoEstudiantes *lista, int legajo, int modo_silencioso);
void buscar_por_nombre(ListadoEstudiantes *lista, const char *nombre);
void buscar_por_rango_edad(ListadoEstudiantes *lista, int edad_min, int edad_max);

int agregar_materia(ListadoMaterias **lista, const char *identificador, const char *nombre, int modo_silencioso);
int eliminar_materia(ListadoMaterias **lista, const char *nombre);
MateriaGlobal *buscar_por_identificador(ListadoMaterias *lista, const char *id, int modo_silencioso);
MateriaGlobal *buscar_materia_por_nombre(ListadoMaterias *lista, const char *nombre);

int cantidad_estudiantes(ListadoEstudiantes *lista);
int cantidad_materias(ListadoMaterias *lista);
int cantidad_cursadas(ListadoCursadas *lista);
int cantidad_materias_aprobadas(ListadoCursadas *lista);
int cantidad_materias_desaprobadas(ListadoCursadas *lista); 

void listar_estudiantes(ListadoEstudiantes *lista);
void listar_materias(ListadoMaterias *lista);
void print_estudiante(Estudiante *estudiante);
void print_materia(MateriaGlobal *materia);
void print_cursada(Cursada *cursada);
void print_detalle(Estudiante *estudiante);

#endif
