#pragma once

using namespace cb;

class Meteorito
{
private:
	float SECS_OF_EXPLOSION = 2.0f;
	int NUM_OF_EXPLOSION_CORES = 5;
	float MIN_RADIUS = 0.25;
	float MAX_RADIUS = 2.0f;
	int MIN_DIVISIONS = 4;
	int MAX_DIVISIONS = 10;
	float x = 0, y = 0, z = 0, radius = 0;
	int slices = 0, stacks = 0;
	Vec3 explosion_pos;
	Vec3 desplazamiento;
	float explosion_time = 0.0f;
	bool isExploding = FALSE;
	bool isPlaying = FALSE;
	float rps = 0, rot_angle = 0, rot_x, rot_y, rot_z;
	float max_distance = DIM_CUBEMAP / 2.0;
	GLUquadricObj* quad;
	GLuint tex_meteorito;
	int numPts = 100;
	void Translate(float delta_time);
	void draw_explosion(float delta_time);
public:
	Meteorito(GLuint textura);
	Vec3 get_position();
	void draw(float delta_time);
	void teleport();
	void cambia_dir();
};


void Meteorito::draw_explosion(float delta_time) 
{
	explosion_time += delta_time;
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

#ifdef SOUND_ON
	if (!isPlaying) {
		isPlaying = TRUE;
		PlaySound(TEXT("sound/explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
#endif

	for (int i = 0; i < NUM_OF_EXPLOSION_CORES; i++) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glTranslatef(
			explosion_pos.x + random(-0.5, i * 0.5),
			explosion_pos.y + random(-0.5, i * 0.5),
			explosion_pos.z + random(-0.5, i * 0.5)
		);
		glRotatef(10 * (i + 1), 0, 1, 0);
		glColor4f(1, 1, random(0,1), 1 - (explosion_time / SECS_OF_EXPLOSION));
		glutSolidSphere(random(0.15, 0.75 + explosion_time), 5, 5);
		glPopAttrib();
		glPopMatrix();
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	if (explosion_time >= SECS_OF_EXPLOSION) {
		explosion_time = 0;
		isExploding = FALSE;
		isPlaying = FALSE;
	}
}

Vec3 Meteorito::get_position()
{
	return Vec3(x, y, z);
}

Meteorito::Meteorito(GLuint textura)
{
	tex_meteorito = textura;
	quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);
	gluQuadricNormals(quad, GLU_SMOOTH);
	x = random(-max_distance, max_distance);
	y = random(-max_distance, max_distance);
	z = random(-max_distance, max_distance);
	radius = random(MIN_RADIUS, MAX_RADIUS);
	slices = int(random(MIN_DIVISIONS, MAX_DIVISIONS));
	stacks = int(random(MIN_DIVISIONS, MAX_DIVISIONS));
	desplazamiento = Vec3(random(-1, 1), random(-1, 1), random(-1, 1));
	rps = random(MIN_RPS_METEORITO, MAX_RPS_METEORITO);
	rot_x = random(0, 1);
	rot_y = random(0, 1);
	rot_z = random(0, 1);
}

void Meteorito::Translate(float delta_time)
{
	x += desplazamiento.x * delta_time;
	y += desplazamiento.y * delta_time;
	z += desplazamiento.z * delta_time;

	if (abs(x) > DIM_CUBEMAP || abs(y) > DIM_CUBEMAP || abs(z) > DIM_CUBEMAP) {
		x = random(-max_distance, max_distance);
		y = random(-max_distance, max_distance);
		z = random(-max_distance, max_distance);
	}
}

void Meteorito::draw(float delta_time)
{
	if (!isExploding) {
		rot_angle += rps * 360 * delta_time;
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glColor3f(1, 1, 1);
		Translate(delta_time);
		glTranslatef(x, y, z);
		glRotatef(rot_angle, rot_x, rot_y, rot_z);
		glBindTexture(GL_TEXTURE_2D, tex_meteorito);
		gluSphere(quad, 0.5, slices, stacks);
		glPopAttrib();
		glPopMatrix();
	}
	else {
		draw_explosion(delta_time);
	}

}

void Meteorito::teleport()
{
	explosion_pos.x = x;
	explosion_pos.y = y;
	explosion_pos.z = z;
	x = random(-max_distance, max_distance);
	y = random(-max_distance, max_distance);
	z = random(-max_distance, max_distance);
	isExploding = TRUE;
}

