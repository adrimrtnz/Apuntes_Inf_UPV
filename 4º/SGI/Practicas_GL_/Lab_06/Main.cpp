/***************************************************
*	Bloque Practica 6
*
*	Simulador
*
*	@author	Adrian Martinez
*	@date Nov,2023
***************************************************/

#define PROYECTO "Simulador"

#include <iostream>
#include <sstream>
#include <codebase.h>
#include "config.h"

using namespace std;
using namespace cb;


// Globales
static const float AREA_MIRILLA = RADIO_MIRILLA_CENTRAL * RADIO_MIRILLA_CENTRAL * PI;
static bool isRolling = FALSE;
static bool lights_on = FALSE;
static bool lights_button_pressed = FALSE;
static int screen_center_x = INITIAL_WIDTH / 2;
static int screen_center_y = INITIAL_HEIGHT / 2;
static float delta_time;
static float z0 = 1.0f;
static Sistema3d *sistema = new Sistema3d(
	Vec3(1, 0, 0),		// u
	Vec3(0, 0, 1),		// v
	Vec3(0, -1, 0),		// w
	Vec3(0, 0, z0)		// o
);

static int mouse_x = screen_center_x;
static int mouse_y = screen_center_y;
static int mouse_viewport_y = screen_center_y;
static float mouse_delta_x = 0.0f;
static float mouse_delta_y = 0.0f;
static float mouse_distance_to_center = 0.0f;
static float cam_x = 0.0f;
static float cam_y = 0.0f;
static float cam_z = 1.0f;
static float speed = 0.0f;
static float speed_delta = 2.0f;
static float ini_x = 0.0f;
static float ini_y = 0.0f;
static float yaw_angle = 0.0f;
static float pitch_angle = 0.0f;
static float roll_angle = 0.0f;
static int roll_side_flip = 0;

static float vertices[4][4] = {
	{-DIM_ESPACIO /  2, -DIM_ESPACIO / 2, 0},
	{DIM_ESPACIO / 2, -DIM_ESPACIO / 2, 0},
	{DIM_ESPACIO / 2, DIM_ESPACIO / 2, 0},
	{-DIM_ESPACIO / 2, DIM_ESPACIO / 2, 0},
};

void draw_circle_viewport(float radius = 1.0f, int num_segments = 10)
{
	// Desactivar la prueba de profundidad
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, screen_center_x * 2, screen_center_y * 2, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
	glColor3f(1, 1, 1);

	glLineWidth(ANCHO_LINEA_MIRILLA);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * PI * float(i) / float(num_segments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		glVertex2f(x + screen_center_x, y + screen_center_y);
	}
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();

	// Volver a activar la prueba de profundidad y luces
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void draw_velocimeter() 
{
	static float radius = 1.0f;
	static float ini_y = 9.25f;
	float speed_ratio = speed / MAX_SPEED;
	int color = floor(speed_ratio * 10 / 3);
	// Desactivar la prueba de profundidad
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, screen_center_x * 2, 10, 0.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_CURRENT_BIT | GL_LINE_BIT);
	glPolygonMode(GL_FRONT, GL_FILL);
	
	//glColor3f(SPEED_COLORS[color][0], SPEED_COLORS[color][1], SPEED_COLORS[color][2]);
	glColor3f(1, 1 * (1 - speed_ratio), 1 * (1 - speed_ratio));
	// Velocimetro rectangular
	glRectf(screen_center_x - 100, 9.30, screen_center_x - 99 + 200 * speed_ratio, 9.5);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();

	// Volver a activar la prueba de profundidad y luces
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}


void put_lights_on_scene()
{
	Vec3 w = sistema->getw();
	Vec3 o = sistema->geto();
	Vec3 poi = o - w;
	GLfloat pos_luz_nave[] = {o.x, o.y, o.z, 1};
	GLfloat poif[] = {poi.x, poi.y, -poi.z};
	//printf("%f, %f, %f | %f, %f, %f\n", o.x, o.y, o.z, poi.x, poi.y, poi.z);

	// Iluminacion Sol (Estrella cercana)
	glLightfv(GL_LIGHT0, GL_POSITION, POS_SOL);

	// Luces de las alas de la nave
	glLightfv(GL_LIGHT1, GL_POSITION, pos_luz_nave);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, poif);

	GLfloat PL1[] = { 0, 5, 1, 1 };
	GLfloat DL1[] = { 0, 0, -1 };
	glLightfv(GL_LIGHT2, GL_POSITION, PL1);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, poif);


	if (lights_on) {
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);

		glPushMatrix();
		glTranslatef(poi.x, poi.y, poi.z);
		glutSolidSphere(0.1, 10, 10);
		glPopMatrix();
	}
	else {
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}
}

void configure_lights()
{
	// Iluminacion Sol (Estrella cercana)
	glLightfv(GL_LIGHT0, GL_AMBIENT, COLOR_SOL);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, COLOR_SOL);

	// Luces de las alas de la nave
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, &LUZ_NAVE_CUTOFF);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DIFFUSE_FOCOS);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, SPECULAR_FOCOS);
	//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, BLANCO);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 70);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10);
}

void init()
{
	cout << glGetString(GL_VERSION) << endl;
	
	configure_lights();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);
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

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Vec3 w = sistema->getw();
	Vec3 v = sistema->getv();
	Vec3 o = sistema->geto();
	Vec3 poi = o - w;
	// Situacion y orientación de la cámara
	gluLookAt(o.x, o.y, o.z, poi.x, poi.y, poi.z, v.x, v.y, v.z);

	sistema->drawGlobal();

	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0, 0, 1);
	glPolygonMode(GL_FRONT, GL_LINE);
	
	// Dibujar la malla
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, AZUL);
	quad(vertices[0], vertices[1], vertices[2], vertices[3], RESOLUCION, RESOLUCION);
	glPopAttrib();

	// Objetos Iluminacion
	put_lights_on_scene();
	glPushMatrix();
	glTranslatef(POS_SOL[0], POS_SOL[1], POS_SOL[2]);
	glutWireSphere(0.1, 10, 10);
	glPopMatrix();

	// Dibujar círculo central mirilla
	draw_circle_viewport(RADIO_MIRILLA_CENTRAL);
	draw_velocimeter();
	
	glPopAttrib();

	glutSwapBuffers();
	FPS();
}

void reshape(GLint w, GLint h)
{
	float ra = (float)w / h;
	glViewport(0, 0, w, h);
	screen_center_x = w / 2;
	screen_center_y = h / 2;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(30, ra, 0.1, zFar);
}

void update()
{
	static int hora_anterior = glutGet(GLUT_ELAPSED_TIME);
	static float mouse_x_from_center = 0.0f;
	static float mouse_y_from_center = 0.0f;
	int hora_actual = glutGet(GLUT_ELAPSED_TIME);
	delta_time = (hora_actual - hora_anterior) / 1000.0f;
	hora_anterior = hora_actual;

	if (mouse_distance_to_center > 0) {
		// Que el raton se estabilice en el centro de nuevo
		int delta_x = mouse_delta_x * delta_time > 0 ? ceil(mouse_delta_x * delta_time) : floor(mouse_delta_x * delta_time);
		int delta_y = mouse_delta_y * delta_time > 0 ? ceil(mouse_delta_y * delta_time) : floor(mouse_delta_y * delta_time);
		int x = mouse_x - delta_x;
		int y = mouse_viewport_y + delta_y;
		//cout << mouse_delta_x << " " << mouse_delta_y << endl;
		glutWarpPointer(x, y);

		// Guinyada de la nave
		yaw_angle = -mouse_delta_x / screen_center_x * 360 * delta_time * FACTOR_SUAVIZADO * PIXELES_X_GRADOS;
		sistema->rotar(rad(yaw_angle), sistema->getv());

		// Cabeceo de la nave
		pitch_angle = mouse_delta_y * FACTOR_SUAVIZADO * delta_time * PIXELES_X_GRADOS;
		pitch_angle = max(-MAX_ANGULO_CABECEO, min(MAX_ANGULO_CABECEO, pitch_angle));
		sistema->rotar(rad(pitch_angle), sistema->getu());
	}

	if (isRolling) {
		// Alabeo de la nave
		roll_angle = ANGULO_ALABEO * roll_side_flip * delta_time * PIXELES_X_GRADOS;
		sistema->rotar(rad(roll_angle), sistema->getw());
	}

	// Movimiento de la nave
	sistema->seto(sistema->geto() - sistema->getw() * speed * delta_time);

	glutPostRedisplay();
}


void onTimer(int time)
{
	glutTimerFunc(time, onTimer, time);
	update();
}

void onKey(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		speed += speed_delta * delta_time;
		speed = min(speed, MAX_SPEED);
		cout << "Acelerando, velocidad = " << speed << endl;
		break;
	case 'z':
		speed -= speed_delta * delta_time;
		speed = max(0, speed);
		cout << "Frenando, velocidad = " << speed << endl;
		break;
	case 'q':
		cout << "Alabeando a la izquierda" << endl;
		isRolling = TRUE;
		roll_side_flip = 1;
		break;
	case 'w':
		cout << "Alabeando a la derecha" << endl;
		isRolling = TRUE;
		roll_side_flip = -1;
		break;
	case 'i':
		if (!lights_button_pressed) {
			if (lights_on) {
				cout << "Apagando luces" << endl;
			}
			else {
				cout << "Encenciendo luces" << endl;
			}
			lights_on = !lights_on;
		}
		lights_button_pressed = TRUE;
		break;
	case 27:
		exit(0);
		break;
	}
	// Algo ha cambiado, encola evento de redibujado
	glutPostRedisplay();
}

void onKeyRelease(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q':
			cout << "Dejando de alabear a la izquierda" << endl;
			isRolling = FALSE;
			break;
		case 'w':
			cout << "Dejando de alabear a la derecha" << endl;
			isRolling = FALSE;
			break;
		case 'i':
			lights_button_pressed = FALSE;
			break;
	}
}

void onMouseHover(int x, int y)
{
	// convertir coordenadas del pixel a coordenadas del viewport
	GLint viewport[4]; // origen x, origen y, extension en x, extension en y
	glGetIntegerv(GL_VIEWPORT, viewport);
	mouse_x = x;
	mouse_y = viewport[3] - y;
	mouse_viewport_y = y;

	static GLfloat max_distance = sqrt(screen_center_x * screen_center_x + screen_center_y * screen_center_y) / AREA_MIRILLA;
	mouse_delta_x = (mouse_x - screen_center_x);
	mouse_delta_y = (mouse_y - screen_center_y);
	mouse_distance_to_center = sqrt(mouse_delta_x * mouse_delta_x + mouse_delta_y * mouse_delta_y) / max_distance;
	mouse_distance_to_center = mouse_distance_to_center < RADIO_MIRILLA_CENTRAL ? 0 : mouse_distance_to_center;
	//printf("Delta x=%.3f, Delta y=%.3f, Distancia=%.3f, Max_distance=%.3f\n", mouse_delta_x, mouse_delta_y, mouse_distance_to_center, max_distance);

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(INITIAL_WIDTH, INITIAL_HEIGHT);
	glutInitWindowPosition(50, 50);

	// Crear ventana
	glutCreateWindow(PROYECTO);

	// Ocultar el cursor del raton
	glutSetCursor(GLUT_CURSOR_CROSSHAIR);

	// Registrar callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(onKey);
	glutKeyboardUpFunc(onKeyRelease);
	glutPassiveMotionFunc(onMouseHover);

	// (1000 / refresh_rate) los milisegundos que tienen que pasar entre frame
	glutTimerFunc(int(1000 / REFRESH_RATE), onTimer, int(1000 / REFRESH_RATE));

	// Inicio propio y del bucle de eventos
	init();
	glutMainLoop();
}