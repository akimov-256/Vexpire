#define CUTE_TILED_IMPLEMENTATION
#include "../include/cute_tiled.h"

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

void RenderMap(cute_tiled_map_t* map, SDL_Renderer* renderer, SDL_Texture* texture) {
	if (!map || !renderer || !texture) {									// Validate input parameters
		return;
	}

	cute_tiled_layer_t* layers = map->layers;								// Extract the layers from the map

	if (layers == NULL) {													// Skip maps without layers
		SDL_Log("No layers to render in the map.");
		return;
	}

	for (cute_tiled_layer_t* layer = layers; layer != NULL; layer = layer->next) {
		for (int i = 0; i < layer->width; i++) {
			for (int j = 0; j < layer->height; j++) {
				int index = j * layer->width + i;							// Calculate the index in the data array

				int gid = layer->data[index];								// Get the GID for the current tile

				if (gid == 0)
					continue;												// Skip empty tiles

				int localId = gid - map->tilesets->firstgid;				// Calculate the local tile ID within the tileset

				// Calculate the row and column of the tile in the tileset
				int column = localId % map->tilesets->columns;
				int row = localId / map->tilesets->columns;

				SDL_FRect srcRect = {										// Source rectangle for the tile in the tileset
					.x = column * map->tilesets->tilewidth,
					.y = row * map->tilesets->tileheight,
					.h = map->tilesets->tileheight,
					.w = map->tilesets->tilewidth
				};

				SDL_FRect destRect = {										// Destination rectangle on the screen
					.x = i * map->tilewidth,
					.y = j * map->tileheight,
					.h = map->tileheight,
					.w = map->tilewidth
				};

				SDL_RenderTexture(renderer, texture, &srcRect, &destRect);	// Render the tile to the screen
			}
		}
	}
}