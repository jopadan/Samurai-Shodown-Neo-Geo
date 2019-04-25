#ifndef __ModuleInputPlayer_H__
#define __ModuleInputPlayer_H__

#include "Module.h"
#include "Globals.h"
#include "p2Qeue.h"
#include "SDL\include\SDL_scancode.h"


class ModuleInputPlayer : public Module
{
public:

	ModuleInputPlayer() {};
	~ModuleInputPlayer() {};

	bool Init() {
		return true;
	}
	update_status Update() {
		return UPDATE_CONTINUE;
	}

	

public:
	bool left = false;
	bool right = false;
	bool down = false;
	bool up = false;
	bool left2 = false;
	bool right2 = false;
	bool down2 = false;
	bool up2 = false;


};

#endif