#ifndef _WORLD_H_
#define _WORLD_H_

#include "entity.h"
#include "camera.h"
#include "env.h"
#include "dirlight.h"
#include "physics.h"

void World_Create();
void World_Update();

void World_AddEntity(entity_t* entity);
void World_AddEntityWithFactory(entity_factory_t* factory);

void World_SetCamera(camera_t* camera);
camera_t* World_GetCamera();

env_t* World_GetEnvironment();
void World_SetEnvironment(env_t* env);

void World_ToggleLight(bool enable);
bool World_IsLightsEnabled();

void World_SetDirectionalLight(dirlight_t* light);
dirlight_t* World_GetDirectionalLight();

physics_world_t* World_GetPhysicsWorld();

#endif // _WORLD_H_