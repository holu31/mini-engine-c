#include "env.h"
#include "malloc.h"

env_t* Environment_Init() {
	env_t* env = malloc(sizeof(env_t));
	if (!env) return NULL;

	env->ambient_strength = 0.1f;
	glm_vec4_one(env->ambient_color);

	return env;
}