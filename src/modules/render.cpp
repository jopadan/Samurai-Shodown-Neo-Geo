#include "globals.h"
#include "app.h"
#include "render.h"
#include "window.h"
#include "input.h"
#include "player.h"
#include "player2.h"
#include "SDL.h"
#include <time.h>


ModuleRender::ModuleRender() : Module()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
	srand(time(NULL));

}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	if (renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	camera.x += App->player->position.x - 30;
	return ret;

	
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()
{
	int speed = 12;
	/*if ((App->player->position.x + App->player2->position.x) / 2 > camera.x + SCREEN_WIDTH / 2 ) {
		//camera.x += speed;
	}
	if ((App->player->position.x + App->player2->position.x) / 2 < camera.x + SCREEN_WIDTH / 2) {
		//camera.x -= speed;
	}
	if ((App->player2->position.x - App->player->position.x) >140){
	//camera.x = (-(App->player->position.x + App->player2->position.x) + SCREEN_WIDTH) * 3;
		camera.x += -(App->player->position.x/3);
	}
	*/
	if((-(((App->player->position.x + App->player2->position.x + 60) / 2 - SCREEN_WIDTH / 2) )) < 0 && (-(((App->player->position.x + App->player2->position.x + 60) / 2 - SCREEN_WIDTH / 2) )) > -333)
	if ((camera.x - 912) / -2 != (App->player->position.x + App->player2->position.x) / 2){
		camera.x = -(((App->player->position.x + App->player2->position.x+60) / 2 - SCREEN_WIDTH/2 ));
	
}
/*
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_REPEAT)
		camera.y -= speed;

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_REPEAT)
		camera.x += speed;

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_REPEAT)
		camera.x -= speed;
*/
	if (shaking)
		UpdateCameraShake();
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, SDL_RendererFlip flip, float speed)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x =  (int)((camera.x + camera_offset.x) * speed) + x * SCREEN_SIZE;
	rect.y =  (int)((camera.y + camera_offset.y) * speed) + y * SCREEN_SIZE;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	//SDL_RenderCopy_Ex https://wiki.libsdl.org/SDL_RenderCopyEx

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, 0, 0, flip) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}
bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x =(int)((camera.x + camera_offset.x) + rect.x * SCREEN_SIZE);
		rec.y = (int)((camera.y + camera_offset.y) + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void ModuleRender::StartCameraShake(int duration, float magnitude)
{
	//TODO 1: Store the data and start the shake
	shake_magnitude = magnitude;
	shake_duration = duration;
	shaking = true;
	shake_timer = SDL_GetTicks();
}

void ModuleRender::UpdateCameraShake()
{
	//TODO 2: Update the shake timer, stop shaking if we reach the full duration
	//		  Generate a random value and set the camera offset
	if (SDL_GetTicks() - shake_timer < shake_duration) {

		camera_offset.x = -(int)shake_magnitude + rand() % (int)shake_magnitude;
		camera_offset.y = -(int)shake_magnitude + rand() % (int)shake_magnitude;

	}
	else {
		camera_offset.x = 0;
		camera_offset.y = 0;
		shaking = false;
	}

}

