#include "Enemy_GreenPlane2.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenPlane2::Enemy_GreenPlane2(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({ 254, 84, 28, 31 });
	flyAnim.speed = 0.05f;
	flyAnim.loop = true;
	currentAnim = &flyAnim;

	flyFlip.PushBack({ 253, 119, 29, 23 });
	flyFlip.PushBack({ 281, 120, 30, 20 });
	flyFlip.PushBack({ 310, 119, 30, 23 });
	flyFlip.PushBack({ 340, 117, 28, 27 });
	flyFlip.speed = 0.05f;
	flyFlip.loop = true;
	//currentAnim = &flyFlip;

	/*flyBack.PushBack({ 142, 117, 22, 27 });
	flyBack.PushBack({ 170, 116, 24, 28 });
	flyBack.PushBack({ 198, 117, 22, 26 });
	flyBack.PushBack({ 25, 88, 26, 24 });*/
	flyBack.PushBack({ 340, 117, 28, 27 });
	flyBack.loop = true;
	flyBack.speed = 0.05f;
	//currentAnim = &flyBack;

	/*flyFlip.PushBack({ 253, 119, 29, 23 });*/
	flyFlip1.PushBack({ 281, 120, 30, 20 });
	flyFlip1.PushBack({ 253, 119, 29, 23 });
	flyFlip1.PushBack({ 252, 85, 31, 29 });
	flyFlip1.speed = 0.05f;
	flyFlip1.loop = true;

	path.PushBack({ 0.0f, 1.0f }, 500, &flyAnim);
	path.PushBack({ -0.1f, -1.0f }, 60, &flyFlip);
	path.PushBack({ 0.0f, -1.5f }, 450, &flyBack);
	path.PushBack({ -0.1f, -1.0f }, 60, &flyFlip1);
	path.PushBack({ 0.0f, 0.05f }, 200, &flyAnim);
	path.loop = true;
	
	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_GreenPlane2::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
