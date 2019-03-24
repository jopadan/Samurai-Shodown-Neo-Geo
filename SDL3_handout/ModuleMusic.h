#ifndef __ModuleMusic_H__
#define __ModuleMusic_H__

#include "Module.h"
#include "Globals.h"


class ModuleMusic : public Module
{
public:

	ModuleMusic();
	~ModuleMusic();

	bool Init();
	update_status PostUpdate();
	update_status PreUpdate();
	bool CleanUp();
	
};
#endif