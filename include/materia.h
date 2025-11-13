#ifndef MATERIA_H
#define MATERIA_H

#include <stdbool.h>

typedef struct Materia {
    char nombre[40];
    char identificador[5];
    bool rendida;
    float nota;
    //struct Materia *materias_correlativas[10];  /* Use pointers instead of array */
} Materia;

void materia_modificar_nombre(void);
void materia_modificar_correlativas(void);

#endif
