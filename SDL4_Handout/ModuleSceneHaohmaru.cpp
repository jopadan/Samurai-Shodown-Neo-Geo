#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNakoruru.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneHaohmaru.h"
#include "ModuleMusic.h"
#include "ModuleMenu.h"
#include "ModuleSceneCongrats.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"


ModuleSceneHaohmaru::ModuleSceneHaohmaru()
{

	// splash animation

	splash1.PushBack({ 0, 0, 0, 0 }, 0.01, 0, 0);
	splash1.PushBack({ 0, 465, 50, 105 }, 0.2, 39, 0);
	splash1.PushBack({ 261, 465, 95, 105 }, 0.2, 17, 0);
	splash1.PushBack({ 376, 465, 116, 105 }, 0.2, 6, 0);
	splash1.PushBack({ 531, 465, 128, 105 }, 0.2, 0, 0);
	splash1.PushBack({ 698, 465, 119, 105 }, 0.2, 5, 0);
	splash1.PushBack({ 836, 465, 129, 105 }, 0.2, 0, 0);
	splash1.PushBack({ 1023, 465, 126, 105 }, 0.2, 1, 0);

	splash2.PushBack({ 0, 0, 0, 0 }, 0.007, 0, 0);
	splash2.PushBack({ 0, 465, 50, 105 }, 0.2, 39, 0);
	splash2.PushBack({ 261, 465, 95, 105 }, 0.2, 17, 0);
	splash2.PushBack({ 376, 465, 116, 105 }, 0.2, 6, 0);
	splash2.PushBack({ 531, 465, 128, 105 }, 0.2, 0, 0);
	splash2.PushBack({ 698, 465, 119, 105 }, 0.2, 5, 0);
	splash2.PushBack({ 836, 465, 129, 105 }, 0.2, 0, 0);
	splash2.PushBack({ 1023, 465, 126, 105 }, 0.2, 1, 0);

	splash3.PushBack({ 0, 0, 0, 0 }, 0.005, 0, 0);
	splash3.PushBack({ 0, 465, 50, 105 }, 0.2, 39, 0);
	splash3.PushBack({ 261, 465, 95, 105 }, 0.2, 17, 0);
	splash3.PushBack({ 376, 465, 116, 105 }, 0.2, 6, 0);
	splash3.PushBack({ 531, 465, 128, 105 }, 0.2, 0, 0);
	splash3.PushBack({ 698, 465, 119, 105 }, 0.2, 5, 0);
	splash3.PushBack({ 836, 465, 129, 105 }, 0.2, 0, 0);
	splash3.PushBack({ 1023, 465, 126, 105 }, 0.2, 1, 0);

	// ground
	ground.x = 0;
	ground.y = 575;
	ground.w = 640;
	ground.h = 416;

	 //sea animation
	sea.PushBack({ 0, 0, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 704, 4, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 1408, 4, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 0, 156, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 704, 156, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 1408, 156, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 0, 312, 630, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 704, 311, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 1408, 311, 640, 140 }, 0.08f, 0, 0);
	
}

ModuleSceneHaohmaru::~ModuleSceneHaohmaru()
{}

// Load assets
bool ModuleSceneHaohmaru::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	
	graphics = App->textures->Load("haohmaru_stage.png");
	App->player->Enable();
	App->music->Play(App->music->LoadMus("bulletSE.wav"), App->music->LoadChunk("Backmusic.ogg"));

	return ret;
}

bool ModuleSceneHaohmaru::CleanUp()
{
	LOG("Unloading Haohmaru scene");
	App->textures->Unload(graphics);

	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHaohmaru::Update()
{

	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, 0, -150, &ground);	

	App->render->Blit(graphics, 0, 53, &(sea.GetCurrentFrame()), 1);

	App->render->Blit(graphics, 80 + splash1.pivotx[splash1.returnCurrentFrame()], 75 + splash1.pivoty[splash1.returnCurrentFrame()], &(splash1.GetCurrentFrame()), 1); // splash
	
	App->render->Blit(graphics, 210 + splash2.pivotx[splash2.returnCurrentFrame()], 75 + splash2.pivoty[splash2.returnCurrentFrame()], &(splash2.GetCurrentFrame()), 1); // splash

	App->render->Blit(graphics, 365 + splash3.pivotx[splash3.returnCurrentFrame()], 40 + splash3.pivoty[splash3.returnCurrentFrame()], &(splash3.GetCurrentFrame()), 1); // splash
	
	//background
	
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->scene_haohmaru, App->scene_nakoruru, 2);
	}
	
	return UPDATE_CONTINUE;
}