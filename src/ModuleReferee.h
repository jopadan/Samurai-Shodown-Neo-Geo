#ifndef __ModuleReferee_H__
#define __ModuleReferee_H__


#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModuleReferee : public Module
{
public:
	ModuleReferee();
	~ModuleReferee();

	bool Start();
	update_status Update();
	bool CleanUp();
public:
	int speedx = 0;
	int speedy = 0;
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	bool damage1 = false;
	bool damage2 = false;
	Animation idle;
	Animation moveleft;
	Animation moveright;
	Animation flag1;
	Animation flag2;
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
	int lastposition;
	iPoint position;
};

#endif