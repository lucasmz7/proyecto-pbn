#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estudiante.h"
#include "database.h"

// TODO agregar nombres
const char *NOMBRES_MATERIAS[] = {
    "Analisis Matematico I", "Analisis Matematico II", "Algebra Lineal",
    "Algoritmos y Estructuras de Datos", "Programacion I",
    "Programacion II", "Arquitectura de Computadoras",
    "Base de Datos", "Fisica I", "Fisica II",
    "Ingenieria de Software", "Sistemas Operativos",
    "Redes de Computadoras", "Calculo Numerico",
    "Probabilidad y Estadistica", "Matematica Discreta",
    "Inteligencia Artificial", "Compiladores",
    "Economia", "Administracion"};

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
