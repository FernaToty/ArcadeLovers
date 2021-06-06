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
	lose2 = false;
	win = false;

	bgTexture = App->textures->Load("Assets/Sprites/Water2.png");
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

	//power up
	WAY = App->textures->Load("Assets/Sprites/3WAY.png");
	AUTO = App->textures->Load("Assets/Sprites/AUTO.png");

	//coin audio
	Coin = App->audio->LoadFx("Assets/Fx/CoinInserted.wav");

	//lifebar low Fx
	lowHp = App->audio->LoadFx("Assets/Fx/LifeBarLow.wav");

	//Scene Audio
	App->audio->PlayMusic("Assets/Music/GamePlayAudio.ogg", 1.0f);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::TONE, 265, -9000);
	App->enemies->AddEnemy(Enemy_Type::SHIP, 140, -2200);	
	App->enemies->AddEnemy(Enemy_Type::TURRET, 149,-1888 );
	App->enemies->AddEnemy(Enemy_Type::TURRET, 149, -1913);
	App->enemies->AddEnemy(Enemy_Type::TURRET,  149, -2093);
	App->enemies->AddEnemy(Enemy_Type::TURRET, 149, -2132);
	App->enemies->AddEnemy(Enemy_Type::SHIP, 400, -6000);
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

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 320, -4500);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -4550);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -4600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 120, -4700);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -5000);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -5050);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -5150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -5300);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -5700);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -5250);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -5600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -5820);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 120, -6510);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -6490);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 160, -6470);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -6450);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -6470);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 280, -6490);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -6510);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -6950);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -7200);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -7150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -6900);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -7560);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -7540);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -7520);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 320, -7500);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 340, -7520);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -7540);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 400, -7560);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -9000);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -9200);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -9150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -9000);

	//POWERUPS
	App->particles->AddParticle(App->particles->Auto, 200, -2000, Collider::Type::AUTO);
	App->particles->AddParticle(App->particles->threeWayAnim, 200, -3800, Collider::Type::POWERUP);
	App->particles->AddParticle(App->particles->threeWayAnim, 400, -6700, Collider::Type::POWERUP);
	App->particles->AddParticle(App->particles->Auto, 100, -12000, Collider::Type::AUTO);
	
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
	App->collisions->AddCollider({ 0, -10000, 500, 600 }, Collider::Type::WIN);

	return ret;
}

UpdateResult SceneLevel2::Update()
{
	App->render->camera.y -= 1 * SCREEN_SIZE;

	if (lose2 == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->endScreenL, 90);
	}
	if (win == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->endScreen, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevel2::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, -12350, NULL);
	App->render->DrawTexture(bgTexture, 0, -25500, NULL);

	//POWER UP blit texture
	if (App->player->AutoPU == true)
	{
		App->render->DrawTexture(AUTO, 0, 0, NULL, false);
	}
	if (App->player->powerUp == true)
	{
		App->render->DrawTexture(WAY, 0, 0, NULL, false);
	}

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
			/* if no coins inserted in 10 seconds GAMEOVER*/
			if ((countDown / 60) == 20)
			{
				lose2 = true;
				App->player->destroyed = true;
				App->player->Disable();
				countDown = 0;
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