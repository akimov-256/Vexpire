#define CUTE_TILED_IMPLEMENTATION
#include "cute_tiled.h"

#include "../include/map.h"

cute_tiled_map_t* LoadMap(const char* path) {
	cute_tiled_map_t* map = cute_tiled_load_map_from_file(path, NULL);

	if (!map) {
		SDL_Log("Failed to load map: %s", path);
		return NULL;
	}

	return map;
}

void DestroyMap(cute_tiled_map_t* map) {
	if (map) {
		cute_tiled_free_map(map);
	}
}