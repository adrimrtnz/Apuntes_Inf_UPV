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
#include <string>
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
static float z0 = .5f;
static Sistema3d *sistema = new Sistema3d(
	Vec3(1, 0, 0),		// u
	Vec3(0, 0, 1),		// v
	Vec3(0, -1, 0),		// w
	Vec3(0, 0, z0)		// o
);

// IDs texturas
static GLuint plataforma;
static GLuint skybox;
static GLuint tex_meteorito;

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
static float speed_delta = 3.0f;
static float ini_x = 0.0f;
static float ini_y = 0.0f;
static float yaw_angle = 0.0f;
static float pitch_angle = 0.0f;
static float roll_angle = 0.0f;
static int roll_side_flip = 0;


//***************************************************************************
class Meteorito2
{
private:
	float x = 0, y = 0, z = 0;
	float rps = 0, rot_angle = 0, rot_x, rot_y, rot_z;
	float x_desp = 0, y_desp = 0, z_desp = 0;
	float max_distance = DIM_CUBEMAP / 2.0;
	GLUquadricObj* quad;
	int numPts = 100;
	void Translate();
public: 
	Meteorito2();
	void draw();
};

Meteorito2::Meteorito2()
{
	quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);
	gluQuadricNormals(quad, GLU_SMOOTH);
	x = random(-max_distance, max_distance);
	y = random(-max_distance, max_distance);
	z = random(-max_distance, max_distance);
	x_desp = random(-1, 1);
	y_desp = random(-1, 1);
	z_desp = random(-1, 1);
	rps = random(MIN_RPS_METEORITO, MAX_RPS_METEORITO);
	rot_x = random(0, 1);
	rot_y = random(0, 1);
	rot_z = random(0, 1);
}

void Meteorito2::Translate()
{
	x += x_desp * delta_time;
	y += y_desp * delta_time;
	z += z_desp * delta_time;

	if (abs(x) > DIM_CUBEMAP || abs(y) > DIM_CUBEMAP || abs(z) > DIM_CUBEMAP) {
		x = random(-max_distance, max_distance);
		y = random(-max_distance, max_distance);
		z = random(-max_distance, max_distance);
	}
}

void Meteorito2::draw()
{
	rot_angle += rps * 360 * delta_time;
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1, 1, 1);
	Translate();
	glTranslatef(x, y, z);
	glRotatef(rot_angle, rot_x, rot_y, rot_z);
	ejes();
	glBindTexture(GL_TEXTURE_2D, tex_meteorito);
	gluSphere(quad, 0.5, 10, 10);

	// Obtiene el número de vértices de la esfera
	glPopAttrib();
	glPopMatrix();
}

static Meteorito2 *meteoritos[NUM_METEORITOS];

//***************************************************************************

void draw_circle_viewport(float radius = 1.0f, int num_segments = 10)
{
	// Desactivar la prueba de profundidad
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

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
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
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

void ship_lights()
{
	static float offset = 0.2f;
	Vec3 w = sistema->getw();
	Vec3 v = sistema->getv();
	Vec3 o = sistema->geto();
	Vec3 poi = o - w;

	/*
	*/
	Vec3 luz_1 = sistema->geto()*offset;
	Vec3 luz_2 = sistema->geto()*-offset;
	GLfloat pos_luz_1[] = { luz_1.x, luz_1.y , luz_1.z , 1 };
	GLfloat pos_luz_2[] = { luz_2.x, luz_2.y , luz_2.z , 1 };
	GLfloat dir_luz_1[] = { offset, 0, -1.0f };
	GLfloat dir_luz_2[] = { -offset, 0, -1.0f };

	// Luces de las alas de la nave
	glLightfv(GL_LIGHT1, GL_POSITION, pos_luz_1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_luz_1);
	glLightfv(GL_LIGHT2, GL_POSITION, pos_luz_2);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_luz_2);

	if (lights_on) {
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
	}
	else {
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
	}
}

void put_lights_on_scene()
{
	// Iluminacion Sol (Estrella cercana)
	glLightfv(GL_LIGHT0, GL_POSITION, POS_SOL);
}

void configure_lights()
{
	// Iluminacion Sol (Estrella cercana)
	glLightfv(GL_LIGHT0, GL_AMBIENT, COLOR_SOL);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, COLOR_SOL);

	// Luces de las alas de la nave
	//glLightfv(GL_LIGHT1, GL_AMBIENT, NEGRO);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, BLANCO);
	glLightfv(GL_LIGHT1, GL_SPECULAR, BLANCO);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, SHIP_LIGHT_CUTOFF);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, SHIP_LIGHT_EXPONENT);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, BLANCO);
	glLightfv(GL_LIGHT2, GL_SPECULAR, BLANCO);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, SHIP_LIGHT_CUTOFF);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, SHIP_LIGHT_EXPONENT);
}

void load_textures()
{
	glGenTextures(1, &plataforma);
	glBindTexture(GL_TEXTURE_2D, plataforma);
	loadImageFile((char*)"img/floor.jpeg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenTextures(1, &skybox);
	glBindTexture(GL_TEXTURE_2D, skybox);
	loadImageFile((char*)"img/skybox_1.jpg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &tex_meteorito);
	glBindTexture(GL_TEXTURE_2D, tex_meteorito);
	loadImageFile((char*)"img/asteroid_00.jpeg");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void init()
{
	cout << glGetString(GL_VERSION) << endl;
	
	configure_lights();
	load_textures();

	for (int i = 0; i < NUM_METEORITOS; i++) {
		meteoritos[i] = new Meteorito2();
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);		// Para que las normales siempre tengan rango 1
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

void load_skybox()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	
	// el cubemap se deberá mover con la cámara para que sea inalcanzable
	Vec3 o = sistema->geto();
	glTranslatef(o.x, o.y, o.z);
	//printf("%f, %f, %f\n", o.x, o.y, o.z);
	
   /***************************************************************************************
	Crear un cubo con 6 quadtex y a cada uno darle unas coordenadas diferentes del cubemap. 
	***************************************************************************************/
	// Cara frontal
	glBindTexture(GL_TEXTURE_2D, skybox);
	quadtex(CUBEMAP_VERTEX[0], CUBEMAP_VERTEX[1], CUBEMAP_VERTEX[2], CUBEMAP_VERTEX[3], 
		0.50f, 0.75f, 1/3.0f, 2/3.0f, 
		1, 1);

	// Cara derecha
	quadtex(CUBEMAP_VERTEX[4], CUBEMAP_VERTEX[5], CUBEMAP_VERTEX[6], CUBEMAP_VERTEX[7],
		0.75f, 1, 1/3.0f, 2/3.0f,
		1, 1);

	// Cara izquierda
	quadtex(CUBEMAP_VERTEX[8], CUBEMAP_VERTEX[9], CUBEMAP_VERTEX[10], CUBEMAP_VERTEX[11],
		0.25, 0.5f, 1/3.0f, 2/3.0f,
		1, 1);

	// Cara trasera
	quadtex(CUBEMAP_VERTEX[12], CUBEMAP_VERTEX[13], CUBEMAP_VERTEX[14], CUBEMAP_VERTEX[15],
		0, 0.25f, 1/3.0f, 2/3.0f,
		1, 1);

	// Cara superior
	quadtex(CUBEMAP_VERTEX[16], CUBEMAP_VERTEX[17], CUBEMAP_VERTEX[18], CUBEMAP_VERTEX[19],
		0.5f, 0.75f, 2/3.0f, 1,
		1, 1);

	// Cara inferior
	quadtex(CUBEMAP_VERTEX[20], CUBEMAP_VERTEX[21], CUBEMAP_VERTEX[22], CUBEMAP_VERTEX[23],
		0.5f, 0.75f, 0, 1/3.0f,
		1, 1);

	glEnable(GL_LIGHTING);
	glPopMatrix();

}

void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Poner las luces de la nave antes de la cámara para que vayan colidarias con ella
	ship_lights();

	Vec3 w = sistema->getw();
	Vec3 v = sistema->getv();
	Vec3 o = sistema->geto();
	Vec3 poi = o - w;

	// Situacion y orientación de la cámara
	gluLookAt(o.x, o.y, o.z, poi.x, poi.y, poi.z, v.x, v.y, v.z);

	sistema->drawGlobal();

	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0, 0, 1);
	//glPolygonMode(GL_FRONT, GL_LINE);
	
	// Dibujar la malla
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, AZUL);
	glBindTexture(GL_TEXTURE_2D, plataforma);
	quad(PLATAFORMA_V[0], PLATAFORMA_V[1], PLATAFORMA_V[2], PLATAFORMA_V[3], RESOLUCION, RESOLUCION);
	glPopAttrib();

	// Objetos Iluminacion
	put_lights_on_scene();
	glPushMatrix();
	glTranslatef(POS_SOL[0], POS_SOL[1], POS_SOL[2]);
	glutWireSphere(0.1, 10, 10);
	glPopMatrix();
	glPopAttrib();

	// colocar el skybox y sus textura
	load_skybox();

	// Dibujar los meteoritos
	for (int i = 0; i < NUM_METEORITOS; i++) {
		meteoritos[i]->draw();
	}

	// Dibujar círculo central mirilla
	draw_circle_viewport(RADIO_MIRILLA_CENTRAL);
	draw_velocimeter();
	

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
		yaw_angle = -mouse_delta_x / screen_center_x * PIXELES_X_GRADOS;
		sistema->rotar(rad(yaw_angle), sistema->getv());

		// Cabeceo de la nave
		pitch_angle = mouse_delta_y / screen_center_y * PIXELES_X_GRADOS;
		pitch_angle = max(-MAX_ANGULO_CABECEO, min(MAX_ANGULO_CABECEO, pitch_angle));
		sistema->rotar(rad(pitch_angle), sistema->getu());
	}

	if (isRolling) {
		// Alabeo de la nave
		// TODO meter el momentum para que sea mas realista
		roll_angle = ANGULO_ALABEO * roll_side_flip * PIXELES_X_GRADOS;
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
	case 'l':
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
		case 'l':
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
}

int main(int argc, char** argv)
{
	// Inicializaciones
	FreeImage_Initialise();
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
	FreeImage_DeInitialise();
}