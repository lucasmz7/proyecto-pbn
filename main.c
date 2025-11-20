#include <stdio.h>
#include <string.h>
#include "estudiante.h"
#include "database.h"
#include <stdbool.h>
#include "persistencia.h"
#include <time.h>
#include "generador.h"
#include "utils.h"

int ventana_legajo();
int ventana_edad();
const char *ventana_identificador();
void menu_modificar_estudiante(ListadoEstudiantes *lista);
void menu_modificar_materia(ListadoMaterias *lista);
void menu_busqueda_estudiante(ListadoEstudiantes *lista);
void menu_busqueda_materia(ListadoMaterias *lista);
void menu_estadisticas(ListadoEstudiantes *estudiantes, ListadoMaterias *materias);

int main()
{
    char opcion;
    char opcion_carga;
    int valido = 0;
    int valido_carga = 0;

    printf("\n");
    printf("|=========================================|\n");
    printf("|=== Sistema de Gestion de Estudiantes ===|\n");
    printf("|=========================================|\n");
    printf("\n");

    ListadoEstudiantes *lista_estudiantes = crear_listado_estudiantes();
    ListadoMaterias *lista_materias = crear_listado_materias();

    while (!valido_carga)
    {
        printf("¿De que forma desea inicializar los datos del sistema?\n");
        printf("\n");
        printf("Opciones: \n");
        printf("A. Inicializar base de datos vacia\n");
        printf("B. Inicializar base de datos a partir de un archivo JSON\n");
        printf("C. Inicializar base de datos con materias y estudiantes aleatorios\n");
        printf("\n");

        scanf(" %c", &opcion_carga);
        switch (opcion_carga)
        {
        case 'A':
            valido_carga = 1;
            break;
        case 'B':
            char path[100];
            printf("Ubicacion: ");
            scanf(" %99s", &path);
            cargar_datos(path, &lista_materias, &lista_estudiantes);
            valido_carga = 1;
            break;
        case 'C':
            printf("\n");
            int cant_estudiantes;
            int cant_materias;
            printf("Cantidad de estudiantes: ");
            scanf(" %d", &cant_estudiantes);
            printf("Cantidad de materias: ");
            scanf(" %d", &cant_materias);
            int check = generador(&lista_estudiantes, &lista_materias, cant_estudiantes, cant_materias);
            if (check != 0)
            {
                break;
            }
            valido_carga = 1;
            break;
        default:
            printf("Opcion invalida.\n");
            printf("\n");
            break;
        }
    }

    while (!valido)
    {
        printf("\n");
        printf("Opciones: \n");
        printf("=== Estudiantes ===\n");
        printf("A. Agregar un estudiante\n");
        printf("B. Eliminar un estudiante\n");
        printf("C. Modificar un estudiante\n");
        printf("D. Buscar estudiantes por nombre\n");
        printf("E. Buscar un estudiante por legajo\n");
        printf("F. Buscar estudiantes por rango de edad\n");
        printf("=== Materias ===\n");
        printf("G. Agregar una materia\n");
        printf("H. Eliminar una materia\n");
        printf("I. Modificar una materia\n");
        printf("J. Anotar un estudiante a una materia\n");
        printf("K. Bajar un estudiante de una materia\n");
        printf("L. Rendir una materia\n");
        printf("=== Bases de datos ===\n");
        printf("M. Listar estudiantes\n");
        printf("N. Listar materias\n");
        printf("=== Otros ===\n");
        printf("O. Estadisticas del sistema\n");
        printf("P. Guardar datos\n");
        printf("Z. Salir del sistema\n");
        printf("\n");

        scanf(" %c", &opcion);
        printf("\n");

        switch (opcion)
        {
        case 'A':
        {
            char nombre[50];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            int edad = ventana_edad();
            int legajo = ventana_legajo();
            agregar_estudiante(&lista_estudiantes, legajo, edad, nombre);
            // TODO: Desea agregar otro estudiante?
            break;
        }
        case 'B':
        {
            int legajo = ventana_legajo();
            eliminar_estudiante(&lista_estudiantes, legajo);
            break;
        }
        case 'C':
            menu_modificar_estudiante(lista_estudiantes);
            break;
        case 'D':
        {
            char nombre[50];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            printf("\n");
            buscar_por_nombre(lista_estudiantes, nombre);
            menu_busqueda_estudiante(lista_estudiantes);
            break;
        }
        case 'E':
        {
            int legajo = ventana_legajo();
            Estudiante *estudiante = buscar_por_legajo(lista_estudiantes, legajo);
            printf("|%-50s|%-6s|%-4s|%-20s|\n", "Nombre", "Legajo", "Edad", "Promedio");
            print_estudiante(estudiante);
            menu_busqueda_estudiante(lista_estudiantes);
            break;
        }
        case 'F':
        {
            printf("Ingresar edad minima:\n");
            int edad_min = ventana_edad();
            printf("Ingresar edad maxima:\n");
            int edad_max = ventana_edad();
            printf("\n");
            buscar_por_rango_edad(lista_estudiantes, edad_min, edad_max);
            menu_busqueda_estudiante(lista_estudiantes);
            break;
        }
        case 'G':
            char nombre[50];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            printf("Ingresar identificador:\n");
            const char *identificador = ventana_identificador();
            agregar_materia(&lista_materias, identificador, nombre);
            // TODO: Desea agregar otra materia?
            break;
        case 'H':
        {
            char nombre[50];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            eliminar_materia(&lista_materias, nombre);
            break;
        }
        case 'I':
            menu_modificar_materia(lista_materias);
            break;
        case 'J':
        {
            printf("Ingresar legajo:\n");
            int legajo = ventana_legajo();
            char nombre[50];
            printf("Nombre de materia: ");
            scanf(" %[^\n]%*c", nombre);
            {
                Estudiante *estudiante = buscar_por_legajo(lista_estudiantes, legajo);
                if (estudiante != NULL)
                {
                    anotar(estudiante, lista_materias, nombre);
                }
            }
            break;
        }
        case 'K':
        {
            int legajo = ventana_legajo();
            char nombre[50];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            {
                Estudiante *estudiante = buscar_por_legajo(lista_estudiantes, legajo);
                bajar(estudiante, nombre);
            }
            break;
        }
        case 'L':
        {
            int legajo = ventana_legajo();
            int nota;
            if (scanf(" %d", &nota) != 1)
            {
                getchar();
                break;
            }
            char nombre[50];
            printf("Nombre: ");
            scanf(" %[^\n]%*c", nombre);
            {
                Estudiante *estudiante = buscar_por_legajo(lista_estudiantes, legajo);
                rendir_final(estudiante, nombre, nota);
            }
            break;
        }
        case 'M':
        {
            listar_estudiantes(lista_estudiantes);
            menu_busqueda_estudiante(lista_estudiantes);
            break;
        }
        case 'N':
        {
            listar_materias(lista_materias);
            menu_busqueda_materia(lista_materias);
            break;
        }
        case 'O':
            menu_estadisticas(lista_estudiantes, lista_materias);
            break;
        case 'P':
        {
            time_t now = time(NULL);
            struct tm *tm_info = localtime(&now);
            char filepath[256];

            strftime(filepath, sizeof(filepath), "./data/datos_%Y%m%d_%H%M%S.json", tm_info);

            guardar_datos(lista_materias, lista_estudiantes, filepath);
            printf("Datos guardados en: %s\n", filepath);
            break;
        }
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

int ventana_legajo()
{
    int legajo;

    while (true)
    {
        printf("Legajo: ");

        if (scanf("%d", &legajo) != 1)
        {
            printf("[ERROR]: Debe ingresar un número\n");
            continue;
        }

        if (legajo < 100000 || legajo > 999999)
        {
            printf("[ERROR]: número de legajo inválido (debe tener 6 dígitos)\n");
            continue;
        }

        printf("\n");

        break; // legajo válido → salir del loop
    }
    return legajo;
}

int ventana_edad()
{
    int edad;
    while (true)
    {
        printf("Edad: ");

        if (scanf("%d", &edad) != 1)
        {
            printf("[ERROR]: Debe ingresar un número\n");
            continue;
        }

        if (edad >= 101)
        {
            printf("[ERROR]: Edad debe ser menor o igual que 100\n");
            continue;
        }

        if (edad < 18)
        {
            printf("[ERROR]: Edad debe ser mayor o igual que 18\n");
            continue;
        }

        printf("\n");

        break;
    }
    return edad;
}

const char *ventana_identificador()
{
    const char *id;
    while (true)
    {
        printf("Identificador: ");

        if (scanf("%c", &id) != 1)
        {
            printf("[ERROR]: Debe ingresar un número\n");
            continue;
        }

        if (strlen(id) > 6)
        {
            printf("[ERROR]: El identificador debe ser de 6 o menos caracteres\n");
            continue;
        }

        if (strlen(id) < 1)
        {
            printf("[ERROR]: El identificador debe ser de 1 o mas caracteres\n");
            continue;
        }

        printf("\n");

        break;
    }
    return id;
}

void menu_modificar_estudiante(ListadoEstudiantes *lista)
{
    printf("¿Que estudiante desea modificar? \n");
    printf("\n");

    int legajo = ventana_legajo();
    Estudiante *estudiante = buscar_por_legajo(lista, legajo);

    char opcion;
    int valido = 0;

    while (!valido)
    {
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
        case 'A':
        {
            char nombre[50];
            printf("Ingresar nuevo nombre: \n");
            scanf(" %[^\n]%*cs", nombre);
            estudiante_modificar_nombre(estudiante, nombre);
            printf("\n");
            break;
        }
        case 'B':
        {
            printf("Ingresar nuevo legajo: \n");
            int nuevo_legajo = ventana_legajo();
            estudiante_modificar_legajo(estudiante, nuevo_legajo);
            break;
        }
        case 'C':
        {
            printf("Ingresar nueva edad: \n");
            int nueva_edad = ventana_edad();
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

void menu_modificar_materia(ListadoMaterias *lista)
{
    printf("¿Que estudiante desea modificar? \n");
    printf("\n");

    const char *id = ventana_identificador();
    MateriaGlobal *materia = buscar_por_identificador(lista, id);

    char opcion;
    int valido = 0;

    while (!valido)
    {
        printf("Opciones:\n");
        printf("A. Modificar nombre\n");
        printf("B. Modificar identificador\n");
        printf("Z. Salir\n");
        printf("\n");

        scanf(" %c", &opcion);
        printf("\n");

        switch (opcion)
        {
        case 'A':
        {
            char nombre[50];
            printf("Ingresar nuevo nombre: \n");
            scanf(" %[^\n]%*cs", nombre);
            materia_modificar_nombre(materia, nombre);
            printf("\n");
            break;
        }
        case 'B':
        {
            printf("Ingresar nuevo identificador: \n");
            const char *nuevo_id = ventana_identificador();
            materia_modificar_identificador(materia, nuevo_id);
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

void menu_busqueda_estudiante(ListadoEstudiantes *lista)
{
    int valido = 0;
    while (!valido)
    {
        char opcion_lista;
        printf("\n");
        printf("A. Mostrar un estudiante\n");
        printf("B. Volver\n");
        printf("\n");
        scanf(" %c", &opcion_lista);

        switch (opcion_lista)
        {
        case 'A':
            printf("\n");
            printf("¿Que estudiante desea ver?");
            printf("\n");
            int legajo = ventana_legajo();
            printf("\n");
            Estudiante *estudiante = buscar_por_legajo(lista, legajo);
            print_detalle(estudiante);
            break;
        case 'B':
            valido = 1;
            return;
        default:
            printf("Opcion invalida.\n");
            printf("\n");
            break;
        }
    }
}

void menu_busqueda_materia(ListadoMaterias *lista)
{
    int valido = 0;
    while (!valido)
    {
        char opcion_lista;
        printf("\n");
        printf("A. Mostrar una materia\n");
        printf("B. Volver\n");
        printf("\n");
        scanf(" %c", &opcion_lista);

        switch (opcion_lista)
        {
        case 'A':
            printf("\n");
            printf("¿Que materia desea ver?");
            printf("\n");
            const char *id = ventana_identificador();
            printf("\n");
            MateriaGlobal *materia = buscar_por_identificador(lista, id);
            print_materia(materia);
            break;
        case 'B':
            valido = 1;
            return;
        default:
            printf("Opcion invalida.\n");
            printf("\n");
            break;
        }
    }
}

void menu_estadisticas(ListadoEstudiantes *estudiantes, ListadoMaterias *materias)
{

    const int cant_estudiantes = cantidad_estudiantes(estudiantes);
    const int cant_materia = cantidad_materias(materias);

    // TODO: si no hay estudiantes volver? si no hay materias volver? o mostrar solo lo que haya

    printf("Estadisticas:\n");
    printf("\n");

    printf("Cantidad total de estudiantes: %d\n", cant_estudiantes);
    printf("Cantidad total de materias: %d\n", cant_materia);
    printf("\n");

    int promedio_general = 0;
    ListadoEstudiantes *actual1 = estudiantes;
    while (actual1 != NULL)
    {
        promedio_general += actual1->data->promedio;
        actual1 = actual1->siguiente;
    }
    printf("Promedio general: %d\n", promedio_general / cant_estudiantes);
    printf("\n");

    int edad_promedio = 0;
    ListadoEstudiantes *actual2 = estudiantes;
    while (actual2 != NULL)
    {
        edad_promedio += actual2->data->edad;
        actual2 = actual2->siguiente;
    }
    printf("Edad promedio: %d\n", edad_promedio / cant_estudiantes);

    int edad_maxima = 0;
    ListadoEstudiantes *actual3 = estudiantes;
    while (actual3 != NULL)
    {
        if (actual3->data->edad > edad_maxima)
        {
            edad_maxima = actual3->data->edad;
        }
        actual3 = actual3->siguiente;
    }

    printf("Edad maxima: %d\n", edad_maxima);
    printf("\n");

    printf("Mejores promedios:\n");
    imprimir_k_mejores_estudiantes(estudiantes, 5);
    printf("\n");

    printf("Peores promedios:\n");
    imprimir_k_peores_estudiantes(estudiantes, 5);
    printf("\n");

    // TODO:
    // 5 materias menos cursadas
    // 5 materias mas cursadas
    // promedio de materias cursadas por estudiante (tasa de aprobacion, tasa de desaprobacion)
    // materias con mas aprobados y mas desaprobados (usar porcentaje)
    // cantidad de estudiantes no cursan nadas
    // estudiantes con mas materias historicas
}
