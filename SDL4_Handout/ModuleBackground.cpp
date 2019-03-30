#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// Background / sky


	// splash animation

	splash1.PushBack({ 0, 0, 0, 0 }, 0.01, 0, 0);
	splash1.PushBack({ 0, 465, 50, 105 }, 0.2, 0, 0);
	splash1.PushBack({ 261, 465, 95, 105 }, 0.2, 0, 0);
	splash1.PushBack({ 376, 465, 116, 105 }, 0.2, 0, 0);
	splash1.PushBack({ 531, 465, 128, 105 }, 0.2, 0, 0);
	splash1.PushBack({ 698, 465, 119, 105 }, 0.2, 0, 0);
	splash1.PushBack({ 836, 465, 129, 105 }, 0.2, 0, 0);
	splash1.PushBack({ 1023, 465, 126, 105 }, 0.2, 0, 0);

	splash2.PushBack({ 0, 0, 0, 0 }, 0.007, 0, 0);
	splash2.PushBack({ 0, 465, 50, 105 }, 0.2, 0, 0);
	splash2.PushBack({ 261, 465, 95, 105 }, 0.2, 0, 0);
	splash2.PushBack({ 376, 465, 116, 105 }, 0.2, 0, 0);
	splash2.PushBack({ 531, 465, 128, 105 }, 0.2, 0, 0);
	splash2.PushBack({ 698, 465, 119, 105 }, 0.2, 0, 0);
	splash2.PushBack({ 836, 465, 129, 105 }, 0.2, 0, 0);
	splash2.PushBack({ 1023, 465, 126, 105 }, 0.2, 0, 0);

	splash3.PushBack({ 0, 0, 0, 0 }, 0.005, 0, 0);
	splash3.PushBack({ 0, 465, 50, 105 }, 0.2, 0, 0);
	splash3.PushBack({ 261, 465, 95, 105 }, 0.2, 0, 0);
	splash3.PushBack({ 376, 465, 116, 105 }, 0.2, 0, 0);
	splash3.PushBack({ 531, 465, 128, 105 }, 0.2, 0, 0);
	splash3.PushBack({ 698, 465, 119, 105 }, 0.2, 0, 0);
	splash3.PushBack({ 836, 465, 129, 105 }, 0.2, 0, 0);
	splash3.PushBack({ 1023, 465, 126, 105 }, 0.2, 0, 0);
	

	// ground
	ground.x = 0;
	ground.y = 575;
	ground.w = 640;
	ground.h = 416;

	 //sea animation
	sea.PushBack({ 0, 0, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 704, 4, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 1408, 4, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 0, 156, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 704, 156, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 1408, 156, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 0, 312, 630, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 704, 311, 640, 140 }, 0.08f, 0, 0);
	sea.PushBack({ 1408, 311, 640, 140 }, 0.08f, 0, 0);
	
	
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
	initializecount();
	
}

// Update: draw background
update_status ModuleBackground::Update()
{
	for (int i = 0; i < 3; i++) {
		cont[i]++;
	}
	/*cont+=0.5;
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
	}*/
	// Draw everything --------------------------------------

	App->render->Blit(graphics, 0, -150, &ground);	

	App->render->Blit(graphics, 0, 53, &(sea.GetCurrentFrame()), 1);

	App->render->Blit(graphics, 80, /*bounce+*/70, &(splash1.GetCurrentFrame()), 1); // splash
	
	App->render->Blit(graphics, 210, /*bounce+*/70, &(splash2.GetCurrentFrame()), 1); // splash

	App->render->Blit(graphics, 370, /*bounce+*/35, &(splash3.GetCurrentFrame()), 1); // splash
	

	//background
	


	

	return UPDATE_CONTINUE;
}