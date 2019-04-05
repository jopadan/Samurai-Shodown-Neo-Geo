#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleMusic.h"


struct SDL_Texture;

class ModulePlayer2 : public Module
{
private:
	int jump;
	bool floor = true;
	bool attAnim = false;
	bool kickAnim = false;
	bool cycloneAnim = false;
	int initialPos;
	float jumpSpeed = 6;
	int animstart = 0;
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Mix_Chunk* senpuu;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jumpup;
	Animation punch;
	Animation kick;
	Animation cyclone;
	iPoint position;
	SDL_Rect Hitbox2;
};
#endif