#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNakoruru.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneHaohmaru.h"
#include "ModuleSceneCongrats.h"


ModuleSceneCongrats::ModuleSceneCongrats()
{



	win.x = 1407;
	win.y = 204;
	win.w = 384;
	win.h = 225;

	//sea animation
	


}

ModuleSceneCongrats::~ModuleSceneCongrats()
{}

// Load assets
bool ModuleSceneCongrats::Start()
{
	LOG("Loading win assets");
	bool ret = true;

	graphics = App->textures->Load("menu_victory.png");
	//App->player->Enable();

	return ret;
}

bool ModuleSceneCongrats::CleanUp()
{
	LOG("Unloading Menu scene");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleSceneCongrats::Update()
{

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &win);
	


	//background

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->congrats, App->menu, 1);
	}

	return UPDATE_CONTINUE;
}