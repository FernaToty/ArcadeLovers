#include "Enemy_Tone.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"

Enemy_Tone::Enemy_Tone(int x, int y) : Enemy(x, y)
{
	tone.PushBack({ 17, 1420, 106, 448 });
	currentAnim = &tone;
	
	App->enemies->AddEnemy(Enemy_Type::TONETURRET, x + 30, y + 63);
	App->enemies->AddEnemy(Enemy_Type::TONETURRET, x + 30, y + 88);
	App->enemies->AddEnemy(Enemy_Type::TONETURRET, x + 30, y + 113);
	App->enemies->AddEnemy(Enemy_Type::MINITURRET, x + 70, y + 179);
	App->enemies->AddEnemy(Enemy_Type::MINITURRET, x + 8, y + 179);
	App->enemies->AddEnemy(Enemy_Type::MINITURRET, x + 8, y + 232);
	App->enemies->AddEnemy(Enemy_Type::MINITURRET, x + 70, y + 232);
	App->enemies->AddEnemy(Enemy_Type::TONETURRET, x + 30, y + 295);
	App->enemies->AddEnemy(Enemy_Type::TONETURRET, x + 30, y + 332);
	App->enemies->AddEnemy(Enemy_Type::TONECORE, x + 24, y + 147);


	path.PushBack({ -0.3f, -0.9f }, 700, &tone);
	path.PushBack({ 0.0f, -0.9f }, 700, &tone);
	path.PushBack({ 0.3f, -0.9f }, 800, &tone);
	path.PushBack({ 0.0f, -0.9f }, 700, &tone);
	path.PushBack({ -0.3f, -0.9f }, 600, &tone);
	path.PushBack({ 0.0f, -0.8f }, 2000, &tone);
	path.PushBack({ 0.0f, -0.7f }, 5000, &tone);

	collider = App->collisions->AddCollider({0, 0, 106, 448}, Collider::Type::TONE);
}

void Enemy_Tone::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
