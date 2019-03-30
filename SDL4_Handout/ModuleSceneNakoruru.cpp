#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNakoruru.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneHaohmaru.h"
#include "SDL/include/SDL.h"

ModuleSceneNakoruru::ModuleSceneNakoruru()
{

	// ground
	ground.x = 702;
	ground.y = 705;
	ground.w = 640;
	ground.h = 416;

	//animals animation
	animals.PushBack({ 702, 0, 640, 208 }, 0.225f, 0, 0);
	animals.PushBack({ 1408, 0, 640, 208 }, 0.225f, 0, 0);
	animals.PushBack({ 0, 233, 640, 208 }, 0.225f, 0, 0);
	animals.PushBack({ 702, 233, 640, 208 }, 0.225f, 0, 0);
	animals.PushBack({ 1408, 233, 640, 208 }, 0.225f, 0, 0);
	animals.PushBack({ 0, 467, 640, 208 }, 0.225f, 0, 0);
	animals.PushBack({ 702, 467, 640, 208 }, 0.225f, 0, 0);
	animals.PushBack({ 1408, 467, 640, 208 }, 0.225f, 0, 0);

}

ModuleSceneNakoruru::~ModuleSceneNakoruru()
{}

// Load assets
bool ModuleSceneNakoruru::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	graphics = App->textures->Load("Nakoruru Map Spritesheet.png");

	App->player->Enable();

	return ret;
	
}
bool ModuleSceneNakoruru::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading honda stage");
	SDL_DestroyTexture(graphics);

	App->player->Disable();

	return true;
}
// Update: draw background
update_status ModuleSceneNakoruru::Update()
{


	// Draw everything --------------------------------------
	
	App->render->Blit(graphics, 0, -150, &ground);

	App->render->Blit(graphics, 0, 7, &(animals.GetCurrentFrame()), 1);
	
	//background

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->scene_nakoruru, App->scene_haohmaru, 2);
	}

	return UPDATE_CONTINUE;
}