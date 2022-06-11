#include "globals.h"
#include "app.h"
#include "textures.h"
#include "render.h"
#include "pet_p1.h"
#include "player.h"
#include "player2.h"
#include "collision.h"


ModulePetp1::ModulePetp1() {
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


	amube.PushBack({ 321, 471, 71, 64 }, 0.2, 0, 0, 0, 0);
	amube.PushBack({ 399, 479, 75, 64 }, 0.2, 0, 0, 0, 0);
}
ModulePetp1::~ModulePetp1() {

}

bool ModulePetp1::Start() {
	LOG("Loading Hawk 1");
	graphics = App->textures->Load(DATADIR "Assets/Image/Nakoruru spritesheet.png");


	position.x = App->player->position.x - 10;
	position.y = App->player->position.y - 140;
	current_animation = &idle;
	bool ret = true;

	return ret;
}
update_status ModulePetp1::Update() {
	speedx = 0;
	speedy = 0;

	if (!yatoro){
		if (colliderAttack != nullptr) {
			colliderAttack->to_delete = true;
		}
		collider = true;
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
		speedy = 1;
	}
	if (position.y > App->player->position.y - 140) {
		speedy = -1;
	}
}
	}
	else {
		
		if(collider == true)	colliderAttack = App->collision->AddCollider({ 3000, 3000, 50, 50 }, COLLIDER_PLAYER_SHOT, this);
		collider = false;
		if (flip == false) {
			
			speedx = 5;
			speedy = 4;
			colliderAttack->SetPos(position.x, position.y-40);
		}
		if (flip == true) {
			speedx = -5;
			speedy = 4;			
			colliderAttack->SetPos(position.x, position.y-40);

		}
		current_animation = &amube;
	}

	App->player->hawkleft = false;
	App->player->hawkright = false;
	App->player->hawkup = false;
	App->player->hawkdown = false;
	//x = 36 && 557
//y = 36 && 84
	if (App->player->OnHawk == true) {
		flip = App->player->flip;
		speedx = 0; speedy = 0;
		if (App->input->right == true && position.x < 557) { speedx = +3; 
		
		App->player->hawkleft = false;
		App->player->hawkright = true;
		}
		else if (App->input->left == true && position.x > 36) { speedx = -3;
		
		App->player->hawkleft = true;
		App->player->hawkright = false;
		}
		
		if (App->input->up == true && position.y > 36) { speedy = -3;
		
		App->player->hawkup = true;
		App->player->hawkdown = false;

		}
		else if (App->input->down == true && position.y < 84) { speedy = +3;
		
		App->player->hawkup = false;
		App->player->hawkdown = true;

		}
		
	
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
