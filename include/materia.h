#ifndef MATERIA_H
#define MATERIA_H

#include <stdbool.h>

typedef enum {
    PENDIENTE,
    REGULAR,
    APROBADA
} EstadoMateria;

typedef struct {
    char nombre[40];
    char identificador[5];
    int id;
    EstadoMateria estado;
    float nota;
    //struct Materia *materias_correlativas[10]; 
} Materia;

//void materia_modificar_correlativas(void);
void materia_modificar_nombre(Materia *materia, char* nuevo_nombre);
void materia_modificar_id(Materia *materia, int nuevo_id);
void materia_modificar_identificador(Materia *materia, const char* nuevo_identificador);

#endif

