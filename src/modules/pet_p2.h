#ifndef __ModulePetP2_H__
#define __ModulePetP2_H__


#include "module.h"
#include "anim.h"
#include "globals.h"
#include "p2point.h"

class ModulePetp2 : public Module
{
public:
	ModulePetp2();
	~ModulePetp2();

	bool Start();
	update_status Update();
	bool CleanUp();
public:
	int speedx = 0;
	int speedy = 0;
	bool yatoro = false;
	bool collider = true;
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation move;
	Animation amube;
	Collider *colliderAttack;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	iPoint position;
};


#endif
