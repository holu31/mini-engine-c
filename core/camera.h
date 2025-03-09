#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "cglm/cglm.h"
#include "stdbool.h"

typedef struct {
	float fov;
	float aspect;
	float near;
	float far;
	vec3 position;
	vec3 rotation;
	bool enabled;
} camera_t;

camera_t* Camera_Init();
void Camera_GetProjectionMatrix(camera_t* camera, mat4 mat);
void Camera_GetViewMatrix(camera_t* camera, mat4 mat);

#endif // _CAMERA_H_