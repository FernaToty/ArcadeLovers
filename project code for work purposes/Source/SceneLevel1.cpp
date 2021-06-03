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
	cloudTexture = App->textures->Load("Assets/Sprites/clouds.png");
	UiTexture = App->textures->Load("Assets/Sprites/1943UI.png");

	healthBar1 = App->textures->Load("Assets/Sprites/life_bar_1.png");
	healthBar2 = App->textures->Load("Assets/Sprites/life_bar_2.png");
	healthBar3 = App->textures->Load("Assets/Sprites/life_bar_3.png");
	healthBar4 = App->textures->Load("Assets/Sprites/life_bar_4.png");
	healthBar5 = App->textures->Load("Assets/Sprites/life_bar_5.png");
	healthBar6 = App->textures->Load("Assets/Sprites/life_bar_6.png");
	healthBar7 = App->textures->Load("Assets/Sprites/life_bar_7.png");
	healthBar8 = App->textures->Load("Assets/Sprites/life_bar_8.png");
	healthBar9 = App->textures->Load("Assets/Sprites/life_bar_9.png");

	App->audio->PlayMusic("Assets/Music/GamePlayAudio.ogg", 1.0f);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -1200);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -1250);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -1300);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -1400);

	//App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -1000);
	//App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 320, -1000);
	//App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 340, -1000);
	//App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -1000);

	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 830, 100);
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 850, 100);
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 870, 100);
	//App->enemies->AddEnemy(Enemy_Type::BROWNSHIP, 890, 100);

	//App->enemies->AddEnemy(Enemy_Type::MECH, 900, 195);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	//App->UI->Enable();
	
	//App->collisions->Enable();
	
	return ret;
}

UpdateResult SceneLevel1::Update()
{
	App->render->camera.y -= 1 * SCREEN_SIZE;

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevel1::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, -12350, NULL);
	App->render->DrawTexture(cloudTexture, 0, -12350, NULL, 0.8f);
	App->render->DrawTexture(UiTexture, 0, 0, NULL, false);

	switch (App->player->playerlife)
	{
	case 9:
		App->render->DrawTexture(healthBar1, 20, 570, NULL, false);
		break;
	case 8:
		App->render->DrawTexture(healthBar2, 20, 570, NULL, false);
		break;
	case 7:
		App->render->DrawTexture(healthBar3, 20, 570, NULL, false);
		break;
	case 6:
		App->render->DrawTexture(healthBar4, 20, 570, NULL, false);
		break;
	case 5:
		App->render->DrawTexture(healthBar5, 20, 570, NULL, false);
		break;
	case 4:
		App->render->DrawTexture(healthBar6, 20, 570, NULL, false);
		break;
	case 3:
		App->render->DrawTexture(healthBar7, 20, 570, NULL, false);
	case 2:
		App->render->DrawTexture(healthBar8, 20, 570, NULL, false);
		break;
	case 1:
		App->render->DrawTexture(healthBar9, 20, 570, NULL, false);
		break;
	default:
		break;
	}
	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	//App->UI->Disable();
	// L10: TODO 5: Remove All Memory Leaks - no solution here... ;)

	return true;
}