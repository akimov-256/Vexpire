#include "../include/player.h"

static Uint64 lastTime = 0;

Player player = {{200, 200, 64, 64}};

// Player movement properties
float speed = 300.0f;

static void Quit() {

}

static void HandleEvents(SDL_Event* event) {

}

static void Update() {
	// Calculate delta time
	Uint64 now = SDL_GetTicks();
	float deltaTime = (now - lastTime) / 1000.0f;
	if (deltaTime > 0.1f) deltaTime = 0.1f;						// clamp to avoid spikes from stalls/drags
	lastTime = now;

	// Get the keyboard status
	const _Bool *keyboardState = SDL_GetKeyboardState(NULL);

	player.animator.current->movement = IDLE;

	float newX = player.dst.x;
	float newY = player.dst.y;

	if (keyboardState[SDL_SCANCODE_W])
	{
		newY -= speed * deltaTime;
		player.animator.current->direction = UP;
		player.animator.current->movement = WALKING;
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		newY += speed * deltaTime;
		player.animator.current->direction = DOWN;
		player.animator.current->movement = WALKING;
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
		newX -= speed * deltaTime;
		player.animator.current->direction = LEFT;
		player.animator.current->movement = WALKING;
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		newX += speed * deltaTime;
		player.animator.current->direction = RIGHT;
		player.animator.current->movement = WALKING;
	}

	// Handle camera movement when player is near the edges of the screen
	if (newX < 150)
		player.camera->x -= speed * deltaTime;
	else if (newX > player.camera->width - 150 - player.dst.w)
		player.camera->x += speed * deltaTime;
	else if (CanMoveTo(player.map, newX + player.camera->x, player.dst.y + player.camera->y, player.dst.w, player.dst.h)) 
		player.dst.x = newX;

	if (newY < 150)
		player.camera->y -= speed * deltaTime;
	else if (newY > player.camera->height - 150 - player.dst.h)
		player.camera->y += speed * deltaTime;
	else if (CanMoveTo(player.map, player.dst.x + player.camera->x, newY + player.camera->y, player.dst.w, player.dst.h))
		player.dst.y = newY;
	
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

	SDL_RenderTexture(renderer, player.texture,
						&src, &player.dst);
}

Entity InitPlayer(SDL_Renderer* renderer, cute_tiled_map_t* map, Camera* camera) {
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

	// Initialize the map
	player.map = map;
	if (player.map == NULL) {
		SDL_Log("Error initializing player map: Map pointer is NULL.");
		return (Entity) { 0 };
	}

	// Initialize the camera
	player.camera = camera;
	if (player.camera == NULL) {
		SDL_Log("Error initializing player camera: Camera pointer is NULL.");
		return (Entity) { 0 };
	}

	Entity player = { Quit, HandleEvents, Update, Render };
	return player;
}