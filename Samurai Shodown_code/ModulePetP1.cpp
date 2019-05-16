#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePetP1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"


ModulePetp1::ModulePetp1() {
	graphics = NULL;
	current_animation = NULL;
	idle.PushBack({ 987, 1788, 44, 72 }, 0.1, 0, 0, 0, 0);
	move.PushBack({ 418, 1539, 52, 58 }, 0.1, 0, 0, 0, 0);
}
ModulePetp1::~ModulePetp1() {

}
bool ModulePetp1::Start() {
	LOG("Loading Hawk 1");
	graphics = App->textures->Load("Assets/Image/Nakoruru spritesheet.png");


	position.x = App->player->position.x - 10;
	position.y = App->player->position.y - 140;
	current_animation = &idle;
	bool ret = true;

	return ret;
}
update_status ModulePetp1::Update() {
	speedx = 0;
	speedy = 0;
	if (App->player->OnHawk == false){
	if (App->player->flip == SDL_FLIP_NONE){
		if (position.x < App->player->position.x - 10){
			speedx = 1;
			flip = App->player->flip;
			current_animation = &idle;
			if (App->player->position.x - 10 - position.x > 20) { 
				speedx = 2; 
				flip = SDL_FLIP_NONE;
				current_animation = &move;
			}
		}
		if (position.x > App->player->position.x - 10) {
			speedx = -1;
			flip = App->player->flip;
			current_animation = &idle;
			if (position.x - App->player->position.x - 10 > 20) { 
				speedx = -2; 
				flip = SDL_FLIP_HORIZONTAL; 
				current_animation = &move;
			}
		}
	}
	

	if (App->player->flip == SDL_FLIP_HORIZONTAL) {
		if (position.x < App->player->position.x + 15) {
			speedx = 1;
			flip = App->player->flip;
			current_animation = &idle;
			if (App->player->position.x - 10 - position.x > 20) { 
				speedx = 2; 
				flip = SDL_FLIP_NONE; 
				current_animation = &move;
			}
		}
		if (position.x > App->player->position.x + 15) {
			speedx = -1;
			flip = App->player->flip;
			current_animation = &idle;
			if (position.x - App->player->position.x - 10 > 20) { 
				speedx = -2; 
				flip = SDL_FLIP_HORIZONTAL; 
				current_animation = &move;
			}
		}

	}

	if (position.y < App->player->position.y - 140) {
		speedy = 4;
	}
	if (position.y > App->player->position.y - 90) {
		speedy = -4;
	}
}
	if (App->player->OnHawk == true) {
		flip = App->player->flip;
		speedx = 0; speedy = 0;
		if (App->input->right == true) { speedx = +3; }
		if (App->input->left == true) { speedx = -3; }
		if (App->input->up == true) { speedy = -3; }
		if (App->input->down == true) { speedy = +3; }
	
	}
	position.x += speedx;
	position.y += speedy;
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, position.x + /*Pivotex*/current_animation->pivotx[current_animation->returnCurrentFrame()], position.y - r.h + /*Pivotey*/ current_animation->pivoty[current_animation->returnCurrentFrame()], &r, flip);
	
	return UPDATE_CONTINUE;
}

bool ModulePetp1::CleanUp() {
	App->textures->Unload(graphics);
	return true;
}