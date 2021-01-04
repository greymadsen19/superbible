#include "render.h"
#include <GLFW/glfw3.h>

#include <stdio.h>

int main(int argc, char* argv[]) {
	glewExperimental = GL_TRUE;
	int running = GL_TRUE;
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
	glfwWindowHint(GL_SAMPLES, 4);

	window = glfwCreateWindow(1280, 720, "Tesselation", NULL, NULL);

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
	fprintf(stderr, "VERSION: %s\n", (char*)glGetString(GL_VERSION));
	fprintf(stderr, "VENDOR: %s\n", (char*)glGetString(GL_VENDOR));
	fprintf(stderr, "RENDERER: %s\n", (char*)glGetString(GL_RENDERER));
#endif

	init();
	
	do {
		render(glfwGetTime());

		glfwSwapBuffers(window);
		glfwPollEvents();

		running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
		running &= (glfwWindowShouldClose(window) != GL_TRUE);
	} while (running);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}