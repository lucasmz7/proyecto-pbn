#ifndef MATERIA_H
#define MATERIA_H

#include <stdbool.h>
typedef struct ListadoCorrelativa ListadoCorrelativa;

typedef enum
{
    CURSANDO,
    REGULAR_PENDIENTE,
    REGULAR_DESAPROBADA,
    REGULAR_APROBADA,
    LIBRE
} EstadoMateria;

typedef struct
{
    char nombre[50];
    char identificador[6];
    // lista enlazada con cada correlativa
    ListadoCorrelativa *correlativas;
} MateriaGlobal;

typedef struct
{
    MateriaGlobal *referencia;
    EstadoMateria estado;
    float nota;
} Cursada;

int materia_modificar_nombre(MateriaGlobal *materia, const char *nuevo_nombre);
int materia_modificar_identificador(MateriaGlobal *materia, const char *nuevo_identificador);
int agregar_correlativa(MateriaGlobal *materia, MateriaGlobal *correlativa);
int eliminar_correlativa(ListadoCorrelativa **lista, const char *nombre);

#endif
