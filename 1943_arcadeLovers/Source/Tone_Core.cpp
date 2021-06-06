#include "Tone_Core.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#include <math.h>

#define PI 3.14159265

Tone_Core::Tone_Core(int x, int y) : Enemy(x, y)
{
	core.PushBack({ 394, 1433, 45, 43 });
	currentAnim = &core;

	path.PushBack({ -0.3f, -0.9f }, 700, currentAnim);
	path.PushBack({ 0.0f, -0.9f }, 700, currentAnim);
	path.PushBack({ 0.3f, -0.9f }, 800, currentAnim);
	path.PushBack({ 0.0f, -0.9f }, 700, currentAnim);
	path.PushBack({ -0.3f, -0.9f }, 600, currentAnim);
	path.PushBack({ 0.0f, -0.8f }, 2000, currentAnim);
	path.PushBack({ 0.0f, -0.7f }, 5000, currentAnim);
	collider = App->collisions->AddCollider({ 0,0, 45, 43 }, Collider::Type::ENEMY, (Module*)App->enemies);
	health = 10;
	degrees = 0;
}

void Tone_Core::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	if (health <= 0)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE);
		App->render->percentage -= 9;
	}
	Enemy::Update();
}