#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleUI.h"

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 208;
	
	position.y = 207;
	initialPos = position.y;

	idle.PushBack({ 7, 273, 75, 113 },		0.15,	0, 0, -1, 0);
	idle.PushBack({ 86, 275, 73, 111 },		0.15,	0, 0, 0, 0);
	idle.PushBack({ 164, 277, 72, 109 },	0.15,	0, 0, 0, 0);
	idle.PushBack({ 241, 279, 72, 107 },	0.15,	0, 0, 0, 0);

	crounch.PushBack({ 750, 432, 81, 121 }, 0.05, 0, 10, 0, 10);
	crounch.PushBack({ 840, 463, 99, 94}, 0.05, -26, 13, 0, 13);
	crounch.loop = false;

	forward.PushBack({ 506, 150, 69, 112 }, 0.1,	0, 0, 0, 0);
	forward.PushBack({ 580, 147, 59, 116 }, 0.25,	0, 0, 0, 0);
	forward.PushBack({ 644, 145, 57, 118 }, 0.1,	0, 0, 0, 0);
	forward.PushBack({ 706, 147, 62, 116 }, 0.25,	0, 0, 0, 0);
	forward.PushBack({ 773, 151, 70, 117 }, 0.1,	0, 0, 0, 0);
													
	backward.PushBack({ 4, 155, 82, 111 },	0.2,	0, 0, 0, 0);
	backward.PushBack({ 88, 152, 75, 114 },	0.2,	0, 0, 0, 0);
	backward.PushBack({ 165, 147, 69, 118 },0.2,	0, 0, 0, 0);
	backward.PushBack({ 236, 145, 66, 120 },0.2,	0, 0, 0, 0);
	backward.PushBack({ 304, 147, 70, 118 },0.2,	0, 0, 0, 0);
	backward.PushBack({ 376, 151, 75, 114 },0.2,	0, 0, 0, 0);
												
	jumpup.PushBack({ 363, 274, 60, 112 },	0.11,	0, 0, 0, 0);
	jumpup.PushBack({ 429, 295, 75, 91 },	0.11,	0, 0, 0, 0);
	jumpup.PushBack({ 510, 303, 76, 83 },	0.09,	0, 0, 0, 0);
	jumpup.PushBack({ 429, 295, 75, 91 },	0.11,	0, 0, 0, 0);
	jumpup.PushBack({ 363, 274, 60, 112 },	0.11,	0, 0, 0, 0);
														
	
	punch.PushBack({ 3, 0, 69, 127 }, 0.3, 0, 0, 0, 0);
	punch.PushBack({ 74, 30, 79, 97 }, 0.1, -10, 0, 0, 0);
	punch.PushBack({ 158, 33, 132, 94 }, 0.6, 0, 0, -20, 0);
	punch.PushBack({ 290, 33, 132, 94 }, 0.6, 0, 0, -20, 0);
	punch.PushBack({ 423, 42, 131, 85 }, 0.6, 0, 0, -20, 0);
	punch.PushBack({ 556, 44, 130, 94 }, 0.6, 0, 11, -20, 11);
	punch.PushBack({ 688, 44, 128, 94 }, 0.6, 0, 11, -20, 11);
	punch.PushBack({ 818, 44, 120, 94 }, 0.6, 0, 11, -16, 11);
	punch.PushBack({ 940, 44, 83, 94 }, 0.2, 0, 11, 4, 11);
	punch.PushBack({ 1025, 42, 131, 85 }, 0.1, 0, 0, -20, 0);
											
	kick.PushBack({ 647, 274, 58, 112 }, 0.2, 0, 0, 4, 0);
	kick.PushBack({ 710, 276, 53, 110 }, 0.1, 0, 0, 2, 0);
	kick.PushBack({ 768, 288, 94, 98 }, 0.1, 0, 0, -14, 0);
	kick.PushBack({ 867, 287, 97, 99 }, 0.1, 0, 0, -14, 0);
	kick.PushBack({ 969, 286, 82, 100 }, 0.2, 0, 0, -4, 0);
			
	cyclone.PushBack({ 8, 452, 90, 88 },	0.1,	0, 0, 0, 0);
	cyclone.PushBack({ 105, 451, 70, 89 },	0.2,	0, 0, 0, 0);
	cyclone.PushBack({ 181, 457, 73, 83 },	0.2,	0, 0, 0, 0);
	cyclone.PushBack({ 261, 449, 58, 91 },	0.2,	0, 0, 0, 0);
	cyclone.PushBack({ 326, 442, 94, 98 },	0.2,	0, 0, 0, 0);
	cyclone.PushBack({ 427, 387, 62, 153 }, 0.2,	0, 0, 0, 0);
	cyclone.PushBack({ 496, 442, 97, 98 },	0.2,  -20, 0, 0, 0);
	cyclone.PushBack({ 600, 450, 97, 90 },	0.08, -20, 0, 0, 0);

	hit.PushBack({ 982, 446, 92, 107 }, 0.08, -20, 10, 0, 10);

}

ModulePlayer::~ModulePlayer()
{}


bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;

	position.x = 208;
	position.y = 207;
	graphics = App->textures->Load("Assets/Image/Haohmaru Spritesheet.png");
	senpuu = App->music->LoadChunk("Assets/Sound/Haohmaru/attacks/senpuu.ogg");
	sword = App->music->LoadChunk("Assets/Sound/Common/Samurai Shodown - A- 01.wav");
	kicks = App->music->LoadChunk("Assets/Sound/Common/Samurai Shodown - KICK (MISS) - 01.wav");
	

	if (flip == SDL_FLIP_HORIZONTAL) {
		colliderPlayer = App->collision->AddCollider({ position.x+60, position.y - 90, 60, 90 }, COLLIDER_PLAYER, this);
	}
	else {
		colliderPlayer = App->collision->AddCollider({ position.x, position.y - 90, 60, 90 }, COLLIDER_PLAYER, this);
	}
	return ret;
}

bool ModulePlayer::CleanUp() {

	LOG("Unloading Player")
		if (colliderPlayer != nullptr) {
	colliderPlayer->to_delete = true;
		}
	position.x = 208;
	position.y = 207;
	App->textures->Unload(graphics);
	App->music->UnloadChunk(senpuu);
	App->music->UnloadChunk(sword);
	App->music->UnloadChunk(kicks);
	return true;
}

update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	player_states current_state = ST_UNKNOWN;
	player_states state = process_fsm(App->input->inputs);
if (state != current_state)
{
	switch (state)
	{
	case ST_IDLE:
	
		break;

	case ST_WALK_FORWARD:
		if (wall && position.x > 100 ) {}
		else if (position.x+60 > (-App->render->camera.x + 912) / 3) {}
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
			current_animation = &jumpup;
			position.y -= jumpSpeed;
			if (wall && position.x < 100) {}
			else if (position.x < -(App->render->camera.x / 3)) {}
			else {
				if (position.x) position.x -= 3;
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
	case ST_CROUCH:
		if (animstart == 0)
		{
			current_animation = &crounch;
			
		}

		LOG("CROUCHING ****\n");
		break;
	case ST_PUNCH_CROUCH:
		LOG("PUNCH CROUCHING **++\n");
		break;
	case ST_DAMAGE:
		
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
				
				if (current_animation->AnimationEnd() == true) { animstart = 1; App->input->inputs.Push(IN_DAMAGE_FINISH); }}
			}
		break;
	case ST_PUNCH_STANDING:
		if (flip == SDL_FLIP_NONE) {
			
			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ position.x, position.y - 70 , 70, 70 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(sword);
				collider = false;
			}

			if (colliderAttack != nullptr)
				colliderAttack->SetPos(position.x + 60, position.y - 70);
			if (animstart == 0)
			{
				current_animation = &punch;
				
				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}
			
		}
		else if (flip == SDL_FLIP_HORIZONTAL) {
			
			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ position.x, position.y - 70, 50, 70 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(sword);
				collider = false;
			}

			if (colliderAttack != nullptr)
				colliderAttack->SetPos(position.x -50, position.y - 70);
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
				current_animation = &kick;
				
				if (current_animation->AnimationEnd() == true) { animstart = 1; colliderAttack->to_delete = true; }
			}
		}
		else if (flip == SDL_FLIP_HORIZONTAL) {
		
			if (collider == true) {
				colliderAttack = App->collision->AddCollider({ position.x+100, position.y - 90, 40, 50 }, COLLIDER_PLAYER_SHOT, this);
				App->music->PlayChunk(kicks);
				collider = false;

			}

			if (colliderAttack != nullptr)
				colliderAttack->SetPos(position.x - 40, position.y - 90);
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
		if (shoot)
		{
		App->particles->AddParticle(App->particles->cyclone, position.x, position.y - 100, COLLIDER_PLAYER_SHOT, 450);
		App->music->PlayChunk(senpuu);
		}
		shoot = false;
		if (animstart == 0)
		{
			current_animation = &cyclone;
			if (current_animation->AnimationEnd() == true) { animstart = 1; }
		}
	}
}
current_state = state;


	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		if (deletecol == true) {
			colliderPlayer->to_delete = true;
			deletecol = false;
		}
		else {
			colliderPlayer=	App->collision->AddCollider({ position.x, position.y - 90, 60, 90 }, COLLIDER_PLAYER, this);
			deletecol = true;
		}
		
	}
	
	if (App->player2->position.x < position.x) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		flip = SDL_FLIP_NONE;
	}
	speed = 2; 
	wall = false;
	SDL_Rect r = current_animation->GetCurrentFrame();

	if (flip == SDL_FLIP_NONE){
	App->render->Blit(graphics, position.x + /*Pivotex*/current_animation->pivotx[current_animation->returnCurrentFrame()], position.y -r.h + /*Pivotey*/ current_animation->pivoty[current_animation->returnCurrentFrame()], &r, flip);
	}
	if (flip == SDL_FLIP_HORIZONTAL) {
		App->render->Blit(graphics, position.x -10 +/*Pivotex*/current_animation->pivotx2[current_animation->returnCurrentFrame()]*2, position.y - r.h + /*Pivotey*/ current_animation->pivoty2[current_animation->returnCurrentFrame()], &r, flip);
	}
	if (colliderPlayer != nullptr)colliderPlayer->SetPos(position.x, position.y - 90);
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
			if (SDL_GetTicks() - combotime < 200) {
				if (combo1 == 2)combo1 = 3;
			}
			switch (last_input)
			{
			case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
			case IN_JUMP: state = ST_JUMP_NEUTRAL;  App->input->jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_1: if (combo1 == 3) { state = ST_TORNADO;  App->input->tornado_timer = SDL_GetTicks(); combo1 = 0; break; }
					   else {
				state = ST_PUNCH_STANDING;  App->input->punch_timer = SDL_GetTicks();  break;
			}
			case IN_2: state = ST_KICK_STANDING;  App->input->kick_timer = SDL_GetTicks();  break;
			//case IN_3: state = ST_TORNADO;  App->input->tornado_timer = SDL_GetTicks();  break;
			case IN_DAMAGE: state = ST_DAMAGE;  break;
			}
		}
		break;

		case ST_WALK_FORWARD:
		{
			if (flip == SDL_FLIP_NONE) {
				if (SDL_GetTicks() - combotime < 120) {
					if (combo1 == 1)combo1 = 2;
					combotime = SDL_GetTicks();
				}
			}
	
			switch (last_input)
			{
			case IN_RIGHT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_FORWARD;  App->input->jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_1:  state = ST_PUNCH_STANDING;  App->input->punch_timer = SDL_GetTicks();  break; 
			case IN_2: state = ST_KICK_STANDING;  App->input->kick_timer = SDL_GetTicks();  break;
			//case IN_3: state = ST_TORNADO;  App->input->tornado_timer = SDL_GetTicks();  break;
			case IN_DAMAGE: state = ST_DAMAGE;  break;
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
			}
			switch (last_input)
			{
			case IN_LEFT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_BACKWARD;  App->input->jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_1: state = ST_PUNCH_STANDING;  App->input->punch_timer = SDL_GetTicks();  break;
			case IN_2: state = ST_KICK_STANDING;  App->input->kick_timer = SDL_GetTicks();  break;
			//case IN_3: state = ST_TORNADO;  App->input->tornado_timer = SDL_GetTicks();  break;
			case IN_DAMAGE: state = ST_DAMAGE;  break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; animstart = 0; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0; break;
				//	case IN_1: state = ST_PUNCH_NEUTRAL_JUMP;  App->input->punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; animstart = 0; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0; break;
				//	case IN_1: state = ST_PUNCH_FORWARD_JUMP;  App->input->punch_timer = SDL_GetTicks(); break;

			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; animstart = 0; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
				//	case IN_1: state = ST_PUNCH_BACKWARD_JUMP;  App->input->punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE;  break;
				case IN_DAMAGE: state = ST_DAMAGE;  break;
			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE;  break;
			case IN_DAMAGE: state = ST_DAMAGE;  break;
			}
		}
		break;

		case ST_PUNCH_BACKWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE;  break;
			case IN_DAMAGE: state = ST_DAMAGE;  break;
			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{

			case IN_PUNCH_FINISH: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			}
		}
		break;
		case ST_KICK_STANDING:
		{

			switch (last_input)
			{
			case IN_KICK_FINISH: state = ST_IDLE; animstart = 0; collider = true; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			}
		}
		break;
		case ST_TORNADO:
			switch (last_input)
			{
			case IN_TORNADO_FINISH: state = ST_IDLE; animstart = 0; shoot = true; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			}
			break;

		case ST_CROUCH:
		{
			combotime = SDL_GetTicks();
			combo1 = 1;
			switch (last_input)
			{
			case IN_CROUCH_UP: state = ST_IDLE; break;
			case IN_1: state = ST_PUNCH_CROUCH; App->input->punch_timer = SDL_GetTicks(); break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			}
		}
		break;
		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_DAMAGE: state = ST_DAMAGE; animstart = 0;  break;
			}
			break;
		}
		case ST_DAMAGE:
		{
			switch (last_input)
			{
			case IN_DAMAGE_FINISH: state = ST_IDLE; animstart = 0; break;
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
	if (colliderPlayer == c1 && c2->type == COLLIDER_ENEMY)
	{
	
		if (flip == SDL_FLIP_HORIZONTAL)
		position.x += App->player2->speed/2;
		if (flip == SDL_FLIP_NONE)
			position.x -= App->player2->speed/2;
	}
	if (colliderPlayer == c1 && c2->type == COLLIDER_ENEMY_SHOT)
	{
		if (App->player2->colliderAttack != nullptr)
			App->player2->colliderAttack->to_delete = true;
		App->ui->HealthBar_p1 -= App->player2->Damage;
		App->input->inputs.Push(IN_DAMAGE);
	
	}

}
