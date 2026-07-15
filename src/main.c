#include "../include/main.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* playerTexture;
SDL_FRect playerSrc = {
	.x = 18,
	.y = 16,
	.w = 13,
	.h = 16
};
SDL_FRect playerDst = {
	.x = 20,
	.y = 20,
	.w = 26,
	.h = 32
};

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}

void Render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderTexture(renderer, playerTexture, &playerSrc, &playerDst);
	SDL_RenderPresent(renderer);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	Render();

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
	// Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Error initializing SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// Create window
	window = SDL_CreateWindow("Vexpire", 800, 600, NULL);
	if (!window) {
		SDL_Log("Error creating window: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_Log("Error creating renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// Load player texture
	const char path[] = "assets/Char_Sprites/char_spritesheet.png";
	playerTexture = IMG_LoadTexture(renderer, path);
	if (!playerTexture) {
		SDL_Log("Error loading player texture: %s", SDL_GetError());
	}
	SDL_SetTextureScaleMode(playerTexture, SDL_SCALEMODE_NEAREST);

	// Initialization successful
	return SDL_APP_CONTINUE;
}
