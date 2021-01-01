#include <GL/glew.h>
#include <math.h>

void render(double currentTime) {
	GLfloat color[] = {
		(float)sin(currentTime) * 0.5f + 0.5f,
		(float)cos(currentTime) * 0.5f + 0.5f,
		0.0f, 1.0f
	};

	glClearBufferfv(GL_COLOR, 0, color);
}