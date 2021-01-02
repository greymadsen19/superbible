#include "render.h"

#include <stdio.h>
#include <stdbool.h>

int main(void) {
	glewExperimental = GL_TRUE;
	bool running = true;
	GLFWwindow* window;

	// Initialize GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Set window hints before creating a window context
	// Set Context version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Enable Context debugging if run through a debugger
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	// Enable the Core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Set Forward compatiblity
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Set the sampling level
	glfwWindowHint(GLFW_SAMPLES, 0);

	window = glfwCreateWindow(800, 600, "Points", NULL, NULL);

	if (!window) {
		fprintf(stderr, "Failed to open window\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// After initializing GLEW display the OpenGL vendor, version and Renderer if in debug mode
#ifdef _DEBUG
	fprintf(stderr, "VENDOR: %s\n", (char*)glGetString(GL_VENDOR));
	fprintf(stderr, "VERSION: %s\n", (char*)glGetString(GL_VERSION));
	fprintf(stderr, "RENDERER: %s\n", (char*)glGetString(GL_RENDERER));
#endif

	init();

	do {
		// Render Graphics
		render(glfwGetTime());

		glfwSwapBuffers(window);
		glfwPollEvents();

		running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
		running &= (glfwWindowShouldClose(window) != GL_TRUE);
	} while (running);

	glDeleteVertexArrays(1, VAO);
	glDeleteProgram(program);
	glDeleteVertexArrays(1, VAO);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}