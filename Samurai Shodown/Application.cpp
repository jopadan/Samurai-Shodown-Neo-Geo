#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleInputPlayer.h"
#include "ModuleTextures.h"
#include "ModuleSceneHaohmaru.h"
#include "ModuleSceneNakoruru.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "ModuleMusic.h"
#include "ModuleVictoryHaohmaru.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"


Application::Application()
{
	
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = input_player = new ModuleInputPlayer();
	modules[4] = textures = new ModuleTextures();
	modules[5] = scene_nakoruru = new ModuleSceneNakoruru();
	modules[6] = scene_haohmaru = new ModuleSceneHaohmaru();
	modules[8] = player = new ModulePlayer();
	modules[7] = player2 = new ModulePlayer2();
	modules[9] = menu = new ModuleMenu();
	modules[10] = winhaoh = new ModuleVictoryHaohmaru();
	modules[11] = particles = new ModuleParticles();
	modules[12] = collision = new ModuleCollision();
	modules[13] = music = new ModuleMusic();
	modules[14] = fade = new ModuleFadeToBlack();
	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;
	input_player->Disable();
	player->Disable();
	player2->Disable();
	scene_nakoruru->Disable();
	scene_haohmaru->Disable();
	winhaoh->Disable();
	collision->Disable();


	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}