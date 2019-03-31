#ifndef __ModuleVictoryHaohmaru_H__
#define __ModuleVictoryHaohmaru_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"


struct SDL_Texture;

class ModuleVictoryHaohmaru : public Module
{
public:
	ModuleVictoryHaohmaru();
	~ModuleVictoryHaohmaru();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Mix_Chunk* chunkload;
	SDL_Rect win;
	


};

#endif
