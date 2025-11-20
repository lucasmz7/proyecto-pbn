#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "materia.h"
#include <string.h>
#include "database.h"

/**
 * @brief Modifica el nombre de una materia.
 * @param materia Puntero a la materia.
 * @param nuevo_nombre Nuevo nombre para la materia.
 * @return int 0 si se modificó correctamente, 1 si hubo error.
 */
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

/**
 * @brief Modifica el identificador de una materia.
 * @param materia Puntero a la materia.
 * @param nuevo_identificador Nuevo identificador para la materia.
 * @return int 0 si se modificó correctamente, 1 si hubo error.
 */
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
