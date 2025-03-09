#ifndef _ENV_H_
#define _ENV_H_

#include "cglm/cglm.h"

typedef struct {
	float ambient_strength;
	vec4 ambient_color;
} env_t;

env_t* Environment_Init();

#endif // _ENV_H_