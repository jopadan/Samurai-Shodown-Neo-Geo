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


ModuleMenu::ModuleMenu()
{
	menu.x = 0;
	menu.y = 204;
	menu.w = 309;
	menu.h = 225;

	menu2.PushBack({ 704, 204, 309, 225 }, 0.01f,0,0);
	menu2.PushBack({ 0, 204, 309, 225 }, 0.04f, 0, 0);
}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading menu assets");
	bool ret = true;

	chunkload = App->music->LoadChunk("Assets/Sound/Static and Dynamic (short).ogg");
	graphics = App->textures->Load("Assets/Image/menu_victory.png");
	App->music->Play(nullptr, chunkload);

	return ret;
}

bool ModuleMenu::CleanUp()
{
	LOG("Unloading Menu scene");
	App->music->Unload(chunkload);
	App->textures->Unload(graphics);
	
	return true;
}

// Update: draw background
update_status ModuleMenu::Update()
{

	App->render->Blit(graphics, 38, 0, &menu);
	App->render->Blit(graphics, 38, 0, &(menu2.GetCurrentFrame()), 1);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->menu, App->scene_haohmaru, 1);
	}

	return UPDATE_CONTINUE;
}