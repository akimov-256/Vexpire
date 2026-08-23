#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "entities.h"
#include "animation.h"
#include "camera.h"
#include "map.h"


typedef struct {
	// Player position
	SDL_FRect dst;

	// Player texture
	SDL_Texture* texture;

	// Player animation
	Animator animator;

	// Player camera
	Camera* camera;

	// Player map
	cute_tiled_map_t* map;
} Player;

Entity InitPlayer(SDL_Renderer* renderer, cute_tiled_map_t* map, Camera* camera);