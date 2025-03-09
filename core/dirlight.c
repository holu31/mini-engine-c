#include "dirlight.h"

dirlight_t* DirectionalLight_Init() {
	dirlight_t* light = malloc(sizeof(dirlight_t));
	if (!light) return NULL;

	glm_vec4_one(light->light_color);
	light->light_strength = 1.f;
	glm_vec3_zero(light->position);

	return light;
}
