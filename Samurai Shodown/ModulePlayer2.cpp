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


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 240;
	position.y = 207;
	initialPos = position.y;

	idle.PushBack({ 0, 0, 69, 100 }, 0, 0, 0);
}

ModulePlayer2::~ModulePlayer2()
{}


bool ModulePlayer2::Start()
{
	LOG("Loading player2 textures");
	bool ret = true;

	position.x = 240;
	position.y = 207;

	graphics = App->textures->Load("Assets/Image/paja_sprite.png");
	colliderPlayer2 = App->collision->AddCollider({ position.x, position.y - 90, 60, 90 }, COLLIDER_ENEMY, this);
	return ret;
}

bool ModulePlayer2::CleanUp() {

	LOG("Unloading Player2")
		if (colliderPlayer2 != nullptr) {
			colliderPlayer2->to_delete = true;
		}
		App->textures->Unload(graphics);
	return true;
}

update_status ModulePlayer2::Update()
{
	Animation* current_animation = &idle;

	

	int speed = 2;
/*
	if ((App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT) && (animstart == 0))
	{
		//current_animation = &forward;
		position.x += speed;
	}
	if ((App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT) && (animstart == 0))
	{
		//current_animation = &backward;
		position.x -= speed;
	}
	if ((App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN || floor == false))
	{
		floor = false;
		//current_animation = &jumpup;
		position.y -= jumpSpeed;

		if (position.y < 120) {
			jumpSpeed -= 0.5;
			if (jumpSpeed < 0) jumpSpeed = -6;
		}
		if (position.y >= initialPos && jumpSpeed < 0) {
			floor = true;
			position.y = initialPos;
			jumpSpeed = 6;
		}
	}

	
*/
	SDL_Rect r = current_animation->GetCurrentFrame();
	

	colliderPlayer2->SetPos(position.x, position.y - 90);

	App->render->Blit(graphics, position.x + /*Pivotex*/current_animation->pivotx[current_animation->returnCurrentFrame()], position.y - r.h + /*Pivotey*/ current_animation->pivoty[current_animation->returnCurrentFrame()], &r, SDL_FLIP_NONE);

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {

	if (colliderPlayer2 == c1 && c2->type== COLLIDER_PLAYER_SHOT)
	{
		LOG("Impact");
		floor = false;
		//current_animation = &jumpup;
		position.y -= jumpSpeed;

		if (position.y < 170) {
			jumpSpeed -= 0.5;
			if (jumpSpeed < 0) jumpSpeed = -6;
		}
		if (position.y >= initialPos && jumpSpeed < 0) {
			floor = true;
			position.y = initialPos;
			jumpSpeed = 6;
		}
		//current_animation =
	}
	if (colliderPlayer2 == c1 && c2->type == COLLIDER_ENEMY)
	{
		App->player->position.x = position.x -60;
		speed = 1;
	}

}
