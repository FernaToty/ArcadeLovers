#include "ModulePlayer.h"

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

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{

	if(life == false)
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


		// flip Front
		dodgeForward.PushBack({ 32,  87, 38, 22 });
		dodgeForward.PushBack({ 75,  87, 43, 21 });
		dodgeForward.PushBack({ 121,  91, 43, 15 });
		dodgeForward.PushBack({ 168,  88, 43, 20 });
		dodgeForward.PushBack({ 212,  85, 43, 25 });
		dodgeForward.PushBack({ 212, 110, 44, 29 });
		dodgeForward.PushBack({ 259,  82, 42, 24 });
		dodgeForward.PushBack({ 304,  87, 42, 20 });
		dodgeForward.PushBack({ 351,  88, 40, 17 });
		dodgeForward.PushBack({ 260, 113, 39, 18 });
		dodgeForward.PushBack({ 169, 112, 37, 20 });
		dodgeForward.PushBack({ 123, 111, 38, 22 });
		dodgeForward.PushBack({ 123, 25, 38, 24 });
		dodgeForward.loop = false;
		dodgeForward.speed = 0.05f;

		//idle sprite
	}

	/*if (Rpressed == true)
	{
		
	}*/
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

	laserFx = App->audio->LoadFx("Assets/Fx/Shoot.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 212;
	position.y = -1613;

	// L10: DONE 4: Retrieve the player when playing a second time
	playerlife = 9;
	R = 3;
	destroyed = false;
	Rpressed = false;
	timerR = 0;
	GodMode = false;

	//reset the point when playing again
	score = 0;

	// L6: DONE 3: Add a collider to the player
	collider = App->collisions->AddCollider({ position.x, position.y, 38, 24 }, Collider::Type::PLAYER, this);

	char lookupTable1[] = { "0123456789 " };
	scoreFont = App->fonts->Load("Assets/Fonts/scoreFont.png", lookupTable1, 1);
	redScoreFont = App->fonts->Load("Assets/Fonts/redScoreFont.png", lookupTable1, 1);

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	DebugFonts = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);

	char lookupTable2[] = { "0123456789abcdefghijklmnopqrstuvwxyz" };
	Font = App->fonts->Load("Assets/Fonts/Fonts.png", lookupTable2, 1);


	return ret;
}

UpdateResult ModulePlayer::Update()
{
	// Get gamepad info
	GamePad& pad = App->input->pads[0];

	// Moving the player with the camera scroll
	App->player->position.y -= 1;

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_1] == KeyState::KEY_DOWN)
	{
		App->input->ShakeController(0, 12, 0.33f);
	}

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_2] == KeyState::KEY_DOWN)
	{
		App->input->ShakeController(0, 36, 0.66f);
	}

	// Debug key for gamepad rumble testing purposes
	if (App->input->keys[SDL_SCANCODE_3] == KeyState::KEY_DOWN)
	{
		App->input->ShakeController(0, 60, 1.0f);
	}

	// L10: DONE: Implement gamepad support
	if (App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_REPEAT || pad.left_x < 0.0f)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_REPEAT || pad.left_x > 0.0f)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KeyState::KEY_REPEAT || pad.left_y > 0.0f)
	{
		if (position.y < App->render->camera.y + 580)
		{
			position.y += speed;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KeyState::KEY_REPEAT || pad.left_y < 0.0f)
	{
		if (position.y > App->render->camera.y + 50)
		{
			position.y -= speed;
		}
	}

	if (R != 0)
	{
		if (Rpressed == false)
		{
			if (App->input->keys[SDL_SCANCODE_R] == KeyState::KEY_DOWN || pad.y == true)
			{
				Rpressed = !Rpressed;
				R--;
			}
		}
	}

	if (!destroyed)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == KeyState::KEY_REPEAT || pad.a == true || pad.b == true || pad.r2 == true)
		{
			if (shotCountdown == 0)
			{
				Particle* newParticle = App->particles->AddParticle(App->particles->laser, position.x + 9, position.y - 3, Collider::Type::PLAYER_SHOT);
				newParticle->collider->AddListener(this);
				App->audio->PlayFx(laserFx);
				App->input->ShakeController(0, 90, 0.66f);
				shotCountdown = shotMaxCountdown;
			}
		}

	}

	if (App->input->keys[SDL_SCANCODE_F3] == KeyState::KEY_DOWN)
	{
		GodMode = !GodMode;
	}

	if (App->input->keys[SDL_SCANCODE_F4] == KeyState::KEY_DOWN)
	{
		playerlife = 0;
	}

	if (position.x == 465)
	{
		position.x -= speed;
	}

	if (position.x == 0)
	{
		position.x += speed;
	}
	
	// If no left/right movement detected, set the current animation back to idle
	if (Rpressed == false)
	{
		timerR = 0;
		dodgeForward.Reset();
		if (pad.enabled)
		{
			if (pad.left_x == 0.0f && pad.left_y == 0.0f) currentAnimation = &idleAnim;
		}
		else if (App->input->keys[SDL_SCANCODE_A] == KeyState::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_D] == KeyState::KEY_IDLE)
			currentAnimation = &idleAnim;
	}
	if (Rpressed == true)
	{
		currentAnimation = &dodgeForward;
		timerR++;
		if (timerR / 500)
		{
			Rpressed = !Rpressed;
		}
	}


	// Switch gamepad debug info
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN || pad.l3 == true)
		debugGamepadInfo = !debugGamepadInfo;

	// L6: DONE 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	// Update shot countdown
	if (shotCountdown > 0) --shotCountdown;

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->DrawTexture(texture, position.x, position.y, &rect);
	}

	if (playerRevive)
	{
		destroyed = false;
		playerlife = 9;
		playerRevive = !playerRevive;
		collider = App->collisions->AddCollider({ position.x, position.y, 38, 24 }, Collider::Type::PLAYER, this);
	}

	////////////////////////////*player DEATH*////////////////////////
	if (playerlife <= 0)
	{
		destroyed = true;
		//App->input->ShakeController(0, 90, 0.66f);
		App->collisions->RemoveCollider(collider);
		// L10: DONE 3: Go back to the intro scene when the player gets killed
		//App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
	}
	// Draw UI (score) --------------------------------------

	sprintf_s(scoreFontText, 10, "%7d", score);
	App->fonts->BlitText(30, 35, scoreFont, scoreFontText);

	sprintf_s(redScoreFontText, 10, "%7d", score);
	App->fonts->BlitText(210, 35, redScoreFont, redScoreFontText);

	sprintf_s(scoreFontText, 10, "%7d", score);
	App->fonts->BlitText(460, 35, scoreFont, "0");
	
	switch (App->player->R)
	{
	case 3:
		App->fonts->BlitText(210, 50, Font, "r");
		App->fonts->BlitText(225, 50, Font, "r");
		App->fonts->BlitText(240, 50, Font, "r");
		break;
	case 2:
		App->fonts->BlitText(210, 50, Font, "r");
		App->fonts->BlitText(225, 50, Font, "r");
		break;
	case 1:
		App->fonts->BlitText(210, 50, Font, "r");
		break;
	default:
		break;
	}
	

	if (debugGamepadInfo == true) DebugDrawGamepadInfo();
	

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// L6: DONE 5: Detect collision with a wall. If so, destroy the player.
	if (Rpressed == false)
	{
		if (GodMode == false)
		{
			if ((c1 == collider) && (c2->type == Collider::Type::ENEMY))
			{
				App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 0);
				App->input->ShakeController(0, 60, 0.66f);
				App->audio->PlayFx(explosionFx);
				playerlife--;
				destroyed = false;
			}
		}
	}
	
	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 20;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WIN)
	{
		destroyed = false;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
	}
}

void ModulePlayer::DebugDrawGamepadInfo()
{
	GamePad& pad = App->input->pads[0];

	sprintf_s(scoreText, 150, "pad 0 %s, press 1/2/3 for rumble", (pad.enabled) ? "plugged" : "not detected");
	App->fonts->BlitText(5, 110, DebugFonts, scoreText);

	sprintf_s(scoreText, 150, "buttons %s %s %s %s %s %s %s %s %s %s %s",
		(pad.a) ? "a" : "",
		(pad.b) ? "b" : "",
		(pad.x) ? "x" : "",
		(pad.y) ? "y" : "",
		(pad.start) ? "start" : "",
		(pad.back) ? "back" : "",
		(pad.guide) ? "guide" : "",
		(pad.l1) ? "lb" : "",
		(pad.r1) ? "rb" : "",
		(pad.l3) ? "l3" : "",
		(pad.r3) ? "r3" : ""
	);
	App->fonts->BlitText(5, 120, DebugFonts, scoreText);

	sprintf_s(scoreText, 150, "dpad %s %s %s %s",
		(pad.up) ? "up" : "",
		(pad.down) ? "down" : "",
		(pad.left) ? "left" : "",
		(pad.right) ? "right" : ""
	);
	App->fonts->BlitText(5, 130, DebugFonts, scoreText);

	sprintf_s(scoreText, 150, "left trigger  %0.2f", pad.l2);
	App->fonts->BlitText(5, 140, DebugFonts, scoreText);
	sprintf_s(scoreText, 150, "right trigger %0.2f", pad.r2);
	App->fonts->BlitText(5, 150, DebugFonts, scoreText);

	sprintf_s(scoreText, 150, "left thumb    %.2fx, %0.2fy", pad.left_x, pad.left_y);
	App->fonts->BlitText(5, 160, DebugFonts, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.left_dz);
	App->fonts->BlitText(5, 170, DebugFonts, scoreText);

	sprintf_s(scoreText, 150, "right thumb   %.2fx, %0.2fy", pad.right_x, pad.right_y);
	App->fonts->BlitText(5, 180, DebugFonts, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.right_dz);
	App->fonts->BlitText(5, 190, DebugFonts, scoreText);
}