#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNakoruru.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneHaohmaru.h"


ModuleMenu::ModuleMenu()
{


	// ground
	menu.x = 0;
	menu.y = 12;
	menu.w = 640;
	menu.h = 417;

	//sea animation
	menu2.PushBack({ 704, 12, 640, 417 }, 0.08f,0,0);
	

}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	graphics = App->textures->Load("menu_victory.png");
	//App->player->Enable();

	return ret;
}

bool ModuleMenu::CleanUp()
{
	LOG("Unloading Menu scene");
	App->textures->Unload(graphics);

	//App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleMenu::Update()
{

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, 0, &menu);

	App->render->Blit(graphics, 0, 0, &(menu2.GetCurrentFrame()), 1);

	

	//background

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->menu, App->scene_haohmaru, 2);
	}

	return UPDATE_CONTINUE;
}