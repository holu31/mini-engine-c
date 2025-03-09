#ifndef _PHYSICS_BODY_H_
#define _PHYSICS_BODY_H_

#include "cglm/cglm.h"

typedef struct {
	bool activated;
	bool dynamic;
	vec3 scale;
	vec3 position;
} physics_body_t;

physics_body_t* PhysicsBody_Init();
bool PhysicsBody_CheckCollision(const physics_body_t* body1, const physics_body_t* body2);

#endif // _PHYSICS_BODY_H_