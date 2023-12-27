#include "Meteorito.h"
/*

Meteorito::Meteorito()
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
	rps = random(0.1, 0.8);
	rot_x = random(0, 1);
	rot_y = random(0, 1);
	rot_z = random(0, 1);
}

void Meteorito::Translate()
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

void Meteorito::draw()
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

*/