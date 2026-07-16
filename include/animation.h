#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	int row;
	int startFrame;
	int frameCount;

	float frameDuration;
	bool loop;
} Animation;

typedef struct {
	const Animation* current;

	int frame;
	float timer;
} Animator;

void AnimatorInit(Animator* animator);

void AnimationPlay(Animator* animator, const Animation* animation);

void AnimatorUpdate(Animator* animator, float deltaTime);

int GetCurrentFrame(Animator* animator);
