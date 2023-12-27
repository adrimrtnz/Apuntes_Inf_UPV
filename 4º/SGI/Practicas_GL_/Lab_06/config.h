#pragma once

// Constantes Globales
static const float REFRESH_RATE = 60;
static const int RESOLUCION = 200;
static const float DIM_ESPACIO = 3;
static const float DIM_CUBEMAP = 150;
static const float SHIP_LIGHT_CUTOFF = 7.5;
static const float SHIP_LIGHT_EXPONENT = 2.0f;
static const float zFar = 1000;
static const float ANGULO_GIRO = 180.0f;
static const float ANGULO_ALABEO = 2.0f;
static const float MAX_ANGULO_CABECEO = 89.0f;
static const float MAX_ANGULO_ALABEO = 30.0f;
static const float PIXELES_X_GRADOS = 1.0f;
static const int INITIAL_WIDTH = 1280;
static const int INITIAL_HEIGHT = 720;
static const float EPSILON = 1e-3;
static const int MAX_SPEED = 10;
static const float RADIO_MIRILLA_CENTRAL = 12.0f;
static const float ANCHO_LINEA_MIRILLA = 3.0f;
static const int NUM_METEORITOS = 200;
static const float MIN_RPS_METEORITO = 0.1f;
static const float MAX_RPS_METEORITO = 0.6f;

// Vertices plataforma
static float PLATAFORMA_V[4][4] = {
	{-DIM_ESPACIO / 2, -DIM_ESPACIO / 2, 0},
	{DIM_ESPACIO / 2, -DIM_ESPACIO / 2, 0},
	{DIM_ESPACIO / 2, DIM_ESPACIO / 2, 0},
	{-DIM_ESPACIO / 2, DIM_ESPACIO / 2, 0},
};

// Vertices del cubemap
GLfloat CUBEMAP_VERTEX[][3] = {
	{ -DIM_CUBEMAP,  DIM_CUBEMAP, -DIM_CUBEMAP },	// Frontal 1 v0
	{  DIM_CUBEMAP,  DIM_CUBEMAP, -DIM_CUBEMAP },	// Frontal 2 v1
	{  DIM_CUBEMAP,  DIM_CUBEMAP,  DIM_CUBEMAP },	// Frontal 3 v2
	{ -DIM_CUBEMAP,  DIM_CUBEMAP,  DIM_CUBEMAP },	// Frontal 4 v3

	{  DIM_CUBEMAP,  DIM_CUBEMAP, -DIM_CUBEMAP },	// Derecha 1 v4
	{  DIM_CUBEMAP, -DIM_CUBEMAP, -DIM_CUBEMAP },	// Derecha 2 v5
	{  DIM_CUBEMAP, -DIM_CUBEMAP,  DIM_CUBEMAP },	// Derecha 3 v6
	{  DIM_CUBEMAP,  DIM_CUBEMAP,  DIM_CUBEMAP },	// Derecha 4 v7

	{ -DIM_CUBEMAP, -DIM_CUBEMAP, -DIM_CUBEMAP },	// Izquierda 1 v8
	{ -DIM_CUBEMAP,  DIM_CUBEMAP, -DIM_CUBEMAP },	// Izquierda 2 v9
	{ -DIM_CUBEMAP,  DIM_CUBEMAP,  DIM_CUBEMAP },	// Izquierda 3 v10
	{ -DIM_CUBEMAP, -DIM_CUBEMAP,  DIM_CUBEMAP },	// Izquierda 4 v11

	{  DIM_CUBEMAP, -DIM_CUBEMAP, -DIM_CUBEMAP },	// Detras 1 v12
	{ -DIM_CUBEMAP, -DIM_CUBEMAP, -DIM_CUBEMAP },	// Detras 2 v13
	{ -DIM_CUBEMAP, -DIM_CUBEMAP,  DIM_CUBEMAP },	// Detras 3 v14
	{  DIM_CUBEMAP, -DIM_CUBEMAP,  DIM_CUBEMAP },	// Detras 4 v15

	{ -DIM_CUBEMAP,  DIM_CUBEMAP,  DIM_CUBEMAP },	// Arriba 1 v16
	{  DIM_CUBEMAP,  DIM_CUBEMAP,  DIM_CUBEMAP },	// Arriba 2 v17
	{  DIM_CUBEMAP, -DIM_CUBEMAP,  DIM_CUBEMAP },	// Arriba 3 v18
	{ -DIM_CUBEMAP, -DIM_CUBEMAP,  DIM_CUBEMAP },	// Arriba 4 v19

	{ -DIM_CUBEMAP, -DIM_CUBEMAP, -DIM_CUBEMAP },	// Abajo 1 v20
	{  DIM_CUBEMAP, -DIM_CUBEMAP, -DIM_CUBEMAP },	// Abajo 2 v21
	{  DIM_CUBEMAP,  DIM_CUBEMAP, -DIM_CUBEMAP },	// Abajo 3 v22
	{ -DIM_CUBEMAP,  DIM_CUBEMAP, -DIM_CUBEMAP },	// Abajo 4 v23
};


// Configuracion Iluminacion
static const float POS_SOL[] = { 1, 10, 2, 0.0 };
static const float COLOR_SOL[] = { 1, 1, 1, 1 };


// Colores y Materiales
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