#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 19

class ModuleWindow;
class ModuleInput;
class ModuleInputPlayer;
class ModuleTextures;
class ModuleRender;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleSceneHaohmaru;
class ModuleSceneNakoruru;
class ModuleMenu;
class ModuleEnding;
class ModulePetp1;
class ModulePetp2;
class ModuleMusic;
class ModuleVictoryHaohmaru;
class ModuleParticles;
class ModuleCollision;
class Module;
class ModuleFonts;
class ModuleUI;

class Application
{
public:

	Module * modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleInputPlayer *input_player;
	ModuleTextures* textures;
	ModuleSceneHaohmaru* scene_haohmaru;
	ModuleSceneNakoruru* scene_nakoruru;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleMusic* music;
	ModuleMenu* menu;
	ModulePetp1* pet;
	ModulePetp2* pet2;
	ModuleEnding* end;
	ModuleVictoryHaohmaru* winhaoh;
	ModuleParticles* particles;
	ModuleFonts* fonts;
	ModuleUI* ui;

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