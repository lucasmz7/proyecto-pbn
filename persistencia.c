#include "database.h"
#include "estudiante.h"
#include "materia.h"
#include "cJSON.h"

EstadoMateria json_a_estado(const char *s)
{
    if (strcmp(s, "CURSANDO") == 0)
        return CURSANDO;
    if (strcmp(s, "REGULAR_PENDIENTE") == 0)
        return REGULAR_PENDIENTE;
    if (strcmp(s, "REGULAR_DESAPROBADA") == 0)
        return REGULAR_DESAPROBADA;
    if (strcmp(s, "REGULAR_APROBADA") == 0)
        return REGULAR_APROBADA;
    if (strcmp(s, "LIBRE") == 0)
        return LIBRE;

    return LIBRE; // Default seguro
}

MateriaGlobal *json_a_materia(cJSON *obj)
{
    MateriaGlobal *m = malloc(sizeof(MateriaGlobal));

    strcpy(m->nombre, cJSON_GetObjectItem(obj, "nombre")->valuestring);
    strcpy(m->identificador, cJSON_GetObjectItem(obj, "id")->valuestring);

    m->correlativas = NULL;
    cJSON *corr = cJSON_GetObjectItem(obj, "correlativas");

    for (int i = 0; i < cJSON_GetArraySize(corr); i++)
    {
        cJSON *idcorr = cJSON_GetArrayItem(corr, i);
        // TODO
        // se procesarán después para evitar buscar antes de cargar todas las materias
        // podés guardarlo en una lista temporal
    }

    return m;
}

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

Cursada *json_a_cursada(cJSON *obj, ListadoMaterias *materias)
{
    Cursada *c = malloc(sizeof(Cursada));

    const char *id = cJSON_GetObjectItem(obj, "id")->valuestring;
    c->referencia = buscar_por_identificador(materias, id);

    c->estado = json_a_estado(cJSON_GetObjectItem(obj, "estado")->valuestring);
    c->nota = cJSON_GetObjectItem(obj, "nota")->valuedouble;

    return c;
}

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

cJSON *materia_a_json(MateriaGlobal *m)
{
    if (!m)
        return NULL;

    cJSON *obj = cJSON_CreateObject();
    cJSON_AddStringToObject(obj, "nombre", m->nombre);
    cJSON_AddStringToObject(obj, "id", m->identificador);

    cJSON *corr_arr = cJSON_CreateArray();

    ListadoCorrelativa *it = m->correlativas;
    while (it)
    {
        cJSON_AddItemToArray(corr_arr,
                             cJSON_CreateString(it->data->nombre));
        it = it->siguiente;
    }

    cJSON_AddItemToObject(obj, "correlativas", corr_arr);
    return obj;
}

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
