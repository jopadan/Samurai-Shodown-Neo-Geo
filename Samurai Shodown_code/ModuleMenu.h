#ifndef __ModuleMenu_H__
#define __ModuleMenu_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"


struct SDL_Texture;

class ModuleMenu : public Module
{
public:
	ModuleMenu();
	~ModuleMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Mix_Music* musload;
	Mix_Chunk* chunkload;
	SDL_Rect menu;
    Animation title;
	Animation start;
	uint timertime;
	uint timer;

};

#endif