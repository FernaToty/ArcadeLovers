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
#include "ModulePlayerAnim.h"
#include "ModuleFonts.h"
#include "ModulePlayerIntro.h"

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
	//reset counter
	counter = 0;
	countDown = 0;
	counterFonts = 0;
	counterFontsHide = false;
	ship = true;

	bgTexture = App->textures->Load("Assets/Sprites/water.png");
	cloudTexture = App->textures->Load("Assets/Sprites/clouds.png");
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

	//Ship sprites
	Ship = App->textures->Load("Assets/Sprites/Ship.png");
	ShipDestroyed = App->textures->Load("Assets/Sprites/ShipDestroyed.png");

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

	// L10: DONE 2: Enable (and properly disable) the player module
	//player animation intro
	App->playerIntro->Enable();
	App->playerIntro->position.x = 215;
	App->playerIntro->position.y = 450;

	App->player->Disable();
	//App->player->position.x = 212;
	//App->player->position.y = -1613;

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	//Finish state
	App->collisions->AddCollider({ 0, -12000, 500, 600 }, Collider::Type::WIN);
	
	return ret;
}

UpdateResult SceneLevel1::Update()
{
	App->render->camera.y -= 1 * SCREEN_SIZE;
	counter++;
	if (counter/400)
	{
		ship = false;
	}
	if (counter / 900)
	{
		counterFontsHide = true;
	}
	if (counter / 1600)
	{
		counterFontsHide = false;
	}
	if (counter / 2000)
	{
		App->playerIntro->Disable();
		anim = false;
	}
	if (anim == false)
	{
		App->player->Enable();
		App->enemies->Enable();
		App->collisions->Enable();
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevel1::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, -12350, NULL);
	App->render->DrawTexture(bgTexture, 0, -25500, NULL);
	App->render->DrawTexture(cloudTexture, 0, -14350, NULL, 0.8f);

	if (ship == true)
	{
		App->render->DrawTexture(Ship, 0, 0, NULL, 0.1f);
	}
	if (ship == false)
	{
		App->render->DrawTexture(ShipDestroyed, 0, -60, NULL, 0.3f);
	}

	if (counterFontsHide == true)
	{
		App->fonts->BlitText(150, 150, Font, "mission");
		App->fonts->BlitText(320, 150, Font, "1");
		counterFonts++;
		if ((counterFonts / 60))
		{
			App->fonts->BlitText(100, 200, Font, "o");
		}
		if ((counterFonts / 70))
		{
			App->fonts->BlitText(118, 200, Font, "f");
		}
		if ((counterFonts / 80))
		{
			App->fonts->BlitText(136, 200, Font, "f");
		}
		if ((counterFonts / 90))
		{
			App->fonts->BlitText(154, 200, Font, "e");
		}
		if ((counterFonts / 100))
		{
			App->fonts->BlitText(172, 200, Font, "n");
		}
		if ((counterFonts / 110))
		{
			App->fonts->BlitText(190, 200, Font, "s");
		}
		if ((counterFonts / 120))
		{
			App->fonts->BlitText(205, 200, Font, "i");
		}
		if ((counterFonts / 130))
		{
			App->fonts->BlitText(220, 200, Font, "v");
		}
		if ((counterFonts / 140))
		{
			App->fonts->BlitText(238, 200, Font, "e");
		}
		if ((counterFonts / 150))
		{
			App->fonts->BlitText(280, 200, Font, "t");
		}
		if ((counterFonts / 160))
		{
			App->fonts->BlitText(298, 200, Font, "a");
		}
		if ((counterFonts / 170))
		{
			App->fonts->BlitText(316, 200, Font, "r");
		}
		if ((counterFonts / 180))
		{
			App->fonts->BlitText(334, 200, Font, "g");
		}
		if ((counterFonts / 190))
		{
			App->fonts->BlitText(352, 200, Font, "e");
		}
		if ((counterFonts / 200))
		{
			App->fonts->BlitText(370, 200, Font, "t");
		}
		if (counterFonts / 210)
		{
			App->fonts->BlitText(200, 250, Font, "tone");
		}
		if ((counterFonts / 230))
		{
			App->fonts->BlitText(50, 300, Font, "m");
		}
		if ((counterFonts / 240))
		{
			App->fonts->BlitText(68, 300, Font, "a");
		}
		if ((counterFonts / 250))
		{
			App->fonts->BlitText(86, 300, Font, "y");
		}
		if ((counterFonts / 260))
		{
			App->fonts->BlitText(122, 300, Font, "y");
		}
		if ((counterFonts / 270))
		{
			App->fonts->BlitText(140, 300, Font, "o");
		}
		if ((counterFonts / 280))
		{
			App->fonts->BlitText(158, 300, Font, "u");
		}
		if ((counterFonts / 290))
		{
			App->fonts->BlitText(196, 300, Font, "f");
		}
		if ((counterFonts / 300))
		{
			App->fonts->BlitText(208, 300, Font, "i");
		}
		if ((counterFonts / 310))
		{
			App->fonts->BlitText(226, 300, Font, "g");
		}
		if ((counterFonts / 320))
		{
			App->fonts->BlitText(244, 300, Font, "h");
		}
		if ((counterFonts / 330))
		{
			App->fonts->BlitText(262, 300, Font, "t");
		}
		if ((counterFonts / 340))
		{
			App->fonts->BlitText(298, 300, Font, "b");
		}
		if ((counterFonts / 350))
		{
			App->fonts->BlitText(316, 300, Font, "r");
		}
		if ((counterFonts / 360))
		{
			App->fonts->BlitText(334, 300, Font, "a");
		}
		if ((counterFonts / 370))
		{
			App->fonts->BlitText(352, 300, Font, "v");
		}
		if (counterFonts / 380)
		{
			App->fonts->BlitText(370, 300, Font, "e");
		}
		if ((counterFonts / 390))
		{
			App->fonts->BlitText(388, 300, Font, "l");
		}
		if (counterFonts / 400)
		{
			App->fonts->BlitText(406, 300, Font, "y");
		}
		if (counterFonts == 700)
		{
			counterFonts = 0;
			counterFontsHide = false;
		}
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
			// if no coins inserted in 30 seconds GAMEOVER
			if ((countDown / 60) == 20)
			{
				App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
			}
			break;
		default:
			break;
		}
	}

	if (anim == false)
	{
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
	}
	
	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
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