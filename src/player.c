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

Player player = {{20, 20, 64, 64}};

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

	player.animator.current->movement = IDLE;

	if (keyboardState[SDL_SCANCODE_W])
	{
		player.dst.y -= speed * deltaTime;
		player.animator.current->direction = UP;
		player.animator.current->movement = WALKING;
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		player.dst.y += speed * deltaTime;
		player.animator.current->direction = DOWN;
		player.animator.current->movement = WALKING;
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
		player.dst.x -= speed * deltaTime;
		player.animator.current->direction = LEFT;
		player.animator.current->movement = WALKING;
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		player.dst.x += speed * deltaTime;
		player.animator.current->direction = RIGHT;
		player.animator.current->movement = WALKING;
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
		(float)((player.animator.current->movement + frame) * 16),
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
		.movement = IDLE,
		.frameCount = 6,
		.frameDuration = 0.2f,
		.loop = true
	};

	AnimatorInit(&player.animator);

	AnimationPlay(&player.animator, &idleDown);

	Entity player = { Quit, HandleEvents, Update, Render };
	return player;
}