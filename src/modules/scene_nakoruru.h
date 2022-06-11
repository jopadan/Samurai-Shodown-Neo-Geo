#ifndef __ModuleSceneNakoruru_H__
#define __ModuleSceneNakoruru_H__

#include "module.h"
#include "anim.h"
#include "globals.h"
#include "music.h"


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

	Mix_Chunk* end;
	Mix_Chunk* starto;
	Mix_Chunk* ippon;
	Mix_Chunk* Round;

	char timer_text[10];
	int font_timer = -1;
	uint timer;
	uint endingtimer = 0;
	int starttime;
	int timertime;
	int startroundtime;
	int startroundtime2;
	uint rounds1;
	uint rounds2;
	bool matchstart = false;
	bool playfx = true;
	bool ret = true;
	bool onewins = false;
	bool twowins = false;

};
#endif

