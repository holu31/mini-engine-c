#include "window.h"
#include "gl_main.h"
#include "GLFW/glfw3.h"
#include "stdio.h"
#include "stdlib.h"

static GLFWwindow* window;

void Window_Create() {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	glfwDefaultWindowHints();
	GL_Hints();

	window = glfwCreateWindow(800, 600, "test", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "failed to create window\n");
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	if (!GL_Init()) {
		exit(EXIT_FAILURE);
	}
}

void Window_Show() {
	if (window && glfwGetCurrentContext() == window) {
		glfwShowWindow(window);
	}
}

void Window_Destroy() {
	if (window) {
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}

void Window_SwapBuffers() {
	if (window == NULL) return;

	glfwSwapBuffers(window);
}

bool Window_IsRunning() {
	return window && !glfwWindowShouldClose(window);
}