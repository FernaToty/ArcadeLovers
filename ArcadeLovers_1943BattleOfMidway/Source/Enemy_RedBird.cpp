#include "Enemy_RedBird.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	flyAnim.PushBack({254, 27, 27, 25});
	flyAnim.speed = 0.2f;
	currentAnim = &flyAnim;

	/*flyBack.PushBack({ 111, 140, 35, 30 });
	flyBack.speed = 0.2f;*/

	/*path.PushBack({ 0.0f, 0.3f }, 500, &flyAnim);
	path.PushBack({ 0.0f, -0.3f }, 150, &flyBack);*/

	collider = App->collisions->AddCollider({0, 0, 35, 30}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBird::Update()
{

	position.y += 0.5f;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
