#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleReferee.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"


ModuleReferee::ModuleReferee() {
	graphics = NULL;
	current_animation = NULL;
	idle.PushBack({ 424, 309, 58, 70 }, 0.05, 0, 0, 0, 0);
	idle.PushBack({ 492, 309, 58, 70 }, 0.1, 0, 0, 0, 0);
	idle.PushBack({ 560, 309, 58, 70 }, 0.1, 0, 0, 0, 0);
	idle.PushBack({ 627, 309, 58, 70 }, 0.1, 0, 0, 0, 0);
	idle.PushBack({ 694, 309, 58, 70 }, 0.05, 0, 0, 0, 0);
	idle.PushBack({ 16, 452, 58, 70 }, 0.1, 0, 0, 0, 0);
	idle.PushBack({ 79, 452, 58, 70 }, 0.1, 0, 0, 0, 0);
	idle.PushBack({ 16, 452, 58, 70 }, 0.1, 0, 0, 0, 0);

	

	moveright.PushBack({ 312, 568, 58, 68 }, 0.1, 0, 0, 0, 0);
	moveright.PushBack({ 382, 568, 58, 68 }, 0.2, 0, 0, 0, 0);
	moveright.PushBack({ 233, 568, 60, 68 }, 0.2, 0, 0, 0, 0);
	moveright.PushBack({ 155, 568, 66, 68 }, 0.2, 0, 0, 0, 0);
	moveright.PushBack({ 92, 568, 58, 68 }, 0.2, 0, 0, 0, 0);
	moveright.PushBack({ 19, 568, 58, 68 }, 0.1, 0, 0, 0, 0);
	moveright.PushBack({ 382, 568, 58, 68 }, 0.2, 0, 0, 0, 0);

	moveleft.PushBack({ 312, 568, 58, 68 }, 0.1, 0, 0, 0, 0);
	moveleft.PushBack({ 382, 568, 58, 68 }, 0.2, 0, 0, 0, 0);
	moveleft.PushBack({ 458, 568, 60, 68 }, 0.2, 0, 0, 0, 0);
	moveleft.PushBack({ 524, 568, 66, 68 }, 0.2, 0, 0, 0, 0);
	moveleft.PushBack({ 597, 568, 58, 68 }, 0.2, 0, 0, 0, 0);
	moveleft.PushBack({ 671, 568, 58, 68 }, 0.1, 0, 0, 0, 0);
	moveleft.PushBack({ 382, 568, 58, 68 }, 0.2, 0, 0, 0, 0);

	flag1.PushBack({ 32, 192, 51, 70 }, 0.1, 0, 0, 0, 0);
	flag1.PushBack({ 92, 192, 51, 70 }, 0.2, 0, 0, 0, 0);
	flag1.PushBack({ 143, 170, 79, 92 }, 0.2, 0, 0, 0, 0);
	flag1.PushBack({ 222, 170, 74, 92 }, 0.2, 0, 0, 0, 0);
	flag1.PushBack({ 298, 167, 77, 91 }, 0.2, 0, 0, 0, 0);
	flag1.PushBack({ 375, 179, 69, 79 }, 0.1, 0, 0, 0, 0);
	flag1.PushBack({ 92, 192, 51, 70 }, 0.2, 0, 0, 0, 0);
	
	flag2.PushBack({ 466, 188, 51, 70 }, 0.1, 0, 0, 0, 0);
	flag2.PushBack({ 859, 188, 51, 70 }, 0.2, 0, 0, 0, 0);
	flag2.PushBack({ 684, 166, 81, 92 }, 0.2, 0, 0, 0, 0);
	flag2.PushBack({ 611, 167, 73, 91 }, 0.2, 0, 0, 0, 0);
	flag2.PushBack({ 526, 167, 77, 91 }, 0.2, 0, 0, 0, 0);
	flag2.PushBack({ 773, 179, 69, 79 }, 0.1, 0, 0, 0, 0);
	flag2.PushBack({ 859, 188, 51, 70 }, 0.2, 0, 0, 0, 0);



}
ModuleReferee::~ModuleReferee() {
}
bool ModuleReferee::Start() {
	LOG("Loading Referee");
	graphics = App->textures->Load("Assets/Image/objectes.png");
	position.x = (App->player->position.x + App->player2->position.x) /2;
	position.y = 185;
	lastposition = position.x;
	current_animation = &idle;
	bool ret = true;
	return ret;
}

update_status ModuleReferee::Update() {
	current_animation = &idle;

	if (App->player->position.x < App->player2->position.x) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (App->player->position.x > App->player2->position.x) {
		flip = SDL_FLIP_NONE;
	}
	position.x = (App->player->position.x + App->player2->position.x) / 2;
	if (lastposition > position.x) {
		if(flip == SDL_FLIP_HORIZONTAL)current_animation = &moveleft;
		if (flip == SDL_FLIP_NONE)current_animation = &moveright;
	}
	if (lastposition < position.x) {
		if (flip == SDL_FLIP_HORIZONTAL)current_animation = &moveright;
		if (flip == SDL_FLIP_NONE)current_animation = &moveleft;
	}

	if (damage1) {
		current_animation = &flag2;
		if (current_animation->AnimationEnd() == true)damage1 = false;
	}
	if (damage2) {
		current_animation = &flag1;
		if (current_animation->AnimationEnd() == true)damage2 = false;
	}
	
	lastposition = position.x;
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, position.x + /*Pivotex*/current_animation->pivotx[current_animation->returnCurrentFrame()], position.y - r.h + /*Pivotey*/ current_animation->pivoty[current_animation->returnCurrentFrame()], &r, flip);
return UPDATE_CONTINUE;
}

bool ModuleReferee::CleanUp() {
	App->textures->Unload(graphics);
	return true;
}