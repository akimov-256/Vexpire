#include "../include/player.h"

static SDL_Texture* playerTexture;
static SDL_FRect playerSrc = {
	.x = 18,
	.y = 16,
	.w = 13,
	.h = 16
};
static SDL_FRect playerDst = {
	.x = 20,
	.y = 20,
	.w = 26,
	.h = 32
};

static void Quit() {

}

static void HandleEvents(SDL_Event* event) {

}

static void Update() {

}

static void Render(SDL_Renderer* renderer) {
	SDL_RenderTexture(renderer, playerTexture, &playerSrc, &playerDst);
}

Entity InitPlayer(SDL_Renderer* renderer) {
	// Load player texture
	const char path[] = "assets/Char_Sprites/char_spritesheet.png";
	playerTexture = IMG_LoadTexture(renderer, path);
	if (!playerTexture) {
		SDL_Log("Error loading player texture: %s", SDL_GetError());
	}
	SDL_SetTextureScaleMode(playerTexture, SDL_SCALEMODE_NEAREST);
	Entity player = { Quit, HandleEvents, Update, Render };
	return player;
}