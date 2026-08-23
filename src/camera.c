#include "../include/camera.h"

void Camera_Init(Camera* camera, float x, float y, float width, float height) {
	if (!camera) {								// Validate input parameters
		SDL_Log("Camera pointer is NULL.");
		return;
	}

	camera->x = x;								// Set the camera's position and size
	camera->y = y;
	camera->width = width;
	camera->height = height;
}