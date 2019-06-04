#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePetp2.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"


ModulePetp2::ModulePetp2() {
	graphics = NULL;
	current_animation = NULL;
	idle.PushBack({ 987, 1788, 44, 72 }, 0.15, 0, 0, 0, 0);
	idle.PushBack({ 1034, 1792, 46, 66 }, 0.15, 0, 0, 0, 0);
	idle.PushBack({ 1084, 1797, 48, 64 }, 0.15, 0, 0, 0, 0);
	idle.PushBack({ 1132, 1800, 47, 58 }, 0.2, 0, 0, 0, 0);
	idle.PushBack({ 1181, 1824, 58, 35 }, 0.2, 0, 0, 0, 0);
	idle.PushBack({ 1239, 1817, 54, 48 }, 0.15, 0, 0, 0, 0);
	idle.PushBack({ 1292, 1812, 48, 52 }, 0.15, 0, 0, 0, 0);
	idle.PushBack({ 1342, 1803, 43, 62 }, 0.15, 0, 0, 0, 0);





	move.PushBack({ 418, 1539, 52, 58 }, 0.1, 0, 0, 0, 0);
	move.PushBack({ 474, 1548, 70, 52 }, 0.2, 0, 0, 0, 0);
	move.PushBack({ 544, 1553, 71, 35 }, 0.2, 0, 0, 0, 0);
	move.PushBack({ 614, 1546, 54, 53 }, 0.2, 0, 0, 0, 0);
	move.PushBack({ 666, 1539, 57, 43 }, 0.2, 0, 0, 0, 0);
	move.PushBack({ 720, 1538, 45, 75 }, 0.1, 0, 0, 0, 0);
}
ModulePetp2::~ModulePetp2() {

}
bool ModulePetp2::Start() {
	LOG("Loading Hawk 2");
	graphics = App->textures->Load("Assets/Image/Nakoruru spritesheet p2.png");


	position.x = App->player2->position.x - 10;
	position.y = App->player2->position.y - 140;
	current_animation = &idle;
	bool ret = true;

	return ret;
}
update_status ModulePetp2::Update() {
	speedx = 0;
	speedy = 0;
	if (App->player2->OnHawk == false){
	if (App->player2->flip == SDL_FLIP_NONE){
		if (position.x < App->player2->position.x - 10){
			speedx = 1;
			flip = App->player2->flip;
			current_animation = &idle;
			if (App->player2->position.x - 10 - position.x > 20) { 
				speedx = 2; 
				flip = SDL_FLIP_NONE;
				current_animation = &move;
			}
		}
		if (position.x > App->player2->position.x - 10) {
			speedx = -1;
			flip = App->player2->flip;
			current_animation = &idle;
			if (position.x - App->player2->position.x - 10 > 20) { 
				speedx = -2; 
				flip = SDL_FLIP_HORIZONTAL; 
				current_animation = &move;
			}
		}
	}
	

	if (App->player2->flip == SDL_FLIP_HORIZONTAL) {
		if (position.x < App->player2->position.x + 15) {
			speedx = 1;
			flip = App->player2->flip;
			current_animation = &idle;
			if (App->player2->position.x - 10 - position.x > 20) { 
				speedx = 2; 
				flip = SDL_FLIP_NONE; 
				current_animation = &move;
			}
		}
		if (position.x > App->player2->position.x + 15) {
			speedx = -1;
			flip = App->player2->flip;
			current_animation = &idle;
			if (position.x - App->player2->position.x - 10 > 20) { 
				speedx = -2; 
				flip = SDL_FLIP_HORIZONTAL; 
				current_animation = &move;
			}
		}

	}

	if (position.y < App->player2->position.y - 140) {
		speedy = 1;
	}
	if (position.y > App->player2->position.y - 90) {
		speedy = -1;
	}
}
	/*if (App->player->amubeyatoro == true) {
		//current_animation = &amube;
		flip = App->player->flip;
		if (flip == false) {
			speedx = 20;
			speedy = 5;
		}
		if (flip == true) {
			speedx = -20;
			speedy = -5;
		}
	}*/
	App->player2->hawkleft = false;
	App->player2->hawkright = false;
	App->player2->hawkup = false;
	App->player2->hawkdown = false;

	if (App->player2->OnHawk == true) {
		flip = App->player2->flip;
		speedx = 0; speedy = 0;
		if (App->input->right2 == true) { speedx = +3; 
		
		App->player2->hawkleft = false;
		App->player2->hawkright = true;
		}
		else if (App->input->left2 == true) { speedx = -3; 
		
		App->player2->hawkleft = true;
		App->player2->hawkright = false;
		}
		
		if (App->input->up2 == true) { speedy = -3;
		
		App->player2->hawkup = true;
		App->player2->hawkdown = false;

		}
		else if (App->input->down2 == true) { speedy = +3;
		
		App->player2->hawkup = false;
		App->player2->hawkdown = true;

		}
		
	
	}
	position.x += speedx;
	position.y += speedy;
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, position.x + /*Pivotex*/current_animation->pivotx[current_animation->returnCurrentFrame()], position.y - r.h + /*Pivotey*/ current_animation->pivoty[current_animation->returnCurrentFrame()], &r, flip);
	
	return UPDATE_CONTINUE;
}

bool ModulePetp2::CleanUp() {
	App->textures->Unload(graphics);
	return true;
}