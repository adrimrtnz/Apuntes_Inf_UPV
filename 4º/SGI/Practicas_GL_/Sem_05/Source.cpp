#define PROYECTO "Animacion"

#include <iostream>	
#include <sstream>
#include <codebase.h>

using namespace std;
using namespace cb;

//Globales
static float alfa = 0;
static float refresh_rate = 60;

// Funcion de inicializacion propia
void init()
{
	// Salida por consola
	cout << glGetString(GL_VERSION) << endl;

	// Configuración del motor del render
	glEnable(GL_DEPTH_TEST);
}


void FPS()
{
	static int fps = 0;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	int delta_time = ahora - antes;
	fps++;

	if (delta_time >= 1000) {
		// Cambiar titulo ventana
		stringstream titulo;
		titulo << "FPS=" << fps;
		glutSetWindowTitle(titulo.str().c_str());
		fps = 0;
		antes = ahora;
	}
}


// Funcion de atencion al evento de dibujo
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Situación y orientación de la cámara
	//gluLookAt(0, 4, 0, 0, 0, 0, 1, 0, 0);
	gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);

	ejes();

	glPushMatrix();
	glRotatef(alfa, 0, 1, 0);
	//glTranslatef(0, 0, -2);
	glColor3f(0, 1, 0);
	glutSolidTeapot(0.5);
	glColor3f(1, 1, 1);
	glutWireTeapot(0.51);
	glPopMatrix();

	glTranslatef(0, -1, 0);
	glRotatef(alfa / 2, 0, 1, 0);
	glColor3f(0, 0, 1);
	glutSolidTeapot(0.5);
	glColor3f(1, 1, 1);
	glutWireTeapot(0.51);

	glutSwapBuffers();
	FPS();
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

void update()
{
	// Actualizacion de variables sin tener en cuenta el tiempo
	// alfa += 0.1;

	// Actualizacion dependiendo del tiempo entre frames
	static const float RPS = 0.5; // Revoluciones por segundo
	static int hora_anterior = glutGet(GLUT_ELAPSED_TIME);
	
	int hora_actual = glutGet(GLUT_ELAPSED_TIME);
	float delta_time = (hora_actual - hora_anterior) / 1000.0f;

	alfa += RPS * 360 * delta_time;
	hora_anterior = hora_actual;

	glutPostRedisplay();
}

// Funcion de atencion al timer
void onTimer(int time)
{
	glutTimerFunc(time, onTimer, time);
	update();
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
	// glutIdleFunc(update);

	// (1000 / refresh_rate) los milisegundos que tienen que pasar entre frame
	glutTimerFunc(int(1000 / refresh_rate), onTimer, int(1000 / refresh_rate));

	// Inicio propio y del bucle de eventos
	init();
	glutMainLoop();
}