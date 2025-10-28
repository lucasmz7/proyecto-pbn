#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Materia{
    char nombre[40];
    char identificador[5];
    bool rendida;
    float nota;
    Materia materias_correlativas[10];
} Materia;