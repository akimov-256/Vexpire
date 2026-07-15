#pragma once

#include <SDL3/SDL.h>

typedef struct {
	void (*Quit)(void);
	void (*HandleEvents)(SDL_Event*);
	void (*Update)(void);
	void (*Render)(SDL_Renderer*);
} Entity;