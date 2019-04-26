#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

#include "SDL/include/SDL.h"


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
	//Animation lowHealth;
	bool lowAnim = false;
	SDL_Rect health;
	SDL_Rect health2;
	SDL_Rect lowHealth;
	SDL_Rect lowHealth2;
	SDL_Rect healthCont;
	SDL_Rect healthCont1;
	SDL_Rect healthCont2;
	SDL_Rect ko;
	int HealthBar_p1 = 128;
	int Health_Bar_p2 = 128;
};

#endif // !__ModuleUI_H__