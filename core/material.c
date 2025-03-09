#include "material.h"
#include "camera.h"
#include "world.h"
#include "malloc.h"
#include "glad/glad.h"

material_t* Material_Create(shader_t* shader) {
	material_t* material = malloc(sizeof(material_t));
	if (!material) return NULL;

	if (shader) material->shader = shader;
	glm_vec4_fill(material->base_color, 1.f);
	material->main_texture = Texture_Create();
	material->specular = 1.f;
	material->specular_texture = Texture_Create();

	return material;
}

void Material_BindLights(material_t* material) {
	env_t* environment = World_GetEnvironment();

	int ambient_color_loc = Shader_GetUniformLocation(material->shader, "uAmbientColor");
	Shader_SetUniform4f(material->shader, ambient_color_loc, environment->ambient_color);

	int ambient_strength_loc = Shader_GetUniformLocation(material->shader, "uAmbientStrength");
	Shader_SetUniformf(material->shader, ambient_strength_loc, environment->ambient_strength);

	dirlight_t* world_dirlight = World_GetDirectionalLight();
	if (world_dirlight) {
		int dirlight_color_loc = Shader_GetUniformLocation(material->shader, "uDirectionalLightColor");
		Shader_SetUniform4f(material->shader, dirlight_color_loc, world_dirlight->light_color);

		int dirlight_strength_loc = Shader_GetUniformLocation(material->shader, "uDirectionalLightStrength");
		Shader_SetUniformf(material->shader, dirlight_strength_loc, world_dirlight->light_strength);
		
		int dirlight_position_loc = Shader_GetUniformLocation(material->shader, "uDirectionalLightPosition");
		Shader_SetUniform3f(material->shader, dirlight_position_loc, world_dirlight->position);
	}
}

void Material_Bind(material_t* material, mat4 model) {
	if (material->shader) Shader_Bind(material->shader);

	int base_color_loc = Shader_GetUniformLocation(material->shader, "uMaterial.base_color");
	Shader_SetUniform4f(material->shader, base_color_loc, material->base_color);

	bool lights_enabled = World_IsLightsEnabled(); 

	Shader_SetUniformi(material->shader, Shader_GetUniformLocation(material->shader, "uLightsEnabled"), lights_enabled);
	Material_BindLights(material);

	glActiveTexture(GL_TEXTURE0);
	Texture_Bind(material->main_texture);
	if (material->main_texture) {
		int location = Shader_GetUniformLocation(material->shader, "uMaterial.main_texture");
		Shader_SetUniformi(material->shader, location, 0);
	}

	int specular_loc = Shader_GetUniformLocation(material->shader, "uMaterial.specular");
	Shader_SetUniformf(material->shader, specular_loc, material->specular);

	glActiveTexture(GL_TEXTURE1);
	Texture_Bind(material->specular_texture);
	if (material->specular_texture) {
		int location = Shader_GetUniformLocation(material->shader, "uMaterial.specular_texture");
		Shader_SetUniformi(material->shader, location, 1);
	}

	camera_t* camera = World_GetCamera();
	if (camera && camera->enabled && material->shader) {
		mat4 proj;
		Camera_GetProjectionMatrix(camera, proj);
		Shader_SetUniformMatrix4f(material->shader, Shader_GetUniformLocation(material->shader, "uProj"), proj);

		mat4 view;
		Camera_GetViewMatrix(camera, view);
		Shader_SetUniformMatrix4f(material->shader, Shader_GetUniformLocation(material->shader, "uView"), view);

		Shader_SetUniform3f(material->shader, Shader_GetUniformLocation(material->shader, "uViewPosition"), camera->position);

		Shader_SetUniformMatrix4f(material->shader, Shader_GetUniformLocation(material->shader, "uModel"), model);
	}
}

void Material_Unbind() {
	Shader_Unbind();
	Texture_Unbind();
}