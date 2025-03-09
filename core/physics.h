#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "physics_body.h"

typedef struct {
	physics_body_t** bodies;
	uint32_t bodies_count;
} physics_world_t;

physics_world_t* PhysicsWorld_Init();
void PhysicsWorld_Update(physics_world_t* pworld);
void PhysicsWorld_AddBody(physics_world_t* pworld, physics_body_t* pbody);

#endif _PHYSICS_H_