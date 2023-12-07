#include "Utils.h"

void draw_circle(float center_x, float center_y, float radius, int num_segments)
{
	/**/
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_segments; i++) {
		float theta = 2.0f * PI * float(i) / float(num_segments);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		glVertex2f(x + center_x, y + center_x);
	}
	glEnd();
}