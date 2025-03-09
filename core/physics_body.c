#include "physics_body.h"
#include "malloc.h"

physics_body_t* PhysicsBody_Init() {
	physics_body_t* body = malloc(sizeof(physics_body_t));
	if (!body) return NULL;

	body->activated = true;
	body->dynamic = true;
	glm_vec3_zero(body->position);
	glm_vec3_one(body->scale);

	return body;
}

bool PhysicsBody_CheckCollision(const physics_body_t* body1, const physics_body_t* body2) {
	return false;
}
