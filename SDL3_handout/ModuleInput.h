#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"

typedef unsigned char Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool CleanUp();
	bool up, down, left, right;

public:
	const Uint8 *keyboard = nullptr;
};

#endif // __ModuleInput_H__