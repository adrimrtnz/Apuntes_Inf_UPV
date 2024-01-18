#pragma once

using namespace cb;

class Bala
{
private:
	//void translate(float delta_time);
	Vec3 origen, actual, direccion;
	float VELOCIDAD_PROYECTIL = 150.0f;
	float RADIO_PROYECTIL = .25f;
	float DISTANCIA_MAX_PROYECTIL = 200.0f;
	bool shoot = FALSE;
public:
	bool isShooting();
	void impacto();
	float distancia();
	Vec3 get_position();
	void set_vectors(Vec3 origen, Vec3 direccion);
	void draw(float delta_time);
};

void Bala::set_vectors(Vec3 src, Vec3 dst)
{
	origen = src;
	actual = src;
	direccion = dst;
	shoot = TRUE;
}

void Bala::impacto()
{
	shoot = FALSE;
}

bool Bala::isShooting()
{
	return shoot;
}

float Bala::distancia()
{
	Vec3 dist = origen - actual;
	return dist.norm();
}

Vec3 Bala::get_position()
{
	return actual;
}

void Bala::draw(float delta_time)
{
	if (distancia() < DISTANCIA_MAX_PROYECTIL) {
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);

		// Balas como esferas rojas
		glColor3f(1, 0, 0);
		glTranslatef(actual.x, actual.y, actual.z);
		glutSolidSphere(RADIO_PROYECTIL, 10, 10);
		actual = actual - direccion * VELOCIDAD_PROYECTIL * delta_time;

		glPopAttrib();
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	else {
		shoot = FALSE;
	}
}