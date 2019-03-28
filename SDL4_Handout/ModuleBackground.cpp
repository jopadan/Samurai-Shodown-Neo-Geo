#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 0;
	ground.y = 575;
	ground.w = 640;
	ground.h = 416;

	// Background / sky
	/*background.x = 0;
	background.y = 656;
	background.w = 640;
	background.h = 329;*/

	// Parallax ship
	/*ship.x = 10;
	ship.y = 0;
	ship.w = 536;
	ship.h = 206;*/
	
	 //sea animation
	sea.PushBack({ 0, 58, 640, 85},0.08f);
	sea.PushBack({704, 58, 640, 85 }, 0.08f);
	sea.PushBack({ 1408, 58, 640, 85 }, 0.08f);
	sea.PushBack({ 0, 202, 640, 85 }, 0.08f);
	sea.PushBack({ 704, 202, 640, 85 }, 0.08f);
	sea.PushBack({ 1408, 202, 640, 85 }, 0.08f);
	sea.PushBack({ 0, 343, 640, 85 }, 0.08f);
	sea.PushBack({ 704, 343, 640, 85 }, 0.08f);
	sea.PushBack({ 1408, 343, 640, 85 }, 0.08f);
	
	
	/*//Girl animation
	girl.PushBack({ 624, 16, 32, 56 });
	girl.PushBack({ 624, 80, 32, 56 });
	girl.PushBack({ 624, 144, 40, 40 });
	girl.PushBack({ 624, 80, 32, 56 });
	girl.speed = 0.08f;*/
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("haohmaru_stage.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	cont+=0.5;
	if (cont > 3)
	{
		bounce++;
		bounce -= bouncespeed;
		cont = 0;
	}

	if (bounce < -26)
	{
		bouncespeed=0;
	}
	if (bounce > -24) {

		bouncespeed=2;
	}
	// Draw everything --------------------------------------
	//background
	App->render->Blit(graphics, 0, -150, &ground);
	App->render->Blit(graphics, 0, 87, &(sea.GetCurrentFrame()), 1);
	//App->render->Blit(graphics, 0, -157, &background, 0.75f); // sea and sky
	 // flag animation
	//App->render->Blit(graphics, 0, bounce, &ship, 0.85);
	//App->render->Blit(graphics, 190, bounce+128, &(girl.GetCurrentFrame()), 0.75f);
	// TODO 2: Draw the ship from the sprite sheet with some parallax effect
	// TODO 3: Animate the girl on the ship (see the sprite sheet)
	
	

	return UPDATE_CONTINUE;
}