#include <stdlib.h>
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
    "Procesamiento de Señales",
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
    "Diseño Mecanico",
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
    "Diseño Estructural",
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
    "Diseño de Reactores",
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
    "Molina", "Monzon", "Morales", "Mori", "Navarro",
    "Nuñez", "Ojeda", "Olmedo", "Ortiz", "Paez",
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
    } while (*lista != NULL && buscar_por_legajo(*lista, legajo) != NULL);

    agregar_estudiante(lista, legajo, edad, nombre_completo);
}

/**
 * @brief Genera una materia con datos aleatorios y la agrega a la lista.
 * @param lista Puntero doble a la lista de materias.
 */
void generar_materia_aleatoria(ListadoMaterias **lista)
{

    int total_nombres = sizeof(NOMBRES_MATERIAS) / sizeof(NOMBRES_MATERIAS[0]);
    const char *nombre_random = NOMBRES_MATERIAS[rand() % total_nombres];

    char id[6];

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
    } while (buscar_por_identificador(*lista, id) != NULL && *lista != NULL);

    agregar_materia(lista, id, nombre_random);
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
