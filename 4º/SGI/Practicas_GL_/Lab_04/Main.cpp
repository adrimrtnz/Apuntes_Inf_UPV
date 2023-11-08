#define PROYECTO "Lab_04: Estrella 3D"

#include <iostream>	
#include <codebase.h>

// Globales
static GLfloat radio_int = 0.7f;
static GLfloat radio_ext = 1.0f;
static GLint starList;
float angle = 0.0f;

static const float COLORS[] = { 
	0,0,0,
	0,0,1, 
	0,1,0, 
	0,1,1, 
	1,0,0, 
	1,0,1
};

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
}

// Funcion de atencion al evento de dibujo
void display()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float camY = cosf(angle) * 3.0f;
	float camX = sinf(angle) * 3.0f;

	//cosf((angle++) * 2 * PI / 360)
	gluLookAt(0, 0, 3, 0, 0, 0, camX, camY, 0);	// Situa la camara
	glEnable(GL_DEPTH_TEST);
	angle += 0.1f;

	// Dibujar la estrella usando display list
	glColor3f(0, 0, 0.3f);
	glPolygonMode(GL_FRONT, GL_FILL);

	glutWireSphere(1.0, 20, 20);
	for (int i = 0; i < 6; i++) {
		glColor3f(COLORS[i*3], COLORS[i*3+1], COLORS[i*3+2]);
		glPushMatrix();
		glRotatef(i * 30, 0, 1, 0);
		glCallList(starList);
		glPopMatrix();
	}
	glFlush();

	std::cout << "Se pulsa el raton" << std::endl;
}

// Funcion de atencion al redimensionamiento
void reshape(GLint w, GLint h)
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
	gluPerspective(45, ratio, 2, 10);
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
