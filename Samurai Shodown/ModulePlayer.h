#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleMusic.h"


struct SDL_Texture;

class ModulePlayer : public Module
{
private:
	int jump;
	bool floor = true;
	bool attAnim= false;
	bool kickAnim = false;
	int initialPos;
	float jumpSpeed = 6;
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Mix_Chunk* chunkload;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jumpup;
	Animation punch;
	Animation kick;
	iPoint position;

};

#endif