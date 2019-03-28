#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class Animation
{
public:
	float speed[MAX_FRAMES];
	SDL_Rect frames[MAX_FRAMES];

private:
	float current_frame;
	int last_frame = 0;
	int speeddelay = 0;
	int j = 1;

public:

	void PushBack(const SDL_Rect& rect, float delay)
	{
		frames[last_frame++] = rect;
		
		speed[speeddelay++]= delay;
	}

	SDL_Rect& GetCurrentFrame()
	{
		speeddelay = 0;
		current_frame += speed[(int)current_frame];
		if(current_frame >= last_frame){
			current_frame = 0;
		 speeddelay = 0;
		}

		return frames[(int)current_frame];
	}
};

#endif