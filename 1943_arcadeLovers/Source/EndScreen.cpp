#include "EndScreen.h"

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

#include "SDL/include/SDL_scancode.h"

EndScreen::EndScreen(bool startEnabled) : Module(startEnabled)
{
	planeAnim.PushBack({ 144, 68, 46, 12 });
	planeAnim.PushBack({ 232, 62, 54, 31 });
	planeAnim.PushBack({ 328, 73, 47, 48 });
	planeAnim.PushBack({ 93, 150, 59, 52 });
	planeAnim.PushBack({ 206, 157, 79, 53 });
	planeAnim.PushBack({ 317, 150, 130, 62 });
	planeAnim.PushBack({ 98, 248, 126, 107 });
	planeAnim.PushBack({ 269, 239, 141, 227 });
	planeAnim.speed = 0.01f;
	planeAnim.loop = false;
}

EndScreen::~EndScreen()
{

}

// Load assets
bool EndScreen::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	endPlane = true;

	EndPlane = App->textures->Load("Assets/Sprites/successlevel.png");

	currentAnim = &planeAnim;

	endPlane = true;

	EndPlane = App->textures->Load("Assets/Sprites/EndPlane1.png");
	EndPlane1 = App->textures->Load("Assets/Sprites/EndPlane2.png");
	EndPlane2 = App->textures->Load("Assets/Sprites/EndPlane3.png");
	EndPlane3 = App->textures->Load("Assets/Sprites/EndPlane4.png");
	EndPlane4 = App->textures->Load("Assets/Sprites/EndPlane5.png");
	EndPlane5 = App->textures->Load("Assets/Sprites/EndPlane6.png");
	EndPlane6 = App->textures->Load("Assets/Sprites/EndPlane7.png");
	EndPlane7 = App->textures->Load("Assets/Sprites/EndPlane8.png");

	char lookupTable2[] = { "0123456789abcdefghijklmnopqrstuvwxyz" };
	Font = App->fonts->Load("Assets/Fonts/Fonts.png", lookupTable2, 1);

	healthBar1 = App->textures->Load("Assets/Sprites/life_bar_1.png");
	healthBar2 = App->textures->Load("Assets/Sprites/life_bar_2.png");
	healthBar3 = App->textures->Load("Assets/Sprites/life_bar_3.png");
	healthBar4 = App->textures->Load("Assets/Sprites/life_bar_4.png");
	healthBar5 = App->textures->Load("Assets/Sprites/life_bar_5.png");
	healthBar6 = App->textures->Load("Assets/Sprites/life_bar_6.png");
	healthBar7 = App->textures->Load("Assets/Sprites/life_bar_7.png");
	healthBar8 = App->textures->Load("Assets/Sprites/life_bar_8.png");
	healthBar9 = App->textures->Load("Assets/Sprites/life_bar_9.png");

	counter = 0;
	countDown = 0;
	counterFonts = 0;
	counterTransition = 0;
	counterFontsHide = false;
	counterTransHide = false;

	UiTexture = App->textures->Load("Assets/Sprites/1943UI.png");
	InsertCoinRevive = App->textures->Load("Assets/Sprites/InsertCoinRevive.png");

	successTexture = App->textures->Load("Assets/Sprites/levelsuccess.png");

	App->audio->PlayMusic("Assets/Music/MissionClear.ogg", 2.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//path.PushBack({ 1.0f, 0.5f }, 60, &planeAnim);
	//path.PushBack({ 0.8f, 0.5f }, 60, &planeAnim);
	//path.PushBack({ 0.5f, 0.5f }, 60, &planeAnim);
	//path.PushBack({ 0.5f, 0.2f }, 60, &planeAnim);
	//path.PushBack({ -0.5f, 0.2f },60, &planeAnim);
	//path.PushBack({ -0.5f, -0.2f }, 60, &planeAnim);
	//path.PushBack({ -0.5f, -0.2f }, 60, &planeAnim);
	//path.PushBack({ 0.0f, 0.0f }, 3000, &planeAnim);

	currentAnim = &planeAnim;

	path.loop = false;

	return ret;
}

UpdateResult EndScreen::Update()
{


	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN || App->input->pads->start == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	planeAnim.Update();
	path.Update();

	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult EndScreen::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->DrawTexture(successTexture, 0, 0, NULL);

	SDL_Rect recta = currentAnim->GetCurrentFrame();
	App->render->DrawTexture(EndPlane, 250, 300, &recta);
	/*App->render->DrawTexture(EndPlane, 0, 0, &, false);*/

	counter++;
	if (counter / 60)
	{
		App->render->DrawTexture(EndPlane2, 70, 61, NULL, 0.1f);

	}
	if (counter / 80)
	{
		App->render->DrawTexture(EndPlane3, 233, 96, NULL, 0.1f);
		App->textures->Unload(EndPlane2);
	}
	if (counter / 100)
	{
		App->render->DrawTexture(EndPlane4, 323, 147, NULL, 0.1f);
		App->textures->Unload(EndPlane3);
	}
	if (counter / 120)
	{
		App->render->DrawTexture(EndPlane5, 344, 218, NULL, 0.1f);
		App->textures->Unload(EndPlane4);
	}
	if (counter / 140)
	{
		App->render->DrawTexture(EndPlane6, 228, 295, NULL, 0.1f);
		App->textures->Unload(EndPlane5);
	}
	if (counter / 160)
	{
		App->render->DrawTexture(EndPlane7, 212, 386, NULL, 0.1f);
		App->textures->Unload(EndPlane6);
	}
	if (counter / 180)
	{
		App->render->DrawTexture(EndPlane, 119, 359, NULL, 0.1f);
		App->textures->Unload(EndPlane7);
	}
	if (counter / 200)
	{
		App->render->DrawTexture(EndPlane1, 31, 253, NULL, 0.1f);
		App->textures->Unload(EndPlane);

	}
	counterTransition++;
	if ((counterTransition / 60))
	{
		App->fonts->BlitText(100, 200, Font, "m");
	}
	if ((counterTransition / 70))
	{
		App->fonts->BlitText(118, 200, Font, "i");
	}
	if ((counterTransition / 80))
	{
		App->fonts->BlitText(136, 200, Font, "s");
	}
	if ((counterTransition / 90))
	{
		App->fonts->BlitText(154, 200, Font, "s");
	}
	if ((counterTransition / 100))
	{
		App->fonts->BlitText(172, 200, Font, "i");
	}
	if ((counterTransition / 110))
	{
		App->fonts->BlitText(190, 200, Font, "o");
	}
	if ((counterTransition / 110))
	{
		App->fonts->BlitText(208, 200, Font, "n");
	}
	if ((counterTransition / 120))
	{
		App->fonts->BlitText(238, 200, Font, "c");
	}
	if ((counterTransition / 130))
	{
		App->fonts->BlitText(256, 200, Font, "o");
	}
	if ((counterTransition / 140))
	{
		App->fonts->BlitText(274, 200, Font, "m");
	}
	if ((counterTransition / 150))
	{
		App->fonts->BlitText(292, 200, Font, "p");
	}
	if ((counterTransition / 160))
	{
		App->fonts->BlitText(310, 200, Font, "l");
	}
	if ((counterTransition / 170))
	{
		App->fonts->BlitText(328, 200, Font, "e");
	}
	if ((counterTransition / 180))
	{
		App->fonts->BlitText(346, 200, Font, "t");
	}
	if ((counterTransition / 170))
	{
		App->fonts->BlitText(364, 200, Font, "e");
	}
	if ((counterTransition / 170))
	{
		App->fonts->BlitText(382, 200, Font, "d");
	}
	/*if ((counterTransition / 240))
	{
		App->fonts->BlitText(130, 230, Font, "7");
	}
	if ((counterTransition / 260))
	{
		App->fonts->BlitText(148, 230, Font, "1");
	}
	if ((counterTransition / 270))
	{
		App->fonts->BlitText(166, 230, Font, "%");
	}
	if ((counterTransition / 280))
	{
		App->fonts->BlitText(184, 230, Font, "d");
	}
	if ((counterTransition / 290))
	{
		App->fonts->BlitText(202, 230, Font, "e");
	}
	if ((counterTransition / 300))
	{
		App->fonts->BlitText(220, 230, Font, "s");
	}
	if ((counterTransition / 310))
	{
		App->fonts->BlitText(238, 230, Font, "t");
	}
	if ((counterTransition / 320))
	{
		App->fonts->BlitText(256, 230, Font, "r");
	}
	if ((counterTransition / 330))
	{
		App->fonts->BlitText(274, 230, Font, "o");
	}
	if ((counterTransition / 340))
	{
		App->fonts->BlitText(292, 230, Font, "y");
	}
	if ((counterTransition / 350))
	{
		App->fonts->BlitText(310, 230, Font, "e");
	}
	if ((counterTransition / 360))
	{
		App->fonts->BlitText(328, 230, Font, "d");
	}*/
	if (counterTransition / 470)
	{
		App->fonts->BlitText(70, 260, Font, "r");
	}
	if (counterTransition / 480)
	{
		App->fonts->BlitText(88, 260, Font, "e");
	}
	if (counterTransition / 490)
	{
		App->fonts->BlitText(106, 260, Font, "t");
	}
	if (counterTransition / 500)
	{
		App->fonts->BlitText(124, 260, Font, "u");
	}
	if (counterTransition / 510)
	{
		App->fonts->BlitText(142, 260, Font, "r");
	}
	if (counterTransition / 520)
	{
		App->fonts->BlitText(160, 260, Font, "n");
	}
	if (counterTransition / 530)
	{
		App->fonts->BlitText(178, 260, Font, "i");
	}
	if (counterTransition / 540)
	{
		App->fonts->BlitText(196, 260, Font, "n");
	}
	if (counterTransition / 550)
	{
		App->fonts->BlitText(214, 260, Font, "g");
	}
	if (counterTransition / 570)
	{
		App->fonts->BlitText(244, 260, Font, "t");
	}
	if (counterTransition / 580)
	{
		App->fonts->BlitText(262, 260, Font, "o");
	}
	if (counterTransition / 590)
	{
		App->fonts->BlitText(292, 260, Font, "c");
	}
	if (counterTransition / 600)
	{
		App->fonts->BlitText(310, 260, Font, "a");
	}
	if (counterTransition / 610)
	{
		App->fonts->BlitText(328, 260, Font, "r");
	}
	if (counterTransition / 620)
	{
		App->fonts->BlitText(346, 260, Font, "r");
	}
	if (counterTransition / 620)
	{
		App->fonts->BlitText(364, 260, Font, "i");
	}
	if (counterTransition / 620)
	{
		App->fonts->BlitText(382, 260, Font, "e");
	}
	if (counterTransition / 620)
	{
		App->fonts->BlitText(400, 260, Font, "r");
	}

	App->render->DrawTexture(UiTexture, 0, 0, NULL, false);

	App->render->DrawTexture(healthBar1, 20, 570, NULL, false);

	App->render->DrawTexture(UiTexture, 0, 0, NULL, false);

	counter++;
	if ((counter / 60) % 2 == 0)
	{
		App->render->DrawTexture(InsertCoinRevive, 0, 0, NULL, false);
	}

	/*App->render->DrawTexture(endPlane, 0, 0, planeAnim);*/

	return UpdateResult::UPDATE_CONTINUE;
}

bool EndScreen::CleanUp()
{
	planeAnim.Reset();

	App->textures->Unload(successTexture);
	App->textures->Unload(EndPlane);
	return true;
}