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

public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	player_states process_fsm(p2Qeue<player_inputs>& inputs);
	void OnCollision(Collider* c1, Collider* c2);

public:

	Uint32 speed = 2;
	Uint32 combo1 = 0;
	Uint32 combo2 = 0;
	Uint32 combo3 = 0;
	Uint32 jumptimer = 0;
	Uint32 HawkCarryCombo = 0;
	Uint32 jumptohawktimer = 0;
	Uint32 combotime;
	Uint32 combotimeAnnu;
	Uint32 combotimeAmube;
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
	Animation jumpPunchHeavy;
	Animation jumpFrontPunchHeavy;
	Animation jumpKick;
	Animation jumpKickHeavy;
	Animation jumpFrontKickHeavy;
	Animation punch;
	Animation mediumpunch;
	Animation heavypunch;
	Animation crouch;
	Animation crouchPunch;
	Animation crouchHeavyPunch;
	Animation crouchKick;
	Animation crouchHeavyKick;
	Animation intro;
	Animation kick;
	Animation mediumkick;
	Animation heavykick;
	Animation hit;
	Animation shadow;
	Animation cyclone;
	Animation tornado;
	Animation block;
	Animation win;
	Animation defeat;
	Animation hawk_carry;
	Animation kamui;
	Animation yatoro;
	Animation Annu;
	Animation amube;
	iPoint position;
	Uint32 Damage = 20;
	bool deletecol = true;
	bool defense = false;
	bool playsound = true;
	bool OnHawk = false;
	bool jumptoHawk = true;
	bool jumpattack = false;
	bool jumpattackheavy = false;
	bool hawkleft = false;
	bool hawkright = false;
	bool hawkdown = false;
	bool hawkup = false;
	float mutsubespeed = 10;
	bool amubeyatoro = true;
	float acc = 0.01;
	int height = 0;
	int height2 = 0;
	bool dontflip = false;
	int jumpanim = 0;
	int Heavytimer = 0;
	int heavytimerstart = 0;
	Collider *colliderPlayer2; 
	Collider *colliderPlayer2_2;
	Collider *colliderAttack;
	Uint32 time = 0;
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
	bool wall = false;
};
#endif