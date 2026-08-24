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

void RenderMap(cute_tiled_map_t* map, SDL_Renderer* renderer, SDL_Texture* texture, Camera* camera) {
	if (!map || !renderer || !texture || !camera) {							// Validate input parameters
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
					.x = i * map->tilewidth * 4 - camera->x,				// Use camera position to offset the tile rendering
					.y = j * map->tileheight * 4 - camera->y,				// Scale dest Rectangle by 4 to match player size
					.h = map->tileheight * 4,
					.w = map->tilewidth * 4
				};

				SDL_RenderTexture(renderer, texture, &srcRect, &destRect);	// Render the tile to the screen
			}
		}
	}
}

bool CanMoveTo(cute_tiled_map_t* map, float x, float y, float width, float height) {
	if (!map) {													// Validate input parameters
		SDL_Log("Map is NULL.");
		return false;
	}

	cute_tiled_layer_t* collisionLayer =						// Assuming the first layer is the collision layer
						GetLayerByName(map, "Contents");
	if (!collisionLayer) {
		SDL_Log("Collision layer is NULL.");
		return false;
	}

	// Check all four corners of the player's bounding box
	float corners[4][2] = {											// Make player bounding box smaller for more accurate collision detection
		{ x	+ width / 4	  , y + height / 2	},	// top-left
		{ x + width * 3/4 , y + height / 2	},	// top-right
		{ x	+ width / 4	  , y + height - 1	},	// bottom-left
		{ x + width * 3/4 , y + height - 1  }   // bottom-right
	};

	for (int i = 0; i < 4; i++) {									// Loop through each corner of the bounding box

		int tileX = (int)(corners[i][0] / (map->tilewidth * 4));	// Extract x and y values from the corner
		int tileY = (int)(corners[i][1] / (map->tileheight * 4));	// Convert world coordinates to tile coordinates

		if (tileX < 0 || tileX >= collisionLayer->width ||
			tileY < 0 || tileY >= collisionLayer->height) {
			return false;											// Out of bounds, movement not allowed
		}

		int index = tileY * collisionLayer->width + tileX;			// Calculate the index in the data array
		int gid = collisionLayer->data[index];						// Get the GID for the current tile

		if (gid == 0) {
			continue;												// If GID is 0, the tile is empty and movement is allowed
		}

		int localId = gid - map->tilesets->firstgid;				// Calculate the local tile ID within the tileset

		cute_tiled_tile_descriptor_t* tile =						// Get the tile descriptor for the local ID
			GetTileByLocalId(map->tilesets, localId);

		if (!tile) {
			continue;												// If no tile descriptor is found, treat it as non solid
		}

		for (int i = 0; i < tile->property_count; i++) {			// Loop through the properties of the tile
			cute_tiled_property_t* property = &tile->properties[i];	// Get the current property

			if (strcmp(property->name.ptr, "Solid") == 0) {
				return !property->data.boolean;						// If the tile has a "Solid" property, return its value.
			}
		}
	}

	return true;													// No solid property found, movement is allowed
}

cute_tiled_tile_descriptor_t* GetTileByLocalId(cute_tiled_tileset_t* tilesets, int localId) {
	if (!tilesets) {											// Validate input parameters
		SDL_Log("Tileset is NULL.");
		return NULL;
	}
	
	cute_tiled_tile_descriptor_t* tile = tilesets->tiles;		// Start with the first tile descriptor
	while (tile) {												// Traverse the linked list of tile descriptors
		if (tile->tile_index == localId) {						// Check if the current tile's ID matches the local ID
			return tile;										// Return the matching tile descriptor
		}
		tile = tile->next;										// Move to the next tile descriptor
	}

	return NULL;												// Return NULL if no matching tile was found
}

cute_tiled_layer_t* GetLayerByName(cute_tiled_map_t* map, const char* name) {
	for (cute_tiled_layer_t* layer = map->layers; layer != NULL; layer = layer->next) {
		if (strcmp(layer->name.ptr, name) == 0) {
			return layer;										// Return the matching layer
		}
	}
	return NULL;
}