#include "database.h"
#include "estudiante.h"
#include "materia.h"
#include "cJSON.h"

/**
 * @brief Convierte un string de estado a su valor enum correspondiente.
 * @param s String que representa el estado.
 * @return EstadoMateria Valor del enum EstadoMateria.
 */
EstadoMateria json_a_estado(const char *s)
{
    if (strcmp(s, "CURSANDO") == 0)
        return CURSANDO;
    if (strcmp(s, "REGULAR PENDIENTE") == 0)
        return REGULAR_PENDIENTE;
    if (strcmp(s, "REGULAR DESAPROBADA") == 0)
        return REGULAR_DESAPROBADA;
    if (strcmp(s, "REGULAR APROBADA") == 0)
        return REGULAR_APROBADA;
    if (strcmp(s, "LIBRE") == 0)
        return LIBRE;

    return LIBRE; // Default seguro
}

/**
 * @brief Convierte un objeto JSON a una estructura MateriaGlobal.
 * @param obj Objeto JSON.
 * @return MateriaGlobal* Puntero a la materia creada.
 */
MateriaGlobal *json_a_materia(cJSON *obj)
{
    MateriaGlobal *m = malloc(sizeof(MateriaGlobal));

    strcpy(m->nombre, cJSON_GetObjectItem(obj, "nombre")->valuestring);
    strcpy(m->identificador, cJSON_GetObjectItem(obj, "id")->valuestring);

    return m;
}

/**
 * @brief Convierte un array JSON a una lista de materias.
 * @param arr Array JSON.
 * @return ListadoMaterias* Puntero a la lista de materias creada.
 */
ListadoMaterias *json_a_lista_materias(cJSON *arr)
{
    ListadoMaterias *lista = NULL, *ultimo = NULL;

    for (int i = 0; i < cJSON_GetArraySize(arr); i++)
    {
        cJSON *obj = cJSON_GetArrayItem(arr, i);
        MateriaGlobal *m = json_a_materia(obj);

        ListadoMaterias *nuevo = malloc(sizeof(ListadoMaterias));
        nuevo->data = m;
        nuevo->siguiente = NULL;

        if (!lista)
            lista = nuevo;
        else
            ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
    return lista;
}

/**
 * @brief Convierte un objeto JSON a una estructura Cursada.
 * @param obj Objeto JSON.
 * @param materias Lista de materias disponibles para referencia.
 * @return Cursada* Puntero a la cursada creada.
 */
Cursada *json_a_cursada(cJSON *obj, ListadoMaterias *materias)
{
    Cursada *c = malloc(sizeof(Cursada));

    const char *id = cJSON_GetObjectItem(obj, "id")->valuestring;
    c->referencia = buscar_por_identificador(materias, id);

    c->estado = json_a_estado(cJSON_GetObjectItem(obj, "estado")->valuestring);
    c->nota = cJSON_GetObjectItem(obj, "nota")->valuedouble;

    return c;
}

/**
 * @brief Convierte un array JSON a una lista de cursadas.
 * @param arr Array JSON.
 * @param materias Lista de materias disponibles para referencia.
 * @return ListadoCursadas* Puntero a la lista de cursadas creada.
 */
ListadoCursadas *json_a_lista_cursadas(cJSON *arr, ListadoMaterias *materias)
{
    ListadoCursadas *lista = NULL, *ultimo = NULL;

    for (int i = 0; i < cJSON_GetArraySize(arr); i++)
    {
        cJSON *obj = cJSON_GetArrayItem(arr, i);
        Cursada *c = json_a_cursada(obj, materias);

        ListadoCursadas *nuevo = malloc(sizeof(ListadoCursadas));
        nuevo->data = c;
        nuevo->siguiente = NULL;

        if (!lista)
            lista = nuevo;
        else
            ultimo->siguiente = nuevo;

        ultimo = nuevo;
    }

    return lista;
}

/**
 * @brief Convierte un objeto JSON a una estructura Estudiante.
 * @param obj Objeto JSON.
 * @param materias Lista de materias disponibles para referencia.
 * @return Estudiante* Puntero al estudiante creado.
 */
Estudiante *json_a_estudiante(cJSON *obj, ListadoMaterias *materias)
{
    Estudiante *e = malloc(sizeof(Estudiante));

    strcpy(e->nombre, cJSON_GetObjectItem(obj, "nombre")->valuestring);
    e->legajo = cJSON_GetObjectItem(obj, "legajo")->valueint;
    e->edad = cJSON_GetObjectItem(obj, "edad")->valueint;
    e->promedio = cJSON_GetObjectItem(obj, "promedio")->valuedouble;

    e->cursadas = json_a_lista_cursadas(
        cJSON_GetObjectItem(obj, "cursadas"), materias);

    e->regulares = json_a_lista_cursadas(
        cJSON_GetObjectItem(obj, "regulares"), materias);

    return e;
}

/**
 * @brief Convierte un array JSON a una lista de estudiantes.
 * @param arr Array JSON.
 * @param materias Lista de materias disponibles para referencia.
 * @return ListadoEstudiantes* Puntero a la lista de estudiantes creada.
 */
ListadoEstudiantes *json_a_lista_estudiantes(cJSON *arr, ListadoMaterias *materias)
{
    ListadoEstudiantes *lista = NULL;
    ListadoEstudiantes *ultimo = NULL;

    for (int i = 0; i < cJSON_GetArraySize(arr); i++)
    {
        cJSON *obj = cJSON_GetArrayItem(arr, i);
        Estudiante *e = json_a_estudiante(obj, materias);

        ListadoEstudiantes *nuevo = malloc(sizeof(ListadoEstudiantes));
        nuevo->data = e;
        nuevo->siguiente = NULL;

        if (!lista)
            lista = nuevo;
        else
            ultimo->siguiente = nuevo;

        ultimo = nuevo;
    }

    return lista;
}

/**
 * @brief Convierte una estructura Cursada a un objeto JSON.
 * @param c Puntero a la cursada.
 * @return cJSON* Objeto JSON creado.
 */
cJSON *cursada_a_json(Cursada *c)
{
    if (!c)
        return NULL;

    cJSON *obj = cJSON_CreateObject();

    cJSON_AddStringToObject(obj, "materia", c->referencia->nombre);
    cJSON_AddStringToObject(obj, "id", c->referencia->identificador);
    cJSON_AddStringToObject(obj, "estado", estado_a_string(c->estado));
    cJSON_AddNumberToObject(obj, "nota", c->nota);

    return obj;
}

/**
 * @brief Convierte una estructura MateriaGlobal a un objeto JSON.
 * @param m Puntero a la materia.
 * @return cJSON* Objeto JSON creado.
 */
cJSON *materia_a_json(MateriaGlobal *m)
{
    if (!m)
        return NULL;

    cJSON *obj = cJSON_CreateObject();
    cJSON_AddStringToObject(obj, "nombre", m->nombre);
    cJSON_AddStringToObject(obj, "id", m->identificador);

    return obj;
}

/**
 * @brief Convierte una lista de cursadas a un array JSON.
 * @param lista Puntero a la lista de cursadas.
 * @return cJSON* Array JSON creado.
 */
cJSON *lista_cursadas_a_json(ListadoCursadas *lista)
{
    cJSON *arr = cJSON_CreateArray();
    while (lista)
    {
        cJSON_AddItemToArray(arr, cursada_a_json(lista->data));
        lista = lista->siguiente;
    }
    return arr;
}

/**
 * @brief Convierte una estructura Estudiante a un objeto JSON.
 * @param e Puntero al estudiante.
 * @return cJSON* Objeto JSON creado.
 */
cJSON *estudiante_a_json(Estudiante *e)
{
    cJSON *obj = cJSON_CreateObject();

    cJSON_AddStringToObject(obj, "nombre", e->nombre);
    cJSON_AddNumberToObject(obj, "legajo", e->legajo);
    cJSON_AddNumberToObject(obj, "edad", e->edad);
    cJSON_AddNumberToObject(obj, "promedio", e->promedio);

    cJSON_AddItemToObject(obj, "cursadas", lista_cursadas_a_json(e->cursadas));
    cJSON_AddItemToObject(obj, "regulares", lista_cursadas_a_json(e->regulares));

    return obj;
}

/**
 * @brief Convierte una lista de estudiantes a un array JSON.
 * @param lista Puntero a la lista de estudiantes.
 * @return cJSON* Array JSON creado.
 */
cJSON *lista_estudiantes_a_json(ListadoEstudiantes *lista)
{
    cJSON *arr = cJSON_CreateArray();

    while (lista)
    {
        cJSON_AddItemToArray(arr, estudiante_a_json(lista->data));
        lista = lista->siguiente;
    }

    return arr;
}

/**
 * @brief Convierte una lista de materias a un array JSON.
 * @param lista Puntero a la lista de materias.
 * @return cJSON* Array JSON creado.
 */
cJSON *lista_materias_a_json(ListadoMaterias *lista)
{
    cJSON *arr = cJSON_CreateArray();

    while (lista)
    {
        cJSON_AddItemToArray(arr, materia_a_json(lista->data));
        lista = lista->siguiente;
    }

    return arr;
}

/**
 * @brief Guarda los datos de materias y estudiantes en un archivo JSON.
 * @param materias Lista de materias a guardar.
 * @param estudiantes Lista de estudiantes a guardar.
 * @param path Ruta del archivo de destino.
 */
void guardar_datos(ListadoMaterias *materias,
                   ListadoEstudiantes *estudiantes,
                   const char *path)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "materias",
                          lista_materias_a_json(materias));

    cJSON_AddItemToObject(root, "estudiantes",
                          lista_estudiantes_a_json(estudiantes));

    char *texto = cJSON_Print(root);

    FILE *f = fopen(path, "w");
    if (f)
    {
        fputs(texto, f);
        fclose(f);
    }

    free(texto);
    cJSON_Delete(root);
}

/**
 * @brief Carga los datos de materias y estudiantes desde un archivo JSON.
 * @param path Ruta del archivo de origen.
 * @param materias_out Puntero donde se guardará la lista de materias cargada.
 * @param estudiantes_out Puntero donde se guardará la lista de estudiantes cargada.
 * @return int 0 si se cargó correctamente, 1 si hubo error.
 */
int cargar_datos(const char *path,
                 ListadoMaterias **materias_out,
                 ListadoEstudiantes **estudiantes_out)
{
    FILE *f = fopen(path, "r");
    if (!f)
    {
        printf("[ERROR]: Ubicacion de archivo invalida");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = malloc(tam + 1);
    fread(buffer, 1, tam, f);
    buffer[tam] = '\0';

    fclose(f);

    cJSON *root = cJSON_Parse(buffer);
    free(buffer);

    // 1) cargar materias globales
    cJSON *jsonMaterias = cJSON_GetObjectItem(root, "materias");
    *materias_out = json_a_lista_materias(jsonMaterias);

    // 2) cargar estudiantes usando materias existentes
    cJSON *jsonEstudiantes = cJSON_GetObjectItem(root, "estudiantes");
    *estudiantes_out = json_a_lista_estudiantes(jsonEstudiantes, *materias_out);

    cJSON_Delete(root);
    return 0;
}
