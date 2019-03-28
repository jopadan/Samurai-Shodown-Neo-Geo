#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();

public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;

	Animation splash1;
	Animation splash2;
	Animation splash3;
	Animation sea;

	/*float  bounce = -26;

	SDL_Rect ship;
	Animation sea;
	Animation girl;
	float  bounce = -26;

	float bouncespeed = 0;
	float cont = 0;
	*/
	 int cont[3];
	 void initializecount() {
		 cont[0] = 200;
		 cont[1] = 100;
		 cont[2] = 0;
	 }

};

#endif