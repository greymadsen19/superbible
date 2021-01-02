#include "render.h"
#include "loadshaders.h"
#include <math.h>

void init(void) {
	shaderinfo shaders[] = {
		{ GL_VERTEX_SHADER, "points.vs" },
		{ GL_FRAGMENT_SHADER, "points.fs" },
		{ GL_NONE, NULL }
	};

	program = loadshaders(shaders);
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void render(double currentTime) {
	GLfloat color[] = { cos(currentTime) * 0.5f + 0.5f, 0.0f,  sin(currentTime) * 0.5f + 0.5f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, color);

	glUseProgram(program);

	glPointSize(40.0f);

	glDrawArrays(GL_POINTS, 0, 1);
}