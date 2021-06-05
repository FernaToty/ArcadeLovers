#include "SceneMembers.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneMembers::SceneMembers(bool startEnabled) : Module(startEnabled)
{

}

SceneMembers::~SceneMembers()
{

}

// Load assets
bool SceneMembers::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/arcadeLovers2.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

UpdateResult SceneMembers::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_DOWN || App->input->pads->a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	else
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 500);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult SceneMembers::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->DrawTexture(bgTexture, 0, 0, NULL);

	return UpdateResult::UPDATE_CONTINUE;
}