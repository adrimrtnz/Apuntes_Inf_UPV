/*************************************************
	Autor: Adrian Martinez Martinez
	usuario UPV: amarmar4
*************************************************/

#define PROYECTO "Animacion"

#include <iostream>	
#include <sstream>
#include <codebase.h>

using namespace std;
using namespace cb;

// Globales
static Sistema3d *sistema;
static float alfa = 0;
static float beta = 0;
static float alfa_bolas = 0;
static float alfa_cam = 0;
static float rotacion_vagon = 0;
static const int NUM_PATAS = 6;
static const int NUM_BOLAS = 10;
static bool inside = FALSE;
static double cam_x, cam_y, cam_z;
static const int GRADOS_OFFSET_PATAS = 15;
static float MAX_MOMENTUM = 1.5f;
static float refresh_rate = 60;
static float delta_time = 0;
static GLdouble momentum = 0.0f;
static double modelview[16];
static GLdouble look_at[3] = { 0, 0, 0 };
static GLdouble pos_cam[3] = { 0, 0, 0 };
static float pos_pata_0[3] = { 0, 0, 0 };
static GLuint estrella;
static GLfloat radio_int = 0.7f;
static GLfloat radio_ext = 1.0f;
static double bola_x = 0, bola_y = 0, bola_z = 0;

// Colores
static GLfloat c_vagoneta[]			= { 0.929f, 0.847f, 0.267f };
static GLfloat c_base_vagon[]		= { 0.106f, 0.486f, 0.757f };
static GLfloat c_tentaculo[]		= { 0.922f, 0.922f, 0.922f };
static GLfloat c_suelo[]			= { 0.070f, 0.400f, 0.070f };
static GLfloat c_pulpo[]			= { 0.537f, 0.384f, 0.745f };
static GLfloat c_bola_estrella[]	= { 
										random(0,1), random(0,1), 1,
										random(0,1), random(0,1), 1,
										random(0,1), random(0,1), 1,
										random(0,1), random(0,1), 1,
										random(0,1), random(0,1), 1,
										random(0,1), random(0,1), 1
									};

void draw_floor()
{
	float ancho = 5.0f;
	float largo = 5.0f;
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0.07, 0.40, 0.07);
	glBegin(GL_QUADS);
		glVertex3f(-ancho / 2, 0.0f, -largo / 2);
		glVertex3f(ancho / 2, 0.0f, -largo / 2);
		glVertex3f(ancho / 2, 0.0f, largo / 2);
		glVertex3f(-ancho / 2, 0.0f, largo / 2);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}

void draw_vagon()
{
	float alto = 0.2f;
	float ancho = 0.75f;
	float profundidad = 1.0f;

	glPushMatrix();
	glBegin(GL_QUADS);
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(c_vagoneta[0], c_vagoneta[1], c_vagoneta[2]);

	// Cara frontal
	glVertex3f(-ancho / 2, -alto / 2, profundidad / 2);
	glVertex3f(ancho / 2, -alto / 2, profundidad / 2);
	glVertex3f(ancho / 2, alto / 2, profundidad / 2);
	glVertex3f(-ancho / 2, alto / 2, profundidad / 2);

	// Cara trasera
	glVertex3f(-ancho / 2, -alto / 2, -profundidad / 2);
	glVertex3f(-ancho / 2, alto / 2, -profundidad / 2);
	glVertex3f(ancho / 2, alto / 2, -profundidad / 2);
	glVertex3f(ancho / 2, -alto / 2, -profundidad / 2);

	// Cara superior
	glVertex3f(-ancho / 2, alto / 2, -profundidad / 2);
	glVertex3f(-ancho / 2, alto / 2, profundidad / 2);
	glVertex3f(ancho / 2, alto / 2, profundidad / 2);
	glVertex3f(ancho / 2, alto / 2, -profundidad / 2);

	// Cara inferior
	glVertex3f(-ancho / 2, -alto / 2, -profundidad / 2);
	glVertex3f(ancho / 2, -alto / 2, -profundidad / 2);
	glVertex3f(ancho / 2, -alto / 2, profundidad / 2);
	glVertex3f(-ancho / 2, -alto / 2, profundidad / 2);

	// Cara derecha
	glVertex3f(ancho / 2, -alto / 2, -profundidad / 2);
	glVertex3f(ancho / 2, alto / 2, -profundidad / 2);
	glVertex3f(ancho / 2, alto / 2, profundidad / 2);
	glVertex3f(ancho / 2, -alto / 2, profundidad / 2);

	// Cara izquierda
	glVertex3f(-ancho / 2, -alto / 2, -profundidad / 2);
	glVertex3f(-ancho / 2, -alto / 2, profundidad / 2);
	glVertex3f(-ancho / 2, alto / 2, profundidad / 2);
	glVertex3f(-ancho / 2, alto / 2, -profundidad / 2);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}

void draw_vagon_group(int num_pata)
{
	float x = 1.1f;
	float z = 1.2f;

	glPushMatrix();
	glTranslatef(0, 0.2, 0);
	glTranslatef(-x/2, 0, -z/2);
	draw_vagon();
	if (num_pata == 0) {
		/*
		Trato de coger la posición donde debe estar el lookAt de la cámara cuando está dentro
		del vagón. Intenté otros métodos con la GL_MODELVIEW_MATRIX pero no resultaba y otra
		documentación recomendaba usar otras librerías no usadas como glm.
		*/ 

		double seno = sinf(alfa);
		double escala = 1; // primera escala que se aplica

		// Transformaciones en el animated vagon
		sistema->setv(sistema->getv() + Vec3(-x / 2 * escala, 0, -z / 2 * escala));
		sistema->setv(sistema->getv() + Vec3(0, 0.2 * escala, 0));
			
		sistema->setv(sistema->getv() + Vec3(0, 0, 1.6 * escala)
			.rotate(rad(-90), Vec3(1, 0, 0))
			.rotate(rad(rotacion_vagon), Vec3(0, 1, 0)));
		escala = 0.6;
		sistema->setv(sistema->getv() + Vec3(0, 0, 3 * escala)
			.rotate(rad(60), Vec3(1, 0, 0))
			.rotate(rad(-90), Vec3(1, 0, 0))
			.rotate(rad(rotacion_vagon), Vec3(0, 1, 0)));

		sistema->setv(sistema->getv() + Vec3(0, 0, 0.5 * escala)
			.rotate(rad(-30 + 30 * seno), Vec3(1, 0, 0))
			.rotate(rad(60), Vec3(1, 0, 0))
			.rotate(rad(-90), Vec3(1, 0, 0))
			.rotate(rad(rotacion_vagon), Vec3(0, 1, 0)));

		sistema->setv(sistema->getv() + Vec3(0, -2 * escala, 0)
			.rotate(rad(360 / NUM_PATAS), Vec3(0, 1, 0))
			.rotate(rad(-30 + 30 * seno), Vec3(1, 0, 0))
			.rotate(rad(60), Vec3(1, 0, 0))
			.rotate(rad(-90), Vec3(1, 0, 0))
			.rotate(rad(rotacion_vagon), Vec3(0, 1, 0)));

		escala *= 0.25;
		sistema->setv(sistema->getv() + Vec3(0, 1.0f, 0)
			.rotate(rad(beta), Vec3(0, 1, 0))
			.rotate(rad(360 / NUM_PATAS), Vec3(0, 1, 0))
			.rotate(rad(-30 + 30 * seno), Vec3(1, 0, 0))
			.rotate(rad(60), Vec3(1, 0, 0))
			.rotate(rad(-90), Vec3(1, 0, 0))
			.rotate(rad(rotacion_vagon), Vec3(0, 1, 0)));

		Vec3 pos = sistema->getv();
		double angulo_pata = (-15 + 30 * sinf(alfa)) * PI / 180;
		bola_x = pos.x*0.25*signo(cosf(rad(beta)));
		bola_z = pos.y-2.5;
		bola_y = pos.z*0.5 - sinf(angulo_pata);
	}
	glTranslatef(x, 0, 0);
	draw_vagon();
	glTranslatef(0, 0, z);
	draw_vagon();
	glTranslatef(-x, 0, 0);
	draw_vagon();
	glPopMatrix();

	float radio = 1.7f;
	int num_lados = 20;
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(c_base_vagon[0], c_base_vagon[1], c_base_vagon[2]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < num_lados; i++) {
		glVertex3f(radio * cosf(i * 2 * PI / num_lados), 0, radio * sinf(i * 2 * PI / num_lados));
	}
	glEnd();
	glPopMatrix();
	glPopAttrib();

	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0, 0, 0);
	glRotatef(45, 0, 1, 0);
	glTranslatef(0, 1.5, 0);
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glRotatef(i * 90, 0, 1, 0);
		glRotatef(60, 1, 0, 0);
		glutSolidCylinder(0.1, 1.5, 10, 10);
		glPopMatrix();
	}
	glPopMatrix();
	glPopAttrib();
}

void animated_vagon_group(float flip, int num_pata)
{
	glPushMatrix();
	glRotatef(rotacion_vagon * flip, 0, 1, 0);
	draw_vagon_group(num_pata);
	glPopMatrix();
}

void draw_ojos()
{
	float offset = .2f;
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
		glColor3f(1, 1, 1);
		glTranslatef(-offset/2.0f, 0, 0);
		glutSolidSphere(.1, 10, 10);
		glColor3f(0, 0, 0);
		//glutWireSphere(.11, 10, 10);
		glTranslatef(offset, 0, 0);
		glColor3f(1, 1, 1);
		glutSolidSphere(.1, 10, 10);
		glColor3f(0, 0, 0);
		//glutWireSphere(.11, 10, 10);
	glPopMatrix();
	glPopAttrib();

	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
		glColor3f(0, 0, 0);
		glTranslatef(-offset / 2.0f, 0, .1f);
		glutSolidSphere(.025, 5, 5);
		glColor3f(1, 1, 1);
		//glutWireSphere(.0251, 5, 5);
		glTranslatef(offset, 0, 0);
		glColor3f(0, 0, 0);
		glutSolidSphere(.025, 5, 5);
		glColor3f(1, 1, 1);
		//glutWireSphere(.0251, 5, 5);
	glPopMatrix();
	glPopAttrib();
}

void draw_pata(int num_pata)
{
	int flip;
	int par = num_pata % 2;
	if (par) {
		flip = -1;
	}
	else {
		flip = 1;
	}
	// float offset_pata = (num_pata * GRADOS_OFFSET_PATAS * PI / 180);
	double seno = sinf(alfa) * flip;
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
		glColor3f(c_tentaculo[0], c_tentaculo[1], c_tentaculo[2]);
		glTranslatef(0, 0, 0.5);
		glRotatef(-30 + 30 * seno, 1, 0, 0);
		glutSolidCylinder(0.1, 3, 10, 10);
		glColor3f(0, 0, 0);
		glutWireCylinder(0.11, 3.01, 5, 10);
		glTranslatef(0, 0, 3);
		glRotatef(60, 1, 0, 0);
		glColor3f(c_tentaculo[0], c_tentaculo[1], c_tentaculo[2]);
		glutSolidCylinder(0.1, 0.75, 10, 10);
		glColor3f(0, 0, 0);
		glutWireCylinder(0.11, 0.76, 5, 10);
		glTranslatef(0, 0, 1.6);
		glScalef(0.6, 0.6, 0.6);
		glRotatef(-90, 1, 0, 0);
		animated_vagon_group(flip, num_pata);
	glPopMatrix();
	glPopAttrib();
}

void draw_sombrero()
{
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
		glColor3f(0.2f, 0.2f, 0.2f);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.2, 0.5, 10, 10);
		glColor3f(1, 1, 1);
		glutWireTorus(0.21, 0.51, 10, 10);
		glTranslatef(0, 0, -1);
		glColor3f(0.5f, 0.5f, 0.5f);
		glutSolidCylinder(0.5, 1, 10, 10);
		glColor3f(1, 1, 1);
		glutWireCylinder(0.51, 1.01, 10, 10);
	glPopMatrix();
	glPopAttrib();
}

void draw_pulpo() 
{
	glPushMatrix();
	glScalef(0.25, 0.25, 0.25);
	glTranslatef(0, -2, 0);
	for (int i = 0; i < NUM_PATAS; i++) {
		draw_pata(i);
		glRotatef(360 / NUM_PATAS, 0, 1, 0);
	}
	glPopMatrix();

	glPushMatrix();
	glScalef(0.25, 0.25, 0.25);
	glRotatef(-20, 1, 0, 0);
	glTranslatef(0, 0.4, 0.1);
	draw_sombrero();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.0, 0.13);
	draw_ojos();
	glPopMatrix();

	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
		glColor3f(c_pulpo[0], c_pulpo[1], c_pulpo[2]);

		glScalef(0.25, 0.25, 0.25);
		glRotatef(90, 1, 0, 0);

		glutSolidSphere(0.5, 10, 10);
		glColor3f(0, 0, 0);
		glutWireSphere(0.51, 10, 10);
		glColor3f(c_pulpo[0], c_pulpo[1], c_pulpo[2]);
		glutSolidCylinder(0.5, 2, 10, 10);
		glColor3f(0, 0, 0);
		glutWireCylinder(0.51, 2.01, 10, 10);
		glTranslatef(0, 0, 2);
		glColor3f(0.1f, 0.1f, 0.1f);
		glutSolidCylinder(0.1, 2, 10, 10);
	glPopMatrix();
	glPopAttrib();
}

void pulpo_rotador()
{
	glPushMatrix();
	glRotatef(beta, 0, 1, 0);
	draw_pulpo();
	glPopMatrix();
}

void estrellas_bola()
{
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(.5f, .5f, 1.0f);
	glutWireSphere(1.0, 10, 10);
	for (int i = 0; i < 6; i++) {
		glColor3f(c_bola_estrella[3*i], c_bola_estrella[3 * i + 1], c_bola_estrella[3 * i + 2]);
		glPushMatrix();
		glRotatef(i * 30, 0, 1, 0);
		glCallList(estrella);
		glPopMatrix();
	}
	glPopMatrix();
	glPopAttrib();
}

// Funcion de inicializacion propia
void init()
{
	// Salida por consola
	cout << glGetString(GL_VERSION) << endl;

	// Configuraci�n del motor del render
	glEnable(GL_DEPTH_TEST);

	estrella = glGenLists(1);
	glNewList(estrella, GL_COMPILE);
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


void FPS()
{
	static int fps = 0;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	int ahora = glutGet(GLUT_ELAPSED_TIME);
	int elapsed_time = ahora - antes;
	
	if (elapsed_time >= 1000) {
		// Cambiar titulo ventana
		stringstream titulo;
		titulo << "FPS=" << fps;
		glutSetWindowTitle(titulo.str().c_str());
		fps = 0;
		antes = ahora;
	}
	fps++;
}



// Funcion de atencion al evento de dibujo
void display()
{
	glClearColor(0.122f, 0.110f, 0.349f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Situaci�n y orientaci�n de la c�mara
	/**
		Para la animacion de la camara he utilizado una funcion de Lemniscate
		que hace un patron similar a un 8.

		https://es.wikipedia.org/wiki/Funci%C3%B3n_el%C3%ADptica_lemnisc%C3%A1tica

		El offset es para que el centro de la funcion no pase por el centro de
		la figura, ya que si no el efecto era raro.
	*/


	delete sistema;
	sistema = new Sistema3d(Vec3(), Vec3(0,0,0), Vec3(), Vec3());
	gluLookAt(
		//6,3,6,
		cam_x, cam_y, cam_z,
		look_at[0], look_at[1], look_at[2],
		0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 2, 0);
	glRotatef(-beta, 0, 1, 0);
	glScalef(0.5f, 0.5f, 0.5f);
	estrellas_bola();
	glPopMatrix();

	// Rodeo el pulpo con m�s bolas del lab4
	float radio_bolas = 7.5f;
	float offset = 10.0f;
	float escala_bolas = 0.15f;
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
		glTranslatef(0, fabs(momentum), 0);
		glRotatef(alfa_bolas, 0, 1, 0);
		glScalef(escala_bolas, escala_bolas, escala_bolas);
		for (int i = 0; i < NUM_BOLAS; i++) {
			glPushMatrix();
			glTranslatef(
				(offset + fabs(momentum) * radio_bolas) * cosf(i * 2 * PI / NUM_BOLAS),
				0,
				(offset + fabs(momentum) * radio_bolas) * sinf(i * 2 * PI / NUM_BOLAS));
			glRotatef(alfa_bolas * 2, 1, 0, 0);
			estrellas_bola();
			glPopMatrix();
		}
	glPopMatrix();
	glPopAttrib();

	glPushMatrix();
	glTranslatef(0, 1.0f, 0);
	pulpo_rotador();
	glPopMatrix();
	draw_floor();

	ejes();

	glutSwapBuffers();
	FPS();
}

// Funcion de atencion al redimensionamiento
void reshape(GLint w, GLint h)
{
	float ra = (float)w / h;
	int fov_camara = 45;
	float z_far_camara = 12.0f;

	glViewport(0, 0, w, h);
	// Elegir la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fov_camara, ra, 0.1, z_far_camara);
}

void update()
{
	// Actualizacion de variables sin tener en cuenta el tiempo
	// alfa += 0.1;

	// Actualizacion dependiendo del tiempo entre frames
	static const float RPS = 0.10; // Revoluciones por segundo
	static const float ratio_rotacion = 1.0;
	static int hora_anterior = glutGet(GLUT_ELAPSED_TIME);
	static bool acelerar = TRUE;
	static float time_counter = 0.0f;
	static int radio_camara = 5;
	static int offset_camara = 3;
	static float periodo = 8.0f;

	int hora_actual = glutGet(GLUT_ELAPSED_TIME);
	delta_time = (hora_actual - hora_anterior) / 1000.0f;
	alfa_bolas += RPS * 360 * delta_time;
	alfa_cam += PI * delta_time;
	if (glutGet(GLUT_ELAPSED_TIME) / 1000 > 2) {
		if (momentum < MAX_MOMENTUM && acelerar) {
			momentum += 0.1 * delta_time;
		} else {
			acelerar = FALSE;
		}
		alfa += PI * delta_time * momentum;
		beta += RPS * 360 * delta_time * momentum;
		rotacion_vagon += sinf(alfa / 2) * ratio_rotacion * 360 * delta_time * momentum;
	}

	if (momentum > -MAX_MOMENTUM && !acelerar) {
		momentum -= 0.1 * delta_time;
	}
	else {
		acelerar = TRUE;
	}

	time_counter += delta_time;
	if (time_counter > 5 && !inside) {
		cout << "Han pasado 5 segundos, pa dentro" << endl;
		time_counter = 0;
		inside = !inside;
	} else if (time_counter > 5 && inside) {
		cout << "Han pasado 5 segundos, pa fuera" << endl;
		time_counter = 0;
		inside = !inside;
	}
	double angulo_pata = (-15 + 30 * sinf(alfa)) * PI / 180;
	double factor_radio = 1.2;
	
	if (!inside) {
		cam_x = offset_camara + radio_camara * sinf(alfa_cam / periodo);
		cam_y = 3;
		cam_z = offset_camara + radio_camara * sinf(alfa_cam / periodo) * cosf(alfa_cam / periodo);
		look_at[0] = 0;
		look_at[1] = 1;
		look_at[2] = 0;
	} else if (inside) {
		//double cam_x = sinf(beta * PI / 180) * sqrt(pow(1.1 * sinf(angulo_pata), 2) + pow(1.1 * cosf(angulo_pata), 2));
		cam_x = factor_radio * sinf(beta * PI / 180) * cosf(angulo_pata);
		cam_y = .55 - 0.9 * sinf(angulo_pata);
		//double cam_z = cosf(beta * PI / 180) * sqrt(pow(1.1*sinf(angulo_pata), 2) + pow(1.1*cosf(angulo_pata), 2));
		cam_z = factor_radio * cosf(beta * PI / 180) * cosf(angulo_pata);
		look_at[0] = bola_x;
		look_at[1] = bola_y;
		look_at[2] = bola_z;
	}
	
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
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);

	// Crear ventana
	glutCreateWindow(PROYECTO);

	// Registrar callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// (1000 / refresh_rate) los milisegundos que tienen que pasar entre frame
	glutTimerFunc(int(1000 / refresh_rate), onTimer, int(1000 / refresh_rate));

	// Inicio propio y del bucle de eventos
	init();
	glutMainLoop();
}