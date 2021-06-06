#include "ModulePlayerIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "Animation.h"
#include "ModuleEnemies.h"

#include <stdio.h>

ModulePlayerIntro::ModulePlayerIntro(bool startEnabled) : Module(startEnabled)
{
	// small plane
	smallPlane.PushBack({ 179, 148, 19, 14 });

	// runway
	runWay.PushBack({ 131, 147, 22, 15 });
	runWay.PushBack({ 83, 145, 27, 18 });
	runWay.PushBack({ 33, 145, 36, 20 });
	runWay.loop = false;
	runWay.speed = 0.1f;

	// flip Front
	flipForward.PushBack({ 32,  87, 38, 22 });
	flipForward.PushBack({ 75,  87, 43, 21 });
	flipForward.PushBack({ 121,  91, 43, 15 });
	flipForward.PushBack({ 168,  88, 43, 20 });
	flipForward.loop = false;
	flipForward.speed = 0.15f;

	//flip plane
	flipPlane.PushBack({ 212,  85, 43, 25 });
	flipPlane.PushBack({ 212, 110, 44, 29 });
	flipPlane.loop = false;
	flipPlane.speed = 0.1f;

	// flip Back
	flipBack.PushBack({ 259,  82, 42, 24 });
	flipBack.PushBack({ 304,  87, 42, 20 });
	flipBack.PushBack({ 351,  88, 40, 17 });
	flipBack.PushBack({ 260, 113, 39, 18 });
	flipBack.PushBack({ 169, 112, 37, 20 });
	flipBack.PushBack({ 123, 111, 38, 22 });
	flipBack.loop = false;
	flipBack.speed = 0.15f;

	//idle sprite
	idleAnim.PushBack({ 123, 25, 38, 24 });

	path.PushBack({ 10.0f, 12.0f }, 20, &smallPlane);
	path.PushBack({ 0.0f, 12.0f }, 10, &smallPlane);
	path.PushBack({ 0.0f, -1.0f }, 900, &smallPlane);
	path.PushBack({ 0.0f, -2.0f }, 100, &smallPlane);
	path.PushBack({ 0.0f, -2.0f }, 80, &runWay);
	path.PushBack({ 0.15f, -1.5f }, 80, &flipForward);
	path.PushBack({ 0.0f, 0.5f }, 200, &flipPlane);
	path.PushBack({ 0.0f, -1.05f }, 80, &flipBack);
	path.PushBack({ 0.0f, -2.0f }, 90, &idleAnim);
	path.PushBack({ 0.0f, -1.0f }, 100, &idleAnim);
	path.loop = false;
}

ModulePlayerIntro::~ModulePlayerIntro()
{

}

bool ModulePlayerIntro::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/characteranimation.png");
	currentAnimation = &idleAnim;

	position.x = 215;
	position.y = 450;

	destroyed = false;

	return ret;
}

UpdateResult ModulePlayerIntro::Update()
{
	// Moving the player with the camera scroll
	path.Update();
	currentAnimation->Update();
	position = path.GetRelativePosition();
	currentAnimation = path.GetCurrentAnimation();

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModulePlayerIntro::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->DrawTexture(texture, position.x, position.y, &rect);
	}
	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayerIntro::OnCollision(Collider* c1, Collider* c2)
{

}

bool ModulePlayerIntro::CleanUp()
{
	return true;
}