#define PROYECTO "ISGI::S2E02::Pentagono"

#include <iostream>
#include <cmath>
#include <gl/freeglut.h>

void display()
{

}

void reshape(GLint w, GLint h)
{
	// Funcion de atención al redimensionado
}

void main(int argc, char** argv)
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 400);
	glutInitWindowPosition(50, 200);

	// Crear ventana
	glutCreateWindow(PROYECTO);

	// Registrar callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Bucle de atencion a eventos
	glutMainLoop();
}