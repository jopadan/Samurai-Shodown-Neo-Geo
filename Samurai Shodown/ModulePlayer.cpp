#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 100;
	position.y = 207;
	initialPos = position.y;

	idle.PushBack({ 7, 273, 75, 113 }, 0.15, 0, 0);
	idle.PushBack({ 86, 275, 73, 111 }, 0.15, 0, 0);
	idle.PushBack({ 164, 277, 72, 109 }, 0.15, 0, 0);
	idle.PushBack({ 241, 279, 72, 107 }, 0.15, 0, 0);
	
	forward.PushBack({ 506, 150, 69, 112 }, 0.1, 0, 0);
	forward.PushBack({ 580, 147, 59, 116 }, 0.25, 0, 0);
	forward.PushBack({ 644, 145, 57, 118 }, 0.1, 0, 0);
	forward.PushBack({ 706, 147, 62, 116 }, 0.25, 0, 0);
	forward.PushBack({ 773, 151, 70, 117 }, 0.1, 0, 0);
	
	backward.PushBack({ 4, 155, 82, 111 }, 0.2, 0, 0);
	backward.PushBack({ 88, 152, 75, 114 }, 0.2, 0, 0);
	backward.PushBack({ 165, 147, 69, 118 }, 0.2, 0, 0);
	backward.PushBack({ 236, 145, 66, 120 }, 0.2, 0, 0);
	backward.PushBack({ 304, 147, 70, 118 }, 0.2, 0, 0);
	backward.PushBack({ 376, 151, 75, 114 }, 0.2, 0, 0);

	jumpup.PushBack({ 363, 274, 60, 112 }, 0.11, 0, 0);
	jumpup.PushBack({ 429, 295, 75, 91 }, 0.11, 0, 0);
	jumpup.PushBack({ 510, 303, 76, 83 }, 0.09, 0, 0);
	jumpup.PushBack({ 429, 295, 75, 91 }, 0.11, 0, 0);
	jumpup.PushBack({ 363, 274, 60, 112 }, 0.11, 0, 0);

	punch.PushBack({ 3, 0, 69, 127 }, 0.3, 0, 0); 
	punch.PushBack({ 74, 30, 79, 97 }, 0.1, -10, 0);
	punch.PushBack({ 158, 33, 132, 94 }, 0.6, 0, 0);
	punch.PushBack({ 290, 33, 132, 94 }, 0.6, 0, 0);
	punch.PushBack({ 423, 42, 131, 85 }, 0.6, 0, 0);
	punch.PushBack({ 556, 44, 130, 94 }, 0.6, 0, 11);
	punch.PushBack({ 688, 44, 128, 94 }, 0.6, 0, 11);
	punch.PushBack({ 818, 44, 120, 94 }, 0.6, 0, 11);
	punch.PushBack({ 940, 44, 83, 94 }, 0.2, 0, 11);
	punch.PushBack({ 1025, 42, 131, 85 }, 0.1, 0, 0); 

	kick.PushBack({ 647, 274, 58, 112 }, 0.2, 0, 0); 
	kick.PushBack({ 710, 276, 53, 110 }, 0.2, 0, 0);
	kick.PushBack({ 768, 288, 94, 98 }, 0.2, 0, 0);
	kick.PushBack({ 867, 287, 97, 99 }, 0.2, 0, 0);
	kick.PushBack({ 969, 286, 82, 100 }, 0.2, 0, 0);

	cyclone.PushBack({ 8, 452, 90, 88 }, 0.1, 0, 0);
	cyclone.PushBack({ 105, 451, 70, 89 }, 0.2, 0, 0);
	cyclone.PushBack({ 181, 457, 73, 83 }, 0.2, 0, 0);
	cyclone.PushBack({ 261, 449, 58, 91 }, 0.2, 0, 0);
	cyclone.PushBack({ 326, 442, 94, 98 }, 0.2, 0, 0);
	cyclone.PushBack({ 427, 387, 62, 153 }, 0.2, 0, 0);
	cyclone.PushBack({ 496, 442, 97, 98 }, 0.2, -20, 0);
	cyclone.PushBack({ 600, 450, 97, 90 }, 0.08, -20, 0);
}

ModulePlayer::~ModulePlayer()
{}


bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;

	position.x = 100;
	position.y = 207;

	graphics = App->textures->Load("Assets/Image/Haohmaru Spritesheet.png");
	senpuu = App->music->LoadChunk("Assets/Sound/Haohmaru/attacks/senpuu.ogg");
	colliderPlayer = App->collision->AddCollider({ position.x, position.y-90, 60, 90 }, COLLIDER_PLAYER, this);
	return ret;
}

bool ModulePlayer::CleanUp() {

	LOG("Unloading Player")
		if (colliderPlayer != nullptr){
	colliderPlayer->to_delete = true;}
	App->textures->Unload(graphics);
	App->music->UnloadChunk(senpuu);
	return true;
}

update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 2;
	if (wall && position.x > 100) {}
	else{
	if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) && (animstart == 0))
	{
		current_animation = &forward;
		position.x += speed;
	}
	}
	if(wall && position.x < 100){}
	else{
	if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) && (animstart == 0))
	{
		current_animation = &backward;
		position.x -= speed;
	}
	}
	
	if ((App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN||floor == false))
	{
		floor = false;
		current_animation = &jumpup;
		position.y -= jumpSpeed;

		if (position.y < 120) { jumpSpeed-=0.5;
		if (jumpSpeed<0) jumpSpeed = -6;
		}
		if (position.y >= initialPos && jumpSpeed<0) { 
			floor = true; 
			position.y = initialPos;
			jumpSpeed = 6;
		}
	}
	
	if ((App->input->keyboard[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN || attAnim == true) && (animstart == 0 || animstart == 1))
	{
		attAnim = true;
		animstart = 1;
		current_animation = &punch;
		if (current_animation->AnimationEnd() == true) { attAnim = false; animstart = 0; }

	}
	if ((App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN || kickAnim == true) && (animstart == 0 || animstart == 2))
	{
		kickAnim = true;
		animstart = 2;
		current_animation = &kick;
		if (current_animation->AnimationEnd() == true) { kickAnim = false; animstart = 0;}
	}
	if ((App->input->keyboard[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN ) && (animstart == 0 || animstart == 3))
	{
		cycloneAnim = true;
		animstart = 3;
		App->particles->AddParticle(App->particles->cyclone, position.x, position.y - 100, COLLIDER_PLAYER_SHOT, 450);
		App->music->PlayChunk(senpuu);
	}
	if (cycloneAnim == true) {
		current_animation = &cyclone;
		if (current_animation->AnimationEnd() == true) {cycloneAnim = false; animstart = 0;}
	}

	wall = false;
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, position.x + /*Pivotex*/current_animation->pivotx[current_animation->returnCurrentFrame()], position.y -r.h + /*Pivotey*/ current_animation->pivoty[current_animation->returnCurrentFrame()], &r);
	colliderPlayer->SetPos(position.x, position.y - 90);
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {

	if (colliderPlayer == c1 && c2->type== COLLIDER_WALL)
	{
		wall = true;
	}

}
