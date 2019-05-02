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
	bool tornadoAnim;
	int initialPos;
	float jumpSpeed = 6;
	int animstart=0;
	bool shoot = true;
	bool collider = true;
	int pos;


	
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
	Uint32 combo1 = 0;
	Uint32 combotime;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphicsobj = nullptr;
	Animation* current_animation = nullptr;
	Mix_Chunk* senpuu;
	Mix_Chunk* sword;
	Mix_Chunk* kicks;
	Mix_Chunk* hitted;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jumpup;
	Animation jumpPunch;
	Animation punch;
	Animation crouch;
	Animation crouchPunch;
	Animation crouchKick;
	Animation intro;
	Animation kick;
	Animation hit;
	Animation shadow;
	Animation cyclone;
	Animation block;
	Animation win;
	Animation defeat;
	iPoint position;
	Uint32 Damage = 20;
	bool deletecol = true;
	bool defense = false;
	bool playsound = true;
	int height = 0;
	int height2 = 0;
	Collider *colliderPlayer;
	Collider *colliderPlayer_2;
	Collider *colliderAttack;
	Uint32 time = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	bool wall = false;
};

#endif// __ModulePlayer_H__