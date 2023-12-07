/***************************************************
*	Iluminacion.cpp
*
*	Aplicar luces y materiales a la escena
*
*	@date Nov,2023
***************************************************/
#define PROYECTO "Iluminaçao"

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

	// Luces
	GLfloat A[] = { 1, 1, 1, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, A);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, GRISOSCURO);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, BLANCO);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 12);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 70);

	// Configuración del motor del render
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

// Funcion de atencion al evento de dibujo
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Situar luces fijas en la camara
	GLfloat PL0[] = {0, 0, 1, 0};
	glLightfv(GL_LIGHT0, GL_POSITION, PL0);

	//Situación y orientación de la cámara
	gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);

	// Situar luces fijas en la escena
	GLfloat PL1[] = { 0, 5, 0, 1 };
	GLfloat DL1[] = { 0, -1, 0 };
	glLightfv(GL_LIGHT1, GL_POSITION, PL1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, DL1);


	ejes();


	// glRotatef(giro_x, 1, 0, 0);
	// glRotatef(giro_y, 0, 1, 0);

	// Material Suelo
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLfloat Dm_S[] = { 0.5,0.7,0.6,1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Dm_S);

	// Suelo (vertices en sentido antihorario)
	GLfloat v0[] = { -1, 0, 1 };
	GLfloat v1[] = { 1, 0, 1 };
	GLfloat v2[] = { 1, 0, -1 };
	GLfloat v3[] = { -1, 0, -1 };
	if (modo == ALAMBRICO) {
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT, GL_FILL);
	}
	quad(v0, v1, v2, v3, 100, 100);
	glPopAttrib();

	// Material tetera verde
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLfloat Dm_tv[] = { 0.5,0.7,0.6,1.0 };
	GLfloat Sm_tv[] = { 0.8,0.8,0.8,1.0 };
	GLfloat s_tv = 20.0;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Dm_tv);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Sm_tv);
	glMaterialf(GL_FRONT, GL_SHININESS, s_tv);

	// Tetera verde
	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslatef(0.5, 0.5, 0);
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
	glPopAttrib();

	// Tetera azul
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLfloat s_ta = 40.0;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, BRONCE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ORO);
	glMaterialf(GL_FRONT, GL_SHININESS, s_ta);
	glTranslatef(-0.5, 0.5, 0);
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
	glPopAttrib();

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

	// Apilar el estado de OpenGL
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);

	// Tetera verde
	glColor3f(0, 1, 0);
	glPushMatrix();
	glRotatef(giro_xtv, 1, 0, 0);
	glRotatef(giro_ytv, 0, 1, 0);
	glTranslatef(0.5, 0.5, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();

	// Tetera azul
	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(-0.5, 0.5, 0);
	glRotatef(giro_xta, 1, 0, 0);
	glRotatef(giro_yta, 0, 1, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();
	glPopAttrib();
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