#ifndef UTILS_H
#define UTILS_H

#include "estudiante.h"
#include "materia.h"

int verificar_edad(int edad);
int verificar_nombre_estudiante(const char *nombre);
int verificar_legajo(int legajo);
int verificar_nombre_materia(const char *nombre);
int verificar_identificador(const char *identificador);
int verificar_nota(float nota);
void print_estudiante(Estudiante *estudiante);
void print_materia(MateriaGlobal *materia);
void print_cursada(Cursada *cursada);

#endif
