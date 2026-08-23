#pragma once

#include "cute_tiled.h"

#include <SDL3/SDL.h>

cute_tiled_map_t* LoadMap(const char* path);
void DestroyMap(cute_tiled_map_t* map);
void RenderMap(cute_tiled_map_t* map, SDL_Renderer* renderer, SDL_Texture* texture);