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
#include "ModuleUI.h"



ModuleMenu::ModuleMenu()
{

}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading menu assets");
	timer = SDL_GetTicks();
	bool ret = true;
	menu.x = 0;
	menu.y = 444;
	menu.w = 303;
	menu.h = 223;

	title.PushBack({ 0, 0, 303, 117 }, 0.005, 0, 0, 0, 0);
	title.PushBack({ 349, 0, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 698, 0, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1046, 0, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1395, 0, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1744, 0, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 0, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 349, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 698, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1046, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1395, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1743, 148, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 0, 296, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 349, 296, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 698, 296, 303, 117 }, 0.2, 0, 0, 0, 0);
	title.PushBack({ 1046, 296, 303, 117 }, 0.2, 0, 0, 0, 0);

	start.PushBack({ 1395, 296, 120, 14 }, 0.04f, 0, 0, 0, 0);
	start.PushBack({ 1395, 340, 120, 14 }, 0.025f, 0, 0, 0, 0);


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//musload = App->music->LoadMus("Assets/Sound/Static and Dynamic (short).ogg");
	graphics = App->textures->Load("Assets/Image/Menu Spritesheet.png");
	App->music->PlayMus(musload);
	App->ui->roundsp1 = App->ui->roundsp2 = 0;
	return ret;
}

bool ModuleMenu::CleanUp()
{
	LOG("Unloading Menu scene");
	App->music->UnloadMus(musload);
	App->textures->Unload(graphics);
	title = Animation();
	start = Animation();
	menu = SDL_Rect();
	return true;
}

// Update: draw background
update_status ModuleMenu::Update()
{

	App->render->Blit(graphics, 168, 0, &menu, SDL_FLIP_NONE);
	App->render->Blit(graphics, 168, 52, &(title.GetCurrentFrame()), SDL_FLIP_NONE, 1);
	App->render->Blit(graphics, 254, 172, &(start.GetCurrentFrame()), SDL_FLIP_NONE, 1);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->menu, (Module*)App->scene_haohmaru, 2);
	}
	if (SDL_GetTicks() - timer >= 25000) {
		App->fade->FadeToBlack(App->menu, App->end, 2);
	}
	return UPDATE_CONTINUE;
}