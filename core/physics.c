#include "physics.h"
#include "malloc.h"

const vec3 gravity = { 0.0f, -9.81f, 0.0f };

physics_world_t* PhysicsWorld_Init() {
	physics_world_t* physics_world = malloc(sizeof(physics_world_t));
	if (!physics_world) return NULL;

	physics_world->bodies = malloc(sizeof(physics_body_t*));
	physics_world->bodies_count = 0;

	return physics_world;
}

void PhysicsWorld_Update(physics_world_t* pworld) {
	for (uint32_t i = 0; i < pworld->bodies_count; i++) {
		physics_body_t* body = pworld->bodies[i];
	}
}

void PhysicsWorld_AddBody(physics_world_t* pworld, physics_body_t* pbody) {
	physics_body_t** tmp = realloc(pworld->bodies, (pworld->bodies_count + 1) * sizeof(physics_body_t*));
	if (!tmp) return;

	pworld->bodies = tmp;
	pworld->bodies[pworld->bodies_count] = pbody;
	pworld->bodies_count++;
}
