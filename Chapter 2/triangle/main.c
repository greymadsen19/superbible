#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "render.h"

int main(int argc, char* argv[]) {
	glewExperimental = GL_TRUE;
	GLFWwindow* window;

	// Initialize GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Open Window
	window = glfwCreateWindow(1280, 720, "Triangles", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Failed to open window\n");
		glfwTerminate();
		return -1;
	}

	// Make OpenGL context
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Initialize Shaders
	init();

	while (!glfwWindowShouldClose(window)) {
		// Display Triangles
		display();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
