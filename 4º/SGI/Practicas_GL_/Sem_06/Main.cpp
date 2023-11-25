/***************************************************
*	Interaccion.cpp
*
*	Uso de camaras y visibilidad
*
*	@author	R.Vivo' <rvivo@upv.es>
*	@date Nov,2023
***************************************************/
#define PROYECTO "Interaccion"

#include <iostream>	
#include <codebase.h>

using namespace std;
using namespace cb;

//Globales
static int ini_x = 0;
static int ini_y = 0;
static float pixel2grados = 1.0f;
//static float giro_x = 0.0f, giro_y = 0.0f;
static float giro_xtv = 0, giro_ytv = 0, giro_xta = 0, giro_yta = 0;
static GLubyte objeto[1];

static enum {
	ALAMBRICO,
	SOLIDO,
	DOBLE
} modo;


void onMenu(int value)
{
	if (value == 0) modo = ALAMBRICO;
	if (value == 1) modo = SOLIDO;
	if (value == 2) modo = DOBLE;

	glutPostRedisplay();
}

// Funcion de inicializacion propia
void init()
{
	// Salida por consola
	cout << glGetString(GL_VERSION) << endl;

	// Menu sencillo de popup
	glutCreateMenu(onMenu);
	glutAddMenuEntry("ALAMBRICO", 0);
	glutAddMenuEntry("SOLIDO", 1);
	glutAddMenuEntry("DOBLE", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Configuración del motor del render
	glEnable(GL_DEPTH_TEST);
}

// Funcion de atencion al evento de dibujo
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Situación y orientación de la cámara
	gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);

	ejes();

	// glRotatef(giro_x, 1, 0, 0);
	// glRotatef(giro_y, 0, 1, 0);

	// Tetera verde
	glColor3f(0, 1, 0);
	glPushMatrix();
	glRotatef(giro_xtv, 1, 0, 0);
	glRotatef(giro_ytv, 0, 1, 0);
	if (modo == ALAMBRICO) {
		glutWireTeapot(0.5);
	}
	else if (modo == SOLIDO) {
		glutSolidTeapot(0.5);
	}
	else if (modo == DOBLE) {
		glutSolidTeapot(0.5);
		glColor3f(1, 1, 1);
		glutWireTeapot(0.51);
	}
	glPopMatrix();

	// Tetera azul
	glTranslatef(0, -1, 0);
	glColor3f(0, 0, 1);
	glPushMatrix();
	glRotatef(giro_xta, 1, 0, 0);
	glRotatef(giro_yta, 0, 1, 0);
	if (modo == ALAMBRICO) {
		glutWireTeapot(0.5);
	}
	else if (modo == SOLIDO) {
		glutSolidTeapot(0.5);
	}
	else if (modo == DOBLE) {
		glutSolidTeapot(0.5);
		glColor3f(1, 1, 1);
		glutWireTeapot(0.51);
	}
	glPopMatrix();

	glutSwapBuffers();
}

void select()
{
	// dibuja escena en el backbuffer sin mostrar
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Situación y orientación de la cámara
	gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);

	// Tetera verde
	glColor3f(0, 1, 0);
	glPushMatrix();
	glRotatef(giro_xtv, 1, 0, 0);
	glRotatef(giro_ytv, 0, 1, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();

	// Tetera azul
	glTranslatef(0, -1, 0);
	glColor3f(0, 0, 1);
	glPushMatrix();
	glRotatef(giro_xta, 1, 0, 0);
	glRotatef(giro_yta, 0, 1, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();
}

// Funcion de atencion al redimensionamiento
void reshape(GLint w, GLint h)
{
	float ra = (float)w / h;
	glViewport(0, 0, w, h);
	// Elegir la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*
	if (ra > 1)
		glOrtho(-2 * ra, 2 * ra, -2, 2, -1, 1);
	else
		glOrtho(-2, 2, -2 / ra, 2 / ra, -1, 1);
	*/

	gluPerspective(30, ra, 0.1, 10);
}

void onKey(unsigned char tecla, int x, int y)
{
	switch (tecla) {
	case 'a':
		modo = ALAMBRICO;
		break;
	case 'b':
		modo = SOLIDO;
		break;
	case 'd':
		modo = DOBLE;
		break;
	case 27:
		exit(0);
		break;
	}

	// repintar que algo ha cambiado, encola evento de redibujado
	glutPostRedisplay();
}


void onClick(int button, int state, int x, int y)
{
	// Registrar la posicion del cursor
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		ini_x = x;
		ini_y = y;
	}

	// convertir coordenadas del pixel a coordenadas del viewport
	GLint viewport[4]; // origen x, origen y, extension en x, extension en y
	glGetIntegerv(GL_VIEWPORT, viewport);
	GLint vx = x;
	GLint vy = viewport[3] - y;
	select();
	glReadPixels(vx, vy, 1, 1, GL_BLUE, GL_UNSIGNED_BYTE, objeto);
}

void onDrag(int x, int y)
{
	// al mover el raton hacia la derecha la x aumenta
	// y el giro es alrededor del eje Y positivo
	//giro_y += (x - ini_x) * pixel2grados;

	// al mover el raton hacia abajo la y aumenta
	// y el giro es alrededor del eje X positivo
	//giro_x += (y - ini_y) * pixel2grados;

	if (objeto[0] == 0x00) {	// Tetera verde
		giro_ytv += (x - ini_x) * pixel2grados;
		giro_xtv += (y - ini_y) * pixel2grados;
	}
	else {						// La otra tetera
		giro_yta += (x - ini_x) * pixel2grados;
		giro_xta += (y - ini_y) * pixel2grados;
	}

	ini_x = x;
	ini_y = y;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(50, 50);

	// Crear ventana
	glutCreateWindow(PROYECTO);

	// Registrar callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(onKey);
	glutMouseFunc(onClick);
	glutMotionFunc(onDrag);

	// Inicio propio y del bucle de eventos
	init();
	glutMainLoop();
}