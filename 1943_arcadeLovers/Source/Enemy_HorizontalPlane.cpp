#include "Enemy_HorizontalPlane.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Enemy_HorizontalPlane::Enemy_HorizontalPlane(int x, int y) : Enemy(x, y)
{
	/*flyAnim.PushBack({254, 27, 27, 25});
	flyAnim.speed = 0.2f;
	currentAnim = &flyAnim;

	flyBack.PushBack({ 111, 140, 35, 30 });
	flyBack.speed = 0.2f;

	path.PushBack({ 0.0f, 0.3f }, 500, &flyAnim);
	path.PushBack({ 0.0f, -0.3f }, 150, &flyBack);
	*/
	flyAnim.PushBack({ 139, 306, 28, 25});
	flyAnim.speed = 0.1f;
	flyAnim.loop = true;
	currentAnim = &flyAnim;

	flyFlip.PushBack({ 168, 307, 28, 25 });
	flyFlip.PushBack({ 197, 307, 27, 23 });
	flyFlip.speed = 0.05f;
	flyFlip.loop = false;
	flyFlip2.PushBack({ 228, 310, 23, 22 });
	flyFlip2.PushBack({ 256, 310, 24, 22 });
	flyFlip2.speed = 0.05f;
	flyFlip2.loop = false;
	flyFlip3.PushBack({ 281, 309, 27, 23 });
	flyFlip3.PushBack({ 308, 308, 30, 25 });
	flyFlip3.PushBack({ 339, 310, 28, 21 });
	flyFlip3.speed = 0.05f;
	flyFlip3.loop = false;
	//currentAnim = &flyFlip;

	flyBack.PushBack({ 339, 310, 28, 21 });
	flyBack.PushBack({ 368, 309, 28, 21 });
	
	flyBack.loop = false;
	flyBack.speed = 0.05f;
	//currentAnim = &flyBack;

	path.PushBack({ 0.0f, 0.0f }, 400, &flyAnim);
	path.PushBack({ 1.5f, -0.5f }, 200, &flyAnim);
	path.PushBack({ 1.0f, 0.5f }, 60, &flyFlip);
	path.PushBack({ 0.0f, 0.0f }, 50, &flyFlip2);
	path.PushBack({ -0.1f, 0.5f }, 60, &flyFlip3);
	path.PushBack({ -2.0f, -1.0f }, 30000, &flyBack);
	path.loop = true;

	collider = App->collisions->AddCollider({ 0, 0, 28, 25 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_HorizontalPlane::Update()
{

	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}