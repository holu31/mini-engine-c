#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "cglm/cglm.h"
#include "shader.h"
#include "texture.h"

typedef struct {
	shader_t* shader;
	vec4 base_color;
	texture_t* main_texture;
	float specular;
	texture_t* specular_texture;
} material_t;

material_t* Material_Create(shader_t* shader);
void Material_Bind(material_t* material, mat4 model);
void Material_Unbind();

#endif // _MATERIAL_H_