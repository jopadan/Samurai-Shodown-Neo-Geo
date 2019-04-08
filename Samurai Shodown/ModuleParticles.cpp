#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer2.h"

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
	cyclone.anim.PushBack({ 0, 71, 21, 18 },   0.4,  0, 50);
	cyclone.anim.PushBack({ 22, 71, 24, 19 },  0.4,  0, 50);
	cyclone.anim.PushBack({ 47, 52, 34, 39 },  0.4,  0, 50);
	cyclone.anim.PushBack({ 85, 57, 42, 34 },  0.4,  0, 50);
	cyclone.anim.PushBack({ 129, 39, 31, 52 }, 0.4,  0, 50);
	cyclone.anim.PushBack({ 162, 40, 44, 51 }, 0.4,  0, 50);
	cyclone.anim.PushBack({ 205, 0, 77, 90 },  0.3, -10, 10);
	cyclone.anim.PushBack({ 286, 0, 77, 90 },  0.3,  0, 10);
	cyclone.anim.PushBack({ 364, 0, 83, 90 },  0.3,  0, 10);
	cyclone.anim.PushBack({ 450, 0, 83, 90 },  0.3,  0, 10);
	cyclone.anim.PushBack({ 536, 0, 86, 90 },  0.3,  0, 10);
	cyclone.anim.PushBack({ 622, 0, 86, 90 },  0.3,  0, 10);
	cyclone.anim.PushBack({ 706, 0, 85, 90 },  0.3,  0, 10);
	cyclone.anim.PushBack({ 794, 0, 85, 90 },  0.3,  0, 10);
	cyclone.anim.PushBack({ 880, 0, 88, 90 },  0.3,  0, 10);
	cyclone.anim.PushBack({ 968, 0, 85, 90 },  0.3,  0, 10);
	cyclone.anim.PushBack({ 1056, 0, 78, 90 }, 0.3,  0, 10);
	cyclone.anim.PushBack({ 1137, 0, 78, 90 }, 0.3,  0, 10);
	cyclone.anim.PushBack({ 1219, 0, 74, 90 }, 0.3,  0, 10);
	cyclone.anim.PushBack({ 1295, 0, 74, 90 }, 0.3,  0, 10);
	cyclone.anim.PushBack({ 1370, 0, 52, 90 }, 0.3,  0, 10);
	cyclone.anim.PushBack({ 1427, 0, 52, 90 }, 0.3,  0, 10);
	cyclone.anim.PushBack({ 1481, 0, 42, 90 }, 0.3,  0, 10);

	cyclone.anim.loop = true;
	cyclone.speed = { 4, 0 };
	cyclone.life = 2000;
	

	tornado.anim.PushBack({ 0, 172, 60, 217 }, 0.4, 0, 50);
	tornado.anim.PushBack({ 85, 172, 60, 217 }, 0.4, 0, 50);
	tornado.anim.PushBack({ 181, 172, 60, 217 }, 0.4, 0, 50);
	tornado.anim.PushBack({ 298, 172, 60, 217 }, 0.4, 0, 50);
	tornado.anim.PushBack({ 404, 172, 60, 217 }, 0.4, 0, 50);
	tornado.anim.PushBack({ 507, 172, 60, 217 }, 0.4, 0, 50);
	tornado.anim.PushBack({ 627, 172, 60, 217 }, 0.4, 0, 50);
	tornado.anim.PushBack({ 760, 172, 60, 217 }, 0.4, 0, 50);
	tornado.anim.PushBack({ 865, 172, 60, 217 }, 0.4, 0, 50);
	tornado.anim.loop = true;
	tornado.speed = { 0, 0 };
	tornado.life = 1000;
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
			
			App->render->Blit(graphics, p->position.x + p->anim.pivotx[p->anim.returnCurrentFrame()], p->position.y + p->anim.pivoty[p->anim.returnCurrentFrame()], &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, int delay)
{

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i]==nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x - 120;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider({p->position.x, p->position.y+30, 52, 70 }, collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_ENEMY)
	{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			/*delete active[i];
			active[i] = nullptr;
			*/
			active[i]->anim = tornado.anim;
			active[i]->speed = tornado.speed;
			active[i]->life = tornado.life;
			active[i]->position.x += 50;
			active[i]->position.y -= 150;
			active[i]->collider->to_delete = true;
		
			break;
		}
	}
}
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
Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if (((int)SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y+30);

	return ret;
}