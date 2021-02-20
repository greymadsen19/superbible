#include "loadshaders.h"

#include <stdio.h>
#include <stdlib.h>

static const GLchar* readshader(const char* filename) {
	FILE* infile = fopen(filename, "rb");
	long len;
	GLchar* buffer;

	if (infile == NULL) {
#ifdef _DEBUG
		fprintf(stderr, "Failed to open file %s\n", filename);
#endif
		return NULL;
	}

	fseek(infile, 0L, SEEK_END);
	len = ftell(infile);
	fseek(infile, 0L, SEEK_SET);

	buffer = (char*)calloc(len + 1, sizeof(char));

	if (buffer == NULL) {
#ifdef _DEBUG
		fprintf(stderr, "Failed to allocate memory for file %s\n", filename);
#endif
		return NULL;
	}

	fread(buffer, sizeof(char), len + 1, infile);
	fclose(infile);

	return (const GLchar*)buffer;
}

GLuint loadshaders(shaderinfo* shaders) {
	if (shaders == NULL)
		return 0;

	GLuint program = glCreateProgram();

	shaderinfo* entry = shaders;

	while (entry->type != GL_NONE) {
		GLuint shader = glCreateShader(entry->type);

		entry->shader = shader;

		const GLchar* source = readshader(entry->filename);

		if (source == NULL) {
			for (entry = shaders; entry->type != GL_NONE; ++entry) {
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}

			return 0;
		}

		glShaderSource(shader, 1, &source, NULL);
		free((void*)source);

		glCompileShader(shader);

		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled) {
#ifdef _DEBUG
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
			GLchar* log = malloc(len + 1);
			glGetShaderInfoLog(shader, len, &len, log);
			fprintf(stderr, "Shader failed to compile %s\n", log);
			free(log);
#endif
			return 0;
		}

		glAttachShader(program, shader);
		++entry;
	}

	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (!linked) {
#ifdef _DEBUG
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		GLchar* log = malloc(len + 1);
		glGetProgramInfoLog(program, len, &len, log);
		fprintf(stderr, "Shader failed to link %s\n", log);
		free(log);
#endif
		for (entry = shaders; entry->type != GL_NONE; ++entry) {
			glDeleteShader(entry->shader);
			entry->shader = 0;
		}

		return 0;
	}

	for (entry = shaders; entry->shader != GL_NONE; ++entry) {
		glDeleteShader(entry->shader);
		entry->shader = 0;
	}

	return program;
}
