#include "assets.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

asset_t** asset_table;
uint32_t asset_count;

char* File_Load(const char* filename, size_t* size) {
	FILE* file = fopen(filename, "rb");
	if (!file) {
		fprintf(stderr, "failed to open asset: %s\n", filename);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	*size = ftell(file);
	rewind(file);

	char* buffer = malloc(*size * sizeof(char));
	if (!buffer) {
		fprintf(stderr, "memory alloc failed\n");
		fclose(file);
		return NULL;
	}
	if (fread(buffer, 1, *size, file) != *size) {
		fprintf(stderr, "Error reading file: %s\n", filename);
		free(buffer);
		fclose(file);
		return NULL;
	}

	buffer[*size] = '\0';
	fclose(file);
	return buffer;
}

void Assets_Init() {
	asset_table = NULL;
	asset_count = 0;
}

asset_t* Asset_Load(const char* filename) {
	size_t size;
	char* data = File_Load(filename, &size);
	if (!data) {
		printf("asset not found: %s\n", filename);
		return;
	}

	asset_t** tmp = realloc(asset_table, (asset_count + 1) * sizeof(asset_t*));
	if (!tmp) {
		printf("Memory allocation failed for asset table\n");
		return;
	}
	asset_table = tmp;

	asset_table[asset_count] = malloc(sizeof(asset_t));
	if (!asset_table[asset_count]) {
		printf("Memory allocation failed for asset\n");
		return;
	}

	strncpy(asset_table[asset_count]->name, filename, sizeof(asset_table[asset_count]->name) - 1);
	asset_table[asset_count]->name[sizeof(asset_table[asset_count]->name) - 1] = '\0';
	asset_table[asset_count]->data = data;
	asset_table[asset_count]->size = size;
	asset_count++;

	return asset_table[asset_count - 1];
}

asset_t* Asset_Get(const char* filename) {
	for (uint32_t i = 0; i < asset_count; i++) {
		if (strcmp(asset_table[i]->name, filename) == 0) {
			return asset_table[i];
		}
	}

	return Asset_Load(filename);
}

void Assets_Free() {
	for (uint32_t i = 0; i < asset_count; i++) {
		free(asset_table[i]);
	}
	free(asset_table);

	asset_table = NULL;
	asset_count = 0;
}
