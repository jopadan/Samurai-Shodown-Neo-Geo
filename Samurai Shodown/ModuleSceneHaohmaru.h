#ifndef __ModuleSceneHaohmaru_H__
#define __ModuleSceneHaohmaru_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMusic.h"

struct SDL_Texture;
struct Collider;

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
	
	char timer_text[10];
	int font_timer = -1;
	uint timer;
	uint endingtimer=0;
	int starttime;
	int timertime;
	Collider* colliderMap;
	Collider* colliderMap2;
	Animation splash1;
	Animation splash2;
	Animation splash3;
	Animation sea;
	uint rounds1;
	uint rounds2;
	bool matchstart=false;
	
};

#endif