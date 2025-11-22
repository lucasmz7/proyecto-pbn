#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "materia.h"

typedef struct ListadoCursadas ListadoCursadas;
typedef struct ListadoMaterias ListadoMaterias;

typedef struct Estudiante
{
    char nombre[50];
    int legajo;
    int edad;
    ListadoCursadas *cursadas; // materias que esta cursando
    ListadoCursadas *regulares; // materias regulares, aprobadas y desaprobadas
    float promedio;
} Estudiante;

int estudiante_modificar_legajo(Estudiante *estudiante, int nuevo_legajo);
int estudiante_modificar_edad(Estudiante *estudiante, int nueva_edad);
int estudiante_modificar_nombre(Estudiante *estudiante, const char *nuevo_nombre);
int estudiante_actualizar_promedio(Estudiante *estudiante);
int rendir_final(Estudiante *estudiante, const char *nombre_materia, float nota);
int anotar(Estudiante *estudiante, ListadoMaterias *lista_materias, const char *nombre_materia);
int bajar(Estudiante *estudiante, const char *nombre_materia);

#endif
