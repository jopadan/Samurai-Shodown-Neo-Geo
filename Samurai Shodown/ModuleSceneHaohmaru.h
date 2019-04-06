#ifndef __ModuleSceneHaohmaru_H__
#define __ModuleSceneHaohmaru_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"

struct SDL_Texture;

class ModuleSceneHaohmaru : public Module
{
public:
	ModuleSceneHaohmaru();
	~ModuleSceneHaohmaru();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics = nullptr;
	Mix_Music* musload;
	Mix_Chunk* chunkload;
	SDL_Rect ground;

	Animation splash1;
	Animation splash2;
	Animation splash3;
	Animation sea;
};

#endif