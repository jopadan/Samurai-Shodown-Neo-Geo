#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneHaohmaru.h"
#include "ModuleSceneNakoruru.h"
#include "ModuleMusic.h"
#include "ModuleMenu.h"
#include "ModuleVictoryHaohmaru.h"
#include "ModuleMenu.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleEnding.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"

#include<stdio.h>

ModuleSceneNakoruru::ModuleSceneNakoruru()
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

}

ModuleSceneNakoruru::~ModuleSceneNakoruru()
{}

// Load assets
bool ModuleSceneNakoruru::Start()
{
	bool ret = true;
	endingtimer = 0;
	LOG("Loading background assets");
	musload = App->music->LoadMus("Assets/Sound/Banquet of Nature (Nakoruru).ogg");
	graphics = App->textures->Load("Assets/Image/Nakoruru Map Spritesheet.png");
	font_timer = App->fonts->Load("Ui/UI_Numbers_1.png", "9876543210", 1);
	App->player->deletecol = true;
	App->player2->deletecol = true;
	App->ui->roundstart = true;
	App->ui->matchend = false;
	App->ui->roundend = false;

	starttime = SDL_GetTicks();
	rounds1 = App->ui->roundsp1;
	rounds2 = App->ui->roundsp2;
	timer = 99;


	App->music->PlayMus(musload);
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();
	App->ui->Enable();
	App->particles->Enable();

	colliderMap = App->collision->AddCollider({ 0, -150, 50, 500 }, COLLIDER_WALL);
	colliderMap2 = App->collision->AddCollider({ 590, -150, 50, 500 }, COLLIDER_WALL);

	return ret;
	
}

bool ModuleSceneNakoruru::CleanUp()
{
	matchstart = false;
	LOG("Unloading nakoruru scene");
	if (colliderMap != nullptr) {
		colliderMap->to_delete = true;
	}
	if (colliderMap2 != nullptr) {
		colliderMap2->to_delete = true;
	}
	App->ui->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->player2->Disable();
	App->player->Disable();
	App->fonts->UnLoad(font_timer);
	App->textures->Unload(graphics);
	App->music->UnloadMus(musload);
	App->music->Disable();

	return true;
}
// Update: draw background
update_status ModuleSceneNakoruru::Update()
{
	if (matchstart == false) {
		if (SDL_GetTicks() - starttime >= 4500) {
			matchstart = true;
			App->ui->roundstart = false;
			App->input->playerinput = true;
			timertime = SDL_GetTicks();
		}
		else { timertime = SDL_GetTicks(); }
	}

	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, 0, -150, &ground, SDL_FLIP_NONE);

	App->render->Blit(graphics, 0, 7, &(animals.GetCurrentFrame()), SDL_FLIP_NONE, 1);
	
	//background

	/*if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_START) == 1) {
		App->fade->FadeToBlack(App->scene_nakoruru,(Module*)App->winhaoh, 2);
	}*/
	if (timer == 0) {
		if (App->ui->Health_Bar_p2 < App->ui->HealthBar_p1)App->ui->Health_Bar_p2 = 0;
		if (App->ui->Health_Bar_p2 > App->ui->HealthBar_p1)App->ui->HealthBar_p1 = 0;
	}

	if (App->input->keyboard[SDL_SCANCODE_F2] == 1 /*|| SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1*/) {
		App->ui->Health_Bar_p2 = 0;

	}

	if (App->input->keyboard[SDL_SCANCODE_F3] == 1 /*|| SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1*/) {
		App->ui->HealthBar_p1 = 0;


	}
	if (App->ui->Health_Bar_p2 <= 0) {
		App->input->inputs2.Push(IN_DEFEAT_P2);
		App->input->inputs.Push(IN_WIN);

		App->input->playerinput = false;
		App->ui->matchend = true;
		//if (playfx)App->music->PlayChunk(end); playfx = false;

		if (endingtimer == 0)endingtimer = SDL_GetTicks();
		if (SDL_GetTicks() - endingtimer >= 3000)App->fade->FadeToBlack(App->scene_nakoruru, App->winhaoh, 5);


	}
	if (App->ui->HealthBar_p1 <= 0) {
		App->input->inputs2.Push(IN_WIN_P2);
		App->input->inputs.Push(IN_DEFEAT);

		App->input->playerinput = false;
		App->ui->matchend = true;
		//if (playfx)App->music->PlayChunk(end); playfx = false;

		if (endingtimer == 0)endingtimer = SDL_GetTicks();
		if (SDL_GetTicks() - endingtimer >= 4000)App->fade->FadeToBlack(App->scene_nakoruru, App->end, 5);

	}
	if (SDL_GetTicks() - timertime >= 1000) {
		timertime = SDL_GetTicks();
		timer--;
	}
	sprintf_s(timer_text, 10, "%d", timer);

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 15 - App->render->camera.x, 33 - App->render->camera.y, font_timer, timer_text);
	return UPDATE_CONTINUE;
}