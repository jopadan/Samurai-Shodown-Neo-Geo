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
	iPoint position;
	bool lowAnim = false;
	SDL_Rect health;
	SDL_Rect health2;
	SDL_Rect lowHealth;
	SDL_Rect lowHealth2;
	SDL_Rect healthCont;
	SDL_Rect healthCont2;
	SDL_Rect ko;

};

#endif // !__ModuleUI_H__