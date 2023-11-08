#define PROYECTO "ISGI::S4"

#include <iostream>
#include <GL\freeglut.h>

void display_1()
{
	glClear(GL_COLOR_BUFFER_BIT);			// Borra la pantalla
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);	// Situa la camara
	glutWireSphere(1.0, 20, 20);
	glFlush();
}

void display_2()
{
	glClear(GL_COLOR_BUFFER_BIT);			// Borra la pantalla
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(2, 5, 0, 2, 0, 0, 0, 0, -1);	// Situa la camara
	glTranslatef(2, 0, 0);
	glutWireTeapot(1.0);
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);	// Situa la camara
	glEnable(GL_DEPTH_TEST);

	glColor3f(1, 0, 0);
	glutWireTeapot(0.5);

	glTranslatef(1, 0, -4);
	glColor3f(0, 0, 1);
	glutSolidTeapot(0.5);

	glFlush();
}


void reshape_1(GLint w, GLint h)
{
	// Usar toda el area de dibujo
	glViewport(0, 0, w, h);

	// Definir la camara (matriz de proyeccion)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ratio = (float)w / h;


	// CAMARA ORTOGRAFICA
	// if (w < h) glOrtho(-1, 1, -1/ratio, 1/ratio, 0, 10);
	// else glOrtho(-1*ratio, 1*ratio, -1, 1, 0, 10);
	

	// CAMARA PERSPECTIVA
	gluPerspective(45, ratio, 1, 10);
}

void reshape_2(GLint w, GLint h)
{
	// ratio de la vista
	static const float ratio = 2.0;

	// ratio del area de dibujo
	float ratio_ad = float(w) / h;

	float wp, hp;

	/*
	* Centramos un viewport con la misma razon de la vista.
	* Si el area tiene razon menor la vista se ajusta en horizontal (w)
	* recortando el viewport por arriba y por abajo.
	* Si el area tiene mayor razon que la vista se ajusta en vertical (h)
	* y se recorta por la izquierda y derecha
	*/
	if (ratio_ad < ratio) {
		wp = float(w);
		hp = wp / ratio;
		glViewport(0, int(h / ratio - hp / ratio), w, int(hp));
	}
	else
	{
		hp = float(h);
		wp = hp * ratio;
		glViewport(int(w / ratio - wp / ratio), 0, int(wp), h);
	}

	// Definimos la camara (matriz de proyeccion)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// camara ortografica
	// glOrtho(-1, 1, -1/ratio, 1/ratio, 0, 10);

	// camara perspectiva
	gluPerspective(45, ratio, 1, 10);
}

void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);

	// Definimos la camara (matriz de proyeccion)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ratio = float(w) / h;
	gluPerspective(45, ratio, 1, 10);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);								// Inicializacion de GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);		// Alta de buffers a usar
	glutInitWindowSize(400, 400);
	glutCreateWindow(PROYECTO);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}