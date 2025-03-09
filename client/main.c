#include "engine.h"
#include "world.h"
#include "entity.h"
#include "shader.h"
#include "camera.h"
#include "assets.h"
#include "texture.h"
#include "dirlight.h"
#include "game_time.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct {
	int health;
	camera_t* camera;
} player_t;
#define PLAYER_ENTITY "player_entity"

static float vertices[] = {
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,

	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, -0.5f,

	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,

	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,

	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f
};

static int indices[] = {
	0, 1, 2,
	0, 2, 3,

	4, 5, 6,
	4, 6, 7,

	8, 9, 10,
	8, 10, 11,

	12, 13, 14,
	12, 14, 15,

	16, 17, 18,
	16, 18, 19,

	20, 21, 22,
	20, 22, 23
 };

static float uv[] = {
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
};

static float normals[] = {
	0.0f,  0.0f,  1.0f,
	0.0f,  0.0f,  1.0f,
	0.0f,  0.0f,  1.0f,
	0.0f,  0.0f,  1.0f,

	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,
	0.0f,  0.0f, -1.0f,

	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,
	-1.0f,  0.0f,  0.0f,

	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,
	1.0f,  0.0f,  0.0f,

	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f,
	0.0f,  1.0f,  0.0f,

	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f,
	0.0f, -1.0f,  0.0f
};

void Player_Spawn(entity_t* ent) {
	if (strcmp(ent->entity_name, PLAYER_ENTITY) != 0) return;
	player_t* player = (player_t*)ent->data;

	player->camera = Camera_Init();
	player->camera->position[2] = 2.f;
	World_SetCamera(player->camera);

	printf("player spawned with health %d\n", player->health);

	printf("position: x: %f, y: %f, z: %f\n", ent->position[0], ent->position[1], ent->position[2]);
}

void Player_Update(entity_t* ent) {
	ent->rotation[0] += 10.f * Time_GetDeltaTime();
	ent->rotation[1] += 10.f * Time_GetDeltaTime();
	ent->rotation[2] += 10.f * Time_GetDeltaTime();
}

entity_t* Player_Create() {
	player_t* player = malloc(sizeof(player_t));
	if (!player) return NULL;

	player->health = 100;

	entity_t* ent = Entity_Create();
	
	ent->entity_name = PLAYER_ENTITY;
	ent->spawn = &Player_Spawn;
	ent->update = &Player_Update;
	ent->data = player;

	asset_t* frag_shader = Asset_Get("content/gl_shaders/lit.frag");
	asset_t* vert_shader = Asset_Get("content/gl_shaders/lit.vert");

	ent->material->main_texture->min_filter = FILTER_NEAREST_TO_NEAREST;
	ent->material->main_texture->mag_filter = FILTER_NEAREST;
	Texture_Load(ent->material->main_texture, Asset_Get("content/container2.png"));

	ent->material->specular_texture->min_filter = FILTER_NEAREST_TO_NEAREST;
	ent->material->specular_texture->mag_filter = FILTER_NEAREST;
	Texture_Load(ent->material->specular_texture, Asset_Get("content/container2_specular.png"));

	ent->material->shader = Shader_Create(vert_shader->data, frag_shader->data);
	Mesh_SetBufferf(ent->mesh, 0, 3, sizeof(vertices), vertices);
	Mesh_SetBufferf(ent->mesh, 1, 2, sizeof(uv), uv);
	Mesh_SetBufferf(ent->mesh, 2, 3, sizeof(normals), normals);
	Mesh_SetIndicesData(ent->mesh, sizeof(indices), indices);

	return ent;
}
entity_factory_t player_entity = { Player_Create };

void Game_Init() {
	dirlight_t* dirlight = DirectionalLight_Init();
	dirlight->position[2] = 2.f;
	World_SetDirectionalLight(dirlight);

	World_AddEntityWithFactory(&player_entity);
}

scene_t Game = {
	.Init = Game_Init
};

int main() {
	Engine_Init();
	Engine_SetScene(&Game);
	Engine_Run();

	return 0;
}