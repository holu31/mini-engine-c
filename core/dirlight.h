#ifndef _DIRLIGHT_H_
#define _DIRLIGHT_H_

#include "cglm/cglm.h"

typedef struct {
	vec4 light_color;
	float light_strength;
	vec3 position;
} dirlight_t;

dirlight_t* DirectionalLight_Init();

#endif // _DIRLIGHT_H_