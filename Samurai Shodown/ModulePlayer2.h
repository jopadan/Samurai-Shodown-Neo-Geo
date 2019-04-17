#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleMusic.h"
#include "Globals.h"
#include "ModuleInput.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer2 : public Module
{
private:
	int jump;
	int speed = 2;
	bool deletecol = true;
	bool floor = true;
	bool attAnim = false;
	bool kickAnim = false;
	bool cycloneAnim = false;
	bool tornadoAnim;
	int initialPos;
	float jumpSpeed = 6;
	int animstart = 0;
	bool shoot = true;
	bool collider = true;
	bool wall = false;
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	player_states process_fsm(p2Qeue<player_inputs>& inputs);
	void OnCollision(Collider* c1, Collider* c2);

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
	Collider *colliderPlayer2; 
	Collider *colliderAttack;
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
};
#endif