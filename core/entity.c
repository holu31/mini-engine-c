#include "entity.h"
#include "world.h"
#include "stdlib.h"

entity_t* Entity_Create() {
	entity_t* entity = malloc(sizeof(entity_t));
	if (!entity) return NULL;

	glm_vec3_zero(entity->position);
	glm_vec3_one(entity->scale);
	glm_vec3_zero(entity->rotation);

	entity->entity_name = "";
	entity->global_name = "";
	entity->mesh = Mesh_Init();
	entity->body = PhysicsBody_Init();
	entity->material = Material_Create(NULL);

	entity->spawn = (void*)NULL;
	entity->update = (void*)NULL;

	return entity;
}

void Entity_Spawn(entity_t* ent) {
	physics_world_t* physics_world = World_GetPhysicsWorld();

	if (ent != NULL && ent->spawn) {
		PhysicsWorld_AddBody(physics_world, ent->body);
		ent->spawn(ent);
	}
}

void Entity_GetModelMatrix(entity_t* ent, mat4 mat)
{
	glm_mat4_identity(mat);

	vec3 rotation_rad;
	glm_vec3_scale(ent->rotation, -1.0f, rotation_rad);
	rotation_rad[0] = glm_rad(rotation_rad[0]);
	rotation_rad[1] = glm_rad(rotation_rad[1]);
	rotation_rad[2] = glm_rad(rotation_rad[2]);

	glm_rotate_x(mat, rotation_rad[0], mat);
	glm_rotate_y(mat, rotation_rad[1], mat);
	glm_rotate_z(mat, rotation_rad[2], mat);

	glm_translate(mat, ent->position);

	glm_scale(mat, ent->scale);
}

#include "glad/glad.h"

void Entity_Update(entity_t* ent) {	
	camera_t* camera = World_GetCamera();

	mat4 model;
	Entity_GetModelMatrix(ent, model);

	if (ent->material->shader) Material_Bind(ent->material, model);
	Mesh_Draw(ent->mesh);
	Material_Unbind();

	if (ent != NULL && ent->update) {
		glm_vec3_copy(ent->body->position, ent->position);
		ent->update(ent);
	}
}