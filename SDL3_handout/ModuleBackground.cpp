#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleBackground.h"
#include "SDL/include/SDL.h"
#include "ModuleRender.h"


ModuleBackground::ModuleBackground() : Module()
{}

// Destructor
ModuleBackground::~ModuleBackground()
{}

update_status ModuleBackground::Update()
{
	if (App->input->up == true) {
		App->render->y--;
		App->input->up = false;
	}
	if (App->input->down == true) {
		App->render->y++;
		App->input->down = false;
	}
	if (App->input->right == true) {
		App->render->x++;
		App->input->right = false;
	}
	if (App->input->left == true) {
		App->render->x--;
		App->input->left = false;
	}

	return update_status::UPDATE_CONTINUE;
}