#include "mesh.h"
#include "stdlib.h"
#include "glad/glad.h"
#include "stdint.h"

mesh_t* Mesh_Init()
{
	mesh_t* mesh = malloc(sizeof(mesh_t));
	if (!mesh) return NULL;

	glGenVertexArrays(1, &mesh->vao);
	mesh->ebo_length = 0;
	mesh->draw_mode = DRAW_MODE_FILL;

	return mesh;
}

void Mesh_SetBufferf(mesh_t* mesh, int position, int size, size_t data_size, float data[]) {
	uint32_t buffer;
	glGenBuffers(1, &buffer);

	glBindVertexArray(mesh->vao);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, size, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glDeleteBuffers(1, &buffer);
}

void Mesh_SetBufferi(mesh_t* mesh, int position, int size, size_t data_size, int data[]) {
	uint32_t buffer;
	glGenBuffers(1, &buffer);

	glBindVertexArray(mesh->vao);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(position);
	glVertexAttribPointer(position, size, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glDeleteBuffers(1, &buffer);
}

void Mesh_SetIndicesData(mesh_t* mesh, size_t data_size, int data[]) {
	glGenBuffers(1, &mesh->ebo);
	mesh->ebo_length = data_size / sizeof(data[0]);

	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Mesh_Draw(mesh_t* mesh) {
	glPolygonMode(GL_FRONT_AND_BACK, mesh->draw_mode);
	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, mesh->ebo_length, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}