#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");
	timer = 0;
	bool ret = true;
	healtBar1 = App->textures->Load("Assets/Sprites/life_bar_1.png");
	healtBar5 = App->textures->Load("Assets/Sprites/life_bar_5.png");
	healtBar9 = App->textures->Load("Assets/Sprites/life_bar_9.png");

	bgTexture = App->textures->Load("Assets/Sprites/clouds.png");
	App->audio->PlayMusic("Assets/Music/GamePlayAudio.ogg", 1.0f);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 120, 12090);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 160, 12060);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, 12030);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, 12000);

	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 100, 10090);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 250, 10060);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 350, 10030);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 450, 10000);

	App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	App->particles->AddParticle(App->particles->threeWay, 120, 12090  , Collider::Type::POWERUP);

	App->collisions->AddCollider({ 0, 8000, 500, 200 }, Collider::Type::WIN);

	//App->powerUp->AddPowerUp(PowerUp_Type::THREEWAYPOWERUP, 900, 195);

	App->render->camera.x = 0;
	App->render->camera.y = 12470;

	App->player->Enable();
	App->enemies->Enable();
	//App->powerUp->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	App->render->camera.y -= 0.5f;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	switch (App->player->life)
	{
	case 3:
		App->render->Blit(healtBar1, 20, 600, NULL, 0.0f, false);
		break;
	case 2:
		App->render->Blit(healtBar5, 20, 600, NULL, 0.0f, false);
		break;
	case 1:
		App->render->Blit(healtBar9, 20, 600, NULL, 0.0f, false);
		break;
	default:
		break;
	}


	return Update_Status::UPDATE_CONTINUE;
}

void SceneLevel1::OnCollision(Collider* c1, Collider* c2)
{

}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();

	return true;
}