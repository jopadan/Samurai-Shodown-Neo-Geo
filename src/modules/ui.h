#ifndef __UI_H__
#define __UI_H__

#include "globals.h"
#include "module.h"
#include "anim.h"
#include "p2point.h"
#include "music.h"

#include "SDL.h"


class ModuleUI : public Module {
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();
	
public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation lowKo;
	Animation end;
	Animation pow;
	bool roundstart = true;
	bool roundend = false;
	bool matchend = false;
	//Animation lowHealth;
	bool lowAnim = false;
	Mix_Chunk* dama;
	SDL_Rect health;
	SDL_Rect health2;
	SDL_Rect Ippon;
	SDL_Rect Victory;
	SDL_Rect lowHealth;
	SDL_Rect lowHealth2;
	SDL_Rect healthCont;
	SDL_Rect healthCont1;
	SDL_Rect healthCont2;
	SDL_Rect pow1;
	SDL_Rect pow2;
	SDL_Rect pow3;
	SDL_Rect pow4;
	SDL_Rect victory;
	SDL_Rect nakoruru;
	SDL_Rect ko;
	SDL_Rect begin;
	SDL_Rect powCont;
	SDL_Rect powCont2;
	SDL_Rect powBar;
	SDL_Rect powBar2;
	SDL_Rect powBar3;
	SDL_Rect powBar4;
	SDL_Rect powBar5;
	SDL_Rect powBar_p2;
	SDL_Rect powBar2_p2;
	SDL_Rect powBar3_p2;
	SDL_Rect powBar4_p2;
	SDL_Rect powBar5_p2;
	SDL_Rect level4;
	Uint32 powTime;
	bool powtimer = false;
	bool powless = false;
	Uint32 powTime2;
	bool powtimer2 = false;
	bool powless2 = false;
	float powDamage;
	float powDamage2;
	int HealthBar_p1 = 128;
	int Health_Bar_p2 = 128;
	int damage_p1 = 0;
	int damage_p2 = 0;
	int roundsp1 = 0;
	int roundsp2 = 0;
};

#endif // !__UI_H__
