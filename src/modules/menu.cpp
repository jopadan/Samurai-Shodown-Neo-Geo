#include "globals.h"
#include "app.h"
#include "scene_nakoruru.h"
#include "textures.h"
#include "render.h"
#include "music.h"
#include "input.h"
#include "fade_to_black.h"
#include "menu.h"
#include "SDL.h"
#include "scene_haohmaru.h"
#include "player.h"
#include "player2.h"
#include "ui.h"




ModuleMenu::ModuleMenu()
{
	menu.x = 0;
	menu.y = 444;
	menu.w = 303;
	menu.h = 223;

	title.PushBack({ 0, 0, 303, 117 }, 0.005, 0, 0, 0, 0);
	title.PushBack({ 349, 0, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 698, 0, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1046, 0, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1395, 0, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1744, 0, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 0, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 349, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 698, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1046, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1395, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1743, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 0, 296, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 349, 296, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 698, 296, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1046, 296, 303, 117 }, 0.2, 0, 0, 0, 0);

	start.PushBack({ 1395, 296, 120, 14 }, 0.04f,0,0, 0, 0);
	start.PushBack({ 1395, 340, 120, 14 }, 0.025f, 0, 0, 0, 0);
}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading menu assets");
	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	timertime = SDL_GetTicks();
	musload = App->music->LoadMus(DATADIR "Assets/Sound/Static and Dynamic (short).ogg");
	graphics = App->textures->Load(DATADIR "Assets/Image/Menu Spritesheet.png");
	App->music->Enable();
	App->music->PlayMus(musload);
	App->ui->roundsp1 = App->ui->roundsp2 = 0;
	
	return ret;
}

bool ModuleMenu::CleanUp()
{
	LOG("Unloading Menu scene");
	App->music->UnloadMus(musload);
	App->textures->Unload(graphics);
	App->music->Disable();
	return true;
}

// Update: draw background
update_status ModuleMenu::Update()
{

	if (SDL_GetTicks() - timertime >= 30000) {
		
		App->player->process_fsm(App->input->inputs);
		App->player2->process_fsm(App->input->inputs2);
	}
	if (SDL_GetTicks() - timertime >= 35000) {

		timertime = SDL_GetTicks();
	}


	App->render->Blit(graphics, 168, 0, &menu, SDL_FLIP_NONE);
	App->render->Blit(graphics, 168, 52, &(title.GetCurrentFrame()), SDL_FLIP_NONE, 1);
	App->render->Blit(graphics, 254, 172, &(start.GetCurrentFrame()), SDL_FLIP_NONE, 1);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_START) == 1 || SDL_GameControllerGetButton(App->input->gGameController2, SDL_CONTROLLER_BUTTON_START) == 1) {
		App->fade->FadeToBlack(App->menu, (Module*)App->select, 2);
	}

	return UPDATE_CONTINUE;
}
