#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "ModuleVictoryHaohmaru.h"
#include "ModuleEnding.h"


ModuleVictoryHaohmaru::ModuleVictoryHaohmaru()
{
	win.x = 1407;
	win.y = 204;
	win.w = 309;
	win.h = 225;
}

ModuleVictoryHaohmaru::~ModuleVictoryHaohmaru()
{}

// Load assets
bool ModuleVictoryHaohmaru::Start()
{
	LOG("Loading win assets");
	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//musload = App->music->LoadMus("Assets/Sound/Conclusion (Winning Demo).ogg");
	graphics = App->textures->Load("Assets/Image/menu_victory.png");
	App->music->PlayMus(musload);

	return ret;
}

bool ModuleVictoryHaohmaru::CleanUp()
{
	LOG("Unloading Menu scene");
	App->music->UnloadMus(musload);
	App->textures->Unload(graphics);
	
	return true;
}

// Update: draw background
update_status ModuleVictoryHaohmaru::Update()
{

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 168, 0, &win, SDL_FLIP_NONE);
	


	//background

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_START) == 1) {
		App->fade->FadeToBlack(App->winhaoh, App->menu, 2);
	}

	return UPDATE_CONTINUE;
}