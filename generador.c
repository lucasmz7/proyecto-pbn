#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "estudiante.h"
#include "database.h"

const char *NOMBRES_MATERIAS[] = {
    "Algebra I",
    "Algebra II",
    "Algebra Lineal",
    "Analisis Matematico I",
    "Analisis Matematico II",
    "Analisis Matematico III",
    "Probabilidad y Estadistica",
    "Estadistica Aplicada",
    "Ecuaciones Diferenciales",
    "Variable Compleja",
    "Geometria Analitica",
    "Geometria Diferencial",
    "Topologia I",
    "Topologia II",
    "Matematica Discreta",
    "Logica Matematica",
    "Metodos Numericos",
    "Introduccion a la Programacion",
    "Programacion Imperativa",
    "Programacion Orientada a Objetos",
    "Estructuras de Datos",
    "Algoritmos y Complejidad",
    "Bases de Datos",
    "Modelos y Simulacion",
    "Sistemas Operativos",
    "Redes de Computadoras",
    "Arquitectura de Computadoras",
    "Organizacion del Computador",
    "Compiladores",
    "Lenguajes Formales y Automatas",
    "Ingenieria de Software I",
    "Ingenieria de Software II",
    "Metodos Formales",
    "Computacion Grafica",
    "Sistemas Distribuidos",
    "Inteligencia Artificial",
    "Machine Learning",
    "Deep Learning",
    "Sistemas Embebidos",
    "Robotica I",
    "Robotica II",
    "Teoria de la Computacion",
    "Criptografia",
    "Seguridad Informatica",
    "Procesamiento Digital de Imagenes",
    "Vision por Computadora",
    "Biomecanica Computacional",

    // Fisica
    "Fisica I",
    "Fisica II",
    "Fisica III",
    "Fisica Moderna",
    "Electromagnetismo",
    "Mecanica Clasica",
    "Mecanica Analitica",
    "Termodinamica",
    "Optica",
    "Fisica del Estado Solido",
    "Fisica Cuantica I",
    "Fisica Cuantica II",
    "Metodos Experimentales",
    "Laboratorio de Fisica I",
    "Laboratorio de Fisica II",
    "Laboratorio de Optica",
    "Laboratorio de Electricidad y Magnetismo",

    // Quimica
    "Quimica General",
    "Quimica Inorganica",
    "Quimica Organica I",
    "Quimica Organica II",
    "Fisicoquimica",
    "Quimica Analitica",
    "Bioquimica",
    "Laboratorio de Quimica I",
    "Laboratorio de Quimica II",
    "Quimica de Materiales",
    "Nanotecnologia Quimica",

    // Biologia / Exactas
    "Biologia Celular",
    "Biologia Molecular",
    "Genetica",
    "Bioinformatica",
    "Microbiologia",
    "Ecologia",
    "Zoologia",
    "Botanica",

    // Ingenieria Electronica
    "Circuitos Electricos I",
    "Circuitos Electricos II",
    "Electronica I",
    "Electronica II",
    "Electronica Digital",
    "Telecomunicaciones",
    "Sistemas de Control",
    "Control Automatico",
    "Microprocesadores",
    "Antenas y Propagacion",
    "Dispositivos Semiconductores",
    "Instrumentacion Electronica",
    "Electrotecnia",

    // Ingenieria Mecanica
    "Mecanica de Fluidos",
    "Mecanica de Solidos",
    "Estatica",
    "Dinamica",
    "Resistencia de Materiales",
    "Termodinamica Aplicada",
    "Maquinas Termicas",
    "Materiales Industriales",
    "Procesos de Manufactura",
    "Ingenieria de Transporte",

    // Ingenieria Quimica
    "Balance de Materia y Energia",
    "Cinetica Quimica",
    "Operaciones Unitarias I",
    "Operaciones Unitarias II",
    "Reacciones Quimicas",
    "Ingenieria de Procesos",
    "Ingenieria Ambiental",
    "Polimeros",

    // Ingenieria Civil
    "Materiales de Construccion",
    "Hidraulica",
    "Topografia",
    "Geotecnia",
    "Hormigon Armado",
    "Mecanica de Suelos",
    "Transporte y Vias de Comunicacion",
    "Urbanismo",
    "Planificacion Territorial",

    // Ingenierias varias
    "Sistemas de Informacion Geografica",
    "Mineralogia",
    "Geologia General",
    "Petrologia",
    "Geomorfologia",
    "Introduccion a la Aerodinamica",
    "Estructuras Aeronauticas",
    "Propulsion Espacial",

    // Optativas (muchas)
    "Introduccion al Data Science",
    "Mineria de Datos",
    "Teoria de Juegos",
    "Optimizacion I",
    "Optimizacion II",
    "Computacion Paralela",
    "Cloud Computing",
    "Blockchain",
    "Ciberseguridad Avanzada",
    "Desarrollo de Videojuegos",
    "Realidad Aumentada",
    "Realidad Virtual",
    "Criptomonedas y Sistemas Descentralizados",
    "Modelado de Fenomenos Fisicos",
    "Modelado Estocastico",
    "Simulacion Monte Carlo",
    "Astronomia General",
    "Astrofisica",
    "Cosmologia",
    "Energias Renovables",
    "Tecnologia Nuclear",
    "Fision y Fusion Nuclear",
    "Ingenieria Biomedica",
    "Prostetica y Bionica",
    "Bioinstrumentacion",
    "Biofisica",
    "Microbiologia Industrial",
    "Machine Learning para Fisica",
    "Introduccion al Internet de las Cosas",
    "Sistemas Autonomos",
    "Analisis de Big Data",
    "Criptografia Cuantica",
    "Computacion Cuantica",
    "Linguistica Computacional",
    "Matematica para IA",
    "Sistemas no Lineales",
    "Teoria del Caos",
    "Metodos Variacionales",
    "Introduccion a la Nanotecnologia",
    "Fabricacion Aditiva",
    "Ingenieria de Materiales Avanzados",
    "Sensores y Actuadores",
    "Acustica y Vibraciones",
    "Modelos Climaticos",
    "Ciencia del Clima",
    "Bioestadistica",
    "Epistemologia de la Ciencia",
    "Historia de la Tecnologia",
    "Taller de Investigacion",
    "Seminario Final",
    "Seminario de Tesis I",
    "Seminario de Tesis II"};

const int TOTAL_NOMBRES_MATERIAS = sizeof(NOMBRES_MATERIAS) / sizeof(NOMBRES_MATERIAS[0]);

const char *NOMBRES[] = {
    "Agustin", "Alejandro", "Alvaro", "Andres", "Axel",
    "Benjamin", "Bruno", "Camilo", "Carlos", "Cristian",
    "Daniel", "Diego", "Dylan", "Elias", "Emiliano",
    "Esteban", "Facundo", "Federico", "Franco", "Gabriel",
    "Gonzalo", "Guillermo", "Hector", "Hernan", "Ian",
    "Ignacio", "Ismael", "Ivan", "Joaquin", "Joel",
    "Jonathan", "Jose", "Juan", "Julian", "Kevin",
    "Lautaro", "Leonardo", "Lucas", "Luciano", "Luis",
    "Manuel", "Marcos", "Mario", "Martin", "Mateo",
    "Matias", "Maximiliano", "Nicolas", "Pablo", "Patricio",
    "Pedro", "Ramiro", "Ricardo", "Rodrigo", "Santiago",
    "Sebastian", "Sergio", "Tomas", "Ulises", "Valentin",
    "Victor", "Walter", "Yamil", "Zahir",
    "Abril", "Agustina", "Ailen", "Aitana", "Alejandra",
    "Ana", "Andrea", "Antonella", "Azul", "Bianca",
    "Brenda", "Camila", "Candela", "Carla", "Catalina",
    "Cecilia", "Clara", "Constanza", "Daniela", "Delfina",
    "Elena", "Emilia", "Erica", "Eva", "Fiorella",
    "Florencia", "Gabriela", "Giuliana", "Guadalupe", "Ines",
    "Isabella", "Jazmin", "Jennifer", "Jimena", "Josefina",
    "Juana", "Julieta", "Kiara", "Laura", "Lara",
    "Lucia", "Malena", "Marina", "Martina", "Melanie",
    "Milagros", "Micaela", "Morena", "Nadia", "Noelia",
    "Paula", "Pilar", "Rocio", "Romina", "Sabrina",
    "Salome", "Sofia", "Stefania", "Tatiana", "Valeria",
    "Victoria", "Yasmin"};

const char *APELLIDOS[] = {
    "Acosta", "Aguirre", "Alvarez", "Alvarenga", "Amaya",
    "Aranda", "Araujo", "Arias", "Ayala", "Barrera",
    "Barrios", "Benitez", "Blanco", "Borda", "Bravo",
    "Caballero", "Caceres", "Cano", "Cardozo", "Carrizo",
    "Castillo", "Castro", "Cervantes", "Cisneros", "Colman",
    "Cordoba", "Correa", "Cuevas", "Duarte", "Escobar",
    "Esquivel", "Fernandez", "Figueroa", "Flores", "Franco",
    "Galeano", "Gallardo", "Garcia", "Gimenez", "Godoy",
    "Gomez", "Gonzalez", "Guerrero", "Heredia", "Herrera",
    "Ibarra", "Ledesma", "Leguizamon", "Lopez", "Luna",
    "Maidana", "Martinez", "Medina", "Mendez", "Miranda",
    "Molina", "Monzon", "Morales", "Mori", "Navarro", "Ojeda", "Olmedo", "Ortiz", "Paez",
    "Paredes", "Perez", "Ponce", "Ramirez", "Reyes",
    "Rios", "Rivero", "Rodriguez", "Romero", "Ruiz",
    "Salinas", "Sanchez", "Sosa", "Suarez", "Torres",
    "Valdez", "Vargas", "Vazquez", "Velazquez", "Vera",
    "Vergara", "Villalba", "Villanueva", "Zarate", "Zavala"};

/**
 * @brief Genera un estudiante con datos aleatorios y lo agrega a la lista.
 * @param lista Puntero doble a la lista de estudiantes.
 */
void generar_estudiante_aleatorio(ListadoEstudiantes **lista)
{
    const char *nombre = NOMBRES[rand() % (sizeof(NOMBRES) / sizeof(NOMBRES[0]))];
    const char *apellido = APELLIDOS[rand() % (sizeof(APELLIDOS) / sizeof(APELLIDOS[0]))];

    char nombre_completo[50];
    snprintf(nombre_completo, sizeof(nombre_completo), "%s %s", nombre, apellido);

    int legajo = 100000 + rand() % 900000;
    int edad = 18 + rand() % 23;

    do
    {
        legajo = 100000 + rand() % 900000;
    } while (*lista != NULL && buscar_por_legajo(*lista, legajo, 1) != NULL);

    agregar_estudiante(lista, legajo, edad, nombre_completo, 1);
}

/**
 * @brief Genera una materia con datos aleatorios y la agrega a la lista.
 * @param lista Puntero doble a la lista de materias.
 */
void generar_materia_aleatoria(ListadoMaterias **lista)
{

    int total_nombres = sizeof(NOMBRES_MATERIAS) / sizeof(NOMBRES_MATERIAS[0]);
    const char *nombre_random = NOMBRES_MATERIAS[rand() % total_nombres];

    char id[7]; // 6 caracteres para el ID + 1 para el null terminator '\0'
    do
    {
        for (int i = 0; i < 6; i++)
        {
            int r = rand() % 36;
            if (r < 26)
                id[i] = 'A' + r;
            else
                id[i] = '0' + (r - 26);
        }
        id[6] = '\0'; // Null terminator OBLIGATORIO para que sea un string válido
    } while (*lista != NULL && buscar_por_identificador(*lista, id, 1) != NULL);

    agregar_materia(lista, id, nombre_random, 1);
}



/**
 * @brief Genera un conjunto de estudiantes y materias aleatorios.
 * @param estudiantes Puntero doble a la lista de estudiantes.
 * @param materias Puntero doble a la lista de materias.
 * @param cantidad_estudiantes Cantidad de estudiantes a generar.
 * @param cantidad_materias Cantidad de materias a generar.
 * @return int 0 si se generó correctamente, 1 si hubo error.
 */
int generador(ListadoEstudiantes **estudiantes,
              ListadoMaterias **materias,
              int cantidad_estudiantes,
              int cantidad_materias)
{
    srand(time(NULL));

    if (cantidad_materias > TOTAL_NOMBRES_MATERIAS)
    {
        printf("[ERROR]: No se pueden generar %d materias.\n", cantidad_materias);
        printf("Solo hay %d nombres disponibles.\n", TOTAL_NOMBRES_MATERIAS);
        return 1;
    }

    // Legajos disponibles: del 100000 al 999999   → 900000 posibles
    const int TOTAL_LEGAJOS_POSIBLES = 900000;

    if (cantidad_estudiantes > TOTAL_LEGAJOS_POSIBLES)
    {
        printf("[ERROR]: No se pueden generar %d estudiantes.\n", cantidad_estudiantes);
        printf("Solo hay %d legajos disponibles (6 digitos).\n", TOTAL_LEGAJOS_POSIBLES);
        return 1;
    }

    for (int i = 0; i < cantidad_estudiantes; i++)
    {
        generar_estudiante_aleatorio(estudiantes);
    }

    for (int i = 0; i < cantidad_materias; i++)
    {
        generar_materia_aleatoria(materias);
    }

    printf("Generacion exitosa\n");
    return 0;
}

/**
 * @brief Anota a un estudiante en una cantidad aleatoria de materias (entre 0 y 5).
 * @param estudiante Puntero al estudiante a anotar.
 * @param materias Puntero a la lista de materias disponibles.
 * @return int Cantidad de materias en las que se anotó el estudiante.
 */
int anotar_estudiante_materias_aleatorias(Estudiante *estudiante, ListadoMaterias *materias)
{
    if (estudiante == NULL || materias == NULL)
    {
        return 0;
    }

    // Contar cuántas materias hay disponibles
    int total_materias = cantidad_materias(materias);
    if (total_materias == 0)
    {
        return 0;
    }

    // Determinar cantidad de materias a anotar (entre 0 y 5, pero no más que las disponibles)
    int max_anotaciones = (total_materias < 5) ? total_materias : 5;
    int cantidad_a_anotar = rand() % (max_anotaciones + 1); // 0 a max_anotaciones

    if (cantidad_a_anotar == 0)
    {
        return 0;
    }

    // Crear un array con todas las materias disponibles
    MateriaGlobal **materias_disponibles = (MateriaGlobal **)malloc(sizeof(MateriaGlobal *) * total_materias);
    ListadoMaterias *actual = materias;
    int idx = 0;
    while (actual != NULL)
    {
        materias_disponibles[idx++] = actual->data;
        actual = actual->siguiente;
    }

    // Seleccionar materias aleatorias sin repetir
    int anotadas = 0;
    for (int i = 0; i < cantidad_a_anotar; i++)
    {
        // Seleccionar una materia aleatoria del rango restante
        int indice_aleatorio = i + (rand() % (total_materias - i));
        
        // Intercambiar para evitar repeticiones
        MateriaGlobal *temp = materias_disponibles[i];
        materias_disponibles[i] = materias_disponibles[indice_aleatorio];
        materias_disponibles[indice_aleatorio] = temp;

        // Anotar al estudiante en la materia seleccionada
        if (anotar(estudiante, materias, materias_disponibles[i]->nombre) == 0)
        {
            anotadas++;
        }
    }

    free(materias_disponibles);
    return anotadas;
}

/**
 * @brief Hace rendir al estudiante una cantidad aleatoria de sus materias cursadas actuales.
 * @param estudiante Puntero al estudiante.
 * @return int Cantidad de materias rendidas.
 */
int rendir_materias_aleatorias(Estudiante *estudiante)
{
    if (estudiante == NULL || estudiante->cursadas == NULL)
    {
        return 0;
    }

    // Contar cuántas cursadas tiene
    int total_cursadas = cantidad_cursadas(estudiante->cursadas);
    if (total_cursadas == 0)
    {
        return 0;
    }

    // Determinar cantidad de materias a rendir (entre 0 y total_cursadas)
    int cantidad_a_rendir = rand() % (total_cursadas + 1);

    if (cantidad_a_rendir == 0)
    {
        return 0;
    }

    // Crear un array con los NOMBRES de todas las cursadas (no punteros a Cursada)
    // Esto es necesario porque rendir_final() modifica la lista de cursadas
    char **nombres_cursadas = (char **)malloc(sizeof(char *) * total_cursadas);
    ListadoCursadas *actual = estudiante->cursadas;
    int idx = 0;
    while (actual != NULL)
    {
        nombres_cursadas[idx] = (char *)malloc(sizeof(char) * 50);
        strcpy(nombres_cursadas[idx], actual->data->referencia->nombre);
        idx++;
        actual = actual->siguiente;
    }

    // Seleccionar cursadas aleatorias sin repetir
    int rendidas = 0;
    for (int i = 0; i < cantidad_a_rendir; i++)
    {
        // Seleccionar un índice aleatorio del rango restante
        int indice_aleatorio = i + (rand() % (total_cursadas - i));
        
        // Intercambiar para evitar repeticiones
        char *temp = nombres_cursadas[i];
        nombres_cursadas[i] = nombres_cursadas[indice_aleatorio];
        nombres_cursadas[indice_aleatorio] = temp;

        // Generar nota aleatoria entre 1 y 10
        int nota = 1 + (rand() % 10);

        // Rendir la materia
        if (rendir_final(estudiante, nombres_cursadas[i], nota) == 0)
        {
            rendidas++;
        }
    }

    // Liberar memoria
    for (int i = 0; i < total_cursadas; i++)
    {
        free(nombres_cursadas[i]);
    }
    free(nombres_cursadas);
    
    return rendidas;
}
