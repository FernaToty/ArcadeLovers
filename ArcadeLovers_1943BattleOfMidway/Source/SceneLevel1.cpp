#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

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

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/water.png");
	App->audio->PlayMusic("Assets/Music/GamePlayAudio.ogg", 1.0f);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 200, 12090);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 220, 12070);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 240, 12050);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 260, 12030);

	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 735, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 750, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 775, 120);
	App->enemies->AddEnemy(Enemy_Type::REDBIRD, 790, 120);

	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 450, 12090);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 150, 12070);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 290, 12050);
	App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 320, 12030);

	App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	App->render->camera.x = 0;
	App->render->camera.y = 12500;

	App->player->Enable();
	App->enemies->Enable();

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

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();

	return true;
}