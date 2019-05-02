#include "Application.h"
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
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleEnding.h"
#include "ModuleParticles.h"

#include<stdio.h>


ModuleSceneHaohmaru::ModuleSceneHaohmaru()
{

	// splash animation

	
}

ModuleSceneHaohmaru::~ModuleSceneHaohmaru()
{}

// Load assets
bool ModuleSceneHaohmaru::Start()
{
	
	LOG("Loading background assets");
    ret = true;
	playfx = true;
	App->input->playerinput = true;
	App->ui->roundstart = true;
	App->ui->matchend = false;
	App->ui->roundend = false;
	starttime = SDL_GetTicks();
	rounds1 = App->ui->roundsp1;
	rounds2 = App->ui->roundsp2;
	timer = 99;
	endingtimer = 0;
	App->render->camera.x = 0;
	App->render->camera.y = 0;


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


	
	//musload = App->music->LoadMus("Assets/Sound/Masculine Song -Sun- (Haohmaru).ogg");
	//start = App->music->LoadChunk("Assets/Sound/Referee/Samurai Shodown - Referee - Start.wav");
	//ippon = App->music->LoadChunk("Assets/Sound/Referee/Samurai Shodown - Referee - ippon.wav");
	//end = App->music->LoadChunk("Assets/Sound/Referee/Samurai Shodown - Referee - end.wav");

	graphics = App->textures->Load("Assets/Image/haohmaru_stage.png");
	font_timer = App->fonts->Load("Ui/UI_Numbers_1.png", "9876543210", 1);

	App->player->Enable();
	App->player2->Enable();
	App->ui->Enable();
	App->music->PlayMus(musload);
	App->music->PlayChunk(start);


	// COLLIDERS PARA LOS LIMITES DEL MAPA
	colliderMap = App->collision->AddCollider({ -55, -150, 50, 500  }, COLLIDER_WALL);
	colliderMap2 = App->collision->AddCollider({ 640, -150, 50, 500 }, COLLIDER_WALL);


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

	App->ui->Disable();
	App->player2->Disable();
	App->player->Disable();
	App->fonts->UnLoad(font_timer);
	App->textures->Unload(graphics);
	App->music->UnloadChunk(end);
	App->music->UnloadChunk(ippon);
	App->music->UnloadChunk(start);
	App->music->UnloadMus(musload);
	splash1 = Animation();
	splash2 = Animation();
	splash3 = Animation();
	sea = Animation();
	ground = SDL_Rect();
	return true;
}

// Update: draw background
update_status ModuleSceneHaohmaru::Update()
{
	if(matchstart == false){
	if (SDL_GetTicks() - starttime >= 4500) {
		 matchstart = true;
		 App->ui->roundstart = false;
		 timertime = SDL_GetTicks();
	}}
	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, 0, -150, &ground, SDL_FLIP_NONE);

	App->render->Blit(graphics, 0, 53, &(sea.GetCurrentFrame()), SDL_FLIP_NONE, 1);

	App->render->Blit(graphics, 80 + splash1.pivotx[splash1.returnCurrentFrame()], 75 + splash1.pivoty[splash1.returnCurrentFrame()], &(splash1.GetCurrentFrame()), SDL_FLIP_NONE, 1); // splash
	
	App->render->Blit(graphics, 210 + splash2.pivotx[splash2.returnCurrentFrame()], 75 + splash2.pivoty[splash2.returnCurrentFrame()], &(splash2.GetCurrentFrame()), SDL_FLIP_NONE, 1); // splash

	App->render->Blit(graphics, 365 + splash3.pivotx[splash3.returnCurrentFrame()], 40 + splash3.pivoty[splash3.returnCurrentFrame()], &(splash3.GetCurrentFrame()), SDL_FLIP_NONE, 1); // splash
	

	if (timer == 0) {
		if (App->ui->Health_Bar_p2 < App->ui->HealthBar_p1)App->ui->Health_Bar_p2 = 0;
		if(App->ui->Health_Bar_p2 > App->ui->HealthBar_p1)App->ui->HealthBar_p1 = 0;
	}	
	
	if (App->input->keyboard[SDL_SCANCODE_F2] == 1) {
		App->ui->Health_Bar_p2=0;
	
	}

	if (App->input->keyboard[SDL_SCANCODE_F3] == 1) {
		App->ui->HealthBar_p1=0;
		
		
	}
	if (App->ui->Health_Bar_p2 <=0) {
		App->input->inputs2.Push(IN_DEFEAT_P2);
		App->input->inputs.Push(IN_WIN);
		
			App->input->playerinput = false;
			App->ui->matchend = true;
			if (playfx)App->music->PlayChunk(end); playfx = false;

			if (endingtimer ==0)endingtimer = SDL_GetTicks();  
			if (SDL_GetTicks() - endingtimer >= 3000)App->fade->FadeToBlack(App->scene_haohmaru, App->winhaoh, 5);

	
	}
	if (App->ui->HealthBar_p1 <= 0) {
		App->input->inputs2.Push(IN_WIN_P2);
		App->input->inputs.Push(IN_DEFEAT);
		
			App->input->playerinput = false;
			App->ui->matchend = true;
			if (playfx)App->music->PlayChunk(end); playfx = false;

			if (endingtimer == 0)endingtimer = SDL_GetTicks();
			if (SDL_GetTicks() - endingtimer >= 4000)App->fade->FadeToBlack(App->scene_haohmaru, App->end, 5);
		
		
		
	}



	if (SDL_GetTicks() - timertime >= 1000) {
		timertime = SDL_GetTicks();
		timer--;
	}
	sprintf_s(timer_text, 10, "%d", timer);

	App->fonts->BlitText(SCREEN_WIDTH/2-15 - App->render->camera.x / 3, 33 - App->render->camera.y / 3, font_timer, timer_text);
	return UPDATE_CONTINUE;
}