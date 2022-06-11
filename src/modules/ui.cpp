#include "ui.h"
#include "globals.h"
#include "app.h"
#include "textures.h"
#include "render.h"
#include "SDL.h"
#include "music.h"

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

	
	pow.PushBack({ 433, 370, 48, 39 }, 0.2, 0, -4, 0, 0);
	pow.PushBack({ 435, 411, 48, 35 }, 0.2, 0, 0, 0, 0);
	pow.PushBack({ 434, 447, 48, 39 }, 0.2, 0, -4, 0, 0);

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

	victory.x = 486;
	victory.y = 375;
	victory.w = 27;
	victory.h = 18;

	powCont.x = 379;
	powCont.y = 286;
	powCont.w = 65;
	powCont.h = 10;

	powCont2.x = 379;
	powCont2.y = 296;
	powCont2.w = 65;
	powCont2.h = 10;

	powBar.x = 444;
	powBar.y = 246;
	powBar.w = 65;
	powBar.h = 10;

	powBar2.x = 444;
	powBar2.y = 166;
	powBar2.w = 65;
	powBar2.h = 10;

	powBar3.x = 444;
	powBar3.y = 266;
	powBar3.w = 65;
	powBar3.h = 10;

	powBar4.x = 444;
	powBar4.y = 286;
	powBar4.w = 65;
	powBar4.h = 10;

	powBar5.x = 444;
	powBar5.y = 206;
	powBar5.w = 65;
	powBar5.h = 10;

	powBar_p2.x = 444;
	powBar_p2.y = 256;
	powBar_p2.w = 65;
	powBar_p2.h = 10;

	powBar2_p2.x = 444;
	powBar2_p2.y = 176;
	powBar2_p2.w = 65;
	powBar2_p2.h = 10;

	powBar3_p2.x = 444;
	powBar3_p2.y = 276;
	powBar3_p2.w = 65;
	powBar3_p2.h = 10;

	powBar4_p2.x = 444;
	powBar4_p2.y = 296;
	powBar4_p2.w = 65;
	powBar4_p2.h = 10;

	powBar5_p2.x = 444;
	powBar5_p2.y = 216;
	powBar5_p2.w = 65;
	powBar5_p2.h = 10;
	
	level4.x = 275;
	level4.y = 459;
	level4.w = 54;
	level4.h = 9;

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
	dama = App->music->LoadChunk(DATADIR "Assets/Sound/Samurai Shodown - Life Drop.wav");
	bool ret = true;
	graphics = App->textures->Load(DATADIR "UI/Sprite_Sheet_UI_1.png");
	return ret;
}

bool ModuleUI::CleanUp() {

	LOG("Unloading UI");
	App->textures->Unload(graphics);
	App->music->UnloadChunk(dama);
	return true;
}

update_status ModuleUI::Update() {

	health.w = HealthBar_p1;
	health2.w = Health_Bar_p2;
	lowHealth.w = HealthBar_p1;
	lowHealth2.w = Health_Bar_p2;

	powBar.w = damage_p1;
	powBar2.w = damage_p1;
	powBar3.w = damage_p1;
	powBar4.w = damage_p1;
	powBar5.w = damage_p1;
	powBar_p2.w = damage_p2;
	powBar2_p2.w = damage_p2;
	powBar3_p2.w = damage_p2;
	powBar4_p2.w = damage_p2;
	powBar5_p2.w = damage_p2;

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
		//App->music->PlayChunk(dama);
	}
	else {
		App->render->Blit(graphics, -App->render->camera.x + 8, -App->render->camera.y + 12, &healthCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 8, -App->render->camera.y + 23, &healthCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 8 + (128 - HealthBar_p1), -App->render->camera.y + 14, &health, SDL_FLIP_NONE, 1);
	}

	if (Health_Bar_p2 <= 32) {
		App->render->Blit(graphics, -App->render->camera.x + 168, -App->render->camera.y+ 14, &lowHealth2, SDL_FLIP_NONE, 1);
		 //App->music->PlayChunk(dama);

	}
	else {
		App->render->Blit(graphics, -App->render->camera.x + 168, -App->render->camera.y + 12, &healthCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 168, -App->render->camera.y + 23, &healthCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 168, -App->render->camera.y + 14, &health2, SDL_FLIP_NONE, 1);
	}


	if (damage_p1 <= 13) {
		App->render->Blit(graphics, -App->render->camera.x + 46, -App->render->camera.y + 202, &powCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 46 + (67 - damage_p1), -App->render->camera.y + 202, &powBar, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 30, -App->render->camera.y + 200, &pow1, SDL_FLIP_NONE, 1);
		powDamage = 1;
	}
	if (damage_p1 > 13 && damage_p1 <= 26) {
		App->render->Blit(graphics, -App->render->camera.x + 46, -App->render->camera.y + 202, &powCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 46 + (67 - damage_p1), -App->render->camera.y + 202, &powBar2, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 25, -App->render->camera.y + 196, &pow2, SDL_FLIP_NONE, 1);
		powDamage = 1.125;
	}
	if (damage_p1 > 26 && damage_p1 <= 39) {
		App->render->Blit(graphics, -App->render->camera.x + 46, -App->render->camera.y + 202, &powCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 46 + (67 - damage_p1), -App->render->camera.y + 202, &powBar3, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 23, -App->render->camera.y + 191, &pow3, SDL_FLIP_NONE, 1);
		powDamage = 1.25;
	}
	if (damage_p1 > 39 && damage_p1 <= 52) {
		App->render->Blit(graphics, -App->render->camera.x + 46, -App->render->camera.y + 202, &powCont, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 46 + (67 - damage_p1), -App->render->camera.y + 202, &powBar4, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 19, -App->render->camera.y + 187, &pow4, SDL_FLIP_NONE, 1);
		powDamage = 1.375;
	}
	if (damage_p1 > 52) {
		App->render->Blit(graphics, -App->render->camera.x + 46, -App->render->camera.y + 202, &powCont, SDL_FLIP_NONE, 1);
		if (damage_p1 >= 65) {
			App->render->Blit(graphics, -App->render->camera.x + 46, -App->render->camera.y + 202, &powBar5, SDL_FLIP_NONE, 1);
		}
		else {
			App->render->Blit(graphics, -App->render->camera.x + 46 + (67 - damage_p1), -App->render->camera.y + 202, &powBar5, SDL_FLIP_NONE, 1);
		}
		current_animation = &pow;
		App->render->Blit(graphics, -App->render->camera.x + 5, -App->render->camera.y + 177 + current_animation->pivoty[current_animation->returnCurrentFrame()], &(pow.GetCurrentFrame()), SDL_FLIP_NONE, 1);
		powDamage = 1.5;
	}
	
	if (damage_p1 >= 65 && powtimer == false) {
		powTime = SDL_GetTicks();
		powtimer = true;
	}
	if (damage_p1 >= 65 && powtimer == true) {
		if (SDL_GetTicks() - powTime > 15000) {
			powless = true;
			powtimer = false;
		}
	}
	if (powless == true) {
		if (damage_p1 > 0) {
			damage_p1 -= 1;
		}
		else {
			damage_p1 = 0;
			powless = false;
		}
	}
	

	if (damage_p2 <= 13) {
		App->render->Blit(graphics, -App->render->camera.x + 186, -App->render->camera.y + 202, &powCont2, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 186, -App->render->camera.y + 202, &powBar_p2, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 250, -App->render->camera.y + 200, &pow1, SDL_FLIP_NONE, 1);
		powDamage2 = 1;
	}
	if (damage_p2 > 13 && damage_p2 <= 26) {
		App->render->Blit(graphics, -App->render->camera.x + 186, -App->render->camera.y + 202, &powCont2, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 186, -App->render->camera.y + 202, &powBar2_p2, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 250, -App->render->camera.y + 196, &pow2, SDL_FLIP_NONE, 1);
		powDamage2 = 1.125;
	}
	if (damage_p2 > 26 && damage_p2 <= 39) {
		App->render->Blit(graphics, -App->render->camera.x + 186, -App->render->camera.y + 202, &powCont2, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 186, -App->render->camera.y + 202, &powBar3_p2, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 250, -App->render->camera.y + 191, &pow3, SDL_FLIP_NONE, 1);
		powDamage2 = 1.25;
	}
	if (damage_p2 > 39 && damage_p2 <= 52) {
		App->render->Blit(graphics, -App->render->camera.x + 186, -App->render->camera.y + 202, &powCont2, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 186, -App->render->camera.y + 202, &powBar4_p2, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 250, -App->render->camera.y + 187, &pow4, SDL_FLIP_NONE, 1);
		powDamage2 = 1.375;
	}
	if (damage_p2 > 52) {
		App->render->Blit(graphics, -App->render->camera.x + 186, -App->render->camera.y + 202, &powCont2, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 186, -App->render->camera.y + 202, &powBar5_p2, SDL_FLIP_NONE, 1);
		current_animation = &pow;
		App->render->Blit(graphics, -App->render->camera.x + 244, -App->render->camera.y + 177 + current_animation->pivoty[current_animation->returnCurrentFrame()], &(pow.GetCurrentFrame()), SDL_FLIP_NONE, 1);
		powDamage2 = 1.5;
	}

	if (damage_p2 >= 65 && powtimer2 == false) {
		powTime2 = SDL_GetTicks();
		powtimer2 = true;
	}
	if (damage_p2 >= 65 && powtimer2 == true) {
		if (SDL_GetTicks() - powTime2 > 15000) {
			powless2 = true;
			powtimer2 = false;
		}
	}
	if (powless2 == true) {
		if (damage_p2 > 0) {
			damage_p2 -= 1;
		}
		else {
			damage_p2 = 0;
			powless2 = false;
		}
	}


	if (roundsp1 == 1) {
		App->render->Blit(graphics, -App->render->camera.x + 7, -App->render->camera.y + 33, &victory, SDL_FLIP_NONE, 1);
	}
	if (roundsp2 == 1) {
		App->render->Blit(graphics, -App->render->camera.x + 270, -App->render->camera.y + 33, &victory, SDL_FLIP_NONE, 1);
	}
	if (roundsp1 == 2) {
		App->render->Blit(graphics, -App->render->camera.x + 7, -App->render->camera.y + 33, &victory, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 33, -App->render->camera.y + 33, &victory, SDL_FLIP_NONE, 1);
	}
	if (roundsp2 == 2) {
		App->render->Blit(graphics, -App->render->camera.x + 270, -App->render->camera.y + 33, &victory, SDL_FLIP_NONE, 1);
		App->render->Blit(graphics, -App->render->camera.x + 244, -App->render->camera.y + 33, &victory, SDL_FLIP_NONE, 1);
	}

	App->render->Blit(graphics, -App->render->camera.x + 130, -App->render->camera.y + 215, &level4, SDL_FLIP_NONE, 1);

	return UPDATE_CONTINUE;
}
