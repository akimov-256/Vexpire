#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef enum {
	DOWN = 1,
	LEFT,
	RIGHT,
	UP
} Direction;

typedef struct {
	int startFrame;
	int frameCount;

	Direction direction;

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
