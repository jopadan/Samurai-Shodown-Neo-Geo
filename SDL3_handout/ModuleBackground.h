#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Globals.h"

class ModuleBackground : public Module
{
public:

	ModuleBackground();
	~ModuleBackground();

	bool Init() { return true; }
	update_status Update();
	bool CleanUp() { return true; }
};

#endif // __ModuleInput_H__