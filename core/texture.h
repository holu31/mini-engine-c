#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "assets.h"
#include "cglm/cglm.h"

typedef enum {
	FILTER_NEAREST = 9728,
	FILTER_LINEAR = 9729
} mag_filter_t;

typedef enum {
	FILTER_NEAREST_TO_NEAREST = 9984,
	FILTER_LINEAR_TO_NEAREST = 9985,
	FILTER_NEAREST_TO_LINEAR = 9986,
	FILTER_LINEAR_TO_LINEAR = 9987
} min_filter_t;

typedef struct {
	int id;
	unsigned char* data;
	mag_filter_t mag_filter;
	min_filter_t min_filter;
	ivec2 size;
} texture_t;

texture_t* Texture_Create();
void Texture_Load(texture_t* texture, asset_t* source);
void Texture_Apply(texture_t* texture);
void Texture_Bind(texture_t* texture);
void Texture_Unbind();

#endif // _TEXTURE_H_