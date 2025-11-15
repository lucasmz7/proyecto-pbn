#include <stdio.h>
#include <string.h>
#include "estudiante.h"
#include "database.h"
#include "utils.h"
#include <stdbool.h>

void menu_modificar_estudiante(ListadoEstudiantes *lista) {
    printf("¿Que estudiante desea modificar? \n");
    int legajo;
    
    
    while (true) {
        printf("Legajo: ");

        if (scanf("%d", &legajo) != 1) {
            printf("ERROR: Debe ingresar un número\n");
            continue;
        }

        if (legajo < 10000 || legajo >= 100000) {
            printf("ERROR: número de legajo inválido (debe tener 5 dígitos)\n");
            continue;
        }

        break; // legajo válido → salir del loop
    }
    printf("\n");

    Estudiante *estudiante = buscar_por_legajo(lista, legajo);

    if (estudiante == NULL) {
        printf("Estudiante con legajo (%d) no existe\n", legajo);
        return;
    }
    
    char opcion;
    int valido = 0;

    while (!valido) {
        printf("Opciones:\n");
        printf("A. Modificar nombre\n");
        printf("B. Modificar legajo\n");
        printf("C. Modificar edad\n");
        printf("Z. Salir\n");
        printf("\n");

        scanf(" %c", &opcion);
        printf("\n");
        
        switch (opcion)
        {
        case 'A': {
            char nombre[50];
            printf("Ingresar nuevo nombre: ");
            scanf(" %[^\n]%*cs", nombre);
            estudiante_modificar_nombre(estudiante, nombre);
            printf("\n");
            break;
        }
        case 'B': {
            int nuevo_legajo;
            printf("Ingresar nuevo legajo: ");
            if (scanf(" %d", &nuevo_legajo) != 1) { getchar(); break; }
            printf("\n");
            estudiante_modificar_legajo(estudiante, nuevo_legajo);
            break;
        }
        case 'C': {
            int nueva_edad;
            printf("Ingresar nueva edad: ");
            if (scanf(" %d", &nueva_edad) != 1) { getchar(); break; }
            estudiante_modificar_edad(estudiante, nueva_edad);
            printf("\n");
            break;
        }
        case 'Z':
            valido = 1;
            break;
        default:
            printf("Opcion invalida.\n");
            printf("\n");
            break;
        }
    }
}

void menu_modificar_materia(ListadoMaterias *lista) {}

void menu_estadisticas() {}

//int argc, char *argv[]
int main() {
    char opcion;
    char opcion_carga;
    int valido = 0;
    int valido_carga = 0;

    printf("\n");
    printf("=========================================\n");
    printf("=== Sistema de Gestion de Estudiantes ===\n");
    printf("=========================================\n");
    printf("\n");
    

    ListadoEstudiantes *lista_estudiantes = crear_listado_estudiantes();
    ListadoMaterias *lista_materias = crear_listado_materias();

    while (!valido_carga) {
        printf("¿Desea cargar la informacion de forma manual? [S/N]\n\n");
        
        scanf(" %c", &opcion_carga);
        switch (opcion_carga)
        {
        case 'S':
            valido_carga = 1;
            break;
        case 'N':
            // TODO: parsear y cargar base de datos existente,
            valido_carga = 1;
            break;
        default:
            printf("Opcion invalida.\n");
            printf("\n");
            break;
        }
    }

    while (!valido) {
        printf("\n");
        printf("Opciones: \n");
        printf("A. Agregar un estudiante\n");
        printf("B. Eliminar un estudiante\n");
        printf("C. Modificar un estudiante\n");
        printf("D. Buscar estudiantes por nombre\n");
        printf("E. Buscar un estudiante por legajo\n");
        printf("F. Buscar estudiantes por rango de edad\n");
        printf("G. Agregar una materia\n");
        printf("H. Eliminar una materia\n");
        printf("I. Modificar una materia\n");
        printf("J. Anotar un estudiante a una materia\n");
        printf("K. Bajar un estudiante de una materia\n");
        printf("L. Rendir una materia\n");
        printf("M. Listar estudiantes\n");
        printf("N. Listar materias\n");
        printf("O. Estadisticas del sistema\n");
        printf("P. Guardar datos\n");
        printf("Z. Salir del sistema\n");
        printf("\n");

        scanf(" %c", &opcion);
        printf("\n");

        switch (opcion)
        {
        case 'A': {
            char nombre[50];
            int edad;
            int legajo;
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            printf("Edad: ");
            if (scanf(" %d", &edad) != 1) { getchar(); break; }
            printf("Legajo: ");
            if (scanf(" %d", &legajo) != 1) { getchar(); break; }
            agregar_estudiante(&lista_estudiantes, legajo, edad, nombre);
            // TODO: Desea agregar otro estudiante?
            break;
        }
        case 'B': {
            int legajo;
            printf("Legajo: ");
            printf("\n");
            if (scanf(" %d", &legajo) != 1) { getchar(); break; }
            eliminar_estudiante(&lista_estudiantes, legajo);
            break;
        }
        case 'C':
            menu_modificar_estudiante(lista_estudiantes);
            break;
        case 'D': {
            char nombre[50];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            printf("\n");
            buscar_por_nombre(lista_estudiantes, nombre);
            break;
        }
        case 'E': {
            int legajo;
            printf("Legajo: ");
            if (scanf(" %d", &legajo) != 1) { getchar(); break; }
            Estudiante *estudiante = buscar_por_legajo(lista_estudiantes, legajo);
            printf("|%-50s|%-6s|%-4s|%-20s|\n", "Nombre", "Legajo", "Edad", "Promedio");
            print_estudiante(estudiante);
            break;
        }
        case 'F': {
            int edad_min;
            int edad_max;
            printf("Edad minima (incluyente): ");
            if (scanf(" %d", &edad_min) != 1) { getchar(); break; }
            printf("Edad maxima (incluyente): ");
            if (scanf(" %d", &edad_max) != 1) { getchar(); break; }
            printf("\n");
            buscar_por_rango_edad(lista_estudiantes, edad_min, edad_max);
            break;
        }
        case 'G':
            char nombre[50];
            char identificador[16];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            printf("Identificador: ");
            scanf(" %15s", identificador);
            // TODO: Verificar
            // TODO: materia ya existente con nombre/verificador
            agregar_materia(&lista_materias, identificador, nombre);
            // TODO: Desea agregar otra materia?
            break;
        case 'H': {
            char nombre[50];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            eliminar_materia(&lista_materias, nombre);
            break;
        }
        case 'I':
            menu_modificar_materia(lista_materias);
            break;
        case 'J': {
            int legajo;
            printf("Legajo: ");
            if (scanf(" %d", &legajo) != 1) { getchar(); break; }
            char nombre[50];
            printf("Nombre de materia: ");
            scanf(" %[^\n]%*c", nombre);
            {
                Estudiante *estudiante = buscar_por_legajo(lista_estudiantes, legajo);
                if (estudiante != NULL) {
                    anotar(estudiante, lista_materias, nombre);
                }
            }
            break;
        }
        case 'K': {
            int legajo;
            printf("Legajo: ");
            if (scanf(" %d", &legajo) != 1) { getchar(); break; }
            char nombre[50];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            {
                Estudiante *estudiante = buscar_por_legajo(lista_estudiantes, legajo);
                bajar(estudiante, nombre);
            }
            break;
        }
        case 'L': {
            int legajo;
            printf("Legajo: ");
            if (scanf(" %d", &legajo) != 1) { getchar(); break; }
            int nota;
            if (scanf(" %d", &nota) != 1) { getchar(); break; }
            char nombre[50];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            {
                Estudiante *estudiante = buscar_por_legajo(lista_estudiantes, legajo);
                rendir_final(estudiante, nombre, nota);
            }
            break;
        }
        case 'M': {
            listar_estudiantes(lista_estudiantes);
            char opcion_lista;
            printf("\n");
            printf("A. Volver\n");
            printf("\n");
            scanf(" %c", &opcion_lista);
            if (opcion_lista == 'A') {
                break;
            }
            break;
        }
        case 'N': {
            listar_materias(lista_materias);
            char opcion_lista;
            printf("\n");
            printf("A. Volver\n");
            printf("\n");
            scanf(" %c", &opcion_lista);
            if (opcion_lista == 'A') {
                break;
            }
            break;
        }
        case 'O':
            // TODO
            break;
        case 'Z':
            valido = 1;
            break;                    
        default:
            printf("Opcion invalida.\n");
            break;
        } 
    }

    free(lista_estudiantes);
    free(lista_materias);

    return 0;
}

