#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneHaohmaru.h"
#include "ModuleSceneNakoruru.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePetP1.h"
#include "ModulePetP2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "ModuleEnding.h"
#include "ModuleMusic.h"
#include "ModuleVictoryHaohmaru.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleSlowdown.h"
#include "ModuleReferee.h"
#include "ModuleSelect.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = fonts = new ModuleFonts();
	modules[i++] = scene_haohmaru = new ModuleSceneHaohmaru();
	modules[i++] = scene_nakoruru = new ModuleSceneNakoruru();
	modules[i++] = referee = new ModuleReferee();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = player2 = new ModulePlayer2();
	modules[i++] = pet = new ModulePetp1();
	modules[i++] = pet2 = new ModulePetp2();
	modules[i++] = menu = new ModuleMenu();
	modules[i++] = select = new ModuleSelect();
	modules[i++] = end = new ModuleEnding();
	modules[i++] = winhaoh = new ModuleVictoryHaohmaru();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = ui = new ModuleUI();
	modules[i++] = music = new ModuleMusic();
	modules[i++] = fade = new ModuleFadeToBlack();
	modules[i++] = slowdown = new ModuleSlowdown();

	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;
	LOG("player");
	player->Disable();
	player2->Disable();
	LOG("player2");
	scene_haohmaru->Disable();
	LOG("haohmaru");
	scene_nakoruru->Disable();
	LOG("nakoruru");
	winhaoh->Disable();
	LOG("winhaoh");
	collision->Disable();
	LOG("collision");
	ui->Disable();
	LOG("ui");
	end->Disable();
	LOG("end");
	particles->Disable();
	LOG("particales");
	select->Disable();
	LOG("select");
	pet->Disable();
	LOG("pet");
	pet2->Disable();
	LOG("pet2");
	referee->Disable();
	LOG("referee");
	

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
