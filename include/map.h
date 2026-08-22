#pragma once

#include "cute_tiled.h"

cute_tiled_map_t* LoadMap(const char* path);
void DestroyMap(cute_tiled_map_t* map);