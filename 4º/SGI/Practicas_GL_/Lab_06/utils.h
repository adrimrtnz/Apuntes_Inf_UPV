#pragma once

#include <sstream>

using namespace cb;

GLint wind_list = -1;

void gen_wind_list() 
{
	wind_list = glGenLists(1);
	glNewList(wind_list, GL_COMPILE);

	// Cara superior Ala
	glBegin(GL_POLYGON);
	glVertex3f(0, DIM_SHIP_CUBEMAP, 0);
	glVertex3f(DIM_SHIP_CUBEMAP * 2, 0, 0);
	glVertex3f(0, 0, 0);
	glEnd();

	glEndList();
}

void draw_skybox_cubemap(GLuint textura)
{
	/***************************************************************************************
 Crear un cubo con 6 quadtex y a cada uno darle unas coordenadas diferentes del cubemap.
 ***************************************************************************************/
 // Cara frontal
	glBindTexture(GL_TEXTURE_2D, textura);
	quadtex(CUBEMAP_VERTEX[0], CUBEMAP_VERTEX[1], CUBEMAP_VERTEX[2], CUBEMAP_VERTEX[3],
		0.50f, 0.75f, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara derecha
	quadtex(CUBEMAP_VERTEX[4], CUBEMAP_VERTEX[5], CUBEMAP_VERTEX[6], CUBEMAP_VERTEX[7],
		0.75f, 1, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara izquierda
	quadtex(CUBEMAP_VERTEX[8], CUBEMAP_VERTEX[9], CUBEMAP_VERTEX[10], CUBEMAP_VERTEX[11],
		0.25, 0.5f, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara trasera
	quadtex(CUBEMAP_VERTEX[12], CUBEMAP_VERTEX[13], CUBEMAP_VERTEX[14], CUBEMAP_VERTEX[15],
		0, 0.25f, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara superior
	quadtex(CUBEMAP_VERTEX[16], CUBEMAP_VERTEX[17], CUBEMAP_VERTEX[18], CUBEMAP_VERTEX[19],
		0.5f, 0.75f, 2 / 3.0f, 1,
		1, 1);

	// Cara inferior
	quadtex(CUBEMAP_VERTEX[20], CUBEMAP_VERTEX[21], CUBEMAP_VERTEX[22], CUBEMAP_VERTEX[23],
		0.5f, 0.75f, 0, 1 / 3.0f,
		1, 1);
}

void draw_ship_cubemap_inside(GLuint textura)
{
	/***************************************************************************************
	Crear un cubo con 6 quadtex y a cada uno darle unas coordenadas diferentes del cubemap.
	***************************************************************************************/
	// Cara frontal
	glBindTexture(GL_TEXTURE_2D, textura);
	quadtex(SHIP_CUBEMAP_VERTEX[0], SHIP_CUBEMAP_VERTEX[1], SHIP_CUBEMAP_VERTEX[2], SHIP_CUBEMAP_VERTEX[3],
		0.25f, 0.50f, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara derecha
	quadtex(SHIP_CUBEMAP_VERTEX[4], SHIP_CUBEMAP_VERTEX[5], SHIP_CUBEMAP_VERTEX[6], SHIP_CUBEMAP_VERTEX[7],
		0.50f, 0.75f, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara izquierda
	quadtex(SHIP_CUBEMAP_VERTEX[8], SHIP_CUBEMAP_VERTEX[9], SHIP_CUBEMAP_VERTEX[10], SHIP_CUBEMAP_VERTEX[11],
		0, 0.25f, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara trasera
	quadtex(SHIP_CUBEMAP_VERTEX[12], SHIP_CUBEMAP_VERTEX[13], SHIP_CUBEMAP_VERTEX[14], SHIP_CUBEMAP_VERTEX[15],
		0.75f, 1, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara superior
	quadtex(SHIP_CUBEMAP_VERTEX[16], SHIP_CUBEMAP_VERTEX[17], SHIP_CUBEMAP_VERTEX[18], SHIP_CUBEMAP_VERTEX[19],
		0.25f, 0.50f, 2 / 3.0f, 1,
		1, 1);

	// Cara inferior
	quadtex(SHIP_CUBEMAP_VERTEX[20], SHIP_CUBEMAP_VERTEX[21], SHIP_CUBEMAP_VERTEX[22], SHIP_CUBEMAP_VERTEX[23],
		0.25f, 0.50f, 0, 1 / 3.0f,
		1, 1);
}

void draw_ship_cubemap_outside(GLuint textura)
{
	if (wind_list < 0) {
		gen_wind_list();
	}

	glPushMatrix();
	glTranslatef(DIM_SHIP_CUBEMAP, 0, 0);
	glCallList(wind_list);
	glTranslatef(0, 0, -DIM_SHIP_CUBEMAP / 2);
	glCallList(wind_list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-DIM_SHIP_CUBEMAP, 0, 0);
	glRotatef(180, 0, 1, 0);
	glCallList(wind_list);
	glTranslatef(0, 0, DIM_SHIP_CUBEMAP/2);
	glCallList(wind_list);
	glPopMatrix();

	/***************************************************************************************
	Crear un cubo con 6 quadtex y a cada uno darle unas coordenadas diferentes del cubemap.
	***************************************************************************************/
	// Cara frontal
	glBindTexture(GL_TEXTURE_2D, textura);
	quadtex(SHIP_CUBEMAP_VERTEX_OUTSIDE[0], SHIP_CUBEMAP_VERTEX_OUTSIDE[1], SHIP_CUBEMAP_VERTEX_OUTSIDE[2], SHIP_CUBEMAP_VERTEX_OUTSIDE[3],
		0.25f, 0.50f, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara derecha
	quadtex(SHIP_CUBEMAP_VERTEX_OUTSIDE[4], SHIP_CUBEMAP_VERTEX_OUTSIDE[5], SHIP_CUBEMAP_VERTEX_OUTSIDE[6], SHIP_CUBEMAP_VERTEX_OUTSIDE[7],
		0.50f, 0.75f, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara izquierda
	quadtex(SHIP_CUBEMAP_VERTEX_OUTSIDE[8], SHIP_CUBEMAP_VERTEX_OUTSIDE[9], SHIP_CUBEMAP_VERTEX_OUTSIDE[10], SHIP_CUBEMAP_VERTEX_OUTSIDE[11],
		0, 0.25f, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara trasera
	quadtex(SHIP_CUBEMAP_VERTEX_OUTSIDE[12], SHIP_CUBEMAP_VERTEX_OUTSIDE[13], SHIP_CUBEMAP_VERTEX_OUTSIDE[14], SHIP_CUBEMAP_VERTEX_OUTSIDE[15],
		0.75f, 1, 1 / 3.0f, 2 / 3.0f,
		1, 1);

	// Cara superior
	quadtex(SHIP_CUBEMAP_VERTEX_OUTSIDE[16], SHIP_CUBEMAP_VERTEX_OUTSIDE[17], SHIP_CUBEMAP_VERTEX_OUTSIDE[18], SHIP_CUBEMAP_VERTEX_OUTSIDE[19],
		0.25f, 0.50f, 2 / 3.0f, 1,
		1, 1);

	// Cara inferior
	quadtex(SHIP_CUBEMAP_VERTEX_OUTSIDE[20], SHIP_CUBEMAP_VERTEX_OUTSIDE[21], SHIP_CUBEMAP_VERTEX_OUTSIDE[22], SHIP_CUBEMAP_VERTEX_OUTSIDE[23],
		0.25f, 0.50f, 0, 1 / 3.0f,
		1, 1);
}


string to_string_with_precision(const float a_value, const int n = 2)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return std::move(out).str();
}