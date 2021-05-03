#include "Enemy_RedBird.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	/*flyAnim.PushBack({254, 27, 27, 25});
	flyAnim.speed = 0.2f;
	currentAnim = &flyAnim;

	flyBack.PushBack({ 111, 140, 35, 30 });
	flyBack.speed = 0.2f;

	path.PushBack({ 0.0f, 0.3f }, 500, &flyAnim);
	path.PushBack({ 0.0f, -0.3f }, 150, &flyBack);
	*/
	flyAnim.PushBack({ 254, 27, 27, 25 });
	flyAnim.speed = 0.1f;
	flyAnim.loop = true;
	currentAnim = &flyAnim;

	flyFlip.PushBack({ 196, 58, 28, 21 });
	flyFlip.PushBack({ 225, 57, 28, 21 });
	flyFlip.PushBack({ 253, 57, 28, 21 });
	flyFlip.PushBack({ 281, 56, 30, 23 });
	flyFlip.speed = 0.05f;
	flyFlip.loop = true;
	//currentAnim = &flyFlip;

	flyBack.PushBack({ 54, 57, 24, 25 });
	flyBack.PushBack({ 87, 57, 15, 26 });
	flyBack.PushBack({ 113, 57, 22, 25 });
	flyBack.PushBack({ 24, 26, 27, 26 });
	flyBack.loop = false;
	flyBack.speed = 0.05f;
	//currentAnim = &flyBack;

	path.PushBack({ 0.0f, 1.0f }, 500, &flyAnim);
	path.PushBack({ -0.1f, -1.0f }, 60, &flyFlip);
	path.PushBack({ 0.0f, -1.5f }, 30000, &flyBack);
	path.loop = true;

	collider = App->collisions->AddCollider({0, 0, 35, 30}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBird::Update()
{

	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
