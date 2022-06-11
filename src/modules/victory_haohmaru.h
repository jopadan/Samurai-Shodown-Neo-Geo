#ifndef __victory_haohmaru_H__
#define __victory_haohmaru_H__

#include "module.h"
#include "anim.h"
#include "globals.h"
#include "music.h"


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
