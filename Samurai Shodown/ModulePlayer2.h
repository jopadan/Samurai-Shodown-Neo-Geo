#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleMusic.h"
#include "Globals.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer2 : public Module
{
private:
	int jump;
	int speed = 2;
	bool floor = true;
	int initialPos;
	float jumpSpeed = 6;
	int animstart = 0;
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jumpup;
	iPoint position;
	Collider *colliderPlayer2;
};
#endif