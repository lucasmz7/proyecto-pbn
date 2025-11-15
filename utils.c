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
    printf("|%-50s|%-6d|%-4d|%-5.2f%-15s|\n", estudiante->nombre, estudiante->legajo, estudiante->edad, estudiante->promedio, "");
}

void print_materia(MateriaGlobal *materia) {
    printf("|%-50s|%-6s|\n", materia->nombre, materia->identificador);
}


void print_cursada(Cursada *cursada) {
    printf("|   %-47s|%-6s|%-4d|%-20s|\n", cursada->referencia->nombre, cursada->referencia->identificador, cursada->nota, cursada->estado);
}