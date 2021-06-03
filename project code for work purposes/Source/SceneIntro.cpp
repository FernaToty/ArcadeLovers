#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModulePlayerAnim.h"
#include "ModuleCollisions.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;


	bgTexture = App->textures->Load("Assets/Sprites/water.png");
	menuTexture = App->textures->Load("Assets/Sprites/1943Menu.png");
	cloudTexture = App->textures->Load("Assets/Sprites/clouds.png");
	InsertCoin = App->textures->Load("Assets/Sprites/InsertCoin.png");
	Credits = App->textures->Load("Assets/Sprites/Credit0.png");
	Credit1 = App->textures->Load("Assets/Sprites/Credit1.png");

	healthBar1 = App->textures->Load("Assets/Sprites/life_bar_1.png");
	healthBar2 = App->textures->Load("Assets/Sprites/life_bar_2.png");
	healthBar3 = App->textures->Load("Assets/Sprites/life_bar_3.png");
	healthBar4 = App->textures->Load("Assets/Sprites/life_bar_4.png");
	healthBar5 = App->textures->Load("Assets/Sprites/life_bar_5.png");
	healthBar6 = App->textures->Load("Assets/Sprites/life_bar_6.png");
	healthBar7 = App->textures->Load("Assets/Sprites/life_bar_7.png");
	healthBar8 = App->textures->Load("Assets/Sprites/life_bar_8.png");
	healthBar9 = App->textures->Load("Assets/Sprites/life_bar_9.png");

	App->audio->PlayMusic("Assets/Music/Title.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->playerAnim->Enable();
	//App->collisions->Enable();
	coin = !coin;

	return ret;
}

UpdateResult SceneIntro::Update()
{
	App->render->camera.y -= 1 * SCREEN_SIZE;

	if (App->input->keys[SDL_SCANCODE_C] == KeyState::KEY_DOWN || App->input->pads->r3 == true)
	{
		coin = true;
	}
	if (coin == true)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN || App->input->pads->start == true)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
		}
	}
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneIntro::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, -12350, NULL);
	App->render->DrawTexture(cloudTexture, 0, -12350, NULL, 0.8f);
	App->render->DrawTexture(menuTexture, 0, 0, NULL, false);
	
	counter++;
	if (coin == true)
	{
		App->render->DrawTexture(Credit1, 0, 0, NULL, false);
	}
	else if ((counter / 60) % 2 == 0)
	{
		App->render->DrawTexture(InsertCoin, 0, 0, NULL, false);
	}
	
	if (coin == false)
	{
		App->render->DrawTexture(Credits, 0, 0, NULL, false);
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

bool SceneIntro::CleanUp()
{
	// L10: DONE 2: Enable (and properly disable) the player module
	App->playerAnim->Disable();
	//App->collisions->Disable();

	return true;
}