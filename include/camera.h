#pragma once

typedef struct {							// Camera structure
	int x;
	int y;

	int width;
	int height;

} Camera;

void Camera_Init(Camera* camera,			// Initialize the camera with position and size
					int x, int y,
					int width, int height); 