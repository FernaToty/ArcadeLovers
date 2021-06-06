#include "EndScreenL.h"

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

EndScreenL::EndScreenL(bool startEnabled) : Module(startEnabled)
{
	
}

EndScreenL::~EndScreenL()
{

}

// Load assets
bool EndScreenL::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	char lookupTable2[] = { "0123456789abcdefghijklmnopqrstuvwxyz" };
	Font = App->fonts->Load("Assets/Fonts/Fonts.png", lookupTable2, 1);

	counter = 0;
	countDown = 0;
	counterFonts = 0;
	counterTransition = 0;
	counterFontsHide = false;
	counterTransHide = false;

	UiTexture = App->textures->Load("Assets/Sprites/1943UI.png");
	InsertCoinRevive = App->textures->Load("Assets/Sprites/InsertCoinRevive.png");

	/*successTexture = App->textures->Load("Assets/Sprites/levelsuccess.png");*/
	defeatTexture = App->textures->Load("Assets/Sprites/BlackBackgrounf.png");

	App->audio->PlayMusic("Assets/Music/MissionFailed.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}



UpdateResult EndScreenL::Update()
{

	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN || App->input->pads->start == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult EndScreenL::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->DrawTexture(defeatTexture, 0, 0, NULL);

	counterTransition++;
	if ((counterTransition / 60))
	{
		App->fonts->BlitText(180, 200, Font, "m");
	}
	if ((counterTransition / 70))
	{
		App->fonts->BlitText(198, 200, Font, "i");
	}
	if ((counterTransition / 80))
	{
		App->fonts->BlitText(216, 200, Font, "s");
	}
	if ((counterTransition / 90))
	{
		App->fonts->BlitText(234, 200, Font, "s");
	}
	if ((counterTransition / 100))
	{
		App->fonts->BlitText(252, 200, Font, "i");
	}
	if ((counterTransition / 110))
	{
		App->fonts->BlitText(270, 200, Font, "o");
	}
	if ((counterTransition / 110))
	{
		App->fonts->BlitText(288, 200, Font, "n");
	}
	if ((counterTransition / 120))
	{
		App->fonts->BlitText(190, 230, Font, "f");
	}
	if ((counterTransition / 130))
	{
		App->fonts->BlitText(208, 230, Font, "a");
	}
	if ((counterTransition / 140))
	{
		App->fonts->BlitText(226, 230, Font, "i");
	}
	if ((counterTransition / 150))
	{
		App->fonts->BlitText(244, 230, Font, "l");
	}
	if ((counterTransition / 160))
	{
		App->fonts->BlitText(262, 230, Font, "e");
	}
	if ((counterTransition / 170))
	{
		App->fonts->BlitText(280, 230, Font, "d");
	}
	
	//App->render->DrawTexture(UiTexture, 0, 0, NULL, false);

	//App->render->DrawTexture(InsertCoinRevive, 0, 0, NULL, false);

	return UpdateResult::UPDATE_CONTINUE;
}

bool EndScreenL::CleanUp()
{
	App->textures->Unload(defeatTexture);
	App->textures->Unload(UiTexture);
	App->textures->Unload(InsertCoinRevive);
	return true;
}