#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneSpace.h"
#include "ModuleFadeToBlack.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneIntro::ModuleSceneIntro()
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading space scene");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	background = App->textures->Load("rtype/intro.png");

	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	// Draw everything --------------------------------------
	App->render->Blit(background, 7, -25, NULL);


	if (App->input->keyboard[SDL_SCANCODE_BACKSPACE] == 1) {
		App->fade->FadeToBlack(App->scene_intro, App->scene_space, 2);
	}

	return UPDATE_CONTINUE;
}