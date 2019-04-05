#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 13

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleSceneHaohmaru;
class ModuleSceneNakoruru;
class ModuleMenu;
class ModuleMusic;
class ModuleVictoryHaohmaru;
class ModuleParticles;
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
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleMusic* music;
	ModuleMenu* menu;
	ModuleVictoryHaohmaru* winhaoh;
	ModuleParticles* particles;


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