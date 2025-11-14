#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"
#include <utils.c>
#include <string.h>

void estudiante_modificar_legajo(Estudiante *estudiante, int nuevo_legajo) {
    if (verificar_legajo(nuevo_legajo) != 0) {
        printf("No se pudo modificar el legajo. Legajo invalido");
        return;
    }

    estudiante->legajo = nuevo_legajo;
}

void estudiante_modificar_edad(Estudiante *estudiante, int nueva_edad) {
    if (verificar_edad(nueva_edad) != 0) {
        printf("No se pudo modificar la edad. Edad invalida");
        return;
    }

    estudiante->edad = nueva_edad;
}

void estudiante_modificar_nombre(Estudiante *estudiante, const char* nuevo_nombre) {
    if (verificar_nombre_estudiante(nuevo_nombre) != 0) {
        printf("No se pudo modificar el nombre del estudiante. Nombre invalido");
        return;
    }
    strcpy(estudiante->nombre, nuevo_nombre);
}

void estudiante_actualizar_promedio(Estudiante *estudiante) {
    // TODO
}