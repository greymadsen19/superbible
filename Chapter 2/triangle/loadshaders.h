#ifndef _LOAD_SHADERS_H
#define _LOAD_SHADERS_H
#ifdef WIN32
#pragma once
#endif

#include <GL/glew.h>

typedef struct {
	GLenum type;
	const char* filename;
	GLuint shader;
} shaderinfo;

GLuint loadshaders(shaderinfo*);
#endif
