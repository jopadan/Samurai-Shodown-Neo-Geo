#ifndef __select_H__
#define __select_H__

#include "module.h"
#include "anim.h"
#include "globals.h"
#include "music.h"


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
	Mix_Chunk* select;
	Mix_Chunk* enter;

	SDL_Rect r;
	SDL_Rect name;
	Animation p2square;
	Animation p1square;
	Animation idle;
	iPoint position1;
	iPoint position2;
	Animation Attack;
	Animation* current_animation;
	bool up = true;
	bool down = true;
	bool right = true;
	bool left = true;
	bool up2 = true;
	bool down2 = true;
	bool right2 = true;
	bool left2 = true;
	bool ready1 = false;
	bool ready2 = false;
	Uint32 timertime;

};

#endif

