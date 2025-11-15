#include <stdio.h>
#include "estudiante.h"
#include <stdlib.h>

// TODO: funcion para comprobar nombre?

// int verificar_listas() {}

int verificar_edad(int edad) {
    (void)edad; /* placeholder - implement validation */
    return 0;
}

int verificar_nombre_estudiante(const char *nombre) {
    (void)nombre; /* placeholder - implement validation */
    return 0;
}

int verificar_legajo(int legajo) {
    (void)legajo; /* placeholder - implement validation */
    return 0;
}

int verificar_nombre_materia(const char *nombre) {
    (void)nombre; /* placeholder - implement validation */
    return 0;
}

int verificar_identificador(const char *identificador) {
    (void)identificador; /* placeholder - implement validation */
    return 0;
}

int verificar_nota(float nota) {
    (void)nota; /* placeholder - implement validation */
    return 0;
}

void print_estudiante(Estudiante *estudiante) {
    printf("|%-30s|%-5d|%-2d|%-5.2f|\n", estudiante->nombre, estudiante->legajo, estudiante->edad, estudiante->promedio);
}

void print_materia(MateriaGlobal *materia) {
    printf("|%-5s|%-40s|\n", materia->nombre, materia->identificador);
}