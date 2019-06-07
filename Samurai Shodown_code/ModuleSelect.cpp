#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNakoruru.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include "ModuleUI.h"
#include "ModuleSelect.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"

ModuleSelect::ModuleSelect()
{
	r.x = 10;
	r.y = 1460;
	r.w = 303;
	r.h = 223;

	

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

	start.PushBack({ 1395, 296, 120, 14 }, 0.04f, 0, 0, 0, 0);
	start.PushBack({ 1395, 340, 120, 14 }, 0.025f, 0, 0, 0, 0);
}

ModuleSelect::~ModuleSelect()
{}

// Load assets
bool ModuleSelect::Start()
{
	LOG("Loading menu assets");
	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	musload = App->music->LoadMus("Assets/Sound/Static and Dynamic (short).ogg");
	graphics = App->textures->Load("Assets/Image/Nakoruru spritesheet.png");
	player1 = App->textures->Load("Assets/Image/Nakoruru spritesheet.png");
	player2 = App->textures->Load("Assets/Image/Nakoruru spritesheet p2.png");

	App->music->Enable();
	App->music->PlayMus(musload);
	App->ui->roundsp1 = App->ui->roundsp2 = 0;

	return ret;
}

bool ModuleSelect::CleanUp()
{
	LOG("Unloading Menu scene");
	App->music->UnloadMus(musload);
	App->textures->Unload(graphics);
	App->music->Disable();
	return true;
}

// Update: draw background
update_status ModuleSelect::Update()
{

	if (SDL_GetTicks() - timertime >= 30000) {

		App->player->process_fsm(App->input->inputs);
		App->player2->process_fsm(App->input->inputs2);
	}
	if (SDL_GetTicks() - timertime >= 35000) {

		timertime = SDL_GetTicks();
	}


	App->render->Blit(graphics, 0, 0, &r, SDL_FLIP_NONE);
	//App->render->Blit(graphics, 168, 52, &(title.GetCurrentFrame()), SDL_FLIP_NONE, 1);
	//App->render->Blit(graphics, 254, 172, &(start.GetCurrentFrame()), SDL_FLIP_NONE, 1);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_START) == 1) {
		App->fade->FadeToBlack(App->select, (Module*)App->scene_nakoruru, 2);
	}

	return UPDATE_CONTINUE;
}