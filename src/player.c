#include "../include/player.h"

static SDL_Texture* playerTexture;
static SDL_FRect playerSrc = {
	.x = 18,
	.y = 16,
	.w = 13,
	.h = 16
};
static float lastTime = 0;

typedef struct {
	float x;
	float y;
} Position;

Position playerPosition = {20, 20};

// Player movement properties
float speed = 300.0f;

static void Quit() {

}

static void HandleEvents(SDL_Event* event) {

}

static void Update() {
	// Calculate delta time
	float now = SDL_GetTicks();
	float deltaTime = (now - lastTime) / 1000;
	lastTime = now;

	// Get the keyboard status
	const _Bool *keyboardState = SDL_GetKeyboardState(NULL);

	if (keyboardState[SDL_SCANCODE_W])
		playerPosition.y -= speed * deltaTime;
	if (keyboardState[SDL_SCANCODE_S])
		playerPosition.y += speed * deltaTime;
	if (keyboardState[SDL_SCANCODE_A])
		playerPosition.x -= speed * deltaTime;
	if (keyboardState[SDL_SCANCODE_D])
		playerPosition.x += speed * deltaTime;
}

static void Render(SDL_Renderer* renderer) {
	SDL_FRect playerDst = {
		.x = playerPosition.x,
		.y = playerPosition.y,
		.w = 26,
		.h = 32
	};
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