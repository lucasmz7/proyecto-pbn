#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "materia.h"
#include "utils.h"
#include <string.h>

// Modificar los datos de una materia del listado global
void materia_modificar_nombre(Materia *materia, const char* nuevo_nombre) {
    if (verificar_nombre_materia(nuevo_nombre) != 0) {
        printf("No se pudo modificar el nombre de la materia. Nombre invalido");
        return;
    }
    strcpy(materia->nombre, nuevo_nombre);
}

void materia_modificar_identificador(Materia *materia, const char* nuevo_identificador) {
    if (verificar_identificador(nuevo_identificador) != 0) {
        printf("No se pudo modificar el identificador de la materia. Identificador invalido");
        return;        
    }
    strcpy(materia->identificador, nuevo_identificador);
}

//void materia_modificar_id(Materia *materia, int nuevo_id) {}

