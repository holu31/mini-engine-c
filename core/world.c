#include "world.h"
#include "stdlib.h"

typedef struct {
	entity_t** entities;
	size_t count;
	camera_t* camera;
	env_t* env;
	dirlight_t* dirlight;
	bool lights_enabled;
	physics_world_t* physics_world;
} world_t;

static world_t* world = NULL;

void World_Create() {
	if (world != NULL) free(world);
	world = malloc(sizeof(world_t));

	if (world != NULL) {
		world->entities = malloc(sizeof(entity_t*));
		world->count = 0;
		world->camera = Camera_Init();
		world->env = Environment_Init();
		world->dirlight = NULL;
		world->lights_enabled = true;
		world->physics_world = PhysicsWorld_Init();
	}
}

void World_Update() {
	PhysicsWorld_Update(world->physics_world);

	for (int i = 0; i < world->count; i++) {
		entity_t* entity = world->entities[i];

		Entity_Update(entity);
	}
}

void World_AddEntity(entity_t* entity) {
	if (!entity) return;

	entity_t** new_entities = realloc(world->entities, (world->count + 1) * sizeof(entity_t*));
	if (new_entities != NULL) {
		world->entities = new_entities;
		world->entities[world->count] = entity;
		world->count++;

		Entity_Spawn(entity);
	}
}

void World_AddEntityWithFactory(entity_factory_t* factory) {
	entity_t* entity = factory->create();

	World_AddEntity(entity);
}

void World_SetCamera(camera_t* camera) {
	if (camera && world) {
		world->camera = camera;
	}
}

camera_t* World_GetCamera() {
	return world ? world->camera : NULL;
}

env_t* World_GetEnvironment() {
	return world->env;
}

void World_SetEnvironment(env_t* env) {
	if (env) world->env = env;
}

void World_ToggleLight(bool enable) {
	world->lights_enabled = enable;
}

bool World_IsLightsEnabled() {
	return world->lights_enabled;
}

void World_SetDirectionalLight(dirlight_t* light) {
	if (light) world->dirlight = light;
}

dirlight_t* World_GetDirectionalLight() {
	return world->dirlight;
}

physics_world_t* World_GetPhysicsWorld() {
	return world->physics_world;
}