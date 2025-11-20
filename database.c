#include <stdio.h>
#include <stdlib.h>
#include "estudiante.h"
#include "materia.h"
#include <string.h>
#include "database.h"

Estudiante *buscar_por_legajo(ListadoEstudiantes *lista, int legajo);
MateriaGlobal *buscar_por_identificador(ListadoMaterias *lista, const char *id);

/**
 * @brief Crea una nueva lista de estudiantes vacía.
 * @return ListadoEstudiantes* Puntero a la nueva lista (inicialmente NULL).
 */
ListadoEstudiantes *crear_listado_estudiantes()
{
    return NULL;
}

/**
 * @brief Crea una nueva lista de materias vacía.
 * @return ListadoMaterias* Puntero a la nueva lista (inicialmente NULL).
 */
ListadoMaterias *crear_listado_materias()
{
    return NULL;
}

/**
 * @brief Crea una nueva lista de cursadas vacía.
 * @return ListadoCursadas* Puntero a la nueva lista (inicialmente NULL).
 */
ListadoCursadas *crear_listado_cursadas()
{
    return NULL;
}

/**
 * @brief Agrega un nuevo estudiante a la lista.
 * @param lista Puntero doble a la lista de estudiantes.
 * @param legajo Número de legajo del estudiante.
 * @param edad Edad del estudiante.
 * @param nombre Nombre del estudiante.
 * @return int 0 si se agregó correctamente, 1 si hubo error.
 */
int agregar_estudiante(ListadoEstudiantes **lista, int legajo, int edad, const char *nombre)
{

    if (edad < 18 || edad > 100)
    {
        printf("[ERROR]: Edad invalida\n");
        return 1;
    }

    if (legajo < 100000 || legajo > 999999)
    {
        printf("[ERROR]: Legajo invalido\n");
        return 1;
    }

    if (strlen(nombre) < 1 || strlen(nombre) > 50)
    {
        printf("[ERROR]: Nombre de estudiante invalido\n");
        return 1;
    }

    if (buscar_por_legajo(*lista, legajo) != NULL)
    {
        printf("Ya existe un estudiante con ese legajo");
        return 1;
    }

    // Inicializamos Estudiante
    Estudiante *nuevo_estudiante = malloc(sizeof(Estudiante));
    nuevo_estudiante->legajo = legajo;
    nuevo_estudiante->edad = edad;
    strcpy(nuevo_estudiante->nombre, nombre);
    nuevo_estudiante->promedio = 0.0f;
    nuevo_estudiante->cursadas = NULL;
    nuevo_estudiante->regulares = NULL;

    // Incializamos nuevo nodo de la lista
    ListadoEstudiantes *nuevo_nodo = malloc(sizeof(ListadoEstudiantes));
    nuevo_nodo->data = nuevo_estudiante;
    nuevo_nodo->siguiente = NULL;

    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (*lista == NULL)
    {
        *lista = nuevo_nodo;
    }
    else // Si no, recorremos la lista hasta el final y añadimos el nuevo nodo
    {
        ListadoEstudiantes *actual = *lista;
        while (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_nodo;
    }
    return 0;
}

/**
 * @brief Agrega una nueva materia a la lista.
 * @param lista Puntero doble a la lista de materias.
 * @param identificador Identificador único de la materia.
 * @param nombre Nombre de la materia.
 * @return int 0 si se agregó correctamente, 1 si hubo error.
 */
int agregar_materia(ListadoMaterias **lista, const char *identificador, const char *nombre)
{

    if (strlen(identificador) > 6 || strlen(identificador) < 1)
    {
        printf("[ERROR]: Identificador de materia invalido\n");
        return 1;
    }

    if (strlen(nombre) > 50 || strlen(nombre) < 1)
    {
        printf("[ERROR]: Nombre de materia invalido\n");
        return 1;
    }

    if (buscar_por_identificador(*lista, identificador) != NULL)
    {
        printf("Ya existe una materia con ese identificador");
        return 1;
    }

    if (buscar_materia_por_nombre(*lista, nombre) != NULL)
    {
        printf("Ya existe una materia con ese nombre");
        return 1;
    }

    // Inicializamos Materia
    MateriaGlobal *nueva_materia = malloc(sizeof(MateriaGlobal));
    strcpy(nueva_materia->identificador, identificador);
    strcpy(nueva_materia->nombre, nombre);
    nueva_materia->cursantes = 0;
    nueva_materia->aprobados = 0;
    nueva_materia->desaprobados = 0;

    // Incializamos nuevo nodo de la lista
    ListadoMaterias *nuevo_nodo = malloc(sizeof(ListadoMaterias));
    nuevo_nodo->data = nueva_materia;
    nuevo_nodo->siguiente = NULL;

    // Si la lista está vacía, el nuevo nodo se convierte en la cabeza
    if (*lista == NULL)
    {
        *lista = nuevo_nodo;
    }
    else // Si no, recorremos la lista hasta el final y añadimos el nuevo nodo
    {
        ListadoMaterias *actual = *lista;
        while (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_nodo;
    }
    return 0;
}

/**
 * @brief Elimina un estudiante de la lista por su legajo.
 * @param lista Puntero doble a la lista de estudiantes.
 * @param legajo Legajo del estudiante a eliminar.
 * @return int 0 si se eliminó correctamente, 1 si hubo error.
 */
int eliminar_estudiante(ListadoEstudiantes **lista, int legajo)
{
    if (*lista == NULL)
    {
        printf("No hay estudiantes en la lista\n");
        return 1;
    }

    if (legajo < 100000 || legajo >= 999999)
    {
        printf("[ERROR]: Legajo invalido\n");
        return 1;
    }

    ListadoEstudiantes *actual = *lista;
    ListadoEstudiantes *previo = NULL;

    // Si el estudiante a eliminar es el primero
    if (actual->data->legajo == legajo)
    {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return 0;
    }

    // Recorremos hasta llegar encontrar el nodo a eliminar
    while (actual != NULL && (actual->data->legajo == legajo))
    {
        previo = actual;
        actual = actual->siguiente;
    }

    // Si no se encontrro
    if (actual == NULL)
    {
        printf("No existe ningun estudiante con ese legajo\n");
        return 1;
    }
    // Eliminamos el nodo y reconectamos la lista
    previo->siguiente = actual->siguiente;
    free(actual->data);
    free(actual);
    return 0;
}

/**
 * @brief Elimina una materia de la lista por su nombre.
 * @param lista Puntero doble a la lista de materias.
 * @param nombre Nombre de la materia a eliminar.
 * @return int 0 si se eliminó correctamente, 1 si hubo error.
 */
int eliminar_materia(ListadoMaterias **lista, const char *nombre)
{
    if (*lista == NULL)
    {
        printf("No hay materias en la lista\n");
        return 1;
    }

    if (strlen(nombre) < 1 || strlen(nombre) > 50)
    {
        printf("[ERROR]: Nombre de materia invalido\n");
        return 1;
    }

    ListadoMaterias *actual = *lista;
    ListadoMaterias *previo = NULL;

    // Si la materia a eliminar es la primera
    if (strcmp(actual->data->nombre, nombre) == 0)
    {
        *lista = actual->siguiente;
        free(actual->data);
        free(actual);
        return 0;
    }

    // Recorremos hasta llegar encontrar el nodo a eliminar
    while (actual != NULL && strcmp(actual->data->nombre, nombre) != 0)
    {
        previo = actual;
        actual = actual->siguiente;
    }

    // Si no se encontrro
    if (actual == NULL)
    {
        printf("No existe una materia con ese nombre\n");
        return 1;
    }

    // Eliminamos el nodo y reconectamos la lista
    previo->siguiente = actual->siguiente;
    free(actual->data);
    free(actual);
    return 0;
}

/**
 * @brief Cuenta la cantidad de estudiantes en la lista.
 * @param lista Puntero a la lista de estudiantes.
 * @return int Cantidad de estudiantes.
 */
int cantidad_estudiantes(ListadoEstudiantes *lista)
{
    int cantidad = 0;
    ListadoEstudiantes *actual = lista;
    while (actual != NULL)
    {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}

/**
 * @brief Cuenta la cantidad de materias en la lista.
 * @param lista Puntero a la lista de materias.
 * @return int Cantidad de materias.
 */
int cantidad_materias(ListadoMaterias *lista)
{
    int cantidad = 0;
    ListadoMaterias *actual = lista;
    while (actual != NULL)
    {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}

/**
 * @brief Cuenta la cantidad de cursadas en la lista.
 * @param lista Puntero a la lista de cursadas.
 * @return int Cantidad de cursadas.
 */
int cantidad_cursadas(ListadoCursadas *lista)
{
    int cantidad = 0;
    ListadoCursadas *actual = lista;
    while (actual != NULL)
    {
        cantidad++;
        actual = actual->siguiente;
    }
    return cantidad;
}

/**
 * @brief Cuenta la cantidad de materias aprobadas en la lista.
 * @param lista Puntero a la lista de cursadas.
 * @return int Cantidad de materias aprobadas.
 */
int cantidad_materias_aprobadas(ListadoCursadas *lista)
{
    int cantidad = 0;
    ListadoCursadas *actual = lista;
    while (actual != NULL)
    {
        if (actual->data->estado == REGULAR_APROBADA)
        {
            cantidad++;
        }
        actual = actual->siguiente;
    }
    return cantidad;
}

/**
 * @brief Cuenta la cantidad de materias desaprobadas en la lista.
 * @param lista Puntero a la lista de cursadas.
 * @return int Cantidad de materias desaprobadas.
 */
int cantidad_materias_desaprobadas(ListadoCursadas *lista)
{
    int cantidad = 0;
    ListadoCursadas *actual = lista;
    while (actual != NULL)
    {
        if (actual->data->estado == REGULAR_DESAPROBADA)
        {
            cantidad++;
        }
        actual = actual->siguiente;
    }
    return cantidad;
}



/**
 * @brief Muestra por pantalla el listado de estudiantes.
 * @param lista Puntero a la lista de estudiantes.
 */
void listar_estudiantes(ListadoEstudiantes *lista)
{
    if (lista == NULL)
    {
        printf("No hay estudiantes\n");
        return;
    }

    ListadoEstudiantes *actual = lista;

    printf("|%-50s|%-6s|%-4s|%-10s|%-17s|%-18s|%-21s|\n", "Nombre", "Legajo", "Edad", "Promedio", "Materias cursadas", "Materias aprobadas", "Materias desaprobadas");
    printf("|==================================================|======|====|==========|=================|==================|=====================|\n");

    while (actual != NULL)
    {
        print_estudiante(actual->data);
        actual = actual->siguiente;
    }
}

/**
 * @brief Muestra por pantalla el listado de materias.
 * @param lista Puntero a la lista de materias.
 */
void listar_materias(ListadoMaterias *lista)
{
    if (lista == NULL)
    {
        printf("No hay materias en la lista\n");
        return;
    }

    ListadoMaterias *actual = lista;

    printf("|%-50s|%-6s|%-4s|%-10s|%-17s|%-18s|%-21s|\n", "Nombre", "Legajo", "Edad", "Promedio", "Materias cursadas", "Materias aprobadas", "Materias desaprobadas");
    printf("|==================================================|======|====|==========|=================|==================|=====================|\n");

    while (actual != NULL)
    {
        print_materia(actual->data);
        actual = actual->siguiente;
    }
}

/**
 * @brief Busca estudiantes por nombre y los muestra por pantalla.
 * @param lista Puntero a la lista de estudiantes.
 * @param nombre Nombre a buscar.
 */
void buscar_por_nombre(ListadoEstudiantes *lista, const char *nombre)
{
    if (lista == NULL)
    {
        printf("No hay estudiantes en la lista\n");
        return;
    }

    if (strlen(nombre) > 50)
    {
        printf("[ERROR]: nombre demasiado largo (máximo 50 chars)\n");
        return;
    }

    ListadoEstudiantes *actual = lista;
    int encontrado = 0;

    // Recorremos la lista
    while (actual != NULL)
    {
        if (strcmp(actual->data->nombre, nombre) == 0)
        {
            // Mostrar encabezado solo la primera vez
            if (!encontrado)
            {
                printf("|%-50s|%-6s|%-4s|%-10s|%-17s|%-18s|%-21s|\n", "Nombre", "Legajo", "Edad", "Promedio", "Materias cursadas", "Materias aprobadas", "Materias desaprobadas");
                printf("|==================================================|======|====|==========|=================|==================|=====================|\n");
            }

            print_estudiante(actual->data);
            encontrado = 1;
        }

        actual = actual->siguiente;
    }

    if (!encontrado)
    {
        printf("No existe ningún estudiante con ese nombre\n");
    }
}

// Tanto edad_min como edad_max son incluyentes
/**
 * @brief Busca estudiantes dentro de un rango de edad y los muestra por pantalla.
 * @param lista Puntero a la lista de estudiantes.
 * @param edad_min Edad mínima (inclusiva).
 * @param edad_max Edad máxima (inclusiva).
 */
void buscar_por_rango_edad(ListadoEstudiantes *lista, int edad_min, int edad_max)
{
    if (lista == NULL)
    {
        printf("No hay estudiantes en la lista\n");
        return;
    }

    if (edad_min < 18 || edad_min > 100)
    {
        printf("[ERROR]: Edad mínima inválida\n");
        return;
    }

    if (edad_max < 18 || edad_max > 100)
    {
        printf("[ERROR]: Edad máxima inválida\n");
        return;
    }

    if (edad_max < edad_min)
    {
        printf("[ERROR]: El rango es inválido (edad_max < edad_min)\n");
        return;
    }

    ListadoEstudiantes *actual = lista;
    int encontrado = 0;

    while (actual != NULL)
    {
        if (actual->data->edad >= edad_min && actual->data->edad <= edad_max)
        {
            if (!encontrado)
            {
                printf("Estudiantes en el rango %d - %d\n", edad_min, edad_max);
                printf("\n");
    printf("|%-50s|%-6s|%-4s|%-10s|%-17s|%-18s|%-21s|\n", "Nombre", "Legajo", "Edad", "Promedio", "Materias cursadas", "Materias aprobadas", "Materias desaprobadas");
    printf("|==================================================|======|====|==========|=================|==================|=====================|\n");
            }

            print_estudiante(actual->data);
            encontrado = 1;
        }

        actual = actual->siguiente;
    }

    if (!encontrado)
    {
        printf("No se encontraron estudiantes entre %d y %d años.\n",
               edad_min, edad_max);
    }
}

/**
 * @brief Busca un estudiante por su legajo.
 * @param lista Puntero a la lista de estudiantes.
 * @param legajo Legajo a buscar.
 * @return Estudiante* Puntero al estudiante encontrado o NULL si no existe.
 */
Estudiante *buscar_por_legajo(ListadoEstudiantes *lista, int legajo)
{
    if (lista == NULL)
    {
        printf("No hay estudiantes en la lista\n");
        return NULL;
    }

    if (legajo < 100000 || legajo >= 999999)
    {
        printf("[ERROR]: numero de legajo invalido (debe ser de 6 digitos)\n");
        return NULL;
    }

    ListadoEstudiantes *actual = lista;
    while (actual != NULL)
    {
        if (actual->data->legajo == legajo)
        {
            return actual->data;
        }
        actual = actual->siguiente;
    }

    // No encontrado
    printf("No existe un estudiante con ese legajo\n");
    return NULL;
}

/**
 * @brief Busca una materia por su identificador.
 * @param lista Puntero a la lista de materias.
 * @param id Identificador a buscar.
 * @return MateriaGlobal* Puntero a la materia encontrada o NULL si no existe.
 */
MateriaGlobal *buscar_por_identificador(ListadoMaterias *lista, const char *id)
{
    if (lista == NULL)
    {
        printf("No hay materias en la lista\n");
        return NULL;
    }

    if (strlen(id) < 1 || strlen(id) > 6)
    {
        printf("[ERROR]: Identificador invalido\n");
        return NULL;
    }

    while (lista)
    {
        if (strcmp(lista->data->identificador, id) == 0)
            return lista->data;
        lista = lista->siguiente;
    }
    printf("No existe una materia con ese identificador\n");
    return NULL;
}

/**
 * @brief Busca una materia por su nombre.
 * @param lista Puntero a la lista de materias.
 * @param nombre Nombre a buscar.
 * @return MateriaGlobal* Puntero a la materia encontrada o NULL si no existe.
 */
MateriaGlobal *buscar_materia_por_nombre(ListadoMaterias *lista, const char *nombre)
{
    ListadoMaterias *actual = lista;
    while (actual != NULL)
    {
        if (strcmp(actual->data->nombre, nombre) == 0)
            return actual->data;

        actual = actual->siguiente;
    }
    return NULL;
}

/**
 * @brief Convierte el estado de una materia a string.
 * @param e Estado de la materia.
 * @return const char* Representación en string del estado.
 */
const char *estado_a_string(EstadoMateria e)
{
    switch (e)
    {
    case CURSANDO:
        return "CURSANDO";
    case REGULAR_PENDIENTE:
        return "REGULAR PENDIENTE";
    case REGULAR_DESAPROBADA:
        return "REGULAR DESAPROBADA";
    case REGULAR_APROBADA:
        return "REGULAR APROBADA";
    case LIBRE:
        return "LIBRE";
    }
    return "DESCONOCIDO";
}

/**
 * @brief Imprime los datos básicos de un estudiante.
 * @param estudiante Puntero al estudiante.
 */
void print_estudiante(Estudiante *estudiante)
{
    if (estudiante == NULL)
    {
        printf("[ERROR]: Struct 'Estudiante' invalido\n");
    }

    estudiante_actualizar_promedio(estudiante);
    printf("|%-50s|%-6d|%-4d|%-10.2f|%-17d|%-18d|%-21d|\n", estudiante->nombre, estudiante->legajo, estudiante->edad, estudiante->promedio, cantidad_cursadas(estudiante->regulares), cantidad_materias_aprobadas(estudiante->regulares), cantidad_materias_desaprobadas(estudiante->regulares));
}

/**
 * @brief Imprime los datos de una materia.
 * @param materia Puntero a la materia.
 */
void print_materia(MateriaGlobal *materia)
{
    if (materia == NULL)
    {
        printf("[ERROR]: Struct 'MateriaGlobal' invalido\n");
    }

    printf("|%-50s|%-6s|%-9d|%-9d|%-12d|\n", materia->nombre, materia->identificador, materia->cursantes, materia->aprobados, materia->desaprobados);
}

/**
 * @brief Imprime los datos de una cursada.
 * @param cursada Puntero a la cursada.
 */
void print_cursada(Cursada *cursada)
{
    if (cursada == NULL)
    {
        printf("[ERROR]: Struct 'Cursada' invalido\n");
    }

    const char *estado = estado_a_string(cursada->estado);

    printf("|      %-44s|%-6s|%-2.2f|%-20s|\n", cursada->referencia->nombre, cursada->referencia->identificador, cursada->nota, estado);
}

/**
 * @brief Imprime el detalle completo de un estudiante, incluyendo cursadas.
 * @param estudiante Puntero al estudiante.
 */
void print_detalle(Estudiante *estudiante)
{
    printf("|%-50s|%-6d|%-4d|%-20.2f|%-17d|%-18d|%-21d|\n", estudiante->nombre, estudiante->legajo, estudiante->edad, estudiante->promedio, cantidad_cursadas(estudiante->regulares), cantidad_materias_aprobadas(estudiante->regulares), cantidad_materias_desaprobadas(estudiante->regulares));

    ListadoCursadas *actual_cursadas = estudiante->cursadas;
    ListadoCursadas *actual_regulares = estudiante->regulares;
    printf("|==================================================|======|====|====================|=================|==================|=====================|\n");
    printf("|   %-47s|%-6s|%-4s|%-20s|\n", "Materias en curso:", "ID", "Nota", "Estado");
    while (actual_cursadas != NULL)
    {
        print_cursada(actual_cursadas->data);
        actual_cursadas = actual_cursadas->siguiente;
    }
    printf("|   %-47s|%-6s|%-4s|%-20s|\n", "Materias regulares:", "ID", "Nota", "Estado");
    while (actual_regulares != NULL)
    {
        print_cursada(actual_regulares->data);
        actual_regulares = actual_regulares->siguiente;
    }
}
