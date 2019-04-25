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
#include "ModuleEnding.h"



ModuleEnding::ModuleEnding()
{
	end.x = 27;
	end.y = 39;
	end.w = 319;
	end.h = 230;

	flower.PushBack({ 456, 40, 91, 232 }, 0.005, 0, 0, 0, 0);
	flower.PushBack({ 579, 40, 91, 232 }, 0.005, 0, 0, 0, 0);
	
	
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

	
	App->render->Blit(graphics, 38, 52, &(flower.GetCurrentFrame()), SDL_FLIP_NONE, 1);
	App->render->Blit(graphics, 38, 0, &end, SDL_FLIP_NONE);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->end, (Module*)App->menu, 1);
	}

	return UPDATE_CONTINUE;
}