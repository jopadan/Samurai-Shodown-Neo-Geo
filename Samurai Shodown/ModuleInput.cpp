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

bool ModuleInput::external_input(p2Qeue<player_inputs>& inputs)
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;
			case SDLK_s:
				key = CROUCH_UP;
				//inputs.Push(IN_CROUCH_UP);
				break;
			case SDLK_w:
				key = JUMP_UP;
				break;
			case SDLK_a:
				key = LEFT_UP;
				//inputs.Push(IN_LEFT_UP);
			//	left = false;
				break;
			case SDLK_d:
				key = RIGHT_UP;
			//	inputs.Push(IN_RIGHT_UP);
			
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_1:
				key = ONE;
				break;
			case SDLK_2:
				key = TWO;
				break;
			case SDLK_3:
				key = THREE;
				break;
			case SDLK_w:
				key = JUMP;
				break;
			case SDLK_s:
				key = CROUCH_DOWN;
				break;
			case SDLK_a:
				key = LEFT_DOWN;
				break;
			case SDLK_d:
				key = RIGHT_DOWN;
				break;
			}
		}
		
	}
/*
	if (left && right)
		inputs.Push(IN_LEFT_AND_RIGHT);
	{
		if (left)
			inputs.Push(IN_LEFT_DOWN);
		if (right)
			inputs.Push(IN_RIGHT_DOWN);
	}

	if (up && down)
		inputs.Push(IN_JUMP_AND_CROUCH);
	else
	{
		if (down)
			inputs.Push(IN_CROUCH_DOWN);
		if (up)
			inputs.Push(IN_JUMP);
	}
*/
	return true;
}

void ModuleInput::internal_input(p2Qeue<player_inputs>& inputs)
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
	if (external_input(inputs) == false){		return update_status::UPDATE_STOP;}
	else{ 
		internal_input(inputs);
		
	
		return update_status::UPDATE_CONTINUE;
	}
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