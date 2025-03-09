#include "camera.h"
#include "GLFW/glfw3.h"

camera_t* Camera_Init()
{
	camera_t* camera = malloc(sizeof(camera_t));
	if (!camera) return NULL;

	int width, height;
	GLFWwindow* context = glfwGetCurrentContext();
	glfwGetWindowSize(context, &width, &height);

	camera->fov = 90.f;
	camera->aspect = (float) width / (float) height;
	camera->near = .01f;
	camera->far = 100.f;

	glm_vec3_zero(camera->position);
	glm_vec3_zero(camera->rotation);

	camera->enabled = true;

	return camera;
}

void Camera_GetProjectionMatrix(camera_t* camera, mat4 mat)
{
	glm_mat4_zero(mat);
	glm_perspective(glm_rad(camera->fov), camera->aspect, camera->near, camera->far, mat);
}

void Camera_GetViewMatrix(camera_t* camera, mat4 mat)
{
	glm_mat4_identity(mat);

	vec3 rotation_rad;
	glm_vec3_scale(camera->rotation, -1.0f, rotation_rad);
	rotation_rad[0] = glm_rad(rotation_rad[0]);
	rotation_rad[1] = glm_rad(rotation_rad[1]);
	rotation_rad[2] = glm_rad(rotation_rad[2]);

	glm_rotate_x(mat, rotation_rad[0], mat);
	glm_rotate_y(mat, rotation_rad[1], mat);
	glm_rotate_z(mat, rotation_rad[2], mat);

	vec3 negate_position;
	glm_vec3_scale(camera->position, -1.f, negate_position);
	glm_translate(mat, negate_position);
}
