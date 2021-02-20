#include "loadshaders.h"

#include <stddef.h>

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

void init(void) {
	static const GLfloat vertices[3][2] = {
		{ -0.90f, -0.90f },
		{ 0.85f, -0.90f },
		{ -0.90f, 0.85f },
	};

	glCreateBuffers(NumBuffers, Buffers);
	glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);

	shaderinfo shaders[] = {
		{ GL_VERTEX_SHADER, "../triangles.vs" },
		{ GL_FRAGMENT_SHADER, "../triangles.fs" },
		{ GL_NONE, NULL}
	};

	GLuint program = loadshaders(shaders);
	glUseProgram(program);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	glEnableVertexAttribArray(vPosition);
}

void display(void) {
	static const float orng[] = { 0.8f, 0.8f, 0.4f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, orng);

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}