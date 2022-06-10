#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 1000

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	int born = 0;
	int life = 0;
	bool fx_played = false;
	char* direction;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type /*= COLLIDER_NONE*/, int delay);

private:

	SDL_Texture* graphics = nullptr;
	
	Particle* active[MAX_ACTIVE_PARTICLES];
	//uint last_particle = 0;

public:
	Animation * current_animation = nullptr;
	Particle cyclone;
	Particle tornado;
	
	//Particle flower;
	int* direction[MAX_ACTIVE_PARTICLES];
};

#endif // __MODULEPARTICLES_H__