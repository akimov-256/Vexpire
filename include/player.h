#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "entities.h"
#include "animation.h"
#include "camera.h"


typedef struct {
	// Player position
	SDL_FRect dst;

	// Player texture
	SDL_Texture* texture;

	// Player animation
	Animator animator;

	// Player camera
	Camera* camera;
} Player;

Entity InitPlayer(SDL_Renderer* renderer, Camera* camera);