#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i) particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/explosion.png");

	// Explosion particle
	explosion.anim.PushBack({ 85, 91, 23, 22 });
	explosion.anim.PushBack({ 116, 88, 35, 31 });
	explosion.anim.PushBack({ 151, 88, 38, 30 });
	explosion.anim.PushBack({ 188, 86, 35, 31 });
	explosion.anim.PushBack({ 225, 84, 36, 33 });
	explosion.anim.PushBack({ 262, 84, 36, 32 });
	explosion.anim.PushBack({ 298, 83, 38, 34 });
	explosion.anim.PushBack({ 335, 80, 37, 34 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	//players death
	death.anim.PushBack({ 60, 311, 36, 30 });
	death.anim.PushBack({ 102, 310, 44, 33 });
	death.anim.PushBack({ 152, 313, 47, 35 });
	death.anim.PushBack({ 201, 312, 45, 39 });
	death.anim.PushBack({ 247, 307, 52, 43 });
	death.anim.PushBack({ 296, 308, 50, 45 });
	death.anim.PushBack({ 352, 306, 44, 45 });
	death.anim.PushBack({ 404, 305, 48, 48 });
	death.anim.PushBack({ 58, 352, 42, 48 });
	death.anim.PushBack({ 79, 352, 39, 48 });
	death.anim.PushBack({ 110, 352, 43, 54 });
	death.anim.PushBack({ 156, 352, 49, 52 });
	death.anim.PushBack({ 205, 351, 49, 55 });
	death.anim.PushBack({ 254, 352, 50, 53 });
	death.anim.PushBack({ 304, 352, 51, 49 });
	death.anim.PushBack({ 355, 352, 50, 53 });
	death.anim.PushBack({ 409, 364, 42, 41 });
	death.anim.loop = false;
	death.speed.y -= 2;
	death.anim.speed = 0.1f;

	// 3-Way Power-up animation shoot
	threeWayL.anim.PushBack({ 283, 421, 19, 23 });
	threeWayL.speed.y -= 5;
	threeWayL.speed.x -= 2;
	threeWayL.lifetime = 180;

	threeWayR.anim.PushBack({ 329, 421, 17, 23 });
	threeWayR.speed.y -= 5;
	threeWayR.speed.x += 2;
	threeWayR.lifetime = 180;


	// 3Way Power-up anim
	threeWayAnim.anim.PushBack({ 155, 482, 31, 29 });
	threeWayAnim.anim.PushBack({ 185, 482, 29, 28 });
	threeWayAnim.anim.PushBack({ 213, 484, 29, 28 });
	threeWayAnim.anim.PushBack({ 241, 484, 29, 28 });
	threeWayAnim.anim.loop = true;
	threeWayAnim.anim.speed = 0.1f;

	//shoot anim
	laser.anim.PushBack({ 304, 420, 23, 25 });
	laser.speed.y -= 5;
	laser.lifetime = 180;
	laser.anim.speed = 0.2f;

	return true;
}

UpdateResult ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
	}
}

UpdateResult ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModuleParticles::PostUpdate()
{
	// Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->DrawTexture(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			// Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}