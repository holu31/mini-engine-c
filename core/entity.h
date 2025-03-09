#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "cglm/cglm.h"
#include "mesh.h"
#include "material.h"
#include "physics_body.h"

#include "stdint.h"

typedef struct entity_t entity_t;

typedef struct entity_t {
	char* entity_name;
	char* global_name;
	material_t* material;
	mesh_t* mesh;
	physics_body_t* body;
	vec3 position;
	vec3 scale;
	vec3 rotation;
	void (*spawn)(entity_t* ent);
	void (*update)(entity_t* ent);
	void* data;
} entity_t;

typedef struct {
	entity_t* (*create)();
} entity_factory_t;

entity_t* Entity_Create();
void Entity_Spawn(entity_t* ent);
void Entity_Update(entity_t* ent);

#endif // _ENTITY_H_