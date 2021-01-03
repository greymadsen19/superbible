#include "loadshaders.h"

#include <stddef.h>
#include <math.h>

static GLuint vao;
static GLuint program;

void init(void) {
	shaderinfo shaders[3] = {
		{ GL_VERTEX_SHADER, "offset.vs" },
		{ GL_FRAGMENT_SHADER, "fcolor.fs" },
		{ GL_NONE, NULL}
	};

	program = loadshaders(shaders);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void render(double currentTime) {
	GLfloat color[4] = { 0.5f * (float)sin(currentTime) + 0.5f, 0.0f, 0.5f * (float)cos(currentTime) + 0.5f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, color);

	glUseProgram(program);

	GLfloat attrib[4] = {
		0.5f * (float)cos(currentTime),
		0.5f * (float)sin(currentTime),
		0.0f,
		0.0f
	};

	GLfloat vcolor[4] = {
		0.0f,
		0.0f,
		0.5f * (float)cos(currentTime) + 0.5f,
		1.0f
	};

	glVertexAttrib4fv(0, attrib);
	glVertexAttrib4fv(1, vcolor);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}