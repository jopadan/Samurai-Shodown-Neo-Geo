#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 9

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleSceneHaohmaru;
class ModuleSceneNakoruru;
class ModuleMenu;
class Module;

class Application
{
public:

	Module * modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneHaohmaru* scene_haohmaru;
	ModuleSceneNakoruru* scene_nakoruru;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleMenu* menu;


public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__