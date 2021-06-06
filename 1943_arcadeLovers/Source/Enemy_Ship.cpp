#include "Enemy_Ship.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

Enemy_Ship::Enemy_Ship(int x, int y) : Enemy(x, y)
{
	ship.PushBack({ 195, 1445, 64, 311 });
	currentAnim = &ship;

	App->enemies->AddEnemy(Enemy_Type::TURRET, x + 9, y + 30);
	App->enemies->AddEnemy(Enemy_Type::TURRET, x + 9, y + 125);
	App->enemies->AddEnemy(Enemy_Type::TURRET, x + 9, y + 183);
	App->enemies->AddEnemy(Enemy_Type::TURRET, x + 9, y + 207);
	App->enemies->AddEnemy(Enemy_Type::TURRET, x + 9, y + 231);

	path.PushBack({ 0.0f, -0.8f }, 5000, &ship);

	collider = App->collisions->AddCollider({ 0, 0, 64, 311 }, Collider::Type::TONE);
}

void Enemy_Ship::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
