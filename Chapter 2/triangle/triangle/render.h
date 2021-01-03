#ifndef _RENDER_H
#define _RENDER_H
#ifdef WIN32
#pragma once
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void init(void);
void render(void);

GLuint program;
GLuint VAO;
#endif
