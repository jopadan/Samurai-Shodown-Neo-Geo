#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneCongrats.h"


ModuleSceneCongrats::ModuleSceneCongrats()
{
	win.x = 1407;
	win.y = 204;
	win.w = 384;
	win.h = 225;
}

ModuleSceneCongrats::~ModuleSceneCongrats()
{}

// Load assets
bool ModuleSceneCongrats::Start()
{
	LOG("Loading win assets");
	bool ret = true;

	chunkload = App->music->LoadChunk("Assets/Sound/Conclusion (Winning Demo).ogg");
	graphics = App->textures->Load("Assets/Image/menu_victory.png");
	App->music->Play(nullptr, chunkload);
	//App->player->Enable();

	return ret;
}

bool ModuleSceneCongrats::CleanUp()
{
	LOG("Unloading Menu scene");
	App->textures->Unload(graphics);
	App->music->Unload(chunkload);
	return true;
}

// Update: draw background
update_status ModuleSceneCongrats::Update()
{

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &win);
	


	//background

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->congrats, App->menu, 2);
	}

	return UPDATE_CONTINUE;
}