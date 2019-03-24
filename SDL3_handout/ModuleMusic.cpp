#include "Globals.h"
#include "Application.h"
#include "ModuleMusic.h"
#include "SDL/include/SDL.h"
#include "SDL_Mixer/Include/SDL_mixer.h"

#pragma comment(lib, "SDL/libx86/SDL2.lib")
#pragma comment(lib, "SDL/libx86/SDL2main.lib")
#pragma comment(lib, "SDL_Mixer/libx86/SDL2_mixer.lib")


ModuleMusic::ModuleMusic() : Module()
{}

// Destructor
ModuleMusic::~ModuleMusic()
{}

bool ModuleMusic::Init() {
	Mix_Chunk *backMus;
	LOG("Init Music library");
	bool ret = true;
	int flags = (MIX_INIT_OGG);
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Sound lib. MIX_Init: %s", Mix_GetError());
		ret = false;
	}
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);

	backMus = Mix_LoadWAV("Backmusic.ogg");
	if (!backMus) {
		ret = false;
	}
	Mix_PlayChannel(-1, backMus, 0);
	return ret;
}
update_status ModuleMusic::PreUpdate(){

	return update_status::UPDATE_CONTINUE;
}
update_status ModuleMusic::PostUpdate(){

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleMusic::CleanUp()
{
	LOG("Freeing Sound library");

	Mix_CloseAudio();
	Mix_Quit();
	return true;
}