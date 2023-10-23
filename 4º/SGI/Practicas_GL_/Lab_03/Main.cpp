#define PROYECTO "Lab_03: Mosaico"

#include <codebase.h>

// Globales
static GLfloat radio_int = 0.7f;
static GLfloat radio_ext = 1.0f;
static GLint starList;
static GLint twoStarList;

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
		glVertex3f(radio_int * cosf(i * 2 * PI / 3 + 3 * PI / 2), radio_int * sinf(i * 2 * PI / 3 + 3 * PI / 2), 0);
		glVertex3f(radio_ext * cosf(i * 2 * PI / 3 + 3 * PI / 2), radio_ext * sinf(i * 2 * PI / 3 + 3 * PI / 2), 0);
	}
	glEnd();
	glEndList();

	twoStarList = glGenLists(1);
	glNewList(twoStarList, GL_COMPILE);
	
		// Guardar el color que hay en ese momento en la máquina de estados
		glPushAttrib(GL_CURRENT_BIT);
		// Guardar la matriz de transformación que hubiera antes
		glPushMatrix();
		glColor3f(0, 0, 0.3f);

		glScalef(0.5, 0.5, 1);
		glCallList(starList);
		glRotatef(-30, 0, 0, 1);
		glScalef(0.4, 0.4, 1);
		glCallList(starList);

		glPopMatrix();
		glPopAttrib();

	glEndList();
}


void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Dibujar la estrella usando display list
	glColor3f(0, 0, 0.3f);
	glPolygonMode(GL_FRONT, GL_FILL);

	glPushMatrix();
	glTranslatef(-0.5, 0.5, 0);
	glRotatef(15, 0, 0, 1);
	glCallList(twoStarList);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.5, 0);
	glRotatef(-15, 0, 0, 1);
	glCallList(twoStarList);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5, -0.5, 0);
	glRotatef(-15, 0, 0, 1);
	glCallList(twoStarList);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, -0.5, 0);
	glRotatef(15, 0, 0, 1);
	glCallList(twoStarList);
	glPopMatrix();

	glFlush();
}


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

	// Bucle de atención a eventos
	init();
	glutMainLoop();
}
