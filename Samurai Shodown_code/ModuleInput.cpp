#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "p2Qeue.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_gamecontroller.h"


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
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	if (SDL_NumJoysticks() < 1)
	{
		LOG("Warning: No joysticks connected!\n");
	}
	else
	{
		//Load joystick
		gGameController = SDL_JoystickOpen(0);
		controller = true;
		if (gGameController == NULL)
		{
			LOG("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			controller = false;
		}
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
				if (playerinput == true)
					down = false;
				break;
			case SDLK_k:
				if (playerinput == true)
					down2 = false;
				break;
			case SDLK_w:
				if (playerinput == true)
					up = false;
				break;
			case SDLK_i:
				if (playerinput == true)
					up2 = false;
				break;
			case SDLK_a:
				if (playerinput == true)
					left = false;
				break;
			case SDLK_j:
				if (playerinput == true)
					left2 = false;
				break;
			case SDLK_d:
				if (playerinput == true)
					right = false;
				break;
			case SDLK_l:
				if (playerinput == true)
					right2 = false;
				break;
			}
		}

		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_1:
				if (playerinput == true)
					App->input->inputs.Push(IN_1);
				break;
			case SDLK_2:
				if (playerinput == true)
					App->input->inputs.Push(IN_2);
				break;
			case SDLK_3:
				if (playerinput == true)
					App->input->inputs.Push(IN_3);
				break;
			/*case SDLK_w:
				if (playerinput == true)
					up = true;
				break;
			case SDLK_s:
				if (playerinput == true)
					down = true;
				break;
			case SDLK_a:
				if (playerinput == true)
					left = true;
				break;
			case SDLK_d:
				if (playerinput == true)
					right = true;
				break;*/
			case SDLK_7:
				if (playerinput == true)
					App->input->inputs2.Push(IN_1_P2);
				break;
			case SDLK_8:
				if (playerinput == true)
					App->input->inputs2.Push(IN_2_P2);
				break;
			case SDLK_9:
				if (playerinput == true)
					App->input->inputs2.Push(IN_3_P2);
				break;
			case SDLK_i:
				if (playerinput == true)
					up2 = true;
				break;
			case SDLK_k:
				if (playerinput == true)
					down2 = true;
				break;
			case SDLK_j:
				if (playerinput == true)
					left2 = true;
				break;
			case SDLK_l:
				if (playerinput == true)
					right2 = true;
				break;
			}
		}
		if (event.type == SDL_JOYDEVICEADDED) {
			if (event.jaxis.which == 0) {
				LOG("Game controller connected");
				controller = true;
			}
		}
		if (event.type == SDL_JOYDEVICEREMOVED) {
			if (event.jaxis.which == 0) {
				LOG("Game controller disconnected");
				controller = false;
			}
		}
		if (controller == false) {
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				switch (event.key.keysym.sym) {
				case SDLK_w:
					if (playerinput == true)
						up = true;
					break;
				case SDLK_s:
					if (playerinput == true)
						down = true;
					break;
				case SDLK_a:
					if (playerinput == true)
						left = true;
					break;
				case SDLK_d:
					if (playerinput == true)
						right = true;
					break;
				}
			}
		}
		if (controller == true) {
			if (event.type == SDL_JOYAXISMOTION) {
				if (event.jaxis.which == 0) { //En el gamepad 0
					if (event.jaxis.axis == 0)
					{
						//Left of dead zone
						if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
						{
							left = true;
							right = false;
						}
						//Right of dead zone
						else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
						{
							right = true;
							left = false;
						}
						else
						{
							left = false;
							right = false;
						}
					}
					else if (event.jaxis.axis == 1)
					{
						//Below of dead zone
						if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
						{
							down = false;
							up = true;
						}
						//Above of dead zone
						else if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
						{
							up = false;
							down = true;
						}
						else
						{
							down = false;
							up = false;
						}
					}
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
	if (punch_c_timer > 0)
	{
		if (SDL_GetTicks() - punch_c_timer > CROUCH_PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_CROUCH_FINISH);
			punch_c_timer = 0;
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
	if (punch_c_timer2 > 0)
	{
		if (SDL_GetTicks() - punch_c_timer2 > CROUCH_PUNCH_TIME)
		{
			inputs2.Push(IN_PUNCH_CROUCH_FINISH_P2);
			punch_c_timer2 = 0;
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
	SDL_JoystickClose(gGameController);
	gGameController = NULL;
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}