#!/bin/bash

# Crear directorio de salida para binarios
cd "$(dirname "$0")"
mkdir -p bin

# Flags comunes
CFLAGS="-I../include -g"
LIBS="../database.c ../estudiante.c ../materia.c ../utils.c ../persistencia.c ../generador.c ../lib/cJSON.c"

echo "Compilando y ejecutando tests..."

# Test Materia
echo "--------------------------------"
echo "Test Materia"
gcc $CFLAGS -o bin/test_materia test_materia.c $LIBS
if [ $? -eq 0 ]; then
    ./bin/test_materia
else
    echo "Compilación fallida para test_materia"
fi

# Test Estudiante
echo "--------------------------------"
echo "Test Estudiante"
gcc $CFLAGS -o bin/test_estudiante test_estudiante.c $LIBS
if [ $? -eq 0 ]; then
    ./bin/test_estudiante
else
    echo "Compilación fallida para test_estudiante"
fi

# Test Database
echo "--------------------------------"
echo "Test Database"
gcc $CFLAGS -o bin/test_database test_database.c $LIBS
if [ $? -eq 0 ]; then
    ./bin/test_database
else
    echo "Compilación fallida para test_database"
fi

# Test Utils (unificado)
echo "--------------------------------"
echo "Test Utils"
gcc $CFLAGS -o bin/test_utils test_utils.c $LIBS
if [ $? -eq 0 ]; then
    ./bin/test_utils
else
    echo "Compilación fallida para test_utils"
fi

# Test Persistencia
echo "--------------------------------"
echo "Test Persistencia"
gcc $CFLAGS -o bin/test_persistencia test_persistencia.c $LIBS
if [ $? -eq 0 ]; then
    ./bin/test_persistencia
else
    echo "Compilación fallida para test_persistencia"
fi

# Test Generador
echo "--------------------------------"
echo "Test Generador"
gcc $CFLAGS -o bin/test_generador test_generador.c $LIBS
if [ $? -eq 0 ]; then
    ./bin/test_generador
else
    echo "Compilación fallida para test_generador"
fi
