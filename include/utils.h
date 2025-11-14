/* utils.h - utility function prototypes and validations */
#ifndef UTILS_H
#define UTILS_H

#include "estudiante.h"
#include "materia.h"

/* Validation helpers - return 0 on success, non-zero on error */
int verificar_edad(int edad);
int verificar_nombre_estudiante(const char *nombre);
int verificar_legajo(int legajo);
int verificar_nombre_materia(const char *nombre);
int verificar_identificador(const char *identificador);
int verificar_nota(float nota);

/* Print helpers */
void print_estudiante(Estudiante *estudiante);
void print_materia(Materia *materia);

#endif /* UTILS_H */
