#ifndef LISTA_H
#define LISTA_H

#include "materia.h"

typedef struct Estudiante {
    char nombre[50];
    int legajo;
    int edad;
    Materia materias_cursando[5];
    Materia materias_aprobadas[60];
    struct Estudiante *siguiente;
    float promedio;
} Estudiante;

Estudiante* list_create(void);
void alta_estudiante(Estudiante **lista, int legajo);
void estudiante_modificar_legajo(Estudiante **lista);
void estudiante_modificar_edad(Estudiante **lista);
void estudiante_modificar_nombre(Estudiante **lista);
void estudiante_promedio(Estudiante **lista);
int list_length(Estudiante *lista);
Estudiante* list_getByIndex(Estudiante **lista, int index);
void baja_estudiante(Estudiante **lista, int legajo);
void list_print(Estudiante *lista);
Estudiante *buscar_por_edad(void);
Estudiante *buscar_por_nombre(void);

#endif
