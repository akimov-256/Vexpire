#include "../include/animation.h"

void AnimatorInit(Animator* animator) {
	animator->current = NULL;
	animator->frame = 0;
	animator->timer = 0.0f;
}

void AnimationPlay(Animator* animator, const Animation* animation) {
	if (animator->current == animation)
		return;

	animator->current = animation;
	animator->frame = 0;
	animator->timer = 0.0f;
}

void AnimatorUpdate(Animator* animator, float deltaTime)
{
    if (animator->current == NULL)
        return;

    animator->timer += deltaTime;

    if (animator->timer >= animator->current->frameDuration)
    {
        animator->timer -= animator->current->frameDuration;

        animator->frame++;

        if (animator->frame >= animator->current->frameCount)
        {
            if (animator->current->loop)
                animator->frame = 0;
            else
                animator->frame = animator->current->frameCount - 1;
        }
    }
}

int GetCurrentFrame(Animator* animator) {
	if (animator->current == NULL)
		return 0;

	return animator->frame;
}