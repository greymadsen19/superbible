#include "render.h"

#include <stdio.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
	glewExperimental = GL_TRUE;
	bool running = true;;
	GLFWwindow* window;

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_SAMPLES, 0);

	window = glfwCreateWindow(800, 600, "Triangles", NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to open window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

#ifdef _DEBUG
	fprintf(stderr, "VENDER: %s\n", (char*)glGetString(GL_VENDOR));
	fprintf(stderr, "VERSION: %s\n", (char*)glGetString(GL_VERSION));
	fprintf(stderr, "RENDERER: %s\n", (char*)glGetString(GL_RENDERER));
#endif

	init();

	do {
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
		running &= (glfwWindowShouldClose(window) != GL_TRUE);
	} while (running);

	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &VAO);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}