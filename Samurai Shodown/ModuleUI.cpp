#include "ModuleUI.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"

ModuleUI::ModuleUI() {

	current_animation = NULL;
	
	ko.x = 484;
	ko.y = 394;
	ko.w = 28;
	ko.h = 21;

	healthCont.x = 273;
	healthCont.y = 421;
	healthCont.w = 133;
	healthCont.h = 14;

	healthCont2.x = 273;
	healthCont2.y = 405;
	healthCont2.w = 133;
	healthCont2.h = 14;

	lowKo.PushBack({ 484, 394, 28, 21 }, 0.2, 0, 0, 0, 0);//178, 5
	lowKo.PushBack({ 484, 417, 28, 21 }, 0.2, 0, 0, 0, 0);

	end.PushBack({ 484, 441, 28, 21 }, 0.2, 0, 0, 0, 0);
	end.PushBack({ 484, 465, 28, 21 }, 0.2, 0, 0, 0, 0);

	
	
	health.x = 273;//25, 9,,207, 9
	health.y = 310;
	health.w = HealthBar_p1;
	health.h = 8;

	health2.x = 273;
	health2.y = 310;
	health2.w = Health_Bar_p2;
	health2.h = 8;

	lowHealth.x = 277;
	lowHealth.y = 326;
	lowHealth.w = HealthBar_p1;
	lowHealth.h = 8;

	lowHealth2.x = 277;
	lowHealth2.y = 326;
	lowHealth2.w = Health_Bar_p2;
	lowHealth2.h = 8;

}
ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start() {
	LOG("Loading UI textures");
	bool ret = true;
	graphics = App->textures->Load("UI/Sprite_Sheet_UI_1.png");
	return ret;
}

bool ModuleUI::CleanUp() {

	LOG("Unloading UI");
	App->textures->Unload(graphics);
	return true;
}

update_status ModuleUI::Update() {


	if (HealthBar_p1 <= 32) {
		App->render->Blit(graphics, -App->render->camera.x / 3 + 25 + (127 - HealthBar_p1), -App->render->camera.y / 3, &lowHealth, SDL_FLIP_NONE, 1);
	}
	else {
		App->render->Blit(graphics, -App->render->camera.x / 3 + 25 + (127 - HealthBar_p1), -App->render->camera.y / 3, &health, SDL_FLIP_NONE, 1);
	}
	
	if (Health_Bar_p2 <= 32) {
		App->render->Blit(graphics, -App->render->camera.x / 3 + 207, -App->render->camera.y / 3 + 9, &lowHealth2, SDL_FLIP_NONE, 1);
	}
	else {
		App->render->Blit(graphics, -App->render->camera.x / 3 + 207, -App->render->camera.y / 3 + 9, &health2, SDL_FLIP_NONE, 1);
	}

	App->render->Blit(graphics, -App->render->camera.x / 3 + 15, -App->render->camera.y / 3 + 12, &healthCont, SDL_FLIP_NONE, 1);
	App->render->Blit(graphics, -App->render->camera.x / 3 + 150, -App->render->camera.y / 3 + 12, &healthCont2, SDL_FLIP_NONE, 1);
	App->render->Blit(graphics, -App->render->camera.x / 3 + 128, -App->render->camera.y / 3 + 5, &ko, SDL_FLIP_NONE, 1);

	return UPDATE_CONTINUE;
}
