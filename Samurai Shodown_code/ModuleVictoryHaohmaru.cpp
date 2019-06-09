#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "ModuleVictoryHaohmaru.h"
#include "ModuleEnding.h"
#include "ModuleUI.h"


ModuleVictoryHaohmaru::ModuleVictoryHaohmaru()
{
	// ground
	ground.x = 702;
	ground.y = 705;
	ground.w = 640;
	ground.h = 416;

	//animals animation
	animals.PushBack({ 702, 0, 640, 208 }, 0.225f, 0, 0, 0, 0);
	animals.PushBack({ 1408, 0, 640, 208 }, 0.225f, 0, 0, 0, 0);
	animals.PushBack({ 0, 233, 640, 208 }, 0.225f, 0, 0, 0, 0);
	animals.PushBack({ 702, 233, 640, 208 }, 0.225f, 0, 0, 0, 0);
	animals.PushBack({ 1408, 233, 640, 208 }, 0.225f, 0, 0, 0, 0);
	animals.PushBack({ 0, 467, 640, 208 }, 0.225f, 0, 0, 0, 0);
	animals.PushBack({ 702, 467, 640, 208 }, 0.225f, 0, 0, 0, 0);
	animals.PushBack({ 1408, 467, 640, 208 }, 0.225f, 0, 0, 0, 0);
	
	win.x = 1407;
	win.y = 204;
	win.w = 309;
	win.h = 225;

	blackBands.x = 1407;
	blackBands.y = 703;
	blackBands.w = 306;
	blackBands.h = 225;

	speech.x = 1407;
	speech.y = 934;
	speech.w = 242;
	speech.h = 34;

	nakoruru.x = 327;
	nakoruru.y = 897;
	nakoruru.w = 208;
	nakoruru.h = 137;

	nakoruru2.x = 69;
	nakoruru2.y = 897;
	nakoruru2.w = 208;
	nakoruru2.h = 137;

	loser.PushBack({ 20, 774, 185, 83 }, 0.2, 0, 0, 0, 0);
	loser.PushBack({ 206, 771, 187, 86 }, 0.2, 0, 0, 0, 0);
	loser.PushBack({ 20, 774, 185, 83 }, 0.2, 0, 0, 0, 0);
	loser.PushBack({ 395, 777, 189, 80 }, 0.2, 0, 0, 0, 0);
}

ModuleVictoryHaohmaru::~ModuleVictoryHaohmaru()
{}

// Load assets
bool ModuleVictoryHaohmaru::Start()
{
	LOG("Loading win assets");
	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	musload = App->music->LoadMus("Assets/Sound/Conclusion (Winning Demo).ogg");
	graphics = App->textures->Load("Assets/Image/Nakoruru Map Spritesheet.png");
	App->music->PlayMus(musload);

	if (App->ui->roundsp1 >= 2) {
		positionNakoruru = 500;
		positionLoser = 100;
	}
	if (App->ui->roundsp2 >= 2) {
		positionNakoruru = -208;
		positionLoser = 400;
	}

	return ret;
}

bool ModuleVictoryHaohmaru::CleanUp()
{
	LOG("Unloading Menu scene");
	App->music->UnloadMus(musload);
	App->textures->Unload(graphics);
	
	return true;
}

// Update: draw background
update_status ModuleVictoryHaohmaru::Update()
{
	App->render->Blit(graphics, 0, -150, &ground, SDL_FLIP_NONE);

	App->render->Blit(graphics, 0, 7, &(animals.GetCurrentFrame()), SDL_FLIP_NONE, 1);
	
	if (App->ui->roundsp1 >= 2) {
		positionLoser += 3;
		App->render->Blit(graphics, positionLoser, 100, &(loser.GetCurrentFrame()), SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, 167, -1, &blackBands, SDL_FLIP_NONE);
		if (positionNakoruru >= 175) {
			positionNakoruru -= 5;
		}
		else {
			App->render->Blit(graphics, 205, 182, &speech, SDL_FLIP_NONE);
		}
		App->render->Blit(graphics, positionNakoruru, 56, &nakoruru, SDL_FLIP_NONE);
	}
	if (App->ui->roundsp2 >= 2) {
		positionLoser -= 3;
		App->render->Blit(graphics, positionLoser, 100, &(loser.GetCurrentFrame()), SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, 167, -1, &blackBands, SDL_FLIP_NONE);
		if (positionNakoruru <= 250) {
			positionNakoruru += 5;
		}
		else {
			App->render->Blit(graphics, 200, 182, &speech, SDL_FLIP_NONE);
		}
		App->render->Blit(graphics, positionNakoruru, 56, &nakoruru2, SDL_FLIP_NONE);
	}
	
	//App->render->Blit(graphics, 168, 0, &win, SDL_FLIP_NONE);
	
	//background

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_START) == 1 || SDL_GameControllerGetButton(App->input->gGameController2, SDL_CONTROLLER_BUTTON_START) == 1) {
		App->fade->FadeToBlack(App->winhaoh, App->menu, 2);
	}

	return UPDATE_CONTINUE;
}