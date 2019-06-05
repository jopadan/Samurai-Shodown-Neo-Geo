#ifndef __ModulePetP1_H__
#define __ModulePetP1_H__


#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePetp1 : public Module
{
public:
	ModulePetp1();
	~ModulePetp1();

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