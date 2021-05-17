#include "teamMembers.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

TeamMembers::TeamMembers(bool startEnabled) : Module(startEnabled)
{

}

TeamMembers::~TeamMembers()
{

}

// Load assets
bool TeamMembers::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/arcadeLovers2.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}



Update_Status TeamMembers::Update()
{
	
	App->fade->FadeToBlack(this, (Module*)App->projectTutors, 500);


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status TeamMembers::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}