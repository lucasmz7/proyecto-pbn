#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "materia.h"
#include "estudiante.h"
#include "cJSON.h"

MateriaGlobal *json_a_materia(cJSON *obj);
ListadoMaterias *json_a_lista_materias(cJSON *arr);

Cursada *json_a_cursada(cJSON *obj, ListadoMaterias *materias);
ListadoCursadas *json_a_lista_cursadas(cJSON *arr, ListadoMaterias *materias);

Estudiante *json_a_estudiante(cJSON *obj, ListadoMaterias *materias);
ListadoEstudiantes *json_a_lista_estudiantes(cJSON *arr, ListadoMaterias *materias);

cJSON *materia_a_json(MateriaGlobal *m);
cJSON *lista_materias_a_json(ListadoMaterias *lista);

cJSON *cursada_a_json(Cursada *c);
cJSON *lista_cursadas_a_json(ListadoCursadas *lista);

cJSON *estudiante_a_json(Estudiante *e);
cJSON *lista_estudiantes_a_json(ListadoEstudiantes *lista);

const char *estado_a_json(EstadoMateria e);

void guardar_datos(ListadoMaterias *materias,
                   ListadoEstudiantes *estudiantes,
                   const char *path);

void cargar_datos(const char *path,
                  ListadoMaterias **materias_out,
                  ListadoEstudiantes **estudiantes_out);

#endif