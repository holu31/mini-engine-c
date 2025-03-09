#ifndef _ASSETS_H_
#define _ASSETS_H_

#include "stdint.h"

#define MAX_ASSET_NAME 64

typedef struct {
	char name[MAX_ASSET_NAME];
	char* data;
	size_t size;
} asset_t;

void Assets_Init();
asset_t* Asset_Load(const char* filename);
asset_t* Asset_Get(const char* filename);
void Assets_Free();

#endif // _ASSETS_H_