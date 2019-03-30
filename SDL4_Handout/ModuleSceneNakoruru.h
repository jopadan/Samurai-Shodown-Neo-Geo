#ifndef __ModuleSceneNakoruru_H__
#define __ModuleSceneNakoruru_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneNakoruru : public Module
{
public:
	ModuleSceneNakoruru();
	~ModuleSceneNakoruru();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;

	Animation animals;
	

};
#endif

