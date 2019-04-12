#ifndef __ModuleInputPlayer_H__
#define __ModuleInputPlayer_H__

#include "Module.h"
#include "Globals.h"
#include "p2Qeue.h"
#include "SDL\include\SDL_scancode.h"


class ModuleInputPlayer : public Module
{
public:

	ModuleInputPlayer();
	~ModuleInputPlayer();

	bool Init() {
		return true;
	}
	update_status PreUpdate();
//	void internal_input();

	bool CleanUp() { return true; }
	

public:
	bool left = false;
	bool right = false;
	bool down = false;
	bool up = false;


};

#endif