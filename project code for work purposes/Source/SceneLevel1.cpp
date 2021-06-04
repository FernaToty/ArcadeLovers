#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

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
	InsertCoinRevive = App->textures->Load("Assets/Sprites/InsertCoinRevive.png");

	//healtbar
	healthBar1 = App->textures->Load("Assets/Sprites/life_bar_1.png");
	healthBar2 = App->textures->Load("Assets/Sprites/life_bar_2.png");
	healthBar3 = App->textures->Load("Assets/Sprites/life_bar_3.png");
	healthBar4 = App->textures->Load("Assets/Sprites/life_bar_4.png");
	healthBar5 = App->textures->Load("Assets/Sprites/life_bar_5.png");
	healthBar6 = App->textures->Load("Assets/Sprites/life_bar_6.png");
	healthBar7 = App->textures->Load("Assets/Sprites/life_bar_7.png");
	healthBar8 = App->textures->Load("Assets/Sprites/life_bar_8.png");
	healthBar9 = App->textures->Load("Assets/Sprites/life_bar_9.png");


	//Coins
	Credit1 = App->textures->Load("Assets/Sprites/Credit1.png");
	Credit2 = App->textures->Load("Assets/Sprites/Credit2.png");
	Credit3 = App->textures->Load("Assets/Sprites/Credit3.png");
	Credit4 = App->textures->Load("Assets/Sprites/Credit4.png");
	Credit5 = App->textures->Load("Assets/Sprites/Credit5.png");
	Credit6 = App->textures->Load("Assets/Sprites/Credit6.png");
	Credit7 = App->textures->Load("Assets/Sprites/Credit7.png");
	Credit8 = App->textures->Load("Assets/Sprites/Credit8.png");
	Credit9 = App->textures->Load("Assets/Sprites/Credit9.png");

	//Scene Audio
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

	//Finish state
	App->collisions->AddCollider({ 0, -12000, 500, 600 }, Collider::Type::WIN);
	
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

	//If player is dead, insert coin to revive (max 9 coins)
	if (App->player->playerlife == 0)
	{
		switch (App->sceneIntro->coin)
		{
		case 9:
			App->render->DrawTexture(Credit9, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			break;
		case 8:
			App->render->DrawTexture(Credit8, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
			}
			break;
		case 7:
			App->render->DrawTexture(Credit7, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
			}
			break;
		case 6:
			App->render->DrawTexture(Credit6, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
			}
			break;
		case 5:
			App->render->DrawTexture(Credit5, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
			}
			break;
		case 4:
			App->render->DrawTexture(Credit4, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
			}
			break;
		case 3:
			App->render->DrawTexture(Credit3, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
			}
			break;
		case 2:
			App->render->DrawTexture(Credit2, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
			}
			break;
		case 1:
			App->render->DrawTexture(Credit1, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
			}
			break;
		case 0:
			counter++;
			if ((counter / 60) % 2 == 0)
			{
				App->render->DrawTexture(InsertCoinRevive, 0, 0, NULL, false);
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
			}
			// if no coins inserted in 30 seconds GAMEOVER
			if ((counter/60) == 60)
			{
				App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
			}
			break;
		default:
			break;
		}
	}

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
		break;
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