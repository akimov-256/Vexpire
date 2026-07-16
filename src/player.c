#include "../include/player.h"

static float lastTime = 0;

typedef struct {
	// Player position
	SDL_FRect dst;

	// Player texture
	SDL_Texture* texture;

	// Player animation
	Animator animator;
} Player;

Player player = {{20, 20, 32, 32}};

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
	{
		player.dst.y -= speed * deltaTime;
		player.animator.current->direction = UP;
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		player.dst.y += speed * deltaTime;
		player.animator.current->direction = DOWN;
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
		player.dst.x -= speed * deltaTime;
		player.animator.current->direction = LEFT;
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		player.dst.x += speed * deltaTime;
		player.animator.current->direction = RIGHT;
	}

	// Handle Animation
	AnimatorUpdate(&player.animator, deltaTime);
}

static void Render(SDL_Renderer* renderer) {
	if (player.animator.current == NULL)
		return;

	if (player.texture == NULL)
		return;

	int frame = GetCurrentFrame(&player.animator);

	SDL_FRect src =
	{
		(float)(player.animator.current->startFrame + frame * 16),
		(float)(player.animator.current->direction * 16),
		16,
		16
	};

	SDL_RenderTexture(renderer,
		player.texture,
		&src,
		&player.dst);
}

Entity InitPlayer(SDL_Renderer* renderer) {
	// Load player texture
	const char path[] = "assets/Char_Sprites/char_spritesheet.png";
	player.texture = IMG_LoadTexture(renderer, path);
	if (!player.texture) {
		SDL_Log("Error loading player texture: %s", SDL_GetError());
		return (Entity) { 0 };
	}
	SDL_SetTextureScaleMode(player.texture, SDL_SCALEMODE_NEAREST);

	// Initialize the animator
	static Animation idleDown =
	{
		.direction = DOWN,
		.startFrame = 128,
		.frameCount = 6,
		.frameDuration = 0.2f,
		.loop = true
	};

	AnimatorInit(&player.animator);

	AnimationPlay(&player.animator, &idleDown);

	Entity player = { Quit, HandleEvents, Update, Render };
	return player;
}