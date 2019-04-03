#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Image/Particle Spritesheet.png");
	cyclone.anim.PushBack({ 0, 71, 21, 18 },   0.3, 0, 0);
	cyclone.anim.PushBack({ 22, 71, 24, 19 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 47, 52, 34, 39 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 85, 57, 42, 34 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 129, 39, 31, 52 }, 0.3, 0, 0);
	cyclone.anim.PushBack({ 162, 40, 44, 51 }, 0.3, 0, 0);
	cyclone.anim.PushBack({ 205, 0, 77, 90 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 286, 0, 77, 90 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 364, 0, 83, 90 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 450, 0, 83, 90 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 536, 0, 86, 90 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 622, 0, 86, 90 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 706, 0, 85, 90 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 794, 0, 85, 90 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 880, 0, 88, 90 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 968, 0, 85, 90 },  0.3, 0, 0);
	cyclone.anim.PushBack({ 1056, 0, 78, 90 }, 0.3, 0, 0);
	cyclone.anim.PushBack({ 1137, 0, 78, 90 }, 0.3, 0, 0);
	cyclone.anim.PushBack({ 1219, 0, 74, 90 }, 0.3, 0, 0);
	cyclone.anim.PushBack({ 1295, 0, 74, 90 }, 0.3, 0, 0);
	cyclone.anim.PushBack({ 1370, 0, 52, 90 }, 0.3, 0, 0);
	cyclone.anim.PushBack({ 1427, 0, 52, 90 }, 0.3, 0, 0);
	cyclone.anim.PushBack({ 1481, 0, 42, 90 }, 0.3, 0, 0);

	cyclone.anim.loop = false;
	cyclone.speed = { 5, 0 };
	cyclone.life = 1000;
/*
	// Explosion particle
	explosion.anim.PushBack({ 274, 296, 33, 30 });
	explosion.anim.PushBack({ 313, 296, 33, 30 });
	explosion.anim.PushBack({ 346, 296, 33, 30 });
	explosion.anim.PushBack({ 382, 296, 33, 30 });
	explosion.anim.PushBack({ 419, 296, 33, 30 });
	explosion.anim.PushBack({ 457, 296, 33, 30 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	// TODO 2: Create the template for a new particle "laser"
	laser.anim.PushBack({ 168, 137, 47, 11 });
	laser.anim.PushBack({ 217, 136, 47, 13 });
	laser.anim.loop = true;
	laser.anim.speed = 0.1f;
	laser.speed = { 7, 0 };
	laser.life = 2000;
*/
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active[last_particle++] = p;
}


Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}