#include <stdio.h>
#include <stdlib.h>

#include "loadshaders.h"

static const GLchar* readshader(const char* filename) {
	FILE* infile = fopen(filename, "rb");
	long len;
	GLchar* source;

	if (infile == NULL) {
		fprintf(stderr, "Unable to open file %s\n", filename);
		return NULL;
	}

	fseek(infile, 0L, SEEK_END);
	len = ftell(infile);
	fseek(infile, 0L, SEEK_SET);

	source = (char*)calloc(len + 1, sizeof(char));

	if (source == NULL) {
		fprintf(stderr, "Memory allocation error at %p\n", &source);
		return NULL;
	}

	fread(source, sizeof(char), len + 1, infile);
	fclose(infile);

	source[len] = '\0';

	return (const char*)source;
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
		free((GLchar*)source);

		glCompileShader(shader);
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
			GLchar* log = malloc(len + 1);
			glGetShaderInfoLog(shader, len, &len, log);
			fprintf(stderr, "Shader compilation failed: %s\n", log);
			free(log);
			return 0;
		}

		glAttachShader(program, shader);

		++entry;
	}

	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (!linked) {
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = malloc(len + 1);
		glGetProgramInfoLog(program, len, &len, log);
		fprintf(stderr, "Shader linking failed: %s\n", log);
		free(log);

		for (entry = shaders; entry->type != GL_NONE; ++entry) {
			glDeleteShader(entry->shader);
			entry->shader = 0;
		}

		return 0;
	}

	return program;
}
