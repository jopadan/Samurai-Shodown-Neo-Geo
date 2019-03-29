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
	idle.PushBack({ 7, 273, 75, 113 }, 0.15);
	idle.PushBack({ 86, 275, 73, 111 }, 0.15);
	idle.PushBack({ 164, 277, 72, 109 }, 0.15);
	idle.PushBack({ 241, 279, 72, 107 }, 0.15);
	
	
	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({ 506, 150, 69, 112 }, 0.1);
	forward.PushBack({ 580, 147, 59, 116 }, 0.25);
	forward.PushBack({ 644, 145, 57, 118 }, 0.1);
	forward.PushBack({ 706, 147, 62, 116 }, 0.25);
	forward.PushBack({ 773, 151, 70, 117 }, 0.1);
	

	// TODO 4: Make ryu walk backwards with the correct animations
	backward.PushBack({ 4, 155, 82, 111 }, 0.2);
	backward.PushBack({ 88, 152, 75, 114 }, 0.2);
	backward.PushBack({ 165, 147, 69, 118 }, 0.2);
	backward.PushBack({ 236, 145, 66, 120 }, 0.2);
	backward.PushBack({ 304, 147, 70, 118 }, 0.2);
	backward.PushBack({ 376, 151, 75, 114 }, 0.2);

	jumpup.PushBack({ 363, 274, 60, 112 }, 0.1);
	jumpup.PushBack({ 429, 295, 75, 91 }, 0.1);
	jumpup.PushBack({ 510, 303, 76, 83 }, 0.09);
	jumpup.PushBack({ 429, 295, 75, 91 }, 0.1);
	jumpup.PushBack({ 363, 274, 60, 112 }, 0.1);

	punch.PushBack({ 3, 0, 69, 127 }, 0.3); //127
	punch.PushBack({ 74, 30, 79, 97 }, 0.1);
	punch.PushBack({ 158, 33, 132, 94 }, 0.6);
	punch.PushBack({ 290, 33, 132, 94 }, 0.6);
	punch.PushBack({ 423, 42, 131, 85 }, 0.6);
	punch.PushBack({ 556, 44, 130, 94 }, 0.6); //138 S'ha de baixar 11 pixels
	punch.PushBack({ 688, 44, 128, 94 }, 0.6);
	punch.PushBack({ 818, 44, 120, 94 }, 0.6);
	punch.PushBack({ 940, 44, 83, 94 }, 0.2);
	punch.PushBack({ 1025, 42, 131, 85 }, 0.2); //127

	kick.PushBack({ 647, 274, 58, 112 }, 0.2); //386
	kick.PushBack({ 710, 276, 53, 110 }, 0.2);
	kick.PushBack({ 768, 288, 94, 98 }, 0.2);
	kick.PushBack({ 867, 287, 97, 99 }, 0.2);
	kick.PushBack({ 969, 286, 82, 100 }, 0.2);
}

ModulePlayer::~ModulePlayer()
{

}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Haohmaru Spritesheet.png"); // arcade version
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
	/*	if (current_animation->returnFrame()==6) {
			position.y+11;
		}
		*/
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