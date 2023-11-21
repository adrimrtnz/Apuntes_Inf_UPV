#define PROYECTO "ISGI::S5E01::Cuadrado rebotante"

#include <iostream>
#include <cmath>
#include <gl\freeglut.h>

using namespace std;

static float posicionx(0.2);
static float posiciony(0.0);
static GLuint cuadrado;
static const GLfloat semilado(0.1);
static GLfloat semiancho, semialto;

void init()
{
	cout << "Version: OpenGL " << glGetString(GL_VERSION) << endl;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0, 0, 0);

	// Crea un cuadrado de lado x lado
	cuadrado = glGenLists(1);
	glNewList(cuadrado, GL_COMPILE);
	glBegin(GL_POLYGON);
		glVertex3f(-semilado, -semilado, 0.0);
		glVertex3f(semilado, -semilado, 0.0);
		glVertex3f(semilado, semilado, 0.0);
		glVertex3f(-semilado, semilado, 0.0);
	glEnd();
	glEndList();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glTranslatef(posicionx, posiciony, 0);
	glCallList(cuadrado);

	glFlush();
}

void reshape(GLint w, GLint h)
{
	// Tam objetivo de la ventana del mundo real
	static const GLfloat ANCHO(2.0), ALTO(2.0);

	// Usamos toda el area de dibujo
	glViewport(0, 0, w, h);

	// Definimos la camara (matriz de proyeccion)
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	float razon = (float)w / h;

	if (w < h) {
		semiancho = ANCHO / 2;
		semialto = ALTO / 2 / razon;
	}
	else {
		semiancho = ANCHO * razon / 2;
		semialto = ALTO / 2;
	}

	glOrtho(-semiancho, semiancho, -semialto, semialto, 0, 10);
}

void onIdle()
{
	// Vector velocidad del cuadrado en u/frame en ambas direcciones
	static float uperframe[] = { 0.0005, 0.0005 };

	// posicion = posicion_anterior + velocidad*frame
	posicionx += uperframe[0];
	posiciony += uperframe[1];

	// La ventana mide ancho x alto
	// Deteccion de colisiones
	if (posicionx + semilado >= semiancho || posicionx - semilado <= -semiancho) uperframe[0] *= -1;
	if (posiciony + semilado >= semialto || posiciony - semilado <= -semialto) uperframe[1] *= -1;


	// puede ocurrir que al variar el marco, la posicion actual quede fuera de la ventana
	// con lo que el cuadrado desaparece.
	// Se puede mejorar, pero por simplicidad hacemos reset al centro.
	if (abs(posicionx) > semiancho || abs(posiciony) > semialto) {
		posicionx = 0.0;
		posiciony = 0.0;
	}

	glutPostRedisplay();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow(PROYECTO);
	std::cout << PROYECTO << " running" << std::endl;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(onIdle);
	init();
	glutMainLoop();
}
