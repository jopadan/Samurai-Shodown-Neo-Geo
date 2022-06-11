#ifndef __ModuleEnding_H__
#define __ModuleEnding_H__

#include "module.h"
#include "anim.h"
#include "globals.h"
#include "music.h"


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
