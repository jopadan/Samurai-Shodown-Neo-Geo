#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"
#include "ModulePlayer.h"
#include "ModulePetP1.h"
#include "ModuleParticles.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleSceneHaohmaru.h"
#include "ModuleSceneNakoruru.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleSlowdown.h"
#include "ModuleUI.h"

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 208;
	
	position.y = 207;
	initialPos = position.y;


	idle.PushBack({ 13, 1614, 65, 87 }, 0.15, 0, 0, 0, 0);
	idle.PushBack({ 82, 1614, 65, 87 }, 0.15, 1, 0, 0, 0);
	idle.PushBack({ 149, 1614, 65, 91 }, 0.15, 0, 4, 0, 4);
	idle.PushBack({ 214, 1612, 66, 91 }, 0.15, 0, 2, 0, 2);
	idle.PushBack({ 282, 1612, 67, 92 }, 0.15, 0, 1, -1, 1);
	idle.PushBack({ 349, 1612, 66, 91 }, 0.15, 0, 2, 0, 2);

	forward.PushBack({ 1176, 458, 47, 95 }, 0.1, 0, 2, 0, 0);
	forward.PushBack({ 1228, 458, 48, 94 }, 0.1, 0, 2, 0, 0);
	forward.PushBack({ 1280, 463, 53, 86 }, 0.2, 0, 2, 0, 0);
	forward.PushBack({ 1339, 467, 56, 91 }, 0.2, -2, 6, 0, 5);
	forward.PushBack({ 1394, 467, 46, 74 }, 0.2, -2, -4, 0, -2);
	forward.PushBack({ 1450, 463, 49, 89 }, 0.1, -2, 6, 0, 0);
	forward.PushBack({ 1498, 461, 48, 91 }, 0.1, 0, 2, 0, 0);

	backward.PushBack({ 325, 557, 55, 84 }, 0.1, 0, 0, 0, -1);
	backward.PushBack({ 76, 552, 45, 86 }, 0.25, 0, 0, 0, -1);
	backward.PushBack({ 122, 551, 49, 90 }, 0.1, 0, 0, 0, -1);
	backward.PushBack({ 175, 548, 47, 91 }, 0.25, 0, 0, 0, -1);
	backward.PushBack({ 222, 550, 47, 90 }, 0.1, 0, 2, 0, 1);
	backward.PushBack({ 271, 557, 54, 85 }, 0.1, 0, 2, 0, 1);

	crouch.PushBack({ 581, 628, 46, 80 }, 0.25, 3, 1, 3, 1);
	crouch.PushBack({ 16, 992, 51, 63 }, 0.1, 3, 7, 3, 7);
	crouch.loop = false;

	jumpup.PushBack({ 496, 1604, 60, 105 }, 0.11, 0, 0, 0, 0);
	jumpup.PushBack({ 556, 1606, 53, 103 }, 0.2, 0, 0, 0, 0);
	jumpup.PushBack({ 610, 1618, 50, 79 }, 0.2, 0, 0, 0, 0);
	jumpup.PushBack({ 660, 1623, 47, 71 }, 0.2, 0, 0, 0, 0);
	jumpup.PushBack({ 711, 1616, 44, 61 }, 0.2, 0, 0, 0, 0);
	jumpup.PushBack({ 556, 1606, 53, 103 }, 0.2, 0, 0, 0, 0);
	jumpup.PushBack({ 496, 1604, 60, 105 }, 0.11, 0, 0, 0, 0);
	jumpup.loop = false;

	hawk_carry.PushBack({ 64, 1547, 46, 56 }, 0.11, 0, 0, 7, 0);
	hawk_carry.PushBack({ 112, 1541, 43, 67 }, 0.11, 0, 0,7, 0);
	hawk_carry.PushBack({ 159, 1547, 42, 60 }, 0.11, 0, 0, 7, 0);
	hawk_carry.PushBack({ 204, 1546, 42, 60 }, 0.11, 0, 0, 7, 0);
	hawk_carry.PushBack({ 247, 1544, 41, 60 }, 0.11, 0, 0, 7, 0);
	//hawk_carry.PushBack({ 292, 1544, 47, 62 }, 0.11, 0, 0, 0, 0);
	//hawk_carry.PushBack({ 337, 1535, 51, 77 }, 0.11, 0, 0, 0, 0);
	hawk_carry.loop = false;

	punch.PushBack({ 11, 713, 103, 91 }, 0.4, 0, 2, -19, 2);
	punch.PushBack({ 117, 713, 89, 92 }, 0.4, 19, 0, -22, 0);
	punch.PushBack({ 204, 711, 97, 94 }, 0.4, 13, 0, -20, 0);
	punch.PushBack({ 303, 708, 93, 95 }, 0.4, 8, 0, -17, 0);
	punch.PushBack({ 395, 708, 101, 92 }, 0.3, -33, 0, 0, 0);

	
	mediumpunch.PushBack({ 851, 1030, 90, 98 }, 0.4, -21, -1, 0, -1);
	mediumpunch.PushBack({ 941, 1012, 74, 118 }, 0.4,  -2, -1, 0, -1);
	mediumpunch.PushBack({ 1020, 1011, 98, 120 }, 0.4, 11, 0, -19, 0);
	mediumpunch.PushBack({ 1119, 1018, 102, 112 }, 0.4, 10, 0, -20, 0);
	mediumpunch.PushBack({ 1221, 1022, 105, 107 }, 0.4, 6, 0, -20, 0);
	mediumpunch.PushBack({ 1325, 1020, 103, 111 }, 0.4, 5, 6, -18, 6);
	mediumpunch.PushBack({ 1424, 1017, 84, 106}, 0.4,   1, -1, -8, -1);

	//TO DO
	heavypunch.PushBack({ 807, 694, 57, 92 }, 0.04, 13, 0, 8, 0);
	heavypunch.PushBack({ 864, 691, 54, 95 }, 0.04, 13, 0, 8, 0);
	heavypunch.PushBack({ 917, 693, 62, 93 }, 0.04, 13, 0, 8, 0);
	heavypunch.PushBack({ 978, 693, 76, 94 }, 0.04, -3, 4, 0, 4);
	heavypunch.PushBack({ 1054, 672, 79, 110 }, 0.04, 6, 2, -4, 2);
	heavypunch.PushBack({ 1133, 673, 88, 111 }, 0.04, 16, 2, -11, 2);
	heavypunch.PushBack({ 1221, 680, 89, 106 }, 0.04, 23, 0, -14, 0);
	//heavypunch.PushBack({ 1307, 649, 84, 138 }, 0.04, 21, -1, 0, -1);
	//heavypunch.PushBack({ 1391, 646, 93, 136 }, 0.02, 10, 0, 0, 0);
	//heavypunch.PushBack({ 1484, 643, 64, 133 }, 0.02, 12, 0, 0, 0);

	//TO DO
	Annu.PushBack({ 15, 638, 78, 62 }, 0.02, 13, 0, -20, 0);
	Annu.PushBack({ 987, 162, 142, 51 }, 0.02, 13, 0, -20, 0);
	Annu.PushBack({ 240, 650, 142, 51 }, 0.2, 13, 0, -20, 0);

	kick.PushBack({ 14, 1061, 56, 98 }, 0.2, 0, 0, 4, 0);
	kick.PushBack({ 70, 1060, 53, 100 }, 0.1, 0, 0, 8, 0);
	kick.PushBack({ 121, 1061, 95, 98 }, 0.1, 0, 0, -14, 0);
	kick.PushBack({ 70, 1060, 53, 100 }, 0.1, 0, 0, 8, 0);
	kick.PushBack({ 14, 1061, 56, 98 }, 0.2, 0, 0, 4, 0);
	

	//TO DO
	mediumkick.PushBack({ 14, 1061, 56, 98 }, 0.01, 0, 0, 4, 0);
	


	//TO DO
	heavykick.PushBack({ 121, 1061, 95, 98 }, 0.01, 0, 0, -14, 0);
	
	//TO DO
	jumpPunch.PushBack({ 11, 713, 103, 91 }, 0.4, 0, 2, -19, 2);
	jumpPunch.PushBack({ 117, 713, 89, 92 }, 0.4, 19, 0, -22, 0);
	jumpPunch.PushBack({ 204, 711, 97, 94 }, 0.4, 13, 0, -20, 0);
	jumpPunch.PushBack({ 303, 708, 93, 95 }, 0.4, 8, 0, -17, 0);
	jumpPunch.PushBack({ 395, 708, 101, 92 }, 0.3, -33, 0, 0, 0);


	//To DO

	jumpPunchHeavy.PushBack({ 807, 694, 57, 92 }, 0.4, 13, 0, -20, 0);
	jumpPunchHeavy.PushBack({ 864, 691, 54, 95 }, 0.4, 13, 0, -20, 0);
	jumpPunchHeavy.PushBack({ 917, 693, 62, 93 }, 0.4, 13, 0, -20, 0);
	jumpPunchHeavy.PushBack({ 978, 693, 76, 94 }, 0.4, -3, 4, -20, 0);
	jumpPunchHeavy.PushBack({ 1054, 672, 79, 110 }, 0.4, 6, 2, -20, 0);
	jumpPunchHeavy.PushBack({ 1133, 673, 88, 111 }, 0.4, 16, 2, -20, 0);
	jumpPunchHeavy.PushBack({ 1221, 680, 89, 106 }, 0.4, 23, 0, -20, 0);
	jumpPunchHeavy.PushBack({ 1307, 649, 84, 138 }, 0.4, 21, -1, -20, 0);
	jumpPunchHeavy.PushBack({ 1391, 646, 93, 136 }, 0.2, 10, 0, -20, 0);
	jumpPunchHeavy.PushBack({ 1484, 643, 64, 133 }, 0.2, 12, 0, -20, 0);

	//TO DO
	jumpKick.PushBack({ 14, 1061, 56, 98 }, 0.2, 0, 0, 4, 0);
	jumpKick.PushBack({ 70, 1060, 53, 100 }, 0.1, 0, 0, 8, 0);
	jumpKick.PushBack({ 121, 1061, 95, 98 }, 0.1, 0, 0, -14, 0);
	jumpKick.PushBack({ 70, 1060, 53, 100 }, 0.1, 0, 0, 8, 0);
	jumpKick.PushBack({ 14, 1061, 56, 98 }, 0.2, 0, 0, 4, 0);


	//TO DO
	jumpKickHeavy.PushBack({ 14, 1061, 56, 98 }, 0.01, 0, 0, 4, 0);
	jumpKickHeavy.PushBack({ 14, 1061, 56, 98 }, 0.01, 0, 0, 4, 0);
	jumpKickHeavy.PushBack({ 14, 1061, 56, 98 }, 0.01, 0, 0, 4, 0);
	jumpKickHeavy.PushBack({ 14, 1061, 56, 98 }, 0.01, 0, 0, 4, 0);
	jumpKickHeavy.PushBack({ 14, 1061, 56, 98 }, 0.01, 0, 0, 4, 0);
	jumpKickHeavy.PushBack({ 14, 1061, 56, 98 }, 0.01, 0, 0, 4, 0);

	
	crouchPunch.PushBack({ 10, 1460, 53, 61 }, 0.2, 0, 4, 3, 4);
	crouchPunch.PushBack({ 62, 1462, 85, 65 }, 0.2, 0, 6, -8, 10);
	crouchPunch.PushBack({ 148, 1463, 86, 62 }, 0.2, 1, 6, -9, 8);
	crouchPunch.PushBack({ 235, 1466, 82, 60 }, 0.2, 4, 4, -10, 6);
	crouchPunch.PushBack({ 317, 1465, 66, 60 }, 0.2, 4, 4, -2, 7);

	hit.PushBack({ 1805, 51, 69, 98 }, 0.2, 0, 5, 0, 5);
	hit.PushBack({ 1876, 53, 73, 95 }, 0.08, 0, 5, 0, 5);



shadow.PushBack({ 659, 70, 70, 14 }, 1.8, 0, 0, 0, 0);
shadow.PushBack({ 733, 70, 70, 14 }, 1.8, 0, 0, 0, 0);
	
}

ModulePlayer::~ModulePlayer()
{}


bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	App->input->left = false;
	App->input->right = false;
	App->input->down = false;
	App->input->up = false;
	defeat.Reset();
	win.Reset();
	intro.Reset();

	position.x = 208;
	position.y = 207;
	graphics = App->textures->Load("Assets/Image/Nakoruru spritesheet.png");
	graphicsobj = App->textures->Load("Assets/Image/objectes.png");
	senpuu = App->music->LoadChunk("Assets/Sound/Haohmaru/attacks/senpuu.ogg");
	sword = App->music->LoadChunk("Assets/Sound/Common/Samurai Shodown - A- 01.wav");
	kicks = App->music->LoadChunk("Assets/Sound/Common/Samurai Shodown - KICK (MISS) - 01.wav");
	hitted = App->music->LoadChunk("Assets/Sound/Haohmaru/Samurai Shodown - Haohmaru - Hitted 8.wav");
	App->ui->HealthBar_p1 = 128;
	

	if (flip == SDL_FLIP_HORIZONTAL) {
		colliderPlayer = App->collision->AddCollider({ position.x+60, position.y - 90, 47, 50 }, COLLIDER_PLAYER, this);
	}
	else {
		colliderPlayer = App->collision->AddCollider({ position.x+45, position.y - 90, 47, 50 }, COLLIDER_PLAYER, this);
	}
	if (flip == SDL_FLIP_HORIZONTAL) {
		colliderPlayer_2 = App->collision->AddCollider({ position.x + 60, position.y - 90, 35, 40 }, COLLIDER_PLAYER, this);
	}
	else {
		colliderPlayer_2 = App->collision->AddCollider({ position.x + 45, position.y - 90, 35, 40 }, COLLIDER_PLAYER, this);
	}
	return ret;
}

bool ModulePlayer::CleanUp() {
	App->input->inputs.Push(IN_WIN_FINISH);
	App->input->inputs.Push(IN_DEFEAT_FINISH);

	LOG("Unloading Player")
		if (colliderPlayer != nullptr) {
	colliderPlayer->to_delete = true;
	colliderPlayer_2->to_delete = true;
		}
	position.x = 208;
	position.y = 207;
	App->textures->Unload(graphics);
	App->textures->Unload(graphicsobj);
	App->music->UnloadChunk(senpuu);
	App->music->UnloadChunk(sword);
	App->music->UnloadChunk(kicks);
	App->music->UnloadChunk(hitted);
	return true;
}

update_status ModulePlayer::Update()
{
	//LOG("%d", combo2);
	OnHawk = false;
	Animation* current_animation = &idle;  //&intro;
if (App->scene_nakoruru->matchstart == true) current_animation = &idle;

SDL_Rect r2 = shadow.GetCurrentFrame();
	App->render->Blit(graphicsobj, position.x, 201, &r2, SDL_FLIP_NONE);

	player_states current_state = ST_UNKNOWN;
	player_states state = process_fsm(App->input->inputs);
	if (wall == true){
	if (flip == SDL_FLIP_HORIZONTAL)
		position.x -= speed;
	if (flip == SDL_FLIP_NONE)
		position.x += speed;
	wall = false;
	}


if (state != current_state)
{
	if (state != ST_WALK_BACKWARD || state != ST_WALK_FORWARD) {
		defense = false;
	}
	switch (state)
	{
	case ST_IDLE:
		if (colliderAttack != nullptr) colliderAttack->to_delete = true; collider = true;
		jumpSpeed = 6;
		height = 0;
		height2 = 0;
		break;

	case ST_WALK_FORWARD:
		height2 = 0;
		if (flip == SDL_FLIP_HORIZONTAL)defense = true;
		if (wall && position.x > 100 ) {}
		else if (position.x+60 > (-App->render->camera.x + 912)) {}
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
		height2 = 0;
		if (flip == SDL_FLIP_NONE)defense = true;
		if (wall && position.x < 100) {}
		else if (position.x < -(App->render->camera.x)) {}
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
		height2 = 15;
		
		if (animstart == 0 || 2)
		{
			switch (jumpanim) {
			case 0:
				current_animation = &jumpup;
				break;
			case 1:
				if (animstart == 0) {
					current_animation = &jumpPunch;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			case 2:
				if (animstart == 0) {
					current_animation = &jumpPunchHeavy;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			case 3:
				if (animstart == 0) {
					current_animation = &jumpKick;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			case 4:
				if (animstart == 0) {
					current_animation = &jumpKickHeavy;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			}

			position.y -= jumpSpeed;
			if (position.y < 120) {
				jumpSpeed -= 0.5;
				if (jumpSpeed < 0) jumpSpeed = -6;
			}
			if (position.y >= initialPos) {
				animstart = 1;
				position.y = initialPos;
				jumpPunch.Reset();
				jumpPunchHeavy.Reset();
				jumpKick.Reset();
				jumpKickHeavy.Reset();

			}
		}
		
		
		break;
	case ST_JUMP_FORWARD:
		height2 = 15;
		dontflip = true;
		if (animstart == 0 || 2)
		{
			switch (jumpanim) {
			case 0:
				current_animation = &jumpup;
				break;
			case 1:
				if (animstart == 0) {
					current_animation = &jumpPunch;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			case 2:
				if (animstart == 0) {
					current_animation = &jumpPunchHeavy;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			case 3:
				if (animstart == 0) {
					current_animation = &jumpKick;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			case 4:
				if (animstart == 0) {
					current_animation = &jumpKickHeavy;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			}
			position.y -= jumpSpeed;
			if (wall && position.x > 100) {}
			else if (position.x + 60 > (-App->render->camera.x + 912)) {}
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
				jumpPunch.Reset();
				jumpPunchHeavy.Reset();
				jumpKick.Reset();
				jumpKickHeavy.Reset();
				dontflip = false;
			}
		}
		break;
	case ST_JUMP_BACKWARD:
		height2 = 15;
		dontflip = true;
		if (animstart == 0 || 2)
		{
			switch (jumpanim) {
			case 0:
				current_animation = &jumpup;
				break;
			case 1:
				if (animstart == 0) {
					current_animation = &jumpPunch;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			case 2:
				if (animstart == 0) {
					current_animation = &jumpPunchHeavy;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			case 3:
				if (animstart == 0) {
					current_animation = &jumpKick;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			case 4:
				if (animstart == 0) {
					current_animation = &jumpKickHeavy;
					if (collider == true) {
						colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
						App->music->PlayChunk(sword);
						collider = false;
						time = SDL_GetTicks();
					}
					if (SDL_GetTicks() - time > 150) {
						if (colliderAttack != nullptr)
							colliderAttack->SetPos(position.x + 30, position.y - 70);
					}
					if (current_animation->AnimationEnd() == true) { colliderAttack->to_delete = true; animstart = 2; collider = true; }

				}
				break;
			}
			position.y -= jumpSpeed;
			if (wall && position.x > 100) {}
			else if (position.x + 60 > (-App->render->camera.x + 912)) {}
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
				jumpPunch.Reset();
				jumpPunchHeavy.Reset();
				jumpKick.Reset();
				jumpKickHeavy.Reset();
				dontflip = false;
			}
		}
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
				colliderAttack = App->collision->AddCollider({ position.x-5, position.y - 40 , 60, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(sword);
				collider = false;
			}

			if (colliderAttack != nullptr)
				colliderAttack->SetPos(position.x + 50, position.y - 40);
			if (animstart == 0)
			{
				current_animation = &crouchPunch;
			}
			if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }

		}
		else if (flip == SDL_FLIP_HORIZONTAL) {

			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ position.x, position.y -50, 60, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(sword);
				collider = false;
			}

			if (colliderAttack != nullptr)
				colliderAttack->SetPos(position.x - 45, position.y - 40);
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
					if (!wall)position.x -= 4;
				}
				if (flip == SDL_FLIP_HORIZONTAL) {
					if (!wall)position.x += 4;
				}
				if (position.y != initialPos) {
					current_animation = &hit; 
					jumpSpeed = 3;
					position.y += jumpSpeed;
					
				}
				else {
				
					if (current_animation->AnimationEnd() == true) { animstart = 1; App->input->inputs.Push(IN_DAMAGE_FINISH); playsound = true; }
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
		if (current_animation->AnimationEnd() == true) { animstart = 1; App->input->inputs.Push(IN_BLOCK_FINISH); }
		break;

	case ST_PUNCH_STANDING:
		Damage = 25;
		if (flip == SDL_FLIP_NONE) {
			
			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
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
				colliderAttack = App->collision->AddCollider({ 6000,6000, 100, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(sword);
				collider = false;
			time = SDL_GetTicks();
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
	case ST_MEDIUM_PUNCH_STANDING:
		Damage = 25;
		if (flip == SDL_FLIP_NONE) {

			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
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
				current_animation = &mediumpunch;

				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}

		}
		else if (flip == SDL_FLIP_HORIZONTAL) {

			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ 6000,6000, 100, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(sword);
				collider = false;
				time = SDL_GetTicks();
			}
			if (SDL_GetTicks() - time > 150) {
				if (colliderAttack != nullptr)
					colliderAttack->SetPos(position.x - 75, position.y - 70);
			}
			if (animstart == 0)
			{
				current_animation = &mediumpunch;

				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}

		}
		break;

	case ST_HEAVY_PUNCH_STANDING:
		Damage = 25;
		if (flip == SDL_FLIP_NONE) {

			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ 3000, 3000 , 100, 30 }, COLLIDER_PLAYER_SHOT, this);
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
				current_animation = &heavypunch;

				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}

		}
		else if (flip == SDL_FLIP_HORIZONTAL) {

			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ 6000,6000, 100, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(sword);
				collider = false;
				time = SDL_GetTicks();
			}
			if (SDL_GetTicks() - time > 150) {
				if (colliderAttack != nullptr)
					colliderAttack->SetPos(position.x - 75, position.y - 70);
			}
			if (animstart == 0)
			{
				current_animation = &heavypunch;
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
		Damage = 15;
		if (flip == SDL_FLIP_NONE) {
			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ position.x, position.y - 90, 40, 50 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(kicks);
				collider = false;
			}

			if (colliderAttack != nullptr)
				colliderAttack->SetPos(position.x + 60, position.y - 90);

			if (animstart == 0)
			{
				current_animation = &crouchKick;

				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}
		}
		else if (flip == SDL_FLIP_HORIZONTAL) {

			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ position.x + 100, position.y - 90, 40, 50 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(kicks);
				collider = false;

			}

			if (colliderAttack != nullptr)
				colliderAttack->SetPos(position.x - 40, position.y - 90);
			if (animstart == 0)
			{
				current_animation = &crouchKick;

				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}

		}
		break;
		break;
	case ST_KICK_STANDING:
		Damage = 15;
		if (flip == SDL_FLIP_NONE) {
			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ 3000, 3000, 40, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(kicks);
				collider = false;
				time = SDL_GetTicks();
			}
			if (SDL_GetTicks()-time > 100){
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
				colliderAttack = App->collision->AddCollider({ 3000, 3000, 40, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(kicks);
				collider = false;

			}

			if (colliderAttack != nullptr)
				colliderAttack->SetPos(position.x - 40, position.y - 80);
			if (animstart == 0)
			{
				current_animation = &kick;
			
				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}
		
		}
		break;

	case ST_MEDIUM_KICK_STANDING:
		Damage = 15;
		if (flip == SDL_FLIP_NONE) {
			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ 3000, 3000, 40, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(kicks);
				collider = false;
				time = SDL_GetTicks();
			}
			if (SDL_GetTicks() - time > 100) {
				if (colliderAttack != nullptr)
					colliderAttack->SetPos(position.x + 60, position.y - 80);
			}
			if (animstart == 0)
			{
				current_animation = &mediumkick;

				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}
		}
		else if (flip == SDL_FLIP_HORIZONTAL) {

			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ 3000, 3000, 40, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(kicks);
				collider = false;

			}

			if (colliderAttack != nullptr)
				colliderAttack->SetPos(position.x - 40, position.y - 80);
			if (animstart == 0)
			{
				current_animation = &mediumkick;

				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}

		}
		break;
	case ST_HEAVY_KICK_STANDING:
		Damage = 15;
		if (flip == SDL_FLIP_NONE) {
			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ 3000, 3000, 40, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(kicks);
				collider = false;
				time = SDL_GetTicks();
			}
			if (SDL_GetTicks() - time > 100) {
				if (colliderAttack != nullptr)
					colliderAttack->SetPos(position.x + 60, position.y - 80);
			}
			if (animstart == 0)
			{
				current_animation = &heavykick;

				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}
		}
		else if (flip == SDL_FLIP_HORIZONTAL) {

			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ 3000, 3000, 40, 30 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(kicks);
				collider = false;

			}

			if (colliderAttack != nullptr)
				colliderAttack->SetPos(position.x - 40, position.y - 80);
			if (animstart == 0)
			{
				current_animation = &heavykick;

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
	case ST_LEYLA_MUTSUBE:
		current_animation = &Annu;
		dontflip = true;
		if (flip == 0) {
			position.x += mutsubespeed;
			mutsubespeed -= 0.01;
		}
		if (flip == 1) {
			position.x -= mutsubespeed;
			mutsubespeed -= 0.01;
		}
		position.y -= 0.1;
		break;

	case ST_HAWKCARRY:
		OnHawk = true;
		if (jumptoHawk == true) {
			if (flip == SDL_FLIP_NONE){
			if (App->pet->position.x < position.x) {
				position.x -= 3;
			}
			else if (App->pet->position.y < position.y) {
				position.y -= 6;
			}
			else {
				jumptoHawk = false;
			}
			}
			if (flip == SDL_FLIP_HORIZONTAL) {
				if (App->pet->position.x > position.x) {
					position.x += 3;
				}
				else if (App->pet->position.y < position.y) {
					position.y -= 6;
				}
				else {
					jumptoHawk = false;
				}
			}
		}
		else{
			position.x = App->pet->position.x;
			position.y = App->pet->position.y+50;
		}
		if (animstart == 0)
		{
			current_animation = &hawk_carry;
			if (current_animation->AnimationEnd() == true) {
				
			
			}
		}
		
		break;
	case ST_ANNU_MUTSUBE:
		current_animation = &Annu;
		dontflip = true;
		if(flip == 0){
			position.x += mutsubespeed;
			mutsubespeed -= 0.03;
		}
		if (flip == 1) {
			position.x -= mutsubespeed;
			mutsubespeed -= 0.03;
		}
			break;
	case ST_YATORO_POKU:
		
		if(position.y<initialPos){ position.y+=10; }
		else {
			position.y = initialPos;
		}
		break;
	case ST_KAMUI_MUTSUBE:
		
		if (position.y<initialPos) { 
			position.y += 10;
			if (flip == SDL_FLIP_NONE)position.x+=5;
			if (flip == SDL_FLIP_HORIZONTAL)position.x -= 5;
		}
		else {
			position.y = initialPos;
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
if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
if (deletecol == true) {
	colliderPlayer->to_delete = true;
	colliderPlayer_2->to_delete = true;
	deletecol = false;
}
else {
		if (flip == SDL_FLIP_HORIZONTAL) {
			colliderPlayer = App->collision->AddCollider({ position.x + 60, position.y - 90, 47, 50 }, COLLIDER_PLAYER, this);
		}
		else {
			colliderPlayer = App->collision->AddCollider({ position.x + 45, position.y - 90, 47, 50 }, COLLIDER_PLAYER, this);
		}
		if (flip == SDL_FLIP_HORIZONTAL) {
			colliderPlayer_2 = App->collision->AddCollider({ position.x + 60, position.y - 90, 35, 40 }, COLLIDER_PLAYER, this);
		}
		else {
			colliderPlayer_2 = App->collision->AddCollider({ position.x + 45, position.y - 90, 35, 40 }, COLLIDER_PLAYER, this);
		}
		deletecol = true;}

	}
	
if (App->player2->position.x < position.x && dontflip == false) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		if(dontflip == false)flip = SDL_FLIP_NONE;
	}
	speed = 2; 
	
	SDL_Rect r = current_animation->GetCurrentFrame();

	if (flip == SDL_FLIP_NONE){

	App->render->Blit(graphics, position.x + /*Pivotex*/current_animation->pivotx[current_animation->returnCurrentFrame()], position.y -r.h + /*Pivotey*/ current_animation->pivoty[current_animation->returnCurrentFrame()], &r, flip);
  
	
	}
	if (flip == SDL_FLIP_HORIZONTAL) {
		App->render->Blit(graphics, position.x -10 +/*Pivotex*/current_animation->pivotx2[current_animation->returnCurrentFrame()]*2, position.y - r.h + /*Pivotey*/ current_animation->pivoty2[current_animation->returnCurrentFrame()], &r, flip);
	}
	if (flip == SDL_FLIP_HORIZONTAL) {
		if (colliderPlayer != nullptr)colliderPlayer->SetPos(position.x +9, position.y - 80 + height);
	}
	else {
		if (colliderPlayer != nullptr)colliderPlayer->SetPos(position.x+9, position.y - 80 + height);
	}
	if (flip == SDL_FLIP_HORIZONTAL) {
		if (colliderPlayer_2 != nullptr)colliderPlayer_2->SetPos(position.x + 15, position.y - 50 - height2);
	}
	else {
		if (colliderPlayer_2 != nullptr)colliderPlayer_2->SetPos(position.x + 15, position.y - 50 - height2);
	}
	return UPDATE_CONTINUE;
}


player_states ModulePlayer::process_fsm(p2Qeue<player_inputs>& inputs) {
	static player_states state = ST_IDLE;
	player_inputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE:
		{

			switch (last_input)
			{
			case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
			case IN_JUMP: state = ST_JUMP_NEUTRAL;  App->input->jump_timer = SDL_GetTicks(); jumptimer = SDL_GetTicks(); break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_1:
				if (SDL_GetTicks() - combotime < 120) {
					if (combo1 == 2)combo1 = 3;
				}
				if (combo1 == 3) { state = ST_LEYLA_MUTSUBE; mutsubespeed = 5; App->input->AnnuM_timer = SDL_GetTicks(); combo1 = 0; break; }
				else {
					state = ST_PUNCH_STANDING;  App->input->punch_timer = SDL_GetTicks();  break;
				}

			case IN_3:
				if (SDL_GetTicks() - combotime < 120) {
					if (HawkCarryCombo == 2)HawkCarryCombo = 3;
				}
				if (HawkCarryCombo == 3) { state = ST_HAWKCARRY; App->input->hawk_carry_timer = SDL_GetTicks(); HawkCarryCombo = 0; break; }
				else {
					state = ST_KICK_STANDING;  App->input->kick_timer = SDL_GetTicks();  break;
				}

			case IN_2:if (SDL_GetTicks() - combotime < 120) {
				if (combo1 == 2)combo1 = 3;
			}
					  if (combo1 == 3) { state = ST_LEYLA_MUTSUBE; mutsubespeed = 5; App->input->AnnuM_timer = SDL_GetTicks(); combo1 = 0; break; }
					  else {
						  state = ST_MEDIUM_PUNCH_STANDING;  App->input->med_punch_timer = SDL_GetTicks();  break;
					  }

			case IN_4: if (SDL_GetTicks() - combotime < 120) {
				if (HawkCarryCombo == 2)HawkCarryCombo = 3;
			}
					   if (HawkCarryCombo == 3) { state = ST_HAWKCARRY; App->input->hawk_carry_timer = SDL_GetTicks(); HawkCarryCombo = 0; break; }
					   else {
						   state = ST_MEDIUM_KICK_STANDING;  App->input->med_kick_timer = SDL_GetTicks();  break;
					   }
			case IN_DAMAGE: state = ST_DAMAGE;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_WALK_FORWARD:
		{

			if (flip == SDL_FLIP_NONE) {
				if (SDL_GetTicks() - combotime < 120) {
					if (combo1 == 1)combo1 = 2;
					
				}
				else { combo1 = 0;
				
				}
				combo3 = 1;
				combotimeAmube = SDL_GetTicks();
			}
			if (flip == SDL_FLIP_HORIZONTAL) {
				combotimeAnnu = SDL_GetTicks();
				combo2 = 1;

				if (SDL_GetTicks() - combotime < 120) {

					if (HawkCarryCombo == 1)HawkCarryCombo = 2;
					combotime = SDL_GetTicks();
				}
				else { HawkCarryCombo = 0; }

				if (SDL_GetTicks() - combotimeAmube < 120) {
					if (combo3 == 2)combo3 = 3;
					combotimeAmube = SDL_GetTicks();
				}
			}


			switch (last_input)
			{
			case IN_BLOCK: state = ST_BLOCK; break;
			case IN_RIGHT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_FORWARD; jumptimer = SDL_GetTicks();  App->input->jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_1:
				if (SDL_GetTicks() - combotime < 120) {
					if (combo1 == 2)combo1 = 3;
				}
				if (SDL_GetTicks() - combotimeAmube < 120) {
					if (combo3 == 3)combo3 = 4;
				}
				if (combo1 == 3) { state = ST_LEYLA_MUTSUBE; mutsubespeed = 5; App->input->AnnuM_timer = SDL_GetTicks(); combo1 = 0; break; }
				else if (combo3 == 4) {
					LOG("Amube Yatoro");
				}

				else {
					state = ST_PUNCH_STANDING;  App->input->punch_timer = SDL_GetTicks();  break;
				}
				break;


			case IN_3:
				if (SDL_GetTicks() - combotime < 120) {
					if (HawkCarryCombo == 2)HawkCarryCombo = 3;
				}
				if (HawkCarryCombo == 3) { state = ST_HAWKCARRY; App->input->hawk_carry_timer = SDL_GetTicks(); HawkCarryCombo = 0; break; }
				else {
					state = ST_KICK_STANDING;  App->input->kick_timer = SDL_GetTicks();  break;
				}

			case IN_2:if (SDL_GetTicks() - combotime < 120) {
				if (combo1 == 2)combo1 = 3;
			}
					  if (combo1 == 3) { state = ST_LEYLA_MUTSUBE; mutsubespeed = 5; App->input->AnnuM_timer = SDL_GetTicks(); combo1 = 0; break; }
					  else {
						  state = ST_MEDIUM_PUNCH_STANDING;  App->input->med_punch_timer = SDL_GetTicks();  break;
					  }

			case IN_4: if (SDL_GetTicks() - combotime < 120) {
				if (HawkCarryCombo == 2)HawkCarryCombo = 3;
			}
					   if (HawkCarryCombo == 3) { state = ST_HAWKCARRY; App->input->hawk_carry_timer = SDL_GetTicks(); HawkCarryCombo = 0; break; }
					   else {
						   state = ST_MEDIUM_KICK_STANDING;  App->input->med_kick_timer = SDL_GetTicks();  break;
					   }
			case IN_DAMAGE: state = ST_DAMAGE;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_WALK_BACKWARD:
		{

			if (flip == SDL_FLIP_HORIZONTAL) {
				if (SDL_GetTicks() - combotime < 120) {
					if (combo1 == 1)combo1 = 2;
					combotime = SDL_GetTicks();
				}
				combo3 = 1;
				combotimeAmube = SDL_GetTicks();
			}
			else { combo1 = 0; }

			if (flip == SDL_FLIP_NONE) {
				combotimeAnnu = SDL_GetTicks();
				combo2 = 1;

				if (SDL_GetTicks() - combotimeAmube < 120) {
					if (combo3 == 2)combo3 = 3;
					combotimeAmube = SDL_GetTicks();
				}

				if (SDL_GetTicks() - combotime < 120) {
					if (HawkCarryCombo == 1)HawkCarryCombo = 2;
					combotime = SDL_GetTicks();
				}
				else { HawkCarryCombo = 0; }

			}



			switch (last_input)
			{
			case IN_BLOCK: state = ST_BLOCK; break;
			case IN_LEFT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_BACKWARD; jumptimer = SDL_GetTicks(); App->input->jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_1:
				if (SDL_GetTicks() - combotime < 120) {
					if (combo1 == 2)combo1 = 3;
				}
				if (SDL_GetTicks() - combotimeAmube < 120) {
					if (combo3 == 3)combo3 = 4;
				}
				if (combo1 == 3) { state = ST_LEYLA_MUTSUBE; mutsubespeed = 5; App->input->AnnuM_timer = SDL_GetTicks(); combo1 = 0; break; }
				else if (combo3 == 4) {
					LOG("Amube Yatoro");
				}

				else {
					state = ST_PUNCH_STANDING;  App->input->punch_timer = SDL_GetTicks();  break;
				}
				break;

			case IN_3:
				if (SDL_GetTicks() - combotime < 120) {
					if (HawkCarryCombo == 2)HawkCarryCombo = 3;
				}
				if (HawkCarryCombo == 3) { LOG("why tho"); state = ST_HAWKCARRY; App->input->hawk_carry_timer = SDL_GetTicks(); HawkCarryCombo = 0; break; }
				else {
					state = ST_KICK_STANDING;  App->input->kick_timer = SDL_GetTicks();  break;
				}

			case IN_2:if (SDL_GetTicks() - combotime < 120) {
				if (combo1 == 2)combo1 = 3;
			}
					  if (combo1 == 3) { state = ST_LEYLA_MUTSUBE; mutsubespeed = 5; App->input->AnnuM_timer = SDL_GetTicks(); combo1 = 0; break; }
					  else {
						  state = ST_MEDIUM_PUNCH_STANDING;  App->input->med_punch_timer = SDL_GetTicks();  break;
					  }

			case IN_4: if (SDL_GetTicks() - combotime < 120) {
				if (HawkCarryCombo == 2)HawkCarryCombo = 3;
			}
					   if (HawkCarryCombo == 3) { state = ST_HAWKCARRY; App->input->hawk_carry_timer = SDL_GetTicks(); HawkCarryCombo = 0; break; }
					   else {
						   state = ST_MEDIUM_KICK_STANDING;  App->input->med_kick_timer = SDL_GetTicks();  break;
			}
			case IN_DAMAGE: state = ST_DAMAGE;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; animstart = 0; jumpanim = 0; collider = false; jumpup.Reset(); break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0; jumpanim = 0; break;
			case IN_LEFT_DOWN: if (initialPos - position.y < 50) state = ST_JUMP_BACKWARD;  jumptimer = SDL_GetTicks(); App->input->jump_timer = SDL_GetTicks();   break;
			case IN_RIGHT_DOWN: if (initialPos - position.y < 50) state = ST_JUMP_FORWARD; jumptimer = SDL_GetTicks();  App->input->jump_timer = SDL_GetTicks();  break;
				//	case IN_1: state = ST_PUNCH_NEUTRAL_JUMP;  App->input->punch_timer = SDL_GetTicks(); break;
			case IN_WIN: state = ST_WIN; jumpanim = 0;  break;
			case IN_DEFEAT: state = ST_DEFEAT; jumpanim = 0; break;
			case IN_1: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 1; } break;
			case IN_2: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 2; } break;
			case IN_3: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 3; }break;
			case IN_4: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 4; } break;
			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			
			switch (last_input)
			{
			case IN_1: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 1; }break;
			case IN_2: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 2; } break;
			case IN_3: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 3; }break;
			case IN_4: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 4; } break;
			case IN_JUMP_FINISH: state = ST_IDLE; animstart = 0; jumpanim = 0; collider = false; jumpup.Reset(); break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0; jumpanim = 0; break;
			case IN_WIN: state = ST_WIN; jumpanim = 0; break;
			case IN_DEFEAT: state = ST_DEFEAT; jumpanim = 0; break;
			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			
			switch (last_input)
			{
			case IN_1: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 1; }break;
			case IN_2: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 2; } break;
			case IN_3: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 3; }break;
			case IN_4: if (SDL_GetTicks() - jumptimer > 300) { if (jumpanim == 0)jumpanim = 4; } break;
			case IN_JUMP_FINISH: state = ST_IDLE; animstart = 0; jumpanim = 0; collider = false; jumpup.Reset(); break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0; jumpanim = 0; break;
				//	case IN_1: state = ST_PUNCH_BACKWARD_JUMP;  App->input->punch_timer = SDL_GetTicks(); break;
			case IN_WIN: state = ST_WIN; jumpanim = 0; break;
			case IN_DEFEAT: state = ST_DEFEAT; jumpanim = 0; break;
			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_2: state = ST_HEAVY_PUNCH_STANDING; App->input->heavy_punch_timer = SDL_GetTicks(); collider = true; break;
			case IN_PUNCH_FINISH: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_MEDIUM_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_1: state = ST_HEAVY_PUNCH_STANDING; App->input->heavy_punch_timer = SDL_GetTicks(); collider = true; break;
			case IN_PUNCH_FINISH: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
		}
		break;
		case ST_HEAVY_PUNCH_STANDING:
		{
			switch (last_input)
			{
			
			case IN_PUNCH_FINISH: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_KICK_STANDING:
		{

			switch (last_input)
			{
			case IN_4: state = ST_HEAVY_KICK_STANDING; App->input->heavy_kick_timer = SDL_GetTicks(); collider = true; break;
			case IN_KICK_FINISH: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
		}
		break;
		case ST_MEDIUM_KICK_STANDING: {

			switch (last_input)
			{
			case IN_3: state = ST_HEAVY_KICK_STANDING; App->input->heavy_kick_timer = SDL_GetTicks(); collider = true; break;
			case IN_KICK_FINISH: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
		}
		break;
		case ST_HEAVY_KICK_STANDING:
		{
			switch (last_input)
			{

			case IN_KICK_FINISH: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
		}
		break;

		case ST_LEYLA_MUTSUBE:
			switch (last_input)
			{
			case IN_ANNU_MUTSUBE_FINISH: state = ST_IDLE; dontflip = false; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			}
			break;
		case ST_HAWKCARRY:
			switch (last_input)
			{
			case IN_HAWK_CARRY_FINISH: state = ST_JUMP_NEUTRAL; App->input->jump_timer = SDL_GetTicks(); animstart = 0; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			case IN_1: 
			case IN_2:
			case IN_3:
			case IN_4:
				if (hawkleft || hawkright) state = ST_YATORO_POKU; App->input->Yatoro_timer = SDL_GetTicks();break;
				if (hawkdown) state = ST_KAMUI_MUTSUBE; App->input->Kamui_timer = SDL_GetTicks(); break;

		}
		break;

		case ST_ANNU_MUTSUBE:
			switch (last_input)
			{
			case IN_ANNU_MUTSUBE_FINISH: state = ST_IDLE; dontflip = false; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			}
			break;

		case ST_YATORO_POKU:
			switch (last_input)
			{
			case IN_YATORO_POKU_FINISH: state = ST_IDLE; dontflip = false; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			}
			break;
		case ST_KAMUI_MUTSUBE:
			switch (last_input)
			{
			case IN_KAMUI_MUTSUBE_FINISH: state = ST_IDLE; dontflip = false; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			}
			break;

		case ST_CROUCH:
		{
			combo1 = 1;
			HawkCarryCombo = 1;
			combotime = SDL_GetTicks();


			if (SDL_GetTicks() - combotimeAnnu < 120) {
				if (combo2 == 1)combo2 = 2;
				combotimeAnnu = SDL_GetTicks();
			}
			if (SDL_GetTicks() - combotimeAmube < 120) {
				if (combo3 == 1)combo3 = 2;
				combotimeAmube = SDL_GetTicks();
			}
			//else (combotimeAnnu = 0);

			switch (last_input)
			{
			case IN_CROUCH_UP: state = ST_IDLE; crouch.Reset();  break;
			case IN_1:
				if (SDL_GetTicks() - combotimeAnnu < 120) {
					if (combo2 == 2)combo2 = 3;
				}
				
				if (combo2 == 3) { mutsubespeed = 5; state = ST_ANNU_MUTSUBE; App->input->AnnuM_timer = SDL_GetTicks(); combo2 = 0; break; }
				else {
					state = ST_PUNCH_CROUCH; App->input->punch_c_timer = SDL_GetTicks(); combo2 = 0; animstart = 0; break;
				}
				break;
			case IN_2:
				if (SDL_GetTicks() - combotimeAnnu < 120) {
					if (combo2 == 2)combo2 = 3;
				}

				if (combo2 == 3) { mutsubespeed = 5; state = ST_ANNU_MUTSUBE; App->input->AnnuM_timer = SDL_GetTicks(); combo2 = 0; break; }
				break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
				break;
			}
		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_CROUCH_FINISH: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
			break;
		}
		case ST_DAMAGE:
		{
			switch (last_input)
			{
			case IN_DAMAGE_FINISH: state = ST_IDLE; animstart = 0; break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
			break;
		}
		case ST_BLOCK:

			switch (last_input) {
			case IN_BLOCK_FINISH: state = ST_IDLE; animstart = 0; break;
			case IN_WIN: state = ST_WIN; break;
			case IN_DEFEAT: state = ST_DEFEAT; break;
			}
		case ST_WIN:
			switch (last_input) {
			case IN_WIN_FINISH: state = ST_IDLE; animstart = 0; break;
			}
			break;
		case ST_DEFEAT:
			switch (last_input) {
			case IN_DEFEAT_FINISH: state = ST_IDLE; animstart = 0; break;
			}
			break;

		}
		}
	}
	return state;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {

	if (colliderPlayer == c1 && c2->type== COLLIDER_WALL)
	{
		wall = true;
	}

	if (App->input->right == true && colliderPlayer == c1 && c2->type == COLLIDER_ENEMY) {
		if (flip == SDL_FLIP_NONE && position.x < 490) {

			App->player2->position.x += speed;
		}
	}
	if (App->input->left == true && colliderPlayer == c1 && c2->type == COLLIDER_ENEMY) {
		if (flip == SDL_FLIP_HORIZONTAL && position.x > 88) {
			App->player2->position.x -= speed;
		}
	}
	
	
	if (colliderPlayer == c1 && c2->type == COLLIDER_ENEMY_SHOT && defense == false)
	{
		if (App->player2->colliderAttack != nullptr){
			App->player2->colliderAttack->to_delete = true;}
		App->ui->HealthBar_p1 -= App->player2->Damage;
		App->slowdown->StartSlowdown(600, 40);
		App->render->StartCameraShake(300, 3);
		App->input->inputs.Push(IN_DAMAGE);
	
		
	}
if (colliderPlayer == c1 && c2->type == COLLIDER_ENEMY_SHOT && defense == true) App->input->inputs.Push(IN_BLOCK); if (App->player2->colliderAttack != nullptr) App->player2->colliderAttack->to_delete = true;
}
