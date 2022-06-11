#include "app.h"
#include "modules/window.h"
#include "modules/render.h"
#include "modules/input.h"
#include "modules/textures.h"
#include "modules/scene_haohmaru.h"
#include "modules/scene_nakoruru.h"
#include "modules/player.h"
#include "modules/player2.h"
#include "modules/pet_p1.h"
#include "modules/pet_p2.h"
#include "modules/fade_to_black.h"
#include "modules/menu.h"
#include "modules/ending.h"
#include "modules/music.h"
#include "modules/victory_haohmaru.h"
#include "modules/particles.h"
#include "modules/collision.h"
#include "modules/fonts.h"
#include "modules/ui.h"
#include "modules/slowdown.h"
#include "modules/referee.h"
#include "modules/select.h"

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
	player->Disable();
	player2->Disable();
	scene_haohmaru->Disable();
	scene_nakoruru->Disable();
	winhaoh->Disable();
	collision->Disable();
	ui->Disable();
	end->Disable();
	particles->Disable();
	select->Disable();
	pet->Disable();
	pet2->Disable();
	referee->Disable();

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
