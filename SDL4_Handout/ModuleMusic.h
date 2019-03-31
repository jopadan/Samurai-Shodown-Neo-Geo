#ifndef __ModuleMusic_H__
#define __ModuleMusic_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_Mixer/Include/SDL_mixer.h"

#define MAX_MUSIC 50


class ModuleMusic : public Module
{
public:
	ModuleMusic();
	~ModuleMusic();
	bool Init();
	bool CleanUp();

	Mix_Music* const LoadMus(const char* path);
	Mix_Chunk* const LoadChunk(const char* path);
	void Play(Mix_Music * music, Mix_Chunk * chunk);
	bool Unload(Mix_Chunk * chunk);
	
public:
	Mix_Music* musics[MAX_MUSIC];
	Mix_Chunk* chunks[MAX_MUSIC];
};

#endif //