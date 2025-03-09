#include "shader.h"
#include "malloc.h"
#include "glad/glad.h"
#include "assert.h"
#include "stdlib.h"
#include "stdio.h"
#include "gl/gl.h"

int Shader_Compile(int type, char* source) {
	int shader = glCreateShader(type);
	if (shader == 0) return -1;

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		char* info_log = malloc(length * sizeof(char));
		glGetShaderInfoLog(shader, length, NULL, info_log);

		const char* typeText = (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";
		fprintf(stderr, "%s shader error: %s\n", typeText, info_log);
		free(info_log);
		exit(EXIT_FAILURE);
	}

	return shader;
}

shader_t* Shader_Create(char* vert_shader, char* frag_shader) {
	shader_t* shader = malloc(sizeof(shader_t));
	if (!shader) return NULL;

	int vert_handle = Shader_Compile(GL_VERTEX_SHADER, vert_shader);
	int frag_handle = Shader_Compile(GL_FRAGMENT_SHADER, frag_shader);

	shader->program = glCreateProgram();
	glAttachShader(shader->program, vert_handle);
	glAttachShader(shader->program, frag_handle);
	glLinkProgram(shader->program);

	int status;
	glGetProgramiv(shader->program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		int length;
		glGetProgramiv(shader->program, GL_INFO_LOG_LENGTH, &length);

		char* info_log = malloc(length * sizeof(char));
		glGetProgramInfoLog(shader->program, length, NULL, info_log);

		fprintf(stderr, "program failure link: %s\n", info_log);
		free(info_log);
		exit(EXIT_FAILURE);
	}

	return shader;

}

void Shader_Bind(shader_t* shader) {
	glUseProgram(shader->program);
}

void Shader_Unbind() {
	glUseProgram(0);
}

int Shader_GetUniformLocation(shader_t* shader, char* uniform) {
	int location = glGetUniformLocation(shader->program, uniform);

	return location;
}

void Shader_SetUniformi(shader_t* shader, int location, int value) {
	glUniform1i(location, value);
}

void Shader_SetUniformf(shader_t* shader, int location, float value) {
	glUniform1f(location, value);
}

void Shader_SetUniform3f(shader_t* shader, int location, vec3 value) {
	glUniform3f(location, value[0], value[1], value[2]);
}

void Shader_SetUniform4f(shader_t* shader, int location, vec4 value) {
	glUniform4f(location, value[0], value[1], value[2], value[3]);
}

void Shader_SetUniformMatrix4f(shader_t* shader, int location, mat4 value) {
	glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*) value);
}