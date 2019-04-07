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
#include "ModuleVictoryHaohmaru.h"

#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

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
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	bool ret = true;

	LOG("Loading background assets");
	

	musload = App->music->LoadMus("Assets/Sound/Banquet of Nature (Nakoruru).ogg");
	graphics = App->textures->Load("Assets/Image/Nakoruru Map Spritesheet.png");

	App->music->PlayMus(musload);
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();

	colliderMap = App->collision->AddCollider({ 0, -150, 50, 500 }, COLLIDER_WALL);
	colliderMap2 = App->collision->AddCollider({ 590, -150, 50, 500 }, COLLIDER_WALL);

	return ret;
	
}

bool ModuleSceneNakoruru::CleanUp()
{
	LOG("Unloading nakoruru scene");
	if (colliderMap != nullptr) {
		colliderMap->to_delete = true;
	}
	if (colliderMap2 != nullptr) {
		colliderMap2->to_delete = true;
	}
	App->music->UnloadMus(musload);
	App->textures->Unload(graphics);
	App->player->Disable();
	App->player2->Disable();


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
		App->fade->FadeToBlack(App->scene_nakoruru,(Module*)App->winhaoh, 2);
	}

	return UPDATE_CONTINUE;
}