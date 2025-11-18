#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estudiante.h"
#include "database.h"

// TODO agregar nombres
const char *NOMBRES_MATERIAS[] = {
    "Algebra I",
    "Algebra II",
    "Algebra Lineal",
    "Analisis Matemático I",
    "Analisis Matemático II",
    "Analisis Matemático III",
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
    "Métodos Numéricos",
    "Introduccion a la Programacion",
    "Programacion Imperativa",
    "Programacion Orientada a Objetos",
    "Estructuras de Datos",
    "Algoritmos y Complejidad",
    "Bases de Datos",
    "Modelos y Simulación",
    "Sistemas Operativos",
    "Redes de Computadoras",
    "Arquitectura de Computadoras",
    "Organización del Computador",
    "Compiladores",
    "Lenguajes Formales y Autómatas",
    "Ingeniería de Software I",
    "Ingeniería de Software II",
    "Métodos Formales",
    "Computación Gráfica",
    "Sistemas Distribuidos",
    "Inteligencia Artificial",
    "Machine Learning",
    "Deep Learning",
    "Sistemas Embebidos",
    "Robótica I",
    "Robótica II",
    "Teoría de la Computación",
    "Criptografia",
    "Seguridad Informática",
    "Procesamiento de Señales",
    "Procesamiento Digital de Imágenes",
    "Visión por Computadora",
    "Biomecánica Computacional",

    // Física
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

    // Química
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

    // Biología / Exactas
    "Biologia Celular",
    "Biologia Molecular",
    "Genetica",
    "Bioinformatica",
    "Microbiologia",
    "Ecologia",
    "Zoologia",
    "Botanica",

    // Ingeniería Electrónica
    "Circuitos Electricos I",
    "Circuitos Electricos II",
    "Electrónica I",
    "Electrónica II",
    "Electrónica Digital",
    "Telecomunicaciones",
    "Sistemas de Control",
    "Control Automático",
    "Microprocesadores",
    "Antenas y Propagación",
    "Dispositivos Semiconductores",
    "Instrumentación Electrónica",
    "Electrotecnia",

    // Ingeniería Mecánica
    "Mecanica de Fluidos",
    "Mecanica de Solidos",
    "Estatica",
    "Dinamica",
    "Resistencia de Materiales",
    "Termodinámica Aplicada",
    "Máquinas Térmicas",
    "Diseño Mecánico",
    "Materiales Industriales",
    "Procesos de Manufactura",
    "Ingeniería de Transporte",

    // Ingeniería Química
    "Balance de Materia y Energía",
    "Cinetica Quimica",
    "Operaciones Unitarias I",
    "Operaciones Unitarias II",
    "Reacciones Químicas",
    "Ingenieria de Procesos",
    "Ingeniería Ambiental",
    "Polímeros",

    // Ingeniería Civil
    "Materiales de Construcción",
    "Hidráulica",
    "Topografía",
    "Geotecnia",
    "Diseño Estructural",
    "Hormigón Armado",
    "Mecánica de Suelos",
    "Transporte y Vías de Comunicación",
    "Urbanismo",
    "Planificación Territorial",

    // Ingenierías varias
    "Sistemas de Información Geográfica",
    "Mineralogía",
    "Geología General",
    "Petrología",
    "Geomorfología",
    "Introducción a la Aerodinámica",
    "Estructuras Aeronáuticas",
    "Propulsión Espacial",

    // Optativas (muchas)
    "Introducción al Data Science",
    "Minería de Datos",
    "Teoría de Juegos",
    "Optimización I",
    "Optimización II",
    "Computación Paralela",
    "Cloud Computing",
    "Blockchain",
    "Ciberseguridad Avanzada",
    "Desarrollo de Videojuegos",
    "Realidad Aumentada",
    "Realidad Virtual",
    "Criptomonedas y Sistemas Descentralizados",
    "Modelado de Fenómenos Físicos",
    "Modelado Estocástico",
    "Simulación Monte Carlo",
    "Astronomía General",
    "Astrofísica",
    "Cosmología",
    "Energías Renovables",
    "Tecnología Nuclear",
    "Fisión y Fusión Nuclear",
    "Diseño de Reactores",
    "Ingeniería Biomédica",
    "Prostética y Biónica",
    "Bioinstrumentación",
    "Biofísica",
    "Microbiología Industrial",
    "Machine Learning para Física",
    "Introducción al Internet de las Cosas",
    "Sistemas Autónomos",
    "Análisis de Big Data",
    "Criptografía Cuántica",
    "Computación Cuántica",
    "Linguistica Computacional",
    "Matemática para IA",
    "Sistemas no Lineales",
    "Teoría del Caos",
    "Métodos Variacionales",
    "Introducción a la Nanotecnología",
    "Fabricación Aditiva",
    "Ingeniería de Materiales Avanzados",
    "Sensores y Actuadores",
    "Acústica y Vibraciones",
    "Modelos Climáticos",
    "Ciencia del Clima",
    "Bioestadística",
    "Epistemología de la Ciencia",
    "Historia de la Tecnología",
    "Taller de Investigación",
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
    "Manuel", "Marcos", "Mario", "Martín", "Mateo",
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
    "Paula", "Pilar", "Rocío", "Romina", "Sabrina",
    "Salome", "Sofia", "Stefania", "Tatiana", "Valeria",
    "Victoria", "Yasmin"};

const char *APELLIDOS[] = {
    "Acosta", "Aguirre", "Alvarez", "Alvarenga", "Amaya",
    "Aranda", "Araujo", "Arias", "Ayala", "Barrera",
    "Barrios", "Benitez", "Blanco", "Borda", "Bravo",
    "Caballero", "Caceres", "Cano", "Cardozo", "Carrizo",
    "Castillo", "Castro", "Cervantes", "Cisneros", "Colman",
    "Córdoba", "Correa", "Cuevas", "Duarte", "Escobar",
    "Esquivel", "Fernandez", "Figueroa", "Flores", "Franco",
    "Galeano", "Gallardo", "García", "Gimenez", "Godoy",
    "Gomez", "Gonzalez", "Guerrero", "Heredia", "Herrera",
    "Ibarra", "Ledesma", "Leguizamon", "Lopez", "Luna",
    "Maidana", "Martinez", "Medina", "Mendez", "Miranda",
    "Molina", "Monzón", "Morales", "Mori", "Navarro",
    "Nuñez", "Ojeda", "Olmedo", "Ortiz", "Paez",
    "Paredes", "Perez", "Ponce", "Ramirez", "Reyes",
    "Rios", "Rivero", "Rodriguez", "Romero", "Ruiz",
    "Salinas", "Sanchez", "Sosa", "Suarez", "Torres",
    "Valdez", "Vargas", "Vazquez", "Velazquez", "Vera",
    "Vergara", "Villalba", "Villanueva", "Zarate", "Zavala"};

void generar_estudiante_aleatorio(ListadoEstudiantes **lista)
{
    const char *nombre = NOMBRES[rand() % (sizeof(NOMBRES) / sizeof(NOMBRES[0]))];
    const char *apellido = APELLIDOS[rand() % (sizeof(APELLIDOS) / sizeof(APELLIDOS[0]))];

    char nombre_completo[30];
    snprintf(nombre_completo, sizeof(nombre_completo), "%s %s", nombre, apellido);

    int legajo = 100000 + rand() % 900000;
    while (buscar_por_legajo(*lista, legajo) != NULL)
    {
        legajo = 100000 + rand() % 900000;
    }

    int edad = 18 + rand() % 23;

    agregar_estudiante(lista, legajo, edad, nombre_completo);
}

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
    } while (buscar_por_identificador(*lista, id) != NULL);

    agregar_materia(lista, id, nombre_random);
}

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
        printf("Solo hay %d legajos disponibles (6 dígitos).\n", TOTAL_LEGAJOS_POSIBLES);
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

    printf("Generación exitosa\n");
    return 0;
}
