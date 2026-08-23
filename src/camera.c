#include "../include/camera.h"

void Camera_Init(Camera* camera, int x, int y, int width, int height) {
	if (!camera) {								// Validate input parameters
		SDL_Log("Camera pointer is NULL.");
		return;
	}

	camera->x = x;								// Set the camera's position and size
	camera->y = y;
	camera->width = width;
	camera->height = height;
}