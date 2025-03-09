#ifndef _MESH_H_
#define _MESH_H_

#include "stddef.h"

typedef enum {
	DRAW_MODE_POINT = 6912,
	DRAW_MODE_LINE = 6913,
	DRAW_MODE_FILL = 6914,
} draw_mode_t;

typedef struct {
	int vao;
	int ebo;
	int ebo_length;
	draw_mode_t draw_mode;
} mesh_t;

mesh_t* Mesh_Init();

void Mesh_SetBufferf(mesh_t* mesh, int position, int size, size_t data_size, float data[]);
void Mesh_SetBufferi(mesh_t* mesh, int position, int size, size_t data_size, int data[]);
void Mesh_SetIndicesData(mesh_t* mesh, size_t data_size, int data[]);

void Mesh_Draw(mesh_t* mesh);

#endif // _MESH_H_