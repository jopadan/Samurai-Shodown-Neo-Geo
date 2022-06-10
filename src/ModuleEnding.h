#ifndef __ModuleEnding_H__
#define __ModuleEnding_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"


struct SDL_Texture;

class ModuleEnding : public Module
{
public:
	ModuleEnding();
	~ModuleEnding();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Mix_Music* musload;
	Mix_Chunk* chunkload;
	SDL_Rect end;
	SDL_Rect black;
	Animation flower;
	


};

#endif