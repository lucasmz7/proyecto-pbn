#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "materia.h"
#include <string.h>
#include "database.h"

int materia_modificar_nombre(MateriaGlobal *materia, const char *nuevo_nombre)
{
    if (strlen(nuevo_nombre) > 50 || strlen(nuevo_nombre) < 1)
    {
        printf("[ERROR]: Nombre de materia invalido\n");
        return 1;
    }
    strcpy(materia->nombre, nuevo_nombre);
    return 0;
}

int materia_modificar_identificador(MateriaGlobal *materia, const char *nuevo_identificador)
{
    if (strlen(nuevo_identificador) > 6 || strlen(nuevo_identificador) < 1)
    {
        printf("[ERROR]: Identificador de materia invalido\n");
        return 1;
    }
    strcpy(materia->identificador, nuevo_identificador);
    return 0;
}
