#include "ModulePlayerAnim.h"

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

ModulePlayerAnim::ModulePlayerAnim(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 123, 25, 38, 24 });

	// Move Left
	idleAnim.PushBack({ 123, 25, 38, 24 });
	leftAnim.PushBack({ 81, 26, 34, 23 });
	leftAnim.PushBack({ 38, 26, 30, 23 });
	leftAnim.loop = false;
	leftAnim.speed = 0.1f;

	// Move Right
	idleAnim.PushBack({ 123, 25, 38, 24 });
	rightAnim.PushBack({ 167, 26, 36, 23 });
	rightAnim.PushBack({ 215, 26, 30, 25 });
	rightAnim.loop = false;
	rightAnim.speed = 0.1f;

	path.PushBack({ 10.0f, 12.0f },  20, &idleAnim);
	path.PushBack({  0.0f, 12.0f },  10, &idleAnim);
	path.PushBack({  0.0f, -1.0f }, 300, &idleAnim); //Starts in place
	path.PushBack({  0.8f, -1.0f }, 200, &rightAnim);
	path.PushBack({ -0.8f, -1.0f }, 300, &leftAnim);
	path.PushBack({  0.0f, -1.0f }, 400, &idleAnim); //Stays in place
	path.PushBack({  0.8f, -2.0f }, 100, &rightAnim); //Goes Up and Right
	path.PushBack({  0.0f, -1.0f },  50, &idleAnim); //Stays in place
	path.PushBack({  0.8f, -1.0f }, 70, &rightAnim); //Goes Right
	path.PushBack({  0.0f, -1.0f }, 100, &idleAnim); //Stays in place
	path.PushBack({ -0.8f,  0.1f }, 100, &leftAnim); //Goes Down and Left
	path.PushBack({  0.0f, -1.0f }, 500, &idleAnim); //Stays in place
	path.PushBack({ -0.8f, -1.0f }, 100, &leftAnim); //Goes Left
	path.PushBack({  0.0f, -1.0f }, 100, &idleAnim); //Stays in place
	path.PushBack({  0.8f, -1.2f }, 350, &rightAnim);//Goes Right and Up
	path.PushBack({ -0.8f, -1.0f }, 300, &leftAnim); //Goes Left
	path.PushBack({  0.8f,  0.1f }, 100, &rightAnim);//Goes Right and Down
	path.PushBack({  0.0f, -1.0f }, 300, &idleAnim); //Stays in place
	path.PushBack({ -0.8f, -1.0f }, 100, &leftAnim);
	path.PushBack({  0.8f, -1.0f }, 100, &rightAnim);
	path.PushBack({  0.0f, -1.0f },  50, &idleAnim); //Stays in Middle
	path.PushBack({  0.8f, -1.0f }, 100, &rightAnim);//Goes right
	path.PushBack({ -0.8f, -1.0f }, 300, &leftAnim);
	path.PushBack({  0.8f, -1.0f }, 200, &rightAnim);
	path.PushBack({  0.0f, -1.0f }, 500, &idleAnim);
	path.PushBack({  0.0f, -2.0f }, 200, &idleAnim); //Goes Up
	path.PushBack({ -0.8f,  0.1f }, 100, &leftAnim); //Goes Down and Left
	path.PushBack({  0.8f,  0.1f }, 100, &rightAnim);//Goes Right and Down
	path.PushBack({ -0.8f, -1.0f }, 100, &leftAnim); //Goes Left
	path.PushBack({  0.8f, -2.0f }, 100, &rightAnim); //Goes Up and Right
	path.PushBack({  0.8f,  0.1f }, 100, &rightAnim);//Goes Right and Down
	path.PushBack({  0.0f, -2.0f }, 100, &idleAnim); //Goes  UP
	path.PushBack({ -0.8f,  0.1f }, 100, &leftAnim); //Goes Down and Left
	path.PushBack({  0.0f,  0.1f }, 100, &idleAnim); //Goes  Down
	path.PushBack({  0.0f, -2.0f }, 100, &idleAnim); //Goes  UP
	path.PushBack({  0.8f,  0.1f }, 70, &rightAnim);//Goes Right and Down
	path.PushBack({  0.0f, -2.0f }, 100, &idleAnim); //Goes  UP
	path.PushBack({ -0.8f, -1.0f }, 70, &rightAnim); //Goes Left
	path.PushBack({  0.0f, -1.0f }, 300, &idleAnim); //Stays in place
	path.PushBack({  0.0f, -2.0f }, 250, &idleAnim); //Goes Up
	path.PushBack({ 0.8f,  0.1f }, 100, &rightAnim);//Goes Right and Down
	path.PushBack({ -0.8f,  0.1f }, 100, &leftAnim); //Goes Down and Left
	path.PushBack({ -0.8f, -1.0f }, 100, &leftAnim); //Goes Left
	path.PushBack({ 0.8f, -2.0f }, 100, &rightAnim); //Goes Up and Right
	path.PushBack({ 0.8f,  0.1f }, 100, &rightAnim);//Goes Right and Down
	path.PushBack({ 0.0f, -2.0f }, 100, &idleAnim); //Goes  UP
	path.PushBack({ -0.8f, 0.1f }, 100, &leftAnim); //Goes Down and Left
	path.PushBack({ 0.0f,  0.1f }, 100, &idleAnim); //Goes  Down
	path.PushBack({ 0.0f, -2.0f }, 100, &idleAnim); //Goes  UP
	path.PushBack({ 0.8f,  0.1f }, 70, &rightAnim);//Goes Right and Down
	path.PushBack({ 0.0f, -2.0f }, 100, &idleAnim); //Goes  UP
	path.PushBack({ -0.8f, -1.0f }, 70, &rightAnim); //Goes Left
	path.PushBack({ 0.0f, -1.0f }, 300, &idleAnim); //Stays in place
	path.PushBack({ 0.0f, -2.0f }, 200, &idleAnim); //Goes Up
	path.PushBack({ -0.8f, 0.1f }, 100, &leftAnim); //Goes Down and Left
	path.PushBack({ 0.0f, -1.0f },  50, &idleAnim); //Stays in place
	path.PushBack({ 0.8f, -2.0f }, 100, &rightAnim); //Goes Up and Right
	path.PushBack({ 0.0f, -1.0f }, 50, &idleAnim); //Stays in place
	path.PushBack({ 0.0f,  0.0f }, 100, &idleAnim); //Goes  Down
	path.PushBack({ 0.8f, -1.0f }, 100, &rightAnim);//Goes right
	path.PushBack({ -0.8f, -1.0f }, 50, &leftAnim); //Goes Left
	path.PushBack({ 0.0f, -1.0f }, 50, &idleAnim); //Stays in place
	path.PushBack({  -0.8f, -1.0f }, 50, &leftAnim); //Goes Left
	path.PushBack({  0.0f, -1.0f }, 50, &idleAnim); //Stays in place
	path.PushBack({ -0.8f, -1.0f }, 50, &leftAnim); //Goes Left
	path.PushBack({ 0.0f, -1.0f }, 50, &idleAnim); //Stays in place
	path.PushBack({ 0.8f, -1.0f }, 300, &rightAnim);//Goes right
	path.PushBack({ 0.0f, -1.0f }, 50, &idleAnim); //Stays in place
	path.PushBack({ -0.8f, -1.0f }, 270, &leftAnim); //Goes Left
	path.PushBack({ 0.0f, -1.0f }, 50, &idleAnim); //Stays in place
	path.loop = false;
}

ModulePlayerAnim::~ModulePlayerAnim()
{

}

bool ModulePlayerAnim::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/characteranimation.png");
	currentAnimation = &idleAnim;

	//laserFx = App->audio->LoadFx("Assets/Fx/shoot.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 215;
	position.y = 450;

	// L10: DONE 4: Retrieve the player when playing a second time
	destroyed = false;

	// L6: DONE 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 34, 23 }, Collider::Type::PLAYER, this);

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	return ret;
}

UpdateResult ModulePlayerAnim::Update()
{
	// Moving the player with the camera scroll

	path.Update();
	currentAnimation->Update();
	position = path.GetRelativePosition();
	currentAnimation = path.GetCurrentAnimation();
	
	if (shotCountdown == 0)
	{
		Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 9, position.y - 3, Collider::Type::PLAYER_SHOT);
		newParticle->collider->AddListener(this);
		//App->audio->PlayFx(laserFx);
		//App->input->ShakeController(0, 90, 0.66f);
		shotCountdown = 30;
	}


	if (position.x == 465)
	{
		position.x -= speed;
	}

	if (position.x == 0)
	{
		position.x += speed;
	}

	// L6: DONE 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	// Update shot countdown
	if (shotCountdown > 0) --shotCountdown;

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModulePlayerAnim::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->DrawTexture(texture, position.x, position.y, &rect);
	}

	// Draw UI (score) --------------------------------------
	/*sprintf_s(scoreText, 10, "%7d", score);
	App->fonts->BlitText(58, 248, scoreFont, scoreText);
	*/
	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayerAnim::OnCollision(Collider* c1, Collider* c2)
{
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.
	if ((c1 == collider) && (destroyed == false))
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		// L10: DONE 3: Go back to the intro scene when the player gets killed
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
	}
}

bool ModulePlayerAnim::CleanUp()
{
	return true;
}