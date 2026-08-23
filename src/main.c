#include "../include/main.h"

#define QUIT_ENTITIES(entityCount, entities) \
	for (int i = 0; i < entityCount; i++) { \
		entities[i].Quit(); \
	}

#define UPDATE_ENTITIES(entityCount, entities) \
	for (int i = 0; i < entityCount; i++) { \
		entities[i].Update(); \
	}

#define HANDLE_ENTITIES_EVENTS(entityCount, entities, event) \
	for (int i = 0; i < entityCount; i++) { \
		entities[i].HandleEvents(event); \
	}

#define RENDER_ENTITIES(entityCount, entities, renderer) \
	for (int i = 0; i < entityCount; i++) { \
		entities[i].Render(renderer); \
	}

// Declare window resolution properties
float w = 1280;
float h = 720;
float logicalW = 960;
float logicalH = 540;

// Declare state variables
SDL_Window* window;
SDL_Renderer* renderer;

// Declare entities list
Entity entities[MAX_ENTITIES_COUNT];
int entitiyCount = 0;

// Declare map variables
cute_tiled_map_t* map;
SDL_Texture* tilesetTexture;

// Declare camera
Camera camera;

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	QUIT_ENTITIES(entitiyCount, entities);
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

void Update() {
	UPDATE_ENTITIES(entitiyCount, entities);
}

void Render() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_SetTextureScaleMode(tilesetTexture, SDL_SCALEMODE_NEAREST);		// Set the texture scale mode to nearest
	RenderMap(map, renderer, tilesetTexture, &camera);							// Render the map

	RENDER_ENTITIES(entitiyCount, entities, renderer);					// Render entities after rendering the map

	SDL_RenderPresent(renderer);
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	Update();
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
	window = SDL_CreateWindow("Vexpire", w, h, SDL_WINDOW_RESIZABLE);
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

	// Set the logical resolution
	SDL_SetRenderLogicalPresentation(renderer, logicalW, logicalH, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	// Initialize camera
	Camera_Init(&camera, 0.0f, 0.0f, logicalW, logicalH);						// Initialize the camera with position and size

	// Load map
	tilesetTexture = IMG_LoadTexture(renderer, "assets/Overworld_Tileset.png");	// Load the tileset texture
	if (!tilesetTexture) {														// Check if the texture was loaded successfully
		SDL_Log("Error loading tileset texture: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	map = LoadMap("map/map.json");					// Load the map from the JSON file
	if (!map) {										// Check if the map was loaded successfully
		SDL_Log("Error loading map");
		return SDL_APP_FAILURE;
	}

	// Initialize entities
	entities[entitiyCount++] = InitPlayer(renderer, map, &camera);				// Initialize the player entity and add it to the entities list

	// Initialization successful
	return SDL_APP_CONTINUE;
}
