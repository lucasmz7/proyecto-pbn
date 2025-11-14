#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "materia.h"

typedef struct Estudiante {
    char nombre[30];
    int legajo;
    int edad;
    Materia materias_cursando[5];
    Materia materias_aprobadas[60];
    float promedio;
} Estudiante;

void estudiante_modificar_legajo(Estudiante *estudiante, int nuevo_legajo); 
void estudiante_modificar_edad(Estudiante *estudiante, int nueva_edad); 
void estudiante_modificar_nombre(Estudiante *estudiante, const char* nuevo_nombre);
void estudiante_actualizar_promedio(Estudiante *estudiante);

#endif
