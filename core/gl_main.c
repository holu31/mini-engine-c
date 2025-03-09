#include "gl_main.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GL/gl.h"
#include "world.h"

#include "stdio.h"
#include "stdlib.h"

static void GL_FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	camera_t* camera = World_GetCamera();
	camera->aspect = (float) width / (float) height;
}

void GL_Hints() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool GL_Init() {
	if (!glfwGetCurrentContext()) {
		fprintf(stderr, "Error: GLFW context not set\n");
		return GL_FALSE;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "failed to initialize GLAD\n");
		return GL_FALSE;
	}

	glfwSetFramebufferSizeCallback(glfwGetCurrentContext(), GL_FramebufferSizeCallback);

	const GLubyte* version = glGetString(GL_VERSION);
	if (version) {
		printf("OpenGL version %s\n", version);
	}
	else {
		fprintf(stderr, "failed to get OpenGL version\n");
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	return GL_TRUE;
}