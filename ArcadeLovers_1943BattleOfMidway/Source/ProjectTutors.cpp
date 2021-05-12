#include "ProjectTutors.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

ProjectTutors::ProjectTutors(bool startEnabled) : Module(startEnabled)
{

}

ProjectTutors::~ProjectTutors()
{

}

// Load assets
bool ProjectTutors::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/projectTutors.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}



Update_Status ProjectTutors::Update()
{
	
	
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 50);
	

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status ProjectTutors::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}