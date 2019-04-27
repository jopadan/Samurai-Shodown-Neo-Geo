#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNakoruru.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneHaohmaru.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleEnding.h"
#include "ModuleUI.h"



ModuleEnding::ModuleEnding()
{

	end.x = 27;
	end.y = 39;
	end.w = 319;
	end.h = 230;

	flower.PushBack({ 456, 40, 91, 232 }, 0.1, 0, 0, 0, 0);
	flower.PushBack({ 579, 40, 91, 232 }, 0.1, -20, 5, 0, 0);
	flower.PushBack({ 694, 40, 91, 232 }, 0.1, -40, 10, 0, 0);
	flower.PushBack({ 821, 40, 91, 232 }, 0.1, -60, 15, 0, 0);
	flower.PushBack({ 925, 40, 91, 232 }, 0.1, -80, 20, 0, 0);
	flower.PushBack({ 1035, 40, 91, 232 }, 0.1, -100, 25, 0, 0);
	flower.PushBack({ 1151, 40, 91, 232 }, 0.1, -120, 30, 0, 0);
	flower.PushBack({ 1262, 40, 91, 232 }, 0.1, -140, 35, 0, 0);
	flower.PushBack({ 1362, 40, 91, 232 }, 0.1, -160, 40, 0, 0);
	flower.PushBack({ 1471, 40, 91, 232 }, 0.1, -180, 45, 0, 0);
	flower.PushBack({ 1571, 40, 91, 232 }, 0.1, -200, 50, 0, 0);
	flower.PushBack({ 1673, 40, 91, 232 }, 0.1, -220, 55, 0, 0);
	flower.PushBack({ 1775, 40, 91, 232 }, 0.1, -240, 60, 0, 0);
	flower.PushBack({ 455, 338, 91, 232 }, 0.1, -260, 65, 0, 0);
	flower.PushBack({ 577, 338, 91, 232 }, 0.1, -280, 70, 0, 0);
	flower.PushBack({ 693, 338, 91, 232 }, 0.1, -300, 75, 0, 0);
	flower.PushBack({ 820, 338, 91, 232 }, 0.1, -320, 80, 0, 0);
	flower.PushBack({ 922, 338, 91, 232 }, 0.1, -340, 85, 0, 0);
	flower.PushBack({ 1034, 338, 91, 232 }, 0.1, -360, 90, 0, 0);
	flower.PushBack({ 1152, 338, 91, 232 }, 0.1, -380, 95, 0, 0);
	flower.PushBack({ 1261, 338, 91, 232 }, 0.1, -400, 100, 0, 0);
	flower.PushBack({ 1362, 338, 91, 232 }, 0.1, -420, 105, 0, 0);
	flower.PushBack({ 1472, 338, 91, 232 }, 0.1, -440, 110, 0, 0);
	


	black.x = 29;
	black.y = 340;
	black.w = 319;
	black.h = 230;
	
}

ModuleEnding::~ModuleEnding()
{}

// Load assets
bool ModuleEnding::Start()
{
	LOG("Loading end assets");
	bool ret = true;


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	
	graphics = App->textures->Load("Assets/Image/ending_spritesheet.png");
	//App->music->PlayMus(musload);

	return ret;
}

bool ModuleEnding::CleanUp()
{
	LOG("Unloading Menu scene");
	//App->music->UnloadMus(musload);
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleEnding::Update()
{

	App->render->Blit(graphics, 38, 0, &black, SDL_FLIP_NONE);
	App->render->Blit(graphics, 350, -10, &(flower.GetCurrentFrame()), SDL_FLIP_NONE, 1);
	App->render->Blit(graphics, 168, 0, &end, SDL_FLIP_NONE);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->end, App->menu, 1);
	}

	return UPDATE_CONTINUE;
}