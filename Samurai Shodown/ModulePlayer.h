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
	bool floor = true;
	bool attAnim= false;
	bool kickAnim = false;
	bool cycloneAnim = false;
	bool crouch = false;
	bool tornadoAnim;
	int initialPos;
	float jumpSpeed = 6;
	int animstart=0;
	bool shoot = true;
	bool collider = true;
	bool wall = false;

	
public:
	ModulePlayer();
	~ModulePlayer();

	
	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	player_states process_fsm(p2Qeue<player_inputs>& inputs);


public:
	Uint32 speed = 2;
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Mix_Chunk* senpuu;
	Mix_Chunk* sword;
	Mix_Chunk* kicks;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jumpup;
	Animation punch;
	Animation crounch;
	Animation kick;
	Animation hit;
	Animation cyclone;
	Animation tornado;
	iPoint position;
	Uint32 Damage = 20;
	bool deletecol = true;
	Collider *colliderPlayer;
	Collider *colliderAttack;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

};

#endif