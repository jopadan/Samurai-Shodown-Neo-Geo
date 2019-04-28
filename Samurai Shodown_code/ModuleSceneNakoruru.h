#ifndef __ModuleSceneNakoruru_H__
#define __ModuleSceneNakoruru_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"


struct SDL_Texture;
struct Collider;

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
	Mix_Music* musload;
	Mix_Chunk* chunkload;
	SDL_Rect ground;
	Animation animals;
	Collider *colliderMap;
	Collider *colliderMap2;

};
#endif

