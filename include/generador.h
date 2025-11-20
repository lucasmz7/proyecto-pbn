#ifndef GENERADOR_H
#define GENERADOR_H

#include "database.h"

void generar_estudiante_aleatorio(ListadoEstudiantes **lista);

void generar_materia_aleatoria(ListadoMaterias **lista);

int generador(ListadoEstudiantes **estudiantes,
              ListadoMaterias **materias,
              int cantidad_estudiantes,
              int cantidad_materias);

int anotar_estudiante_materias_aleatorias(Estudiante *estudiante, ListadoMaterias *materias);

int rendir_materias_aleatorias(Estudiante *estudiante);

#endif
