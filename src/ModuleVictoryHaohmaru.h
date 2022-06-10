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
	Mix_Music* musload;
	SDL_Rect win;
	SDL_Rect blackBands;
	SDL_Rect speech;
	SDL_Rect nakoruru;
	SDL_Rect nakoruru2;
	Animation loser;
	SDL_Rect ground;
	Animation animals;
	int positionNakoruru;
	int positionLoser;
	

};

#endif
