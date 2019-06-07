#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNakoruru.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"
#include "ModuleUI.h"
#include "ModuleSelect.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"

ModuleSelect::ModuleSelect()
{
	r.x = 0;
	r.y = 0;
	r.w = 319;
	r.h = 230;

	name.x = 2;
	name.y = 229;
	name.w = 128;
	name.h = 51;

	idle.PushBack({ 13, 1614, 65, 87 }, 0.15, 0, 0, 0, 0);
	idle.PushBack({ 82, 1614, 65, 87 }, 0.15, 1, 0, 0, 0);
	idle.PushBack({ 149, 1614, 65, 91 }, 0.15, 0, 4, 0, 4);
	idle.PushBack({ 214, 1612, 66, 91 }, 0.15, 0, 2, 0, 2);
	idle.PushBack({ 282, 1612, 67, 92 }, 0.15, 0, 1, -1, 1);
	idle.PushBack({ 349, 1612, 66, 91 }, 0.15, 0, 2, 0, 2);
	

	Attack.PushBack({ 117, 713, 89, 92 }, 0.2, 11, 0, -22, 0);
	Attack.PushBack({ 204, 711, 97, 94 }, 0.2, 5, 0, -20, 0);
	Attack.PushBack({ 303, 708, 93, 95 }, 0.2, 0, 0, -17, 0);
	Attack.PushBack({ 1065, 896,100, 93 }, 0.2, 0, 0, -17, 0);
	Attack.PushBack({ 1164, 900,100, 93 }, 0.2, 3, 3, -18, 3);
	Attack.PushBack({ 1262, 896,100, 93 }, 0.2, 5, 4, -19, 4);
	Attack.PushBack({ 1459, 899,100, 93 }, 0.1, 7, 4, -19, 4);
	Attack.PushBack({ 1555, 899,100, 93 }, 0.1, 12, 7, -22, 7);
	Attack.PushBack({ 1738, 899,100, 93 }, 0.1, 11, 3, -21, 3);
	Attack.PushBack({ 1833, 899,100, 93 }, 0.1, 11, 4, -22, 4);
	Attack.loop = false;

	p1square.PushBack({ 336, 74, 40, 47 }, 0.075, 0, 0, 0, 0);
	p1square.PushBack({ 376, 74, 40, 47 }, 0.35, 1, 0, 0, 0);
	p1square.PushBack({ 416, 74, 40, 47 }, 0.35, 0, 4, 0, 4);
	p1square.PushBack({ 376, 74, 40, 47 }, 0.35, 1, 0, 0, 0);

	p2square.PushBack({ 376, 23, 40, 46 }, 0.075, 1, 0, 0, 0);
	p2square.PushBack({ 336, 23, 40, 46 }, 0.35, 0, 4, 0, 4);
	p2square.PushBack({ 416, 74, 40, 47 }, 0.35, 0, 4, 0, 4);
	p2square.PushBack({ 336, 23, 40, 46 }, 0.35, 0, 4, 0, 4);
}

ModuleSelect::~ModuleSelect()
{}

// Load assets
bool ModuleSelect::Start()
{
	LOG("Loading menu assets");
	bool ret = true;

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	position1.x = 200;
	position1.y = 18;
	position2.x = 400;
	position2.y = 19;

	ready1 = false;
	ready2 = false;

	musload = App->music->LoadMus("Assets/Sound/Twelve Swordsmen (Player Select).ogg");
	select = App->music->LoadChunk("Assets/Sound/Samurai Shodown - SELECTING IN MENU.ogg");
	graphics = App->textures->Load("Assets/Image/Select.png");
	player1 = App->textures->Load("Assets/Image/Nakoruru spritesheet.png");
	player2 = App->textures->Load("Assets/Image/Nakoruru spritesheet p2.png");

	App->music->Enable();
	App->music->PlayMus(musload);
	App->ui->roundsp1 = App->ui->roundsp2 = 0;

	return ret;
}

bool ModuleSelect::CleanUp()
{
	LOG("Unloading Menu scene");
	App->music->UnloadMus(musload);
	App->music->UnloadChunk(select);
	App->textures->Unload(graphics);
	App->textures->Unload(player1);
	App->textures->Unload(player2);
	App->music->Disable();
	

	return true;
}

// Update: draw background
update_status ModuleSelect::Update()
{

	if (SDL_GetTicks() - timertime >= 30000) {

		App->player->process_fsm(App->input->inputs);
		App->player2->process_fsm(App->input->inputs2);
	}
	if (SDL_GetTicks() - timertime >= 35000) {

		timertime = SDL_GetTicks();
	}
	{
		if (!App->input->right) {
			right = true;
		}

		if (!App->input->left) {
			left = true;
		}

		if (!App->input->up) {
			up = true;
		}

		if (!App->input->down) {
			down = true;
		}

		if (!App->input->right2) {
			right2 = true;
		}

		if (!App->input->left2) {
			left2 = true;
		}

		if (!App->input->up2) {
			up2 = true;
		}

		if (!App->input->down2) {
			down2 = true;
		}
	}
	{if (position1.x == 200) {
		left = false;
	}
	if (position1.x == 400) {
		right = false;
	}
	if (position2.x == 200) {
		left2 = false;
	}
	if (position2.x == 400) {
		right2 = false;
	}

	if (position1.y == 18) {
		up = false;
	}
	if (position1.y == 66) {
		down = false;
	}
	if (position2.y == 19) {
		up2 = false;
	}
	if (position2.y == 67) {
		down2 = false;
	}}

	if (ready1 == true) {
		up = false;
		down = false;
		right = false;
		left = false;
	}
	if (ready2 == true) {
		up2 = false;
		down2 = false;
		right2 = false;
		left2 = false;
	}

	{
		if (App->input->right == true) {
			if (right == true) {
				position1.x += 40;
				App->music->PlayChunk(select);
				right = false;
			}
		}

		if (App->input->left) {
			if (left == true) {
				position1.x -= 40;
				left = false;
				App->music->PlayChunk(select);
			}
		}

		if (App->input->up) {
			if (up == true) {
				position1.y -= 48;
				up = false;
				App->music->PlayChunk(select);
			}
		}

		if (App->input->down) {
			if (down == true) {
				position1.y += 48;
				down = false;
				App->music->PlayChunk(select);
			}
		}

		if (App->input->right2) {
			if (right2 == true) {
				position2.x += 40;
				right2 = false;
				App->music->PlayChunk(select);
			}
		}

		if (App->input->left2) {
			if (left2 == true) {
				position2.x -= 40;
				left2 = false;
				App->music->PlayChunk(select);
			}
		}

		if (App->input->up2) {
			if (up2 == true) {
				position2.y -= 48;
				up2 = false;
				App->music->PlayChunk(select);
			}
		}

		if (App->input->down2) {
			if (down2 == true) {
				position2.y += 48;
				down2 = false;
				App->music->PlayChunk(select);
			}
		}
}

	if (SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_X) == 1) {
		ready1 = true;
	}
	if (SDL_GameControllerGetButton(App->input->gGameController2, SDL_CONTROLLER_BUTTON_X) == 1) {
		ready2 = true;
	}
	if (ready1 && ready2) {
		current_animation = &Attack;
		if (current_animation->AnimationEnd() == true){ App->fade->FadeToBlack(App->select, (Module*)App->scene_nakoruru, 2); }
	}
	else {
		current_animation = &idle;
	}

	Animation* current_animation2 = &p1square;
	Animation* current_animation3 = &p2square;



	SDL_Rect player = current_animation->GetCurrentFrame();
	SDL_Rect square1 = current_animation2->GetCurrentFrame();
	SDL_Rect square2 = current_animation3->GetCurrentFrame();

	App->render->Blit(graphics, 168, 0, &r, SDL_FLIP_NONE);

	App->render->Blit(graphics, position1.x, position1.y, &square1, SDL_FLIP_NONE);
	App->render->Blit(graphics, position2.x, position2.y, &square2, SDL_FLIP_NONE);
	App->render->Blit(player1, 215 + /*Pivotex*/current_animation->pivotx[current_animation->returnCurrentFrame()],200 - player.h + /*Pivotey*/ current_animation->pivoty[current_animation->returnCurrentFrame()], &player, SDL_FLIP_NONE);
	App->render->Blit(player2, 360 + /*Pivotex*/current_animation->pivotx2[current_animation->returnCurrentFrame()], 200 - player.h + /*Pivotey*/ current_animation->pivoty2[current_animation->returnCurrentFrame()], &player, SDL_FLIP_HORIZONTAL);

	App->render->Blit(graphics, 185, 165, &name, SDL_FLIP_NONE);
	App->render->Blit(graphics, 332, 165, &name, SDL_FLIP_NONE);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || SDL_GameControllerGetButton(App->input->gGameController, SDL_CONTROLLER_BUTTON_START) == 1 || SDL_GameControllerGetButton(App->input->gGameController2, SDL_CONTROLLER_BUTTON_START) == 1) {
		App->fade->FadeToBlack(App->select, (Module*)App->scene_nakoruru, 2);
	}

	return UPDATE_CONTINUE;
}