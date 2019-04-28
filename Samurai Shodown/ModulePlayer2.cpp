#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneHaohmaru.h"
#include "ModuleUI.h"


ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 372;
	position.y = 207;
	initialPos = position.y;

	idle.PushBack({ 7, 273, 75, 113 }, 0.15, 0, 0, -2, 0);
	idle.PushBack({ 86, 275, 73, 111 }, 0.15, 0, 0, -1, 0);
	idle.PushBack({ 164, 277, 72, 109 }, 0.15, 0, 0, 0, 0);
	idle.PushBack({ 241, 279, 72, 107 }, 0.15, 0, 0, 0, 0);
	
	crouch.PushBack({ 760, 432, 76, 110 }, 0.25, 0, 1, 0, 2);
	crouch.PushBack({ 854, 460, 103, 84 }, 0.1, -26, 1, 0, 2);
	crouch.loop = false;

	forward.PushBack({ 506, 150, 69, 112 }, 0.1, 0, 0, 0, 0);
	forward.PushBack({ 580, 147, 59, 116 }, 0.25, 0, 0, 0, 0);
	forward.PushBack({ 644, 145, 57, 118 }, 0.1, 0, 0, 0, 0);
	forward.PushBack({ 706, 147, 62, 116 }, 0.25, 0, 0, 0, 0);
	forward.PushBack({ 773, 151, 70, 117 }, 0.1, 0, 0, 0, 0);

	backward.PushBack({ 4, 155, 82, 111 }, 0.2, 0, 0, 0, 0);
	backward.PushBack({ 88, 152, 75, 114 }, 0.2, 0, 0, 0, 0);
	backward.PushBack({ 165, 147, 69, 118 }, 0.2, 0, 0, 0, 0);
	backward.PushBack({ 236, 145, 66, 120 }, 0.2, 0, 0, 0, 0);
	backward.PushBack({ 304, 147, 70, 118 }, 0.2, 0, 0, 0, 0);
	backward.PushBack({ 376, 151, 75, 114 }, 0.2, 0, 0, 0, 0);

	jumpup.PushBack({ 363, 274, 60, 112 }, 0.11, 0, 0, 0, 0);
	jumpup.PushBack({ 429, 295, 75, 91 }, 0.11, 0, 0, 0, 0);
	jumpup.PushBack({ 510, 303, 76, 83 }, 0.09, 0, 0, 0, 0);
	jumpup.PushBack({ 429, 295, 75, 91 }, 0.11, 0, 0, 0, 0);
	jumpup.PushBack({ 363, 274, 60, 112 }, 0.11, 0, 0, 0, 0);

	crouchPunch.PushBack({ 0, 559, 83, 69 }, 0.3, 0, 0, 0, 0);//628
	crouchPunch.PushBack({ 87, 560, 122, 68 }, 0.3, 0, 0, 0, 0);
	crouchPunch.PushBack({ 217, 560, 122, 68 }, 0.3, 0, 0, 0, 0);
	crouchPunch.PushBack({ 347, 558, 118, 70 }, 0.3, 0, 0, 0, 0);
	crouchPunch.PushBack({ 475, 559, 125, 69 }, 0.3, 0, 0, 0, 0);
	crouchPunch.PushBack({ 604, 560, 85, 68 }, 0.3, 0, 0, 0, 0);
	crouchPunch.PushBack({ 693, 560, 81, 68 }, 0.3, 0, 0, 0, 0);
	crouchPunch.PushBack({ 778, 559, 83, 69 }, 0.3, 0, 0, 0, 0);
	crouchPunch.PushBack({ 867, 552, 71, 76 }, 0.3, 0, 0, 0, 0);

	punch.PushBack({ 3, 0, 69, 127 }, 0.1, 0, 0, -1, 0);
	punch.PushBack({ 74, 30, 79, 97 }, 0.3, -10, 0, -2, 0);
	punch.PushBack({ 158, 33, 132, 94 }, 0.6, 0, 0, -32, 0); //
	punch.PushBack({ 290, 33, 132, 94 }, 0.6, 0, 0, -32, 0);
	punch.PushBack({ 423, 42, 131, 85 }, 0.6, 0, 0, -32, 0);
	punch.PushBack({ 556, 44, 130, 94 }, 0.6, 0, 11, -32, 11);
	punch.PushBack({ 688, 44, 128, 94 }, 0.6, 0, 11, -32, 11);
	punch.PushBack({ 818, 44, 120, 94 }, 0.6, 0, 11, -26, 11);
	//punch.PushBack({ 940, 44, 83, 94 }, 0.3, 0, 11, -18, 11);
	punch.PushBack({ 1025, 42, 131, 85 }, 0.1, 0, 0, -27, 0); 

	kick.PushBack({ 647, 274, 58, 112 }, 0.2, 0, 0, 4, 0);
	kick.PushBack({ 710, 276, 53, 110 }, 0.1, 0, 0, 2, 0);
	kick.PushBack({ 768, 288, 94, 98 }, 0.1, 0, 0, -14, 0);
	kick.PushBack({ 867, 287, 97, 99 }, 0.1, 0, 0, -14, 0);
	kick.PushBack({ 969, 286, 82, 100 }, 0.2, 0, 0, -4, 0);

	cyclone.PushBack({ 8, 452, 90, 88 }, 0.1, 0, 0, 0, 0);
	cyclone.PushBack({ 105, 451, 70, 89 }, 0.2, 0, 0, 0, 0);
	cyclone.PushBack({ 181, 457, 73, 83 }, 0.2, 0, 0, 0, 0);
	cyclone.PushBack({ 261, 449, 58, 91 }, 0.2, 0, 0, 0, 0);
	cyclone.PushBack({ 326, 442, 94, 98 }, 0.2, 0, 0, 0, 0);
	cyclone.PushBack({ 427, 387, 62, 153 }, 0.2, 0, 0, 0, 0);
	cyclone.PushBack({ 496, 442, 97, 98 }, 0.2, -20, 0, 0, 0);
	cyclone.PushBack({ 600, 450, 97, 90 }, 0.08, -20, 0, 0, 0);

	
	hit.PushBack({ 985, 446, 92, 107 }, 0.08, -20, 10, 0, 10);
	//Animaciones a completar
	block.PushBack({ 429, 295, 75, 91 }, 0.05, 0, 0, 0, 0);
	
	defeat.PushBack({ 1081, 436, 74, 108 }, 0.02, 0, 2, 0, 2);
	defeat.PushBack({ 1164, 436, 74, 108 }, 0.025, 6, 2, -3, 2);
	defeat.PushBack({ 1241, 436, 70, 108 }, 0.1, 9, 2, -3, 2);
	defeat.PushBack({ 1312, 436, 70, 108 }, 0.1, 9, 2, -3, 2);
	defeat.loop = false;

	defeat.loop = false;
	win.PushBack({ 0, 1000, 84, 106 }, 0.1, 2, 1, 0, 0);
	win.PushBack({ 0 , 1000, 84, 106 }, 0.1, 2, 1, 0, 0);
	win.PushBack({ 165, 1000, 84, 106 }, 0.1, -4, 1, 0, 0);
	win.PushBack({ 251, 1001, 84, 106 }, 0.1, -2, 2, 0, 0);
	win.PushBack({ 340, 1000, 84, 106 }, 0.1, -1, 1, 0, 0);
	win.PushBack({ 429, 1000, 84, 106 }, 0.1, -3, 1, 0, 0);
	win.PushBack({ 521, 993, 84, 113 }, 0.1, -1, 1, 0, 0);
	win.PushBack({ 607, 993, 84, 113 }, 0.1, -3, 1, 0, 0);
	win.PushBack({ 693, 993, 79, 114 }, 0.1, -2, 2, 0, 0);
	win.PushBack({ 777, 993, 84, 113 }, 0.1, 1, 1, 0, 0);
	win.PushBack({ 863, 993, 84, 113 }, 0.1, 0, 1, 0, 0);
	win.PushBack({ 0, 1000, 84, 106 }, 0.1, 2, 1, 0, 0);
	win.loop = false;
	//Hasta aqui

	intro.PushBack({ 0, 1000, 84, 106 }, 0.1, 2, 1, 0, 0);
	intro.PushBack({ 0 , 1000, 84, 106 }, 0.1, 2, 1, 0, 0);
	intro.PushBack({ 165, 1000, 84, 106 }, 0.1, -4, 1, 0, 0);
	intro.PushBack({ 251, 1001, 84, 106 }, 0.1, -2, 2, 0, 0);
	intro.PushBack({ 340, 1000, 84, 106 }, 0.1, -1, 1, 0, 0);
	intro.PushBack({ 429, 1000, 84, 106 }, 0.1, -3, 1, 0, 0);
	intro.PushBack({ 521, 993, 84, 113 }, 0.1, -1, 1, 0, 0);
	intro.PushBack({ 607, 993, 84, 113 }, 0.1, -3, 1, 0, 0);
	intro.PushBack({ 693, 993, 79, 114 }, 0.1, -2, 2, 0, 0);
	intro.PushBack({ 777, 993, 84, 113 }, 0.1, 1, 1, 0, 0);
	intro.PushBack({ 863, 993, 84, 113 }, 0.1, 0, 1, 0, 0);
    intro.PushBack({ 943, 1000, 84, 106 }, 0.15, -4, 2, 0, 0);
	intro.PushBack({ 1030, 1000, 134, 113 }, 0.15, 0, 8, 0, 0);
	intro.PushBack({ 940, 44, 83, 113 }, 0.15, 4, 30, 4, 11);
	intro.PushBack({ 943, 1000, 84, 106 }, 0.15, -4, 2, 0, 0);
	intro.PushBack({ 7, 273, 75, 113 }, 0.15, 0, 0, -1, 0);
	intro.loop = false;

	shadow.PushBack({ 659, 70, 70, 14 }, 1.8, 0, 0, 0, 0);
	shadow.PushBack({ 733, 70, 70, 14 }, 1.8, 0, 0, 0, 0);
}

ModulePlayer2::~ModulePlayer2()
{}


bool ModulePlayer2::Start()
{
	LOG("Loading player2 textures");
	bool ret = true;
	App->input->left2 = false;
	App->input->right2 = false;
	App->input->down2 = false;
	App->input->up2 = false;
	defeat.Reset();
	win.Reset();
	intro.Reset();

	position.x = 372;
	position.y = 207;

	graphics = App->textures->Load("Assets/Image/Haohmaru Spritesheet p2.png");
	graphicsobj = App->textures->Load("Assets/Image/objectes.png");
	senpuu = App->music->LoadChunk("Assets/Sound/Haohmaru/attacks/senpuu.ogg");
	sword = App->music->LoadChunk("Assets/Sound/Common/Samurai Shodown - A- 01.wav");
	kicks = App->music->LoadChunk("Assets/Sound/Common/Samurai Shodown - KICK (MISS) - 01.wav");
	hitted = App->music->LoadChunk("Assets/Sound/Haohmaru/Samurai Shodown - Haohmaru - Hitted 8.wav"); 
	App->ui->Health_Bar_p2 = 128;

	if (flip == SDL_FLIP_HORIZONTAL) {
		colliderPlayer2 = App->collision->AddCollider({ position.x + 60, position.y - 90, 47, 50 }, COLLIDER_ENEMY, this);
	}
	else {
		colliderPlayer2 = App->collision->AddCollider({ position.x + 45, position.y - 90, 47, 50 }, COLLIDER_ENEMY, this);
	}
	if (flip == SDL_FLIP_HORIZONTAL) {
		colliderPlayer2_2 = App->collision->AddCollider({ position.x + 60, position.y - 90, 35, 40 }, COLLIDER_ENEMY, this);
	}
	else {
		colliderPlayer2_2 = App->collision->AddCollider({ position.x + 45, position.y - 90, 35, 40 }, COLLIDER_ENEMY, this);
	}
	return ret;
}

bool ModulePlayer2::CleanUp() {
	App->input->inputs2.Push(IN_WIN_FINISH_P2);
	App->input->inputs2.Push(IN_DEFEAT_FINISH_P2);
	LOG("Unloading Player2")
		if (colliderPlayer2 != nullptr) {
			colliderPlayer2->to_delete = true;
			colliderPlayer2_2->to_delete = true;
		}
	position.x = 372;
	position.y = 207;
	App->textures->Unload(graphics);
	App->textures->Unload(graphicsobj);
	App->music->UnloadChunk(senpuu);
	App->music->UnloadChunk(sword);
	App->music->UnloadChunk(kicks);
	App->music->UnloadChunk(hitted);

	return true;
}

update_status ModulePlayer2::Update()
{
	Animation* current_animation = &intro;
	if (App->scene_haohmaru->matchstart == true) current_animation = &idle;
	
	SDL_Rect r2 = shadow.GetCurrentFrame();
	App->render->Blit(graphicsobj, position.x - 7, 201, &r2, SDL_FLIP_NONE);

	player_states current_state = ST_UNKNOWN;
	player_states state = process_fsm(App->input->inputs2);
	if (state != current_state)
	{
		if (state != ST_WALK_BACKWARD || state != ST_WALK_FORWARD) {
			defense = false;
		}
		switch (state)
		{
		case ST_IDLE:
			jumpSpeed = 6;
			height = 0;
			height2 = 0;
			break;

		case ST_WALK_FORWARD:
			if (flip == SDL_FLIP_HORIZONTAL)defense = true;
			if (wall && position.x > 100) {}
			else if (position.x + 60 > (-App->render->camera.x + 912) / 3) {}
			else {
				if (flip == SDL_FLIP_HORIZONTAL) {
					current_animation = &backward;
					
				}
				if (flip == SDL_FLIP_NONE) {
					current_animation = &forward;
				}
				position.x += speed;
			}

			break;
		case ST_WALK_BACKWARD:
			if (flip == SDL_FLIP_NONE)defense = true;
			if (wall && position.x < 100) {}
			else if (position.x < -(App->render->camera.x / 3)) {}
			else {

				if (flip == SDL_FLIP_HORIZONTAL) {
					current_animation = &forward;
				}
				if (flip == SDL_FLIP_NONE) {
					current_animation = &backward;
					
				}
				position.x -= speed;

			}

			break;
		case ST_JUMP_NEUTRAL:
			if (animstart == 0)
			{
				height2 = 15;

				current_animation = &jumpup;
				position.y -= jumpSpeed;

				if (position.y < 120) {
					jumpSpeed -= 0.5;
					if (jumpSpeed < 0) jumpSpeed = -6;
				}
				if (position.y >= initialPos && jumpSpeed < 0) {
					animstart = 1;
					position.y = initialPos;
					jumpSpeed = 6;
				}
			}


			break;
		case ST_JUMP_FORWARD:
			if (animstart == 0)
			{
				height2 = 15;

				current_animation = &jumpup;
				position.y -= jumpSpeed;
				if (wall && position.x > 100) {}
				else if (position.x + 60 > (-App->render->camera.x + 912) / 3) {}
				else {
					position.x += 3;
				}
				if (position.y < 120) {
					jumpSpeed -= 0.5;
					if (jumpSpeed < 0) jumpSpeed = -6;
				}
				if (position.y >= initialPos && jumpSpeed < 0) {
					animstart = 1;
					position.y = initialPos;
					jumpSpeed = 6;
				}
			}
			break;
		case ST_JUMP_BACKWARD:
			if (animstart == 0)
			{
				height2 = 15;
				current_animation = &jumpup;
				position.y -= jumpSpeed;
				if (wall && position.x < 100) {}
				else if (position.x < -(App->render->camera.x / 3)) {}
				else {
					position.x -= 3;
				}
				if (position.y < 120) {
					jumpSpeed -= 0.5;
					if (jumpSpeed < 0) jumpSpeed = -6;
				}
				if (position.y >= initialPos && jumpSpeed < 0) {
					animstart = 1;
					position.y = initialPos;
					jumpSpeed = 6;
				}
			}
			break;
			break;
		case ST_CROUCH:
			height = +20;
			if (animstart == 0)
			{
				current_animation = &crouch;

			}
		
			break;
		case ST_PUNCH_CROUCH:
			Damage = 25;
			if (flip == SDL_FLIP_NONE) {

				if (collider == true) {
					colliderAttack = App->collision->AddCollider({ position.x, position.y - 70 , 60, 30 }, COLLIDER_ENEMY_SHOT, this);
					App->music->PlayChunk(sword);
					collider = false;
				}

				if (colliderAttack != nullptr)
					colliderAttack->SetPos(position.x + 60, position.y - 40);
				if (animstart == 0)
				{
					current_animation = &crouchPunch;
				}
				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }

			}
			else if (flip == SDL_FLIP_HORIZONTAL) {

				if (collider == true) {
					colliderAttack = App->collision->AddCollider({ position.x, position.y - 70, 50, 70 }, COLLIDER_ENEMY_SHOT, this);
					App->music->PlayChunk(sword);
					collider = false;
				}

				if (colliderAttack != nullptr)
					colliderAttack->SetPos(position.x - 50, position.y - 70);
				if (animstart == 0)
				{
					current_animation = &crouchPunch;
				}
				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}
			break;
		case ST_DAMAGE:
			if (playsound)App->music->PlayChunk(hitted);
			playsound = false;
			if (animstart == 0)
			{
				current_animation = &hit;
				if (flip == SDL_FLIP_NONE) {
					if (!wall)position.x -= 3;
				}
				if (flip == SDL_FLIP_HORIZONTAL) {
					if (!wall)position.x += 3;
				}
				if (position.y != initialPos) {
					current_animation = &hit;
					jumpSpeed = 3;
					position.y += jumpSpeed;
				}
				else {

					if (current_animation->AnimationEnd() == true) { animstart = 1; App->input->inputs2.Push(IN_DAMAGE_FINISH_P2); playsound = true; }
				}
			}
			idle.Reset();
			crouch.Reset();
			forward.Reset();
			backward.Reset();
			jumpup.Reset();
			punch.Reset();
			kick.Reset();
			cyclone.Reset();
			break;
		case ST_BLOCK:
			current_animation = &block;
			if (current_animation->AnimationEnd() == true) { animstart = 1; App->input->inputs2.Push(IN_BLOCK_FINISH_P2); }
			break;
		case ST_PUNCH_STANDING:
			Damage = 25;
			if (flip == SDL_FLIP_NONE) {
				if (collider == true) {
					colliderAttack = App->collision->AddCollider({ 6000, 6000 , 100, 30 }, COLLIDER_ENEMY_SHOT, this);
					App->music->PlayChunk(sword);
					collider = false; 
					time = SDL_GetTicks();
				}
				if (SDL_GetTicks() - time > 150) {

					if (colliderAttack != nullptr)
						colliderAttack->SetPos(position.x + 30, position.y - 70);
				}
				if (animstart == 0)
				{
					current_animation = &punch;
					if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
				}
			}
			else if (flip == SDL_FLIP_HORIZONTAL) {
				if (collider == true) {
					colliderAttack = App->collision->AddCollider({ 6000, 6000, 100, 30 }, COLLIDER_ENEMY_SHOT, this);
					App->music->PlayChunk(sword);
					collider = false; time = SDL_GetTicks();
				}
				if (SDL_GetTicks() - time > 150) {
					if (colliderAttack != nullptr)
						colliderAttack->SetPos(position.x - 75, position.y - 70);
				}
				if (animstart == 0)
				{
					current_animation = &punch;
					if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
				}
			}
			break;
			
		case ST_PUNCH_NEUTRAL_JUMP:
			LOG("PUNCH NEUTRAL JUMP ++++\n");
		case ST_PUNCH_FORWARD_JUMP:
			LOG("PUNCH JUMP FORWARD ^>>+\n");
			break;
		case ST_PUNCH_BACKWARD_JUMP:
			LOG("PUNCH JUMP BACKWARD ^<<+\n");
			break;
		case ST_KICK_CROUCH:
			LOG("KICK CROUCHING **--\n");
			break;
		case ST_KICK_STANDING:
			Damage = 15;
			if (flip == SDL_FLIP_NONE) {
				if (collider == true) {
					colliderAttack = App->collision->AddCollider({ 6000, 6000, 40, 30 }, COLLIDER_ENEMY_SHOT, this);
					App->music->PlayChunk(kicks);
					collider = false; 
					time = SDL_GetTicks();
				}
				if (SDL_GetTicks() - time > 100) {
					if (colliderAttack != nullptr)
						colliderAttack->SetPos(position.x + 60, position.y-80);
				}
				if (animstart == 0)
				{
					current_animation = &kick;
					if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
				}
			}
			else if (flip == SDL_FLIP_HORIZONTAL) {

				if (collider == true) {
					colliderAttack = App->collision->AddCollider({ 6000, 6000, 40, 30 }, COLLIDER_ENEMY_SHOT, this);
					App->music->PlayChunk(kicks);
					collider = false; time = SDL_GetTicks();
				}
				if (SDL_GetTicks() - time > 100) {
					if (colliderAttack != nullptr)
						colliderAttack->SetPos(position.x - 40, position.y - 80);
				}
				if (animstart == 0)
				{
					current_animation = &kick;
					if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
				}

			}
			break;
		case ST_KICK_NEUTRAL_JUMP:
			LOG("KICK JUMP NEUTRAL ^^--\n");
			break;
		case ST_KICK_FORWARD_JUMP:
			LOG("KICK JUMP FORWARD ^>>-\n");
			break;
		case ST_KICK_BACKWARD_JUMP:
			LOG("KICK JUMP BACKWARD ^<<-\n");
			break;
		case ST_TORNADO:
			Damage = 30;
			if (shoot)
			{
				App->particles->AddParticle(App->particles->cyclone, position.x, position.y - 100, COLLIDER_ENEMY_SHOT, 450);
				App->music->PlayChunk(senpuu);
			}
			shoot = false;
			if (animstart == 0)
			{
				current_animation = &cyclone;
				if (current_animation->AnimationEnd() == true) { animstart = 1; }
			}
			break;
		case ST_WIN:
			current_animation = &win;
			break;
		case ST_DEFEAT:
			current_animation = &defeat;
			break;
		}
	}
	current_state = state;



	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {
		if (deletecol == true) {
			colliderPlayer2->to_delete = true;
			colliderPlayer2_2->to_delete = true;
			deletecol = false;
		}
		else {
			if (flip == SDL_FLIP_HORIZONTAL) {
				colliderPlayer2 = App->collision->AddCollider({ position.x + 60, position.y - 90, 47, 50 }, COLLIDER_ENEMY, this);
			}
			else {
				colliderPlayer2 = App->collision->AddCollider({ position.x + 45, position.y - 90, 47, 50 }, COLLIDER_ENEMY, this);
			}
			if (flip == SDL_FLIP_HORIZONTAL) {
				colliderPlayer2_2 = App->collision->AddCollider({ position.x + 60, position.y - 90, 35, 40 }, COLLIDER_ENEMY, this);
			}
			else {
				colliderPlayer2_2 = App->collision->AddCollider({ position.x + 45, position.y - 90, 35, 40 }, COLLIDER_ENEMY, this);
			}
			deletecol = true;
		}

	}


	if (App->player->position.x < position.x) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		flip = SDL_FLIP_NONE;
	}
	speed = 2;
	
	SDL_Rect r = current_animation->GetCurrentFrame();

	if (flip == SDL_FLIP_NONE) {
		App->render->Blit(graphics, position.x + /*Pivotex*/current_animation->pivotx[current_animation->returnCurrentFrame()], position.y - r.h + /*Pivotey*/ current_animation->pivoty[current_animation->returnCurrentFrame()], &r, flip);
	}
	if (flip == SDL_FLIP_HORIZONTAL) {
		App->render->Blit(graphics, position.x -10+/*Pivotex*/current_animation->pivotx2[current_animation->returnCurrentFrame()] * 2, position.y - r.h + /*Pivotey*/ current_animation->pivoty2[current_animation->returnCurrentFrame()], &r, flip);
	}
	if (flip == SDL_FLIP_HORIZONTAL) {
		if (colliderPlayer2 != nullptr)colliderPlayer2->SetPos(position.x + 9, position.y - 80 + height);
	}
	else {
		if (colliderPlayer2 != nullptr)colliderPlayer2->SetPos(position.x + 9, position.y - 80 + height);
	}

	if (flip == SDL_FLIP_HORIZONTAL) {
		if (colliderPlayer2_2 != nullptr)colliderPlayer2_2->SetPos(position.x + 15, position.y - 50 - height2);
	}
	else {
		if (colliderPlayer2_2 != nullptr)colliderPlayer2_2->SetPos(position.x + 15, position.y - 50 - height2);
	}
	return UPDATE_CONTINUE;
}

player_states ModulePlayer2::process_fsm(p2Qeue<player_inputs>& inputs) {
	static player_states state = ST_IDLE;
	player_inputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE:
		{
			if (SDL_GetTicks() - combotime < 200) {
				if (combo1 == 2)combo1 = 3;
			}
			switch (last_input)
			{
			case IN_RIGHT_DOWN_P2: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN_P2: state = ST_WALK_BACKWARD; break;
			case IN_JUMP_P2: state = ST_JUMP_NEUTRAL;  App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN_P2: state = ST_CROUCH; break;
			case IN_1_P2: if (combo1 == 3){ state = ST_TORNADO;  App->input->tornado_timer2 = SDL_GetTicks(); combo1 = 0; break; }
						  else { state = ST_PUNCH_STANDING;  App->input->punch_timer2 = SDL_GetTicks();  break; }
			case IN_2_P2: state = ST_KICK_STANDING;  App->input->kick_timer2 = SDL_GetTicks();  break;
			case IN_3_P2: state = ST_TORNADO;  App->input->tornado_timer2 = SDL_GetTicks();  break;
			case IN_DAMAGE_P2: state = ST_DAMAGE;  break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_WALK_FORWARD:
		{
			height2 = 0;
		if (flip == SDL_FLIP_NONE)	{if (SDL_GetTicks() - combotime < 120) {
				if (combo1 == 1)combo1 = 2;
				combotime = SDL_GetTicks();
			}}
			switch (last_input)
			{
			case IN_BLOCK_P2: state = ST_BLOCK; break;
			case IN_RIGHT_UP_P2: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT_P2: state = ST_IDLE; break;
			case IN_JUMP_P2: state = ST_JUMP_FORWARD;  App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN_P2: state = ST_CROUCH; break;
			case IN_1_P2: state = ST_PUNCH_STANDING;  App->input->punch_timer2 = SDL_GetTicks();  break;
			case IN_2_P2: state = ST_KICK_STANDING;  App->input->kick_timer2 = SDL_GetTicks();  break;
			case IN_3_P2: state = ST_TORNADO;  App->input->tornado_timer2 = SDL_GetTicks();  break;
			case IN_DAMAGE_P2: state = ST_DAMAGE;  break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_WALK_BACKWARD:
		{
			height2 = 0;

			if (flip == SDL_FLIP_HORIZONTAL) {
				if (SDL_GetTicks() - combotime < 120) {
					if (combo1 == 1)combo1 = 2;
					combotime = SDL_GetTicks();
				}
			}
			switch (last_input)
			{
			case IN_BLOCK_P2: state = ST_BLOCK; break;
			case IN_LEFT_UP_P2: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT_P2: state = ST_IDLE; break;
			case IN_JUMP_P2: state = ST_JUMP_BACKWARD;  App->input->jump_timer2 = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN_P2: state = ST_CROUCH; break;
			case IN_1_P2: state = ST_PUNCH_STANDING;  App->input->punch_timer2 = SDL_GetTicks();  break;
			case IN_2_P2: state = ST_KICK_STANDING;  App->input->kick_timer2 = SDL_GetTicks();  break;
			case IN_3_P2: state = ST_TORNADO;  App->input->tornado_timer2 = SDL_GetTicks();  break;
			case IN_DAMAGE_P2: state = ST_DAMAGE;  break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH_P2: state = ST_IDLE; animstart = 0; break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
				//	case IN_1: state = ST_PUNCH_NEUTRAL_JUMP;  App->input->punch_timer = SDL_GetTicks(); break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH_P2: state = ST_IDLE; animstart = 0; break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
				//	case IN_1: state = ST_PUNCH_FORWARD_JUMP;  App->input->punch_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH_P2: state = ST_IDLE; animstart = 0; break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
				//	case IN_1: state = ST_PUNCH_BACKWARD_JUMP;  App->input->punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH_P2: state = ST_IDLE;  break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH_P2: state = ST_IDLE;  break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_PUNCH_BACKWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH_P2: state = ST_IDLE;  break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH_P2: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		}
		break;
		case ST_KICK_STANDING:
		{
			switch (last_input)
			{
			case IN_KICK_FINISH_P2: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		}
		break;
		case ST_TORNADO:
			switch (last_input)
			{
			case IN_TORNADO_FINISH_P2: state = ST_IDLE; animstart = 0; shoot = true; break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
			break;

		case ST_CROUCH:
		{
			combotime = SDL_GetTicks();
			combo1 = 1;
			switch (last_input)
			{
			case IN_CROUCH_UP_P2: state = ST_IDLE; crouch.Reset(); break;
			case IN_1_P2: state = ST_PUNCH_CROUCH; App->input->punch_c_timer2 = SDL_GetTicks(); break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		}
		break;
		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_CROUCH_FINISH_P2: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE_P2: state = ST_DAMAGE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		break;
		}
		case ST_DAMAGE:
		{
			switch (last_input)
			{
			case IN_DAMAGE_FINISH_P2: state = ST_IDLE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
			break;
		}
		case ST_BLOCK:

			switch (last_input) {
			case IN_BLOCK_FINISH_P2: state = ST_IDLE; animstart = 0; break;
			case IN_WIN_P2: state = ST_WIN; break;
			case IN_DEFEAT_P2: state = ST_DEFEAT; break;
			}
		case ST_WIN:
			switch (last_input) {
			case IN_WIN_FINISH_P2: state = ST_IDLE; animstart = 0; break;
			}
			break;
		case ST_DEFEAT:
			switch (last_input) {
			case IN_DEFEAT_FINISH_P2: state = ST_IDLE; animstart = 0; break;
			}
			break;

		}
	}

	return state;
}



void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {

	if (colliderPlayer2 == c1 && c2->type == COLLIDER_WALL)
	{
		wall = true;
		if (flip == SDL_FLIP_HORIZONTAL)
			position.x -= speed * 2;
		if (flip == SDL_FLIP_NONE)
			position.x += speed * 2;
	}
	else { wall = false; }
	if (App->input->keyboard[SDL_SCANCODE_J]|| App->input->keyboard[SDL_SCANCODE_L] && colliderPlayer2 == c1 && c2->type == COLLIDER_PLAYER) {
	
		if (flip == SDL_FLIP_HORIZONTAL)
			App->player->position.x -= speed;
		if (flip == SDL_FLIP_NONE)
			App->player->position.x += speed;

	}
	
	
	if (colliderPlayer2 == c1 && c2->type == COLLIDER_PLAYER_SHOT && defense == false)
	{
		if(App->player->colliderAttack!=nullptr)
			App->player->colliderAttack->to_delete = true;
		App->ui->Health_Bar_p2 -= App->player->Damage;
		App->input->inputs2.Push(IN_DAMAGE_P2);
	}
	if (colliderPlayer2 == c1 && c2->type == COLLIDER_PLAYER_SHOT && defense == true) App->input->inputs2.Push(IN_BLOCK_P2); if (App->player->colliderAttack != nullptr)App->player->colliderAttack->to_delete = true;


}
