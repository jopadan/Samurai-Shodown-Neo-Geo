#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleMusic.h"
#include "ModuleInput.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
private:
	int jump;
	int speed = 2;
	bool deletecol = true;
	bool floor = true;
	bool attAnim= false;
	bool kickAnim = false;
	bool cycloneAnim = false;
	bool tornadoAnim;
	int initialPos;
	float jumpSpeed = 6;
	int animstart=0;
	bool shoot = true;
	bool collider = true;
	bool wall = false;
//	int pivotey = 0, pivotex = 0;
	
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	player_states process_fsm(p2Qeue<player_inputs>& inputs);


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
	Animation tornado;
	iPoint position;

	Collider *colliderPlayer;
	Collider *colliderAttack;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

};

#endif