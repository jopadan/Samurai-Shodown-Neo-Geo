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
#include "ModuleReferee.h"
#include "ModulePetP1.h"
#include "ModulePetP2.h"

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
	end = App->music->LoadChunk("Assets/Sound/Referee/Samurai Shodown - Referee - end.wav");
	ippon = App->music->LoadChunk("Assets/Sound/Referee/Samurai Shodown - Referee - ippon.wav");
	starto = App->music->LoadChunk("Assets/Sound/Referee/Samurai Shodown - Referee - Start.wav");
	Round = App->music->LoadChunk("Assets/Sound/Referee/Samurai Shodown - Referee - Round.wav");
	
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
	App->referee->Enable();
	App->pet->Enable();
	App->pet2->Enable();
	App->music->PlayChunk(starto);
	colliderMap = App->collision->AddCollider({ 0, -150, 50, 500 }, COLLIDER_WALL);
	colliderMap2 = App->collision->AddCollider({ 590, -150, 50, 500 }, COLLIDER_WALL);
	App->ui->Health_Bar_p2 = 128;
	App->ui->HealthBar_p1 = 128;
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
	App->input->playerinput = false;
	App->ui->Disable();
	App->particles->Disable();
	App->collision->Disable();
	App->player2->Disable();
	App->player->Disable();
	App->fonts->UnLoad(font_timer);
	App->textures->Unload(graphics);
	App->music->UnloadMus(musload);
	App->music->Disable();
	App->referee->Disable();
	App->pet->Disable();
	App->pet2->Disable();

	return true;
}
// Update: draw background
update_status ModuleSceneNakoruru::Update()
{
	if (matchstart == false) {
		App->input->playerinput = false;
		if (SDL_GetTicks() - starttime >= 4500) {
			matchstart = true;
			App->ui->roundstart = false;
			App->input->playerinput = true;
			timertime = SDL_GetTicks();
		}
		else { timertime = SDL_GetTicks(); }
	}

	if (App->ui->roundend == true) {
		if (SDL_GetTicks() - startroundtime >= 4500) {
			App->music->PlayChunk(Round);
			App->ui->roundend = false;
			App->player->position.x = 208;
			App->player->position.y = 207;
			App->player2->position.x = 372;
			App->player2->position.y = 207;
			App->ui->Health_Bar_p2 = 128;
			App->ui->HealthBar_p1 = 128;
			App->ui->roundstart = true;
			timer = 99;
			if (twowins == true) {
				App->input->inputs2.Push(IN_WIN_FINISH_P2);
				App->input->inputs.Push(IN_DEFEAT_FINISH);
				twowins = false;
			}
			if (onewins == true) {
				App->input->inputs.Push(IN_WIN_FINISH);
				App->input->inputs2.Push(IN_DEFEAT_FINISH_P2);
				onewins = false;
			}
			
		}
			else { timertime = SDL_GetTicks(); }
		
	}
	if(App->ui->roundsp2 > 0 || App->ui->roundsp1 > 0){

	if (SDL_GetTicks() - startroundtime >= 6000) {
		


		App->input->playerinput = true;
		App->ui->roundstart = false;
		
		

	}
}
	if (App->ui->matchend == true  && SDL_GetTicks() - endingtimer > 4000)App->fade->FadeToBlack(App->scene_nakoruru, App->winhaoh, 5);


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
	
		if (App->ui->roundsp1 == 1 && App->ui->roundend != true && App->ui->matchend == false) {
			App->ui->roundsp1 = 2;
			App->input->inputs2.Push(IN_DEFEAT_P2);
			App->input->inputs.Push(IN_WIN);

			App->input->playerinput = false;
			App->ui->matchend = true;
			App->music->PlayChunk(end);

		 endingtimer = SDL_GetTicks(); 
			
		}
		
		if (App->ui->roundsp1 == 0) {
			App->music->PlayChunk(ippon);
			App->input->inputs2.Push(IN_DEFEAT_P2);
			App->input->inputs.Push(IN_WIN);
			App->input->playerinput = false;
			App->ui->roundend = true;
			startroundtime = SDL_GetTicks();
			onewins = true;
			App->ui->roundsp1 = 1;
		
			
		}


	}
	if (App->ui->HealthBar_p1 <= 0) {

		if (App->ui->roundsp2 == 1 && App->ui->roundend != true && App->ui->matchend == false){
			App->ui->roundsp2 = 2;
			App->input->inputs2.Push(IN_WIN_P2);
			App->input->inputs.Push(IN_DEFEAT);

			App->input->playerinput = false;
			App->ui->matchend = true;
			App->music->PlayChunk(end);

		endingtimer = SDL_GetTicks();
		}
	

		if (App->ui->roundsp2 == 0) {
			App->music->PlayChunk(ippon);
			App->ui->roundsp2 = 1;
			twowins = true;
			App->input->inputs2.Push(IN_WIN_P2);
			App->input->inputs.Push(IN_DEFEAT);
			App->input->playerinput = false;
			App->ui->roundend = true;
			
		
			startroundtime = SDL_GetTicks();
		}
	}
	if (SDL_GetTicks() - timertime >= 1000) {
		timertime = SDL_GetTicks();
		timer--;
	}
	sprintf_s(timer_text, 10, "%d", timer);

	App->fonts->BlitText(SCREEN_WIDTH / 2 - 15 - App->render->camera.x, 33 - App->render->camera.y, font_timer, timer_text);
	return UPDATE_CONTINUE;
}