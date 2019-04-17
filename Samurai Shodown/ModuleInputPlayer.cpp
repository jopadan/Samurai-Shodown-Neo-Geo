#include "Globals.h"
#include "Application.h"
#include "ModuleInputPlayer.h"
#include "ModuleInput.h"
#include "p2Qeue.h"
#include "SDL/include/SDL.h"



ModuleInputPlayer::ModuleInputPlayer() 
{}

// Destructor
ModuleInputPlayer::~ModuleInputPlayer()
{}

update_status ModuleInputPlayer::Update() {
	
	switch (App->input->key) {
	case LEFT_UP:
		LOG("Suelto Left");
		left = false;
		break;
	case LEFT_DOWN:
		LOG("Pulso left");
		left = true;
		break;
	case RIGHT_UP:
		right = false;
		break;
	case RIGHT_DOWN:
		right = true;
		break;
	case ONE:
		App->input->inputs.Push(IN_1);
		break;
	case TWO:
		App->input->inputs.Push(IN_2);
		break;
	case THREE:
		App->input->inputs.Push(IN_3);
		break;
	case JUMP:
		up = true;
		break;
	case JUMP_UP:
		up = false;
		break;
	case CROUCH_DOWN:
		down = true;
		break;
	case CROUCH_UP:
		down = false;
		break;
		
	case LEFT_UP2:
		LOG("Suelto Left");
		left2 = false;
		break;
	case LEFT_DOWN2:
		LOG("Pulso left");
		left2 = true;
		break;
	case RIGHT_UP2:
		right2 = false;
		break;
	case RIGHT_DOWN2:
		right2 = true;
		break;
	case ONE2:
		App->input->inputs2.Push(IN_1_P2);
		break;
	case TWO2:
		App->input->inputs2.Push(IN_2_P2);
		break;
	case THREE2:
		App->input->inputs2.Push(IN_3_P2);
		break;
	case JUMP2:
		up2 = true;
		break;
	case JUMP_UP2:
		up2 = false;
		break;
	case CROUCH_DOWN2:
		down2 = true;
		break;
	case CROUCH_UP2:
		down2 = false;
		break;
		
}

	if (left && right)
		App->input->inputs.Push(IN_LEFT_AND_RIGHT);
	{
		if (left)
			App->input->inputs.Push(IN_LEFT_DOWN);
		if (right)
			App->input->inputs.Push(IN_RIGHT_DOWN);
	}
	
		if (!left)
			App->input->inputs.Push(IN_LEFT_UP);
		if (!right)
			App->input->inputs.Push(IN_RIGHT_UP);
		if (!down)
			App->input->inputs.Push(IN_CROUCH_UP);
	

	if (up && down)
		App->input->inputs.Push(IN_JUMP_AND_CROUCH);
	else
	{
		if (down)
			App->input->inputs.Push(IN_CROUCH_DOWN);
		if (up)
			App->input->inputs.Push(IN_JUMP);
	}
	if (left2 && right2)
		App->input->inputs2.Push(IN_LEFT_AND_RIGHT_P2);
	{
		if (left2)
			App->input->inputs2.Push(IN_LEFT_DOWN_P2);
		if (right2)
			App->input->inputs2.Push(IN_RIGHT_DOWN_P2);
	}

	if (!left2)
		App->input->inputs2.Push(IN_LEFT_UP_P2);
	if (!right2)
		App->input->inputs2.Push(IN_RIGHT_UP_P2);
	if (!down2)
		App->input->inputs2.Push(IN_CROUCH_UP_P2);


	if (up2 && down2)
		App->input->inputs2.Push(IN_JUMP_AND_CROUCH_P2);
	else
	{
		if (down2)
			App->input->inputs2.Push(IN_CROUCH_DOWN_P2);
		if (up2)
			App->input->inputs2.Push(IN_JUMP_P2);
	}
	App->input->key = -1;
	return update_status::UPDATE_CONTINUE;
}

/*
void ModuleInputPlayer::internal_input()
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			App->input->inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			App->input->inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}
}*/