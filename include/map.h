#pragma once

#include "cute_tiled.h"
#include "camera.h"

#include <SDL3/SDL.h>

cute_tiled_map_t* LoadMap(const char* path);
void DestroyMap(cute_tiled_map_t* map);
void RenderMap(cute_tiled_map_t* map, SDL_Renderer* renderer,
				SDL_Texture* texture, Camera* camera);

bool CanMoveTo(cute_tiled_map_t* map, float x, float y, float width, float height);			// Check if the player can move to the specified position (x, y) based on the map's collision layer
cute_tiled_tile_descriptor_t* GetTileByLocalId(						// Get the tile descriptor for a given local tile ID within the tileset)
					cute_tiled_tileset_t* tileset, int localId);	
cute_tiled_layer_t* GetLayerByName(cute_tiled_map_t* map, const char* name);	// Get the layer by its name from the map