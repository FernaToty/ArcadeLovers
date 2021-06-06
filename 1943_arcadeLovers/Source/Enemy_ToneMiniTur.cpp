#include "Enemy_ToneMiniTur.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#include <math.h>

#define PI 3.14159265

Enemy_ToneMiniTur::Enemy_ToneMiniTur(int x, int y) : Enemy(x, y)
{
	angle[0].PushBack({ 138, 1806, 18, 20 });
	angle[1].PushBack({ 156, 1806, 19, 18 });
	angle[2].PushBack({ 175, 1806, 19, 18 });
	angle[3].PushBack({ 194, 1806, 39, 18 });
	angle[4].PushBack({ 213, 1806, 19, 18 });
	angle[5].PushBack({ 232, 1806, 19, 18 });
	angle[6].PushBack({ 251, 1806, 19, 18 });
	angle[7].PushBack({ 270, 1806, 19, 18 });
	angle[8].PushBack({ 289, 1806, 19, 19 });
	angle[9].PushBack({ 308, 1806, 19, 18 });
	angle[10].PushBack({ 327, 1806, 19, 18 });
	angle[11].PushBack({ 346, 1806, 19, 18 });
	angle[12].PushBack({ 365, 1806, 19, 18 });
	angle[13].PushBack({ 384, 1806, 19, 18 });
	angle[14].PushBack({ 403, 1804, 19, 18 });
	angle[15].PushBack({ 422, 1804, 19, 20 });

	currentAnim = &angle[8];

	path.PushBack({ -0.3f, -0.9f }, 700, currentAnim);
	path.PushBack({ 0.0f, -0.9f }, 700, currentAnim);
	path.PushBack({ 0.3f, -0.9f }, 800, currentAnim);
	path.PushBack({ 0.0f, -0.9f }, 700, currentAnim);
	path.PushBack({ -0.3f, -0.9f }, 600, currentAnim);
	path.PushBack({ 0.0f, -0.8f }, 2000, currentAnim);
	path.PushBack({ 0.0f, -0.7f }, 5000, currentAnim);

	collider = App->collisions->AddCollider({ 0,0, 30, 32 }, Collider::Type::ENEMY, (Module*)App->enemies);
	health = 8;
	degrees = 0;
}

void Enemy_ToneMiniTur::Update()
{
	iPoint vect = position - App->player->position;

	if (vect.x != 0)
	{
		degrees = (atan(vect.y / vect.x) * 180) / PI;
		if (vect.x < 0)
			degrees += 180;
		else if (vect.x > 0 && vect.y < 0)
			degrees += 360;
	}
	else
		degrees = 270;

	if (0 <= degrees && degrees < 22.5f)                    // 0
		currentAnim = &angle[12];
	else if (22.5f <= degrees && degrees < 2 * 22.5f)       //12.5
		currentAnim = &angle[13];
	else if (2 * 22.5f <= degrees && degrees < 3 * 22.5f)   //35
		currentAnim = &angle[14];
	else if (3 * 22.5f <= degrees && degrees < 4 * 22.5f)   //57.5
		currentAnim = &angle[15];
	else if (4 * 22.5f <= degrees && degrees < 5 * 22.5f)   // 90
		currentAnim = &angle[0];
	else if (5 * 22.5f <= degrees && degrees < 6 * 22.5f)  //112.5
		currentAnim = &angle[1];
	else if (6 * 22.5f <= degrees && degrees < 7 * 22.5f)  //135
		currentAnim = &angle[2];
	else if ((7 * 22.5f) <= degrees && degrees < (8 * 22.5f))  //157.5
		currentAnim = &angle[3];
	else if (8 * 22.5f <= degrees && degrees < 9 * 22.5f)   //180
		currentAnim = &angle[4];
	else if (9 * 22.5f <= degrees && degrees < 10 * 22.5f)  //202.5
		currentAnim = &angle[5];
	else if (10 * 22.5f <= degrees && degrees < 11 * 22.5f)  //225
		currentAnim = &angle[6];
	else if (11 * 22.5f <= degrees && degrees < 12 * 22.5f)  //247.5
		currentAnim = &angle[7];
	else if (12 * 22.5f <= degrees && degrees < 13 * 22.5f)  //270
		currentAnim = &angle[8];
	else if (13 * 22.5f <= degrees && degrees < 14 * 22.5f)  //292.5
		currentAnim = &angle[9];
	else if (14 * 22.5f <= degrees && degrees < 15 * 22.5f)  // 315
		currentAnim = &angle[10];
	else if (15 * 22.5f <= degrees)                          //337.5
		currentAnim = &angle[11];

	path.Update();
	position = spawnPos + path.GetRelativePosition();

	if (health <= 0)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE);
		App->render->percentage -= 9;
	}
	counter++;
	if (counter >= 650)
	{
		counter = 0;
		App->particles->AddParticle(App->particles->enemyShoot, position.x, position.y, Collider::Type::ENEMY_SHOT, 0, true);
	}
	Enemy::Update();
}