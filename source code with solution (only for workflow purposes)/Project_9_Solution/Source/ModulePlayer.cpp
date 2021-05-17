#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 123, 25, 38, 24 });

	// Move Left
	leftAnim.PushBack({ 81, 26, 34, 23 });
	leftAnim.PushBack({ 38, 26, 30, 23 });
	leftAnim.loop = false;
	leftAnim.speed = 0.1f;

	// Move Right
	rightAnim.PushBack({ 167, 26, 36, 23 });
	rightAnim.PushBack({ 215, 26, 30, 25 });
	rightAnim.loop = false;
	rightAnim.speed = 0.1f;

	//R = Dodge
	dodgeForward.PushBack({});
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/characteranimation.png");
	currentAnimation = &idleAnim;

	laserFx = App->audio->LoadFx("Assets/Fx/shoot.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 215;
	position.y = 12900;

	destroyed = false;

	collider = App->collisions->AddCollider({ position.x, position.y, 38, 24 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);
	//char lookupTable1[] = { "E000   1234567890" };
	//char lookupTable2[] = { "01234567890ABCDEFGHIJKMNOPQRSTUVWXYZ" };
	//scoreFont = App->fonts->Load("Assets/scores.png", lookupTable1, 1);
	

	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	App->player->position.y -= 1;

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_REPEAT)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_REPEAT)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == Key_State::KEY_REPEAT)
	{
		position.y += speed;
	}

	if (App->input->keys[SDL_SCANCODE_W] == Key_State::KEY_REPEAT)
	{
		position.y -= speed;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 12, position.y + 1, Collider::Type::PLAYER_SHOT);
		newParticle->collider->AddListener(this);
		App->audio->PlayFx(laserFx);
	}

	if (App->input->keys[SDL_SCANCODE_F2] == Key_State::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->death, position.x, position.y, Collider::Type::NONE, 9);
		App->audio->PlayFx(explosionFx);
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 60);
		destroyed = true;
	}

	//3-Way Power-up logic
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN && threeWay)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 12, position.y + 1, Collider::Type::PLAYER_SHOT);
		App->particles->AddParticle(App->particles->threeWayL, position.x + 10, position.y + 1, Collider::Type::PLAYER_SHOT);
		App->particles->AddParticle(App->particles->threeWayR, position.x + 14, position.y + 1, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}

	if (position.x == 465)
	{
		position.x -= speed ;
	}

	if (position.x == 0)
	{
		position.x += speed;
	}

	//There should be a code to implement the restrictions of the Y axis for the player.
	//if(       )
	//{
	//
    //}

	// If no left/right movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_IDLE)
		currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN)
	{
		godMode = !godMode;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", score);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(15, 20, scoreFont, scoreText);
	App->fonts->BlitText(415, 20, scoreFont, scoreText);
	App->fonts->BlitText(225, 20, scoreFont, scoreText);

	App->fonts->BlitText(10, 10, scoreFont, "1player");
	App->fonts->BlitText(410, 10, scoreFont, "2player");
	App->fonts->BlitText(220, 10, scoreFont, "highscore");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		if(App->player->life != 0)
		{
		    if (c1 == collider && c2->type == Collider::Type::POWERUP)
		    {
			    threeWay = true;
			    threeWayTimer = 0;
			    destroyed = false;
		    }
		    else if (c1 == collider && c2->type == Collider::Type::ENEMY)
		    {
				life--;
				destroyed = false;
		    }
			
			if (c1 == collider && c2->type == Collider::Type::WIN)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneWin, 60);
				position.x = 0;
				position.y = 0;
			}

			if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
			{
				score += 10;
			}
		}
		//Player explosion anim
		else if(App->player->life == 0)
		{
			App->particles->AddParticle(App->particles->death, position.x, position.y, Collider::Type::NONE, 9);
			App->audio->PlayFx(explosionFx);
			destroyed = true;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 60); 
		}


	}

	/*if (destroyed = true)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneMenu, 60);
	}*/



}
