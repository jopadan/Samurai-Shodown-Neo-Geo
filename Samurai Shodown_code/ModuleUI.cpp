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

	Ippon.x = 495;
	Ippon.y = 62;
	Ippon.w = 99;
	Ippon.h = 38;

	Victory.x = 494;
	Victory.y = 104;
	Victory.w = 118;
	Victory.h = 34;

	ko.x = 484;
	ko.y = 394;
	ko.w = 28;
	ko.h = 21;

	healthCont1.x = 273;
	healthCont1.y = 421;
	healthCont1.w = 134;
	healthCont1.h = 14;

	healthCont2.x = 273;
	healthCont2.y = 405;
	healthCont2.w = 134;
	healthCont2.h = 14;

	healthCont.x = 273;
	healthCont.y = 308;
	healthCont.w = 130;
	healthCont.h = 2;
	
	begin.x	= 493;
	begin.y = 9;
	begin.w = 109;
	begin.h = 49;

	lowKo.PushBack({ 484, 394, 28, 21 }, 0.2, 0, 0, 0, 0);//178, 5
	lowKo.PushBack({ 484, 417, 28, 21 }, 0.2, 0, 0, 0, 0);

	end.PushBack({ 484, 441, 28, 21 }, 0.2, 0, 0, 0, 0);
	end.PushBack({ 484, 465, 28, 21 }, 0.2, 0, 0, 0, 0);

	
	pow.PushBack({ 433, 370, 48, 39 }, 0.2, 0, 0, 0, 0);
	pow.PushBack({ 435, 411, 48, 35 }, 0.2, 0, 0, 0, 0);
	pow.PushBack({ 434, 447, 48, 39 }, 0.2, 0, 0, 0, 0);

	pow1.x = 462;
	pow1.y = 336;
	pow1.w = 17;
	pow1.h = 12;

	pow2.x = 456;
	pow2.y = 351;
	pow2.w = 23;
	pow2.h = 16;

	pow3.x = 483;
	pow3.y = 324;
	pow3.w = 25;
	pow3.h = 21;

	pow4.x = 481;
	pow4.y = 348;
	pow4.w = 29;
	pow4.h = 25;

	nakoruru.x = 276;
	nakoruru.y = 479;
	nakoruru.w = 64;
	nakoruru.h = 8;

	victory.x = 487;
	victory.y = 376;
	victory.w = 25;
	victory.h = 16;

	powCont.x = 379;
	powCont.y = 286;
	powCont.w = 65;
	powCont.h = 10;

	powCont2.x = 379;
	powCont2.y = 296;
	powCont2.w = 65;
	powCont2.h = 10;
	
	
	health.x = 273;//25, 9,,207, 9
	health.y = 310;
	health.w = HealthBar_p1;
	health.h = 9;

	health2.x = 273;
	health2.y = 310;
	health2.w = Health_Bar_p2;
	health2.h = 9;

	lowHealth.x = 277;
	lowHealth.y = 326;
	lowHealth.w = HealthBar_p1;
	lowHealth.h = 9;

	lowHealth2.x = 277;
	lowHealth2.y = 326;
	lowHealth2.w = Health_Bar_p2;
	lowHealth2.h = 9;

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

	health.w = HealthBar_p1;
	health2.w = Health_Bar_p2;
	lowHealth.w = HealthBar_p1;
	lowHealth2.w = Health_Bar_p2;

	if (roundstart == true){ App->render->Blit(graphics, -App->render->camera.x  + 97, -App->render->camera.y + 70, &begin, SDL_FLIP_NONE, 1); }
	if (roundend == true) { App->render->Blit(graphics, -App->render->camera.x + 97, -App->render->camera.y + 70, &Ippon, SDL_FLIP_NONE, 1); }
	if (matchend == true) { App->render->Blit(graphics, -App->render->camera.x+ 97, -App->render->camera.y + 70, &Victory, SDL_FLIP_NONE, 1); }
	
	App->render->Blit(graphics, -App->render->camera.x + 4, -App->render->camera.y + 12, &healthCont1, SDL_FLIP_NONE, 1);
	App->render->Blit(graphics, -App->render->camera.x + 166, -App->render->camera.y + 12, &healthCont2, SDL_FLIP_NONE, 1);
	App->render->Blit(graphics, -App->render->camera.x + 138, -App->render->camera.y + 5, &ko, SDL_FLIP_NONE, 1);
	App->render->Blit(graphics, -App->render->camera.x + 15, -App->render->camera.y + 26, &nakoruru, SDL_FLIP_NONE, 1);
	App->render->Blit(graphics, -App->render->camera.x + 226, -App->render->camera.y + 26, &nakoruru, SDL_FLIP_NONE, 1);

	if (HealthBar_p1 <= 32) {
		App->render->Blit(graphics, -App->render->camera.x + 8 + (128 - HealthBar_p1), -App->render->camera.y + 14, &lowHealth, SDL_FLIP_NONE, 1);
	}
	else {
		App->render->Blit(graphics, -App->render->camera.x + 8, -App->render->camera.y + 12, &healthCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 8, -App->render->camera.y + 23, &healthCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 8 + (128 - HealthBar_p1), -App->render->camera.y + 14, &health, SDL_FLIP_NONE, 1);
	}

	if (Health_Bar_p2 <= 32) {
		App->render->Blit(graphics, -App->render->camera.x + 168, -App->render->camera.y+ 14, &lowHealth2, SDL_FLIP_NONE, 1);
	}
	else {
		App->render->Blit(graphics, -App->render->camera.x + 168, -App->render->camera.y + 12, &healthCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 168, -App->render->camera.y + 23, &healthCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 168, -App->render->camera.y + 14, &health2, SDL_FLIP_NONE, 1);
	}

	if (roundsp1 == 0) {
		App->render->Blit(graphics, -App->render->camera.x + 8, -App->render->camera.y + 33, &victory, SDL_FLIP_NONE, 1);
	}
	if (roundsp2 == 1) {
		App->render->Blit(graphics, -App->render->camera.x + 274, -App->render->camera.y + 33, &victory, SDL_FLIP_NONE, 1);
	}

	return UPDATE_CONTINUE;
}
