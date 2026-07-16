#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef enum {
	DOWN = 1,
	LEFT,
	RIGHT,
	UP
} Direction;

typedef enum {
	WALKING = 1,
	IDLE = 8
} Movement;

typedef struct {
	int frameCount;

	Direction direction;
	Movement movement;

	float frameDuration;
	bool loop;
} Animation;

typedef struct {
	Animation* current;


	int frame;
	float timer;
} Animator;

void AnimatorInit(Animator* animator);

void AnimationPlay(Animator* animator, const Animation* animation);

void AnimatorUpdate(Animator* animator, float deltaTime);

int GetCurrentFrame(Animator* animator);
