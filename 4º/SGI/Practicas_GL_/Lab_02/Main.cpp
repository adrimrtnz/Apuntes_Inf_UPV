#define PROYECTO "Lab_02: Estrella de David"

#include <iostream>	
#include <codebase.h>

// Globales
static GLfloat radio_int = 0.7f;
static GLfloat radio_ext = 1.0f;
static GLint starList;

void init()
{
	starList = glGenLists(1);
	glNewList(starList, GL_COMPILE);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 4; i++) {
		glVertex3f(radio_int * cosf(i * 2 * PI / 3 + PI / 2), radio_int * sinf(i * 2 * PI / 3 + PI / 2), 0);
		glVertex3f(radio_ext * cosf(i * 2 * PI / 3 + PI / 2), radio_ext * sinf(i * 2 * PI / 3 + PI / 2), 0);
	}
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 4; i++) {
		glVertex3f(radio_int * cosf(i * 2 * PI / 3 + 3*PI / 2), radio_int * sinf(i * 2 * PI / 3 + 3*PI / 2), 0);
		glVertex3f(radio_ext * cosf(i * 2 * PI / 3 + 3*PI / 2), radio_ext * sinf(i * 2 * PI / 3 + 3*PI / 2), 0);
	}
	glEnd();
	glEndList();
}

// Funcion de atencion al evento de dibujo
void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Dibujar la estrella usando display list
	glColor3f(0, 0, 0.3f);
	glPolygonMode(GL_FRONT, GL_FILL);
	glCallList(starList);

	glFlush();
}

// Funcion de atencion al redimensionamiento
void reshape(GLint w, GLint h)
{
}

int main(int argc, char** argv)
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(50, 200);

	// Crear ventana
	glutCreateWindow(PROYECTO);

	// Registrar callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// Bucle de atencion a eventos
	init();
	glutMainLoop();
}
