#include "loadshaders.h"

#include <stddef.h>

#include <math.h>

static GLuint vao;

void init(void) {
	shaderinfo shaders[5] = {
		{ GL_VERTEX_SHADER, "../rectangle.vs" },
		{ GL_TESS_CONTROL_SHADER, "../tess.tcs" },
		{ GL_TESS_EVALUATION_SHADER, "../tess.tes" },
		{ GL_FRAGMENT_SHADER, "../color.fs" },
		{ GL_NONE, NULL }
	};

	GLuint program = loadshaders(shaders);

	glUseProgram(program);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void render(double currentTime) {
	static const  GLfloat color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, color);

	GLfloat offset[4] = { 0.6f * (float)cos(currentTime), 0.0f, 0.0f, 1.0f };

	GLfloat fcolor[4] = { 0.8f * (float)sin(currentTime) + 0.8f, 0.8f * cos(currentTime) + 0.8f , 0.8f * (float)cos(currentTime) + 0.8f, 1.0f };

	glVertexAttrib4fv(0, offset);
	glVertexAttrib4fv(1, fcolor);

	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glDrawArrays(GL_PATCHES, 0, 6);

}