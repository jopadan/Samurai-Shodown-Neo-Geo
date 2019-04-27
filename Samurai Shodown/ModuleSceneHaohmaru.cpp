#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNakoruru.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneHaohmaru.h"
#include "ModuleMusic.h"
#include "ModuleMenu.h"
#include "ModuleVictoryHaohmaru.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleEnding.h"

#include<stdio.h>


ModuleSceneHaohmaru::ModuleSceneHaohmaru()
{

	// splash animation

	splash1.PushBack({ 0, 0, 0, 0 }, 0.01, 0, 0, 0, 0);
	splash1.PushBack({ 0, 465, 50, 105 }, 0.2, 39, 0, 0, 0);
	splash1.PushBack({ 261, 465, 95, 105 }, 0.2, 17, 0, 0, 0);
	splash1.PushBack({ 376, 465, 116, 105 }, 0.2, 6, 0, 0, 0);
	splash1.PushBack({ 531, 465, 128, 105 }, 0.2, 0, 0, 0, 0);
	splash1.PushBack({ 698, 465, 119, 105 }, 0.2, 5, 0, 0, 0);
	splash1.PushBack({ 836, 465, 129, 105 }, 0.2, 0, 0, 0, 0);
	splash1.PushBack({ 1023, 465, 126, 105 }, 0.2, 1, 0, 0, 0);

	splash2.PushBack({ 0, 0, 0, 0 }, 0.007, 0, 0, 0, 0);
	splash2.PushBack({ 0, 465, 50, 105 }, 0.2, 39, 0, 0, 0);
	splash2.PushBack({ 261, 465, 95, 105 }, 0.2, 17, 0, 0, 0);
	splash2.PushBack({ 376, 465, 116, 105 }, 0.2, 6, 0, 0, 0);
	splash2.PushBack({ 531, 465, 128, 105 }, 0.2, 0, 0, 0, 0);
	splash2.PushBack({ 698, 465, 119, 105 }, 0.2, 5, 0, 0, 0);
	splash2.PushBack({ 836, 465, 129, 105 }, 0.2, 0, 0, 0, 0);
	splash2.PushBack({ 1023, 465, 126, 105 }, 0.2, 1, 0, 0, 0);

	splash3.PushBack({ 0, 0, 0, 0 }, 0.005, 0, 0, 0, 0);
	splash3.PushBack({ 0, 465, 50, 105 }, 0.2, 39, 0, 0, 0);
	splash3.PushBack({ 261, 465, 95, 105 }, 0.2, 17, 0, 0, 0);
	splash3.PushBack({ 376, 465, 116, 105 }, 0.2, 6, 0, 0, 0);
	splash3.PushBack({ 531, 465, 128, 105 }, 0.2, 0, 0, 0, 0);
	splash3.PushBack({ 698, 465, 119, 105 }, 0.2, 5, 0, 0, 0);
	splash3.PushBack({ 836, 465, 129, 105 }, 0.2, 0, 0, 0, 0);
	splash3.PushBack({ 1023, 465, 126, 105 }, 0.2, 1, 0, 0, 0);

	// ground
	ground.x = 0;
	ground.y = 575;
	ground.w = 640;
	ground.h = 416;

	 //sea animation
	sea.PushBack({ 0, 0, 640, 140 }, 0.08f, 0, 0, 0, 0);
	sea.PushBack({ 704, 4, 640, 140 }, 0.08f, 0, 0, 0, 0);
	sea.PushBack({ 1408, 4, 640, 140 }, 0.08f, 0, 0, 0, 0);
	sea.PushBack({ 0, 156, 640, 140 }, 0.08f, 0, 0, 0, 0);
	sea.PushBack({ 704, 156, 640, 140 }, 0.08f, 0, 0, 0, 0);
	sea.PushBack({ 1408, 156, 640, 140 }, 0.08f, 0, 0, 0, 0);
	sea.PushBack({ 0, 312, 640, 140 }, 0.08f, 0, 0, 0, 0);
	sea.PushBack({ 704, 311, 640, 140 }, 0.08f, 0, 0, 0, 0);
	sea.PushBack({ 1408, 311, 640, 140 }, 0.08f, 0, 0, 0, 0);
	
}

ModuleSceneHaohmaru::~ModuleSceneHaohmaru()
{}

// Load assets
bool ModuleSceneHaohmaru::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	App->player->deletecol = true;
	App->player2->deletecol = true;
	
	starttime = SDL_GetTicks();
	rounds1 = App->ui->roundsp1;
	rounds2 = App->ui->roundsp2;
	timer = 99;
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	App->collision->Enable();

	musload = App->music->LoadMus("Assets/Sound/Masculine Song -Sun- (Haohmaru).ogg");
	graphics = App->textures->Load("Assets/Image/haohmaru_stage.png");
	font_timer = App->fonts->Load("Ui/UI_Numbers_1.png", "9876543210", 1);
	App->music->PlayMus(musload);
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();
	App->ui->Enable();


	// COLLIDERS PARA LOS LIMITES DEL MAPA
	colliderMap = App->collision->AddCollider({ -55, -150, 50, 500  }, COLLIDER_WALL);
	colliderMap2 = App->collision->AddCollider({ 635, -150, 50, 500 }, COLLIDER_WALL);
	return ret;
}

bool ModuleSceneHaohmaru::CleanUp()
{
	LOG("Unloading Haohmaru scene");
	matchstart = false;
	
	if (colliderMap != nullptr) {
		colliderMap->to_delete = true;
	}
	if (colliderMap2 != nullptr) {
		colliderMap2->to_delete = true;
	}
	App->player->deletecol = true;
	App->player2->deletecol = true;
	App->music->UnloadMus(musload);
	App->textures->Unload(graphics);
	App->player->Disable();
	App->player2->Disable();
	App->fonts->UnLoad(font_timer);
	App->ui->Disable();


	return true;
}

// Update: draw background
update_status ModuleSceneHaohmaru::Update()
{
	if(matchstart == false){
	if (SDL_GetTicks() - starttime >= 4000) {
		 matchstart = true;
		 App->input->playerinput = true;
		 timertime = SDL_GetTicks();
	}
	else{ timertime = SDL_GetTicks(); }}
	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, 0, -150, &ground, SDL_FLIP_NONE);

	App->render->Blit(graphics, 0, 53, &(sea.GetCurrentFrame()), SDL_FLIP_NONE, 1);

	App->render->Blit(graphics, 80 + splash1.pivotx[splash1.returnCurrentFrame()], 75 + splash1.pivoty[splash1.returnCurrentFrame()], &(splash1.GetCurrentFrame()), SDL_FLIP_NONE, 1); // splash
	
	App->render->Blit(graphics, 210 + splash2.pivotx[splash2.returnCurrentFrame()], 75 + splash2.pivoty[splash2.returnCurrentFrame()], &(splash2.GetCurrentFrame()), SDL_FLIP_NONE, 1); // splash

	App->render->Blit(graphics, 365 + splash3.pivotx[splash3.returnCurrentFrame()], 40 + splash3.pivoty[splash3.returnCurrentFrame()], &(splash3.GetCurrentFrame()), SDL_FLIP_NONE, 1); // splash
	
	//background
	if (timer == 0) {
		if (App->ui->Health_Bar_p2 < App->ui->HealthBar_p1)App->ui->Health_Bar_p2 = 0;
		else App->ui->HealthBar_p1 = 0;
	}
	if (App->ui->Health_Bar_p2 <=0) {
		if(rounds1 == App->ui->roundsp1)App->ui->roundsp1++;
		if (App->ui->roundsp1 == 3) {
			App->input->playerinput = false;
			if (endingtimer ==0)endingtimer = SDL_GetTicks();
			if (SDL_GetTicks() - endingtimer >= 3000)App->fade->FadeToBlack(App->scene_haohmaru, App->winhaoh, 2);
		}

		else { 
			App->input->playerinput = false;
			if (endingtimer == 0)endingtimer = SDL_GetTicks();
			if (SDL_GetTicks() - endingtimer >= 3000)App->fade->FadeToBlack(App->scene_haohmaru, App->scene_haohmaru, 1);
		}
	}
	if (App->ui->HealthBar_p1 <= 0) {
		if (rounds2 == App->ui->roundsp2)App->ui->roundsp2++;
		if (App->ui->roundsp2 == 3) {
			App->input->playerinput = false;
			if (endingtimer == 0)endingtimer = SDL_GetTicks();
			if (SDL_GetTicks() - endingtimer >= 3000)App->fade->FadeToBlack(App->scene_haohmaru, App->end, 2);
		}
		
		else { 
			App->input->playerinput = false;
			if (endingtimer == 0)endingtimer = SDL_GetTicks();
			if (SDL_GetTicks() - endingtimer >= 3000)App->fade->FadeToBlack(App->scene_haohmaru, App->scene_haohmaru, 1);
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_F2] == 1) {
		App->ui->Health_Bar_p2=0;
	}
	if (App->input->keyboard[SDL_SCANCODE_F3] == 1) {
		App->ui->HealthBar_p1=0;
	}


	if (SDL_GetTicks() - timertime >= 1000) {
		timertime = SDL_GetTicks();
		timer--;
	}
	sprintf_s(timer_text, 10, "%d", timer);

	App->fonts->BlitText(SCREEN_WIDTH/2-15 - App->render->camera.x / 3, 33 - App->render->camera.y / 3, font_timer, timer_text);
	return UPDATE_CONTINUE;
}