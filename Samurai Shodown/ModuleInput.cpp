#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

#include "ModuleInputPlayer.h"
#include "p2Qeue.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleInput::external_input()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;
			case SDLK_s:
				if (App->input_player->IsEnabled() == true)
					down = false;
				break;
			case SDLK_k:
				if (App->input_player->IsEnabled() == true)
					down2 = false;
				break;
			case SDLK_w:
				if (App->input_player->IsEnabled() == true)
					up = false;
				break;
			case SDLK_i:
				if (App->input_player->IsEnabled() == true)
					up2 = false;
				break;
			case SDLK_a:
				if (App->input_player->IsEnabled() == true)
					left = false;
				break;
			case SDLK_j:
				if (App->input_player->IsEnabled() == true)
					left2 = false;
				break;
			case SDLK_d:
				if (App->input_player->IsEnabled() == true)
					right = false;
				break;
			case SDLK_l:
				if (App->input_player->IsEnabled() == true)
					right2 = false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_1:
				if (App->input_player->IsEnabled() == true)
					App->input->inputs.Push(IN_1);
				break;
			case SDLK_2:
				if (App->input_player->IsEnabled() == true)
				App->input->inputs.Push(IN_2);
				break;
			case SDLK_3:
				if (App->input_player->IsEnabled() == true)
				App->input->inputs.Push(IN_3);
				break;
			case SDLK_w:
				if (App->input_player->IsEnabled() == true)
					up = true;
				break;
			case SDLK_s:
				if (App->input_player->IsEnabled() == true)
					down = true;
				break;
			case SDLK_a:
				if (App->input_player->IsEnabled() == true)
					left = true;
				break;
			case SDLK_d:
				if (App->input_player->IsEnabled() == true)
					right = true;
				break;
			case SDLK_7:
				if (App->input_player->IsEnabled() == true)
					App->input->inputs2.Push(IN_1_P2);
				break;
			case SDLK_8:
				if (App->input_player->IsEnabled() == true)
					App->input->inputs2.Push(IN_2_P2);
				break;
			case SDLK_9:
				if (App->input_player->IsEnabled() == true)
					App->input->inputs2.Push(IN_3_P2);
				break;
			case SDLK_i:
				if (App->input_player->IsEnabled() == true)
					up2 = true;
				break;
			case SDLK_k:
				if (App->input_player->IsEnabled() == true)
					down2 = true;
				break;
			case SDLK_j:
				if (App->input_player->IsEnabled() == true)
					left2 = true;
				break;
			case SDLK_l:
				if (App->input_player->IsEnabled() == true)
					right2 = true;
				break;
			}
		}
		
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
	return true;
}

void ModuleInput::internal_input(p2Qeue<player_inputs>& inputs, p2Qeue<player_inputs>& inputs2)
{
	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() - punch_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}
	if (kick_timer > 0)
	{
		if (SDL_GetTicks() - kick_timer > KICK_TIME)
		{
			inputs.Push(IN_KICK_FINISH);
			kick_timer = 0;
		}
	}
	if (tornado_timer > 0)
	{
		if (SDL_GetTicks() - tornado_timer > TORNADO_TIME)
		{
			inputs.Push(IN_TORNADO_FINISH);
			tornado_timer = 0;
		}
	}
	if (jump_timer2 > 0)
	{
		if (SDL_GetTicks() - jump_timer2 > JUMP_TIME)
		{
			inputs2.Push(IN_JUMP_FINISH_P2);
			jump_timer2 = 0;
		}
	}

	if (punch_timer2 > 0)
	{
		if (SDL_GetTicks() - punch_timer2 > PUNCH_TIME)
		{
			inputs2.Push(IN_PUNCH_FINISH_P2);
			punch_timer2 = 0;
		}
	}
	if (kick_timer2 > 0)
	{
		if (SDL_GetTicks() - kick_timer2 > KICK_TIME)
		{
			inputs2.Push(IN_KICK_FINISH_P2);
			kick_timer2 = 0;
		}
	}
	if (tornado_timer2 > 0)
	{
		if (SDL_GetTicks() - tornado_timer2 > TORNADO_TIME)
		{
			inputs2.Push(IN_TORNADO_FINISH_P2);
			tornado_timer2 = 0;
		}
	}
}


update_status ModuleInput::PreUpdate()
{

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	// Para el input que no sean estados
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}
	// Para el input que sean estados
	if (external_input() == false){		return update_status::UPDATE_STOP;}
	else {
		internal_input(inputs, inputs2);
	}

	
		return update_status::UPDATE_CONTINUE;
	
	SDL_PumpEvents();



}
update_status ModuleInput::PostUpdate() {
	key = -1;
	return update_status::UPDATE_CONTINUE;
}
// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}