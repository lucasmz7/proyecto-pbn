# Consigna
Desarrollar un sistema de estudiantes en C. Debe permitir:

CRUD: Create Read Update Delete List
ABM: Alta Baja Modificación

-Dar de alta, modificar, eliminar y listar estudiantes
-Buscar estudiantes por nombre
-Buscar estudiantes por rango de edad

Además cada estudiante puede anotarse en N materias.
-Dar de alta, modificar, eliminar y listar materias
-Anotarse en una materia
-Rendir una materia

El sistema debe poder soportar un gran listado de estudiantes y materias. Utilizar estructuras de datos para almacenar los listados. Decidir si se utiliza ordenamiento de los datos. El diseño del sistema y los modelos son libres. Utilizar la creatividad para que el manejo del sistema sea lo más práctico posible. La única limitación respecto al uso de librerías es que la estructura de datos que usen sea de desarrollo propio.

Si los requerimientos planteados son cumplidos, el ejercicio está aprobado (nota 4). Puede pasar que en situaciones en la que la cantidad de datos sea muy grande, el sistema sea inmanejable. En ese caso, detallar las limitaciones de la solución propuesta (si las limitaciones son reconocidas no se considera desaprobado el punto). Agregar en el README del repositorio.

Ideas no-obligatorias de implementar pero que suman puntos: 
- [ ] Utilizar paginado
- [X] Poder elegir el estudiante/materia de un listado reducido
- [X] Generar estudiantes de prueba y materias aleatorias de forma masiva
- [X] Estadísticas de los estudiantes y materias, etc.
- [ ] Arboles de correlatividad de materias
- [ ] Qué pasa si una materia anterior está desaprobada? Puede anotarse? 
- [X] Cálculo de promedios. 
- [ ] Archivo de configuración general donde se especifican las variables del sistema.
- [ ] Mejoras en la interfaz de usuario
- [X] Tests unitarios
- [X] Persistencia en JSON

# Desarrollo de la solucion
El sistema esta limitado por la cantidad de legajos disponibles (6 digitos y empiezan a partir del 100000, es decir 900000 estudiantes al mismo tiempo). 

El sistema ha sido testeado con distintas cantidades dentro del rango previamente mencionado y no se han detectado problemas en el sistema.

Para la persistencia en JSON se ha utilizado la libreria cJSON.

Para comprobar los tests unitarios se debe ejecutar el archivo run_tests.sh

URL de la demostracion: https://www.youtube.com/watch?v=EeodAtpev2U&feature=youtu.be