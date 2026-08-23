#pragma once

typedef struct {							// Camera structure
	float x;
	float y;

	float width;
	float height;

} Camera;

void Camera_Init(Camera* camera,			// Initialize the camera with position and size
					float x, float y,
					float width, float height); 