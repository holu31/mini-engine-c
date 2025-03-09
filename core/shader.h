#ifndef _SHADER_H_
#define _SHADER_H_

#include "cglm/cglm.h"

typedef struct {
	int program;
} shader_t;

shader_t* Shader_Create(char* vert_shader, char* frag_shader);
void Shader_Bind(shader_t* shader);
void Shader_Unbind();

int Shader_GetUniformLocation(shader_t* shader, char* uniform);

void Shader_SetUniformi(shader_t* shader, int location, int value);
void Shader_SetUniformf(shader_t* shader, int location, float value);
void Shader_SetUniform3f(shader_t* shader, int location, vec3 value);
void Shader_SetUniform4f(shader_t* shader, int location, vec4 value);
void Shader_SetUniformMatrix4f(shader_t* shader, int location, mat4 value);

#endif // _SHADER_H_