#pragma once

// Constantes Globales
static const float REFRESH_RATE = 60;
static const int RESOLUCION = 100;
static const float DIM_ESPACIO = 100;
static const float zFar = 1000;
static const float ANGULO_GIRO = 180.0f;
static const float ANGULO_ALABEO = 2.0f;
static const float MAX_ANGULO_CABECEO = 89.0f;
static const float MAX_ANGULO_ALABEO = 30.0f;
static const float PIXELES_X_GRADOS = 1.0f;
static const int INITIAL_WIDTH = 800;
static const int INITIAL_HEIGHT = 600;
static const float EPSILON = 1e-3;
static const int MAX_SPEED = 10;
static const float RADIO_MIRILLA_CENTRAL = 12.0f;
static const float ANCHO_LINEA_MIRILLA = 3.0f;

// Configuracion Iluminacion
static const float POS_SOL[] = { 1, 10, 2, 0.0 };
static const float COLOR_SOL[] = { 1, 1, 1, 1 };

static const float COLOR_LUZ_NAVE[] = { 1, 1, 1, 1 };
GLfloat AMBIENT_FOCOS[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat DIFFUSE_FOCOS[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat SPECULAR_FOCOS[] = { 0.0, 0.0, 0.0, 0.0 };
static float LUZ_NAVE_CUTOFF = 30.0f;
static float SPEED_COLORS[][3] = {
	{ 0, 0, 1 },
	{ 1, 1, 0 },
	{ 1, 0, 0 },
	{ 0.75, 0, 0}
};