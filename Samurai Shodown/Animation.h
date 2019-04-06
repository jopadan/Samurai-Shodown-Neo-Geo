#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class Animation
{
public:
	double speed[MAX_FRAMES];
	SDL_Rect frames[MAX_FRAMES];
	int pivotx[MAX_FRAMES];
	int pivoty[MAX_FRAMES];
	bool loop = true;

private:
	double current_frame;
	bool animend = false;
	int last_frame = 0;
	int speeddelay = 0;
	int loops = 0;

public:

	Animation()
	{}
	/*
	Animation(const Animation& anim) : loop(anim.loop), speed(anim.), last_frame(anim.last_frame)
	{
		SDL_memcpy(&frames, anim.frames, sizeof(frames));
	}*/
	void PushBack(const SDL_Rect& rect, double delay, int px, int py)
	{	
		pivotx[last_frame] = px;
		pivoty[last_frame] = py;
		frames[last_frame++] = rect;
		speed[speeddelay++]= delay;

	}

	SDL_Rect& GetCurrentFrame()
	{	
		animend = false;
		speeddelay = 0;
		current_frame += speed[(int)current_frame];
		if(current_frame >= last_frame){
			animend = true;
			current_frame = (loop) ? 0.0f : last_frame - 1;
			loops;;
			speeddelay = 0;
		}

		return frames[(int)current_frame];
	}

	int returnCurrentFrame() {
		return (int)current_frame;
	}
	bool AnimationEnd() {
		return animend;
	}
	bool Finished() {
		return loops > 0;
	}
	void Reset() {
		current_frame = 0;
	}

};

#endif