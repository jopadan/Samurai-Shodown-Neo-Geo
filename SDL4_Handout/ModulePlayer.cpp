#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;
	initialPos = position.y;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 7, 14, 60, 90 }, 0.2);
	idle.PushBack({ 95, 15, 60, 89 }, 0.2);
	idle.PushBack({ 184, 14, 60, 90 }, 0.2);
	idle.PushBack({ 276, 11, 60, 93 }, 0.2);
	idle.PushBack({ 366, 12, 60, 92 }, 0.2);

	
	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({78, 131, 60, 88}, 0.2);
	forward.PushBack({162, 128, 64, 92}, 0.2);
	forward.PushBack({259, 128, 63, 90}, 0.2);
	forward.PushBack({352, 128, 54, 91}, 0.2);
	forward.PushBack({432, 131, 50, 89}, 0.2);
	

	// TODO 4: Make ryu walk backwards with the correct animations
	backward.PushBack({ 540, 127, 65, 92 }, 0.2);
	backward.PushBack({ 626, 127, 65, 92 }, 0.2);
	backward.PushBack({ 711, 127, 65, 92 }, 0.2);
	backward.PushBack({ 795, 127, 65, 92 }, 0.2);
	backward.PushBack({ 881, 127, 65, 92 }, 0.2);
	backward.PushBack({ 972, 127, 65, 92 }, 0.05);

	jumpup.PushBack({ 7, 14, 60, 90 }, 0.2);
	jumpup.PushBack({ 95, 15, 60, 89 }, 0.2);
	jumpup.PushBack({ 184, 14, 60, 90 }, 0.2);
	jumpup.PushBack({ 276, 11, 60, 93 }, 0.2);
	jumpup.PushBack({ 366, 12, 60, 92 }, 0.2);

	punch.PushBack({ 540, 127, 65, 92 }, 0.2);
	punch.PushBack({ 626, 127, 65, 92 }, 0.2);
	punch.PushBack({ 711, 127, 65, 92 }, 0.2);
	punch.PushBack({ 795, 127, 65, 92 }, 0.2);
	punch.PushBack({ 881, 127, 65, 92 }, 0.2);
	punch.PushBack({ 972, 127, 65, 92 }, 0.2);

	kick.PushBack({ 78, 131, 60, 88 }, 0.2);
	kick.PushBack({ 162, 128, 64, 92 }, 0.2);
	kick.PushBack({ 259, 128, 63, 90 }, 0.2);
	kick.PushBack({ 352, 128, 54, 91 }, 0.2);
	kick.PushBack({ 432, 131, 50, 89 }, 0.2);
}

ModulePlayer::~ModulePlayer()
{

}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 2;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == 1 || floor == false)
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
	if (App->input->keyboard[SDL_SCANCODE_P] == 1 || attAnim == true)
	{
		attAnim = true;
		current_animation = &punch;


	if (current_animation->AnimationEnd() == true) {
			attAnim = false;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_K] == 1 || kickAnim == true)
	{
		kickAnim = true;
		current_animation = &kick;


		if (current_animation->AnimationEnd() == true) {
			kickAnim = false;
		}
	}


	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}