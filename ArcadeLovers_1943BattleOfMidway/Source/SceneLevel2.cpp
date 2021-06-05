#include "SceneLevel2.h"

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
#include "ModulePlayerAnim.h"
#include "ModuleFonts.h"
#include "ModulePlayerIntro.h"
#include "ModuleParticles.h"

SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel2::~SceneLevel2()
{

}

// Load assets
bool SceneLevel2::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//reset counter
	counter = 0;
	countDown = 0;
	counterFonts = 0;
	counterFontsHide = false;
	ship = true;

	bgTexture = App->textures->Load("Assets/Sprites/water.png");
	UiTexture = App->textures->Load("Assets/Sprites/1943UI.png");
	InsertCoinRevive = App->textures->Load("Assets/Sprites/InsertCoinRevive.png");

	//look up table for fonts in story typing
	char lookupTable2[] = { "0123456789abcdefghijklmnopqrstuvwxyz" };
	Font = App->fonts->Load("Assets/Fonts/Fonts.png", lookupTable2, 1);

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

	//coin audio
	Coin = App->audio->LoadFx("Assets/Fx/CoinInserted.wav");

	//TypeWritter audio
	//TypeWritter = App->audio->LoadFx("Assets/Fx/Type.wav");

	//Loop animation Audio 
	//loopAudio = App->audio->LoadFx("Assets/Fx/LoopAnimAudio.wav");

	//Scene Audio
	App->audio->PlayMusic("Assets/Music/GamePlayAudio.ogg", 1.0f);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -3000);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -3150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -3300);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -2800);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -3200);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -3250);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -3300);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -3400);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -3300);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -3450);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -3400);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -3500);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -3800);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -3750);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -3600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -3900);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -4000);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -4150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -4300);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -4350);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -4500);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -4550);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -4600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -4700);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -5000);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -5050);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -5150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -5300);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -5700);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -5250);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -5600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -5820);

	// L10: DONE 2: Enable (and properly disable) the player module
	//player animation intro
	App->player->Enable();
	App->playerIntro->position.x = 0;
	App->playerIntro->position.y = 0;

	App->enemies->Enable();
	App->collisions->Enable();

	App->render->camera.x = 0;
	App->render->camera.y = -1800;
	//Finish state
	App->collisions->AddCollider({ 0, -12000, 500, 600 }, Collider::Type::WIN);

	return ret;
}

UpdateResult SceneLevel2::Update()
{
	App->render->camera.y -= 1 * SCREEN_SIZE;

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevel2::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, -12350, NULL);
	App->render->DrawTexture(bgTexture, 0, -25500, NULL);

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
				App->audio->PlayFx(Coin);
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
				App->audio->PlayFx(Coin);
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
				App->audio->PlayFx(Coin);
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
				App->audio->PlayFx(Coin);
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
				App->audio->PlayFx(Coin);
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
				App->audio->PlayFx(Coin);
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
				App->audio->PlayFx(Coin);
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
				App->audio->PlayFx(Coin);
			}
			break;
		case 0:
			countDown++;
			if ((countDown / 60) % 2 == 0)
			{
				App->render->DrawTexture(InsertCoinRevive, 0, 0, NULL, false);
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
				App->audio->PlayFx(Coin);
			}
			/* if no coins inserted in 30 seconds GAMEOVER*/
			if ((countDown / 60) == 20)
			{
				App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
			}
			break;
		default:
			break;
		}
	}

	//top UI
	App->render->DrawTexture(UiTexture, 0, 0, NULL, false);

	//player lifebar
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

bool SceneLevel2::CleanUp()
{
	// L10: DONE 2: Enable (and properly disable) the player module
	if (anim == false)
	{
		App->player->Disable();
		App->enemies->Disable();
		App->collisions->Disable();
	}

	//App->UI->Disable();
	// L10: TODO 5: Remove All Memory Leaks - no solution here... ;)

	return true;
}