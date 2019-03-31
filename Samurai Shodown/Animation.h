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

private:
	double current_frame;
	int last_frame = 0;
	int speeddelay = 0;
	bool animend = false;

public:

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
			current_frame = 0;
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

};

#endif