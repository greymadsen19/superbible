#include <GL/glew.h>

void render(void) {
	static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, red);
}