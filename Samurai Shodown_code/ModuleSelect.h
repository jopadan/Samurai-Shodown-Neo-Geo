#ifndef __ModuleSelect_H__
#define __ModuleSelect_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"


struct SDL_Texture;

class ModuleSelect : public Module
{
public:
	ModuleSelect();
	~ModuleSelect();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* player1 = nullptr;
	SDL_Texture* player2 = nullptr;
	Mix_Music* musload;
	Mix_Chunk* chunkload;
	SDL_Rect r;
	Animation title;
	Animation start;
	Uint32 timertime;

};

#endif

