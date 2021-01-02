#include "render.h"
#include "loadshaders.h"

void init(void) {
	shaderinfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangle.vs" },
		{ GL_FRAGMENT_SHADER, "triangle.fs" },
		{ GL_NONE, NULL }
	};

	program = loadshaders(shaders);
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void render(void) {
	const GLfloat color[] = { 0.0f, 0.4f, 0.3f, 1.0f };

	glClearBufferfv(GL_COLOR, 0, color);

	glUseProgram(program);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}