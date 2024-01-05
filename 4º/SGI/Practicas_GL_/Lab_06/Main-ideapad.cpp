/***************************************************
*	Bloque Practica 6
*
*	Simulador
*
*	@author	Adrian Martinez
*	@date Nov,2023
***************************************************/

#define PROYECTO "Simulador"
#define SOUND_ON

#ifdef SOUND_ON
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

#include <iostream>
#include <sstream>
#include <string>
#include <codebase.h>
#include "config.h"
#include "utils.h"
#include "Meteorito.h"
#include "Bala.h"

using namespace std;
using namespace cb;


// Globales
static const float AREA_MIRILLA = RADIO_MIRILLA_CENTRAL * RADIO_MIRILLA_CENTRAL * PI;
static bool isRolling = FALSE;
static bool lights_on = FALSE;
static bool lights_button_pressed = FALSE;
static bool show_cockpit = TRUE;
static bool cockpit_button_pressed = FALSE;
static bool camara_tercera_persona = FALSE;
static bool camara_toggle_pressed = FALSE;
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
Vec3 poi = sistema->geto() - sistema->getw();
static float angulo_poi = 0;
static int poi_direction = 0;
static bool is_poi_yaw = FALSE;

// IDs texturas
static GLuint plataforma;
static GLuint skybox;
static GLuint tex_meteorito;
static GLuint tex_nave;
static GLuint tex_nave_ext;

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
static float ini_x = 0.0f;
static float ini_y = 0.0f;
static GLfloat yaw_angle = 0.0f;
static GLfloat pitch_angle = 0.0f;
static GLfloat roll_angle = 0.0f;
static int roll_side_flip = 0;
static Meteorito* meteoritos[NUM_METEORITOS];
static Bala* balas[NUM_PROYECTILES];
static int num_bala = 0;
static int meteoritos_destruidos = 0;

//***************************************************************************

void draw_gui(float radius = 1.0f, int num_segments = 10)
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

	string points = "Meteoritos destruidos: ";
	points += std::to_string(meteoritos_destruidos);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	texto(TEXT_X_MARGIN, TEXT_Y_MARGIN, (char*)points.c_str());
	glPopAttrib();

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void draw_velocimeter() 
{
	// Desactivar la prueba de profundidad
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
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
	glEnable(GL_TEXTURE_2D);
}

void ship_lights()
{
	static float offset = 0.15f;

	GLfloat pos_luz_1[] = { offset,  0, z0 , 1 };
	GLfloat pos_luz_2[] = { -offset, 0 , z0 , 1 };
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
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, SHIPT_LIGHT_CONSTANT_ATTENUATION);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, SHIPT_LIGHT_LINEAR_ATTENUATION);

	glLightfv(GL_LIGHT2, GL_DIFFUSE, BLANCO);
	glLightfv(GL_LIGHT2, GL_SPECULAR, BLANCO);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, SHIP_LIGHT_CUTOFF);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, SHIP_LIGHT_EXPONENT);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, SHIPT_LIGHT_LINEAR_ATTENUATION);
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

	glGenTextures(1, &tex_nave);
	glBindTexture(GL_TEXTURE_2D, tex_nave);
	loadImageFile((char*)"img/nave_cubemap.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &tex_nave_ext);
	glBindTexture(GL_TEXTURE_2D, tex_nave_ext);
	loadImageFile((char*)"img/nave_cubemap_ext.png");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void init()
{
	cout << glGetString(GL_VERSION) << endl;
	
	configure_lights();
	load_textures();

	for (int i = 0; i < NUM_METEORITOS; i++) {
		meteoritos[i] = new Meteorito(tex_meteorito);
	}

	for (int i = 0; i < NUM_PROYECTILES; i++) {
		balas[i] = new Bala();
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
	
	draw_skybox_cubemap(skybox);

	glEnable(GL_LIGHTING);
	glPopMatrix();

}

void load_ship_cubemap()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();

	Vec3 o = sistema->geto();
	Vec3 w = sistema->getw().normalize();
	Vec3 v = sistema->getv().normalize();
	Vec3 u = sistema->getu().normalize();

	// Construir la matriz de transformación
	GLfloat matriz_transformacion[16] = {
		u.x, u.y, u.z, 0.0f,
		-w.x, -w.y, -w.z, 0.0f,
		v.x, v.y, v.z, 0.0f,
		o.x, o.y, o.z, 1.0f
	};
	glMultMatrixf(matriz_transformacion);

	if (camara_tercera_persona) {
		draw_ship_cubemap_outside(tex_nave_ext);
	}
	else {
		draw_ship_cubemap_inside(tex_nave);
	}

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

	// Situacion y orientación de la cámara
	if (camara_tercera_persona) {
		Vec3 tercera_persona = o + w * 3 + v*0.5;
		gluLookAt(tercera_persona.x, tercera_persona.y, tercera_persona.z, poi.x, poi.y, poi.z, v.x, v.y, v.z);
	} 
	else {
		gluLookAt(o.x, o.y, o.z, poi.x, poi.y, poi.z, v.x, v.y, v.z);
	}

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
		meteoritos[i]->draw(delta_time);
#ifdef SOUND_ON
		if (Vec3(meteoritos[i]->get_position() - o).norm() < MAX_DITANCIA_IMPACTO) {
			PlaySound(TEXT("sound/hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
#endif
	}

	for (int i = 0; i < NUM_PROYECTILES; i++) {
		if (balas[i]->isShooting()) {
			balas[i]->draw(delta_time);
		}
	}

	// Tratar de hacer lo siguiente de forma más óptima
	for (int i = 0; i < NUM_PROYECTILES; i++) {
		if (balas[i]->isShooting()) {
			Vec3 bala_pos = balas[i]->get_position();
			for (int j = 0; j < NUM_METEORITOS; j++) {
				Vec3 met_pos = meteoritos[j]->get_position();
				float distancia = (bala_pos - met_pos).norm();
				if (Vec3(bala_pos - met_pos).norm() < MAX_DITANCIA_IMPACTO) {
					meteoritos[j]->teleport();
					meteoritos_destruidos++;
				}
			}
		}
	}

	if (show_cockpit) {
		load_ship_cubemap();
	}

	// Dibujar elementos de la GUI
	draw_gui(RADIO_MIRILLA_CENTRAL);
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

	Vec3 o = sistema->geto();
	Vec3 w = sistema->getw();
	Vec3 v = sistema->getv();

	// Movimiento de la nave
	sistema->seto(o - w * speed * delta_time);

	// Punto de vista del piloto
	poi = o - w;
	if (is_poi_yaw) {
		angulo_poi += ANGULO_GIRO_POI * poi_direction * PIXELES_X_GRADOS;
	}

	if (camara_tercera_persona) {
		poi = o - w * 3 + v * 0.5;
	}
	poi.rotate(rad(angulo_poi), v);

	glutPostRedisplay();
}


void onTimer(int time)
{
	glutTimerFunc(time, onTimer, time);
	update();
}

void catchKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		angulo_poi = 0;
		is_poi_yaw = FALSE;
		break;
	case GLUT_KEY_LEFT:
		poi_direction = 1;
		is_poi_yaw = TRUE;
		break;
	case GLUT_KEY_RIGHT:
		poi_direction = -1;
		is_poi_yaw = TRUE;
		break;
	
	}
}

void catchReleasedKey(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		is_poi_yaw = FALSE;
		break;
	case GLUT_KEY_RIGHT:
		is_poi_yaw = FALSE;
		break;
	default:
		break;
	}
}

void onKey(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		speed += ACCEL_SPEED * delta_time;
		speed = min(speed, MAX_SPEED);
		cout << "Acelerando, velocidad = " << speed << endl;
		break;
	case 'z':
		speed -= STOP_SPEED * delta_time;
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
	case 'c':
		if (!cockpit_button_pressed) {
			show_cockpit = !show_cockpit;
			cockpit_button_pressed = TRUE;
		}
		break;
	case 'p':
		if (!camara_toggle_pressed) {
			camara_tercera_persona = !camara_tercera_persona;
			camara_toggle_pressed = TRUE;
		}
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
		case 'c':
			cockpit_button_pressed = FALSE;
			break;
		case 'p':
			camara_toggle_pressed = FALSE;
			break;
	}
}

void onMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		Vec3 o = sistema->geto();
		Vec3 w = sistema->getw();
		Vec3 poi = o - w;
		balas[num_bala % NUM_PROYECTILES]->set_vectors(poi, w);
#ifdef SOUND_ON
		PlaySound(TEXT("sound/shooting.wav"), NULL, SND_FILENAME | SND_ASYNC);
#endif // SOUND_ON
		num_bala++;
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
	glutMouseFunc(onMouseClick);
	glutSpecialFunc(catchKey);
	glutSpecialUpFunc(catchReleasedKey);
	glutKeyboardUpFunc(onKeyRelease);
	glutPassiveMotionFunc(onMouseHover);
	

	// (1000 / refresh_rate) los milisegundos que tienen que pasar entre frame
	glutTimerFunc(int(1000 / REFRESH_RATE), onTimer, int(1000 / REFRESH_RATE));

	// Inicio propio y del bucle de eventos
	init();
	glutMainLoop();
	FreeImage_DeInitialise();
}