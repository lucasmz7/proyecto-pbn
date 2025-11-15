#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "materia.h"
#include "database.h"

typedef struct Estudiante {
    char nombre[30];
    int legajo;
    int edad;
    ListadoCursadas *cursadas;
    ListadoCursadas *regulares;
    float promedio;
} Estudiante;

int estudiante_modificar_legajo(Estudiante *estudiante, int nuevo_legajo); 
int estudiante_modificar_edad(Estudiante *estudiante, int nueva_edad); 
int estudiante_modificar_nombre(Estudiante *estudiante, const char* nuevo_nombre);
int estudiante_actualizar_promedio(Estudiante *estudiante);
int rendir_final(Estudiante *estudiante, const char *nombre_materia, float nota);
int anotar(Estudiante *estudiante, MateriaGlobal *materia) ;
int bajar(Estudiante *estudiante, const char* nombre_materia);

#endif
