#include "SceneLevel1.h"

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

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	//reset counter
	counter = 0;
	countDown = 0;
	counterFonts = 0;
	counterTransition = 0;
	counterFontsHide = false;
	counterTransHide = false;
	ship = true;
	lose = false;

	bgTexture = App->textures->Load("Assets/Sprites/water.png");
	cloudTexture = App->textures->Load("Assets/Sprites/clouds.png");
	UiTexture = App->textures->Load("Assets/Sprites/1943UI.png");
	InsertCoinRevive = App->textures->Load("Assets/Sprites/InsertCoinRevive.png");

	//look up table for fonts in story typing
	char lookupTable2[] = { "0123456789abcdefghijklmnopqrstuvwxyz" };
	Font = App->fonts->Load("Assets/Fonts/Fonts.png", lookupTable2, 1);

	//healtbar
	healthBar1 = App->textures->Load("Assets/Sprites/life_bar_1.png");
	healthBar2 = App->textures->Load("Assets/Sprites/life_bar_2.png");
	healthBar3 = App->textures->Load("Assets/Sprites/life_bar_3.png");
	healthBar4 = App->textures->Load("Assets/Sprites/life_bar_4.png");
	healthBar5 = App->textures->Load("Assets/Sprites/life_bar_5.png");
	healthBar6 = App->textures->Load("Assets/Sprites/life_bar_6.png");
	healthBar7 = App->textures->Load("Assets/Sprites/life_bar_7.png");
	healthBar8 = App->textures->Load("Assets/Sprites/life_bar_8.png");
	healthBar9 = App->textures->Load("Assets/Sprites/life_bar_9.png");

	//Ship sprites
	Ship = App->textures->Load("Assets/Sprites/Ship.png");
	ShipDestroyed = App->textures->Load("Assets/Sprites/ShipDestroyed.png");

	//Coins
	Credit1 = App->textures->Load("Assets/Sprites/Credit1.png");
	Credit2 = App->textures->Load("Assets/Sprites/Credit2.png");
	Credit3 = App->textures->Load("Assets/Sprites/Credit3.png");
	Credit4 = App->textures->Load("Assets/Sprites/Credit4.png");
	Credit5 = App->textures->Load("Assets/Sprites/Credit5.png");
	Credit6 = App->textures->Load("Assets/Sprites/Credit6.png");
	Credit7 = App->textures->Load("Assets/Sprites/Credit7.png");
	Credit8 = App->textures->Load("Assets/Sprites/Credit8.png");
	Credit9 = App->textures->Load("Assets/Sprites/Credit9.png");

	//tone red
	Tone = App->textures->Load("Assets/Sprites/Tone.png");

	//power up
	WAY = App->textures->Load("Assets/Sprites/3WAY.png");
	AUTO = App->textures->Load("Assets/Sprites/AUTO.png");

	//Black Background for transition to lvl2
	BlackScreen = App->textures->Load("Assets/Sprites/BlackBackground.png");

	//coin audio
	Coin = App->audio->LoadFx("Assets/Fx/CoinInserted.wav");

	//lifebar low Fx
	lowHp = App->audio->LoadFx("Assets/Fx/LifeBarLow.wav");

	//TypeWritter audio
	//TypeWritter = App->audio->LoadFx("Assets/Fx/Type.wav");

	//Loop animation Audio 
	loopAudio = App->audio->LoadFx("Assets/Fx/LoopAnimAudio.wav");

	//Scene Audio
	App->audio->PlayMusic("Assets/Music/GamePlayAudio.ogg", 1.0f);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -3000);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -3150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -3300);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -2800);

	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -3000);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -3050);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -3100);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -3150);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -3200);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -3250);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -3300);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -3400);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -3300);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -3450);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -3400);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -3500);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -3800);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -3750);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -3600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -3900);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -4000);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -4150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -4300);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -4350);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -4500);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -4550);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -4600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -4700);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -5000);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -5050);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -5150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -5300);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -5700);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -5250);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -5600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -5820);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 280, -5800);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -5350);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -5700);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -5920);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -6150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -6170);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -6190);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -6210);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 120, -6510);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -6490);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 160, -6470);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -6450);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -6470);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 280, -6490);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -6510);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -6810);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -6790);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -6770);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 320, -6750);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -6770);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -6790);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 400, -6810);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 120, -7060);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -7040);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 160, -7020);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -7000);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -7020);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 280, -7040);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -7060);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -7260);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -7240);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -7220);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 320, -7200);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -7220);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -7240);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 400, -7260);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -7400);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -7420);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -7440);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -7460);

	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -7400);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -7420);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -7440);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -7460);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -7600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -8150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -8100);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -7600);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -8500);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -8480);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -8440);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 320, -8420);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -8440);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -8480);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 400, -8500);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -8750);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -9150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -9100);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -8700);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -8850);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -9250);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -9150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -8850);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -9350);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -9370);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -9390);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -9410);

	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -9420);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -9440);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -9460);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -9480);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -9800);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -9780);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -9760);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 320, -9740);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -9760);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -9780);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 400, -9800);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -10250);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -10450);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -10400);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -10250);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -10600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -10750);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -10700);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -10600);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -10800);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -10820);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -10840);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -10860);

	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -11000);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -11050);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -11100);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -11150);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -11610);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -11590);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -11570);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 320, -11550);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -11570);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -11590);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 400, -11610);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -11800);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -12150);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -12050);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -11800);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -12350);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -12550);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -12500);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -12350);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -12700);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -12720);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -12740);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -12760);

	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -13000);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -13200);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -13150);
	App->enemies->AddEnemy(Enemy_Type::HORPLANE, -25, -13000);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 220, -13460);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -13440);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -13420);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 320, -13400);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -13420);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 380, -13440);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 400, -13460);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -13800);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -14000);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -13950);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -13800);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 360, -14250);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 300, -14450);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 240, -14400);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 180, -14250);

	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 260, -14600);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 200, -14750);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 140, -14700);
	App->enemies->AddEnemy(Enemy_Type::GREENPLANE, 80, -14600);

	//POWERUPS
	App->particles->AddParticle(App->particles->Auto, 200, -2000, Collider::Type::AUTO);
	App->particles->AddParticle(App->particles->threeWayAnim, 200, -3800, Collider::Type::POWERUP);
	App->particles->AddParticle(App->particles->threeWayAnim, 400, -6700, Collider::Type::POWERUP);
	App->particles->AddParticle(App->particles->Auto, 100, -12000, Collider::Type::AUTO);

	// L10: DONE 2: Enable (and properly disable) the player module
	//player animation intro
	App->playerIntro->Enable();
	App->playerIntro->position.x = 215;
	App->playerIntro->position.y = 450;

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	//Finish state
	App->collisions->AddCollider({ 0, -15000, 500, 1000 }, Collider::Type::WIN);
	
	return ret;
}

UpdateResult SceneLevel1::Update()
{
	App->render->camera.y -= 1 * SCREEN_SIZE;
	counter++;
	if (counter / 370)
	{
		App->particles->Enable();
		delayExpl = true;
	}
	if (counter / 400)
	{
		ship = false;
		delayExpl = false;
	}
	if (counter / 600)
	{
		//introLoop = true;
	}
	if (counter / 900)
	{
		counterFontsHide = true;
		textType = true;
		introLoop = false;
	}
	if (counter / 1300)
	{
		textType = false;
	}
	if (counter / 1600)
	{
		counterFontsHide = false;
	}
	if (counter / 2000)
	{
		App->playerIntro->Disable();
		anim = false;
	}
	if (anim == false)
	{
		App->player->Enable();
		App->enemies->Enable();
		App->collisions->Enable();
		counter = 0;
	}
	if (App->player->DescendAnim == true)
	{
		counterTransHide = true;
	}
	if (lose == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->endScreenL, 90);
	}
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SceneLevel1::PostUpdate()
{
	// Draw everything
	App->render->DrawTexture(bgTexture, 0, -12350, NULL);
	App->render->DrawTexture(bgTexture, 0, -25500, NULL);
	App->render->DrawTexture(cloudTexture, 0, -14350, NULL, 0.8f);

	if (delayExpl == true)
	{
		App->particles->AddParticle(App->particles->explosion, 200,   0, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosion, 210,  20, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosion, 220, -15, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosion, 185,  20, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosion, 195, -15, Collider::Type::NONE);
	}
	if (ship == true)
	{
		App->render->DrawTexture(Ship, 0, 0, NULL, 0.1f);
	}
	if (ship == false)
	{
		App->render->DrawTexture(ShipDestroyed, 0, -60, NULL, 0.3f);
	}
	//if (introLoop == true)
	//{
	//	//App->audio->PlayFx(loopAudio);                    //audio of the intro loop too loud
	//}
	//if (textType == true)
	//{
	//	//App->audio->PlayFx(TypeWritter);                  //audio of the typewritter too loud
	//}
	if (counterFontsHide == true)
	{
		App->fonts->BlitText(150, 150, Font, "mission");
		App->fonts->BlitText(320, 150, Font, "1");
		counterFonts++;
		if ((counterFonts / 60))
		{
			App->fonts->BlitText(100, 200, Font, "o");
		}
		if ((counterFonts / 70))
		{
			App->fonts->BlitText(118, 200, Font, "f");
		}
		if ((counterFonts / 80))
		{
			App->fonts->BlitText(136, 200, Font, "f");
		}
		if ((counterFonts / 90))
		{
			App->fonts->BlitText(154, 200, Font, "e");
		}
		if ((counterFonts / 100))
		{
			App->fonts->BlitText(172, 200, Font, "n");
		}
		if ((counterFonts / 110))
		{
			App->fonts->BlitText(190, 200, Font, "s");
		}
		if ((counterFonts / 120))
		{
			App->fonts->BlitText(205, 200, Font, "i");
		}
		if ((counterFonts / 130))
		{
			App->fonts->BlitText(220, 200, Font, "v");
		}
		if ((counterFonts / 140))
		{
			App->fonts->BlitText(238, 200, Font, "e");
		}
		if ((counterFonts / 150))
		{
			App->fonts->BlitText(280, 200, Font, "t");
		}
		if ((counterFonts / 160))
		{
			App->fonts->BlitText(298, 200, Font, "a");
		}
		if ((counterFonts / 170))
		{
			App->fonts->BlitText(316, 200, Font, "r");
		}
		if ((counterFonts / 180))
		{
			App->fonts->BlitText(334, 200, Font, "g");
		}
		if ((counterFonts / 190))
		{
			App->fonts->BlitText(352, 200, Font, "e");
		}
		if ((counterFonts / 200))
		{
			App->fonts->BlitText(370, 200, Font, "t");
		}
		if (counterFonts / 210)
		{
			App->render->DrawTexture(Tone, 0, 0, NULL, false);
		}
		if ((counterFonts / 230))
		{
			App->fonts->BlitText(50, 300, Font, "m");
		}
		if ((counterFonts / 240))
		{
			App->fonts->BlitText(68, 300, Font, "a");
		}
		if ((counterFonts / 250))
		{
			App->fonts->BlitText(86, 300, Font, "y");
		}
		if ((counterFonts / 260))
		{
			App->fonts->BlitText(122, 300, Font, "y");
		}
		if ((counterFonts / 270))
		{
			App->fonts->BlitText(140, 300, Font, "o");
		}
		if ((counterFonts / 280))
		{
			App->fonts->BlitText(158, 300, Font, "u");
		}
		if ((counterFonts / 290))
		{
			App->fonts->BlitText(196, 300, Font, "f");
		}
		if ((counterFonts / 300))
		{
			App->fonts->BlitText(208, 300, Font, "i");
		}
		if ((counterFonts / 310))
		{
			App->fonts->BlitText(226, 300, Font, "g");
		}
		if ((counterFonts / 320))
		{
			App->fonts->BlitText(244, 300, Font, "h");
		}
		if ((counterFonts / 330))
		{
			App->fonts->BlitText(262, 300, Font, "t");
		}
		if ((counterFonts / 340))
		{
			App->fonts->BlitText(298, 300, Font, "b");
		}
		if ((counterFonts / 350))
		{
			App->fonts->BlitText(316, 300, Font, "r");
		}
		if ((counterFonts / 360))
		{
			App->fonts->BlitText(334, 300, Font, "a");
		}
		if ((counterFonts / 370))
		{
			App->fonts->BlitText(352, 300, Font, "v");
		}
		if (counterFonts / 380)
		{
			App->fonts->BlitText(370, 300, Font, "e");
		}
		if ((counterFonts / 390))
		{
			App->fonts->BlitText(388, 300, Font, "l");
		}
		if (counterFonts / 400)
		{
			App->fonts->BlitText(406, 300, Font, "y");
		}
		if (counterFonts == 700)
		{
			counterFonts = 0;
			counterFontsHide = false;
		}
	}

	//POWER UP blit texture
	if (App->player->AutoPU == true)
	{
		App->render->DrawTexture(AUTO, 0, 0, NULL, false);
	}
	if (App->player->powerUp == true)
	{
		App->render->DrawTexture(WAY, 0, 0, NULL, false);
	}

	//If player is dead, insert coin to revive (max 9 coins)
	if (App->player->playerlife == 0)
	{
		switch (App->sceneIntro->coin)
		{
		case 9:
			App->render->DrawTexture(Credit9, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			break;
		case 8:
			App->render->DrawTexture(Credit8, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
				App->audio->PlayFx(Coin);
			}
			break;
		case 7:
			App->render->DrawTexture(Credit7, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
				App->audio->PlayFx(Coin);
			}
			break;
		case 6:
			App->render->DrawTexture(Credit6, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
				App->audio->PlayFx(Coin);
			}
			break;
		case 5:
			App->render->DrawTexture(Credit5, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
				App->audio->PlayFx(Coin);
			}
			break;
		case 4:
			App->render->DrawTexture(Credit4, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
				App->audio->PlayFx(Coin);
			}
			break;
		case 3:
			App->render->DrawTexture(Credit3, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
				App->audio->PlayFx(Coin);
			}
			break;
		case 2:
			App->render->DrawTexture(Credit2, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
				App->audio->PlayFx(Coin);
			}
			break;
		case 1:
			App->render->DrawTexture(Credit1, 0, 0, NULL, false);
			if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN || App->input->pads->start == true)
			{
				App->sceneIntro->coin -= 1;
				App->player->playerRevive = true;
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
				App->audio->PlayFx(Coin);
			}
			break;
		case 0:
			countDown++;
			if ((countDown / 60) % 2 == 0)
			{
				App->render->DrawTexture(InsertCoinRevive, 0, 0, NULL, false);
			}
			if (App->input->keys[SDL_SCANCODE_C] == KEY_DOWN || App->input->pads->r3 == true)
			{
				App->sceneIntro->coin += 1;
				App->audio->PlayFx(Coin);
			}
			// if no coins inserted in 30 seconds GAMEOVER
			if ((countDown / 60) == 20)
			{
				lose = true;
				App->player->destroyed = true;
				App->player->Disable();
				countDown = 0;
			}
			break;
		default:
			break;
		}
	}

	if (anim == false)
	{
		//top UI
		App->render->DrawTexture(UiTexture, 0, 0, NULL, false);
		//player lifebar
		if (App->player->playerlife < 3 && App->player->playerlife != 0)
		{
			App->audio->PlayFx(lowHp);
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
			break;
		case 2:
			App->render->DrawTexture(healthBar8, 20, 570, NULL, false);
			break;
		case 1:
			App->render->DrawTexture(healthBar9, 20, 570, NULL, false);
			break;
		default:
			break;
		}
	}
	
	if (counterTransHide == true)
	{
		App->render->DrawTexture(BlackScreen, 0, 0, NULL, false);
		App->render->DrawTexture(UiTexture, 0, 0, NULL, false);
		//player lifebar
		if (App->player->playerlife < 3 && App->player->playerlife != 0)
		{
			App->audio->PlayFx(lowHp);
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
			break;
		case 2:
			App->render->DrawTexture(healthBar8, 20, 570, NULL, false);
			break;
		case 1:
			App->render->DrawTexture(healthBar9, 20, 570, NULL, false);
			break;
		default:
			break;
		}
		counterTransition++;
		if ((counterTransition / 60))
		{
			App->fonts->BlitText(100, 200, Font, "v");
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
			App->fonts->BlitText(154, 200, Font, "u");
		}
		if ((counterTransition / 100))
		{
			App->fonts->BlitText(172, 200, Font, "a");
		}
		if ((counterTransition / 110))
		{
			App->fonts->BlitText(190, 200, Font, "l");
		}
		if ((counterTransition / 120))
		{
			App->fonts->BlitText(220, 200, Font, "c");
		}
		if ((counterTransition / 130))
		{
			App->fonts->BlitText(238, 200, Font, "o");
		}
		if ((counterTransition / 140))
		{
			App->fonts->BlitText(256, 200, Font, "n");
		}
		if ((counterTransition / 150))
		{
			App->fonts->BlitText(274, 200, Font, "t");
		}
		if ((counterTransition / 160))
		{
			App->fonts->BlitText(292, 200, Font, "a");
		}
		if ((counterTransition / 170))
		{
			App->fonts->BlitText(310, 200, Font, "c");
		}
		if ((counterTransition / 180))
		{
			App->fonts->BlitText(328, 200, Font, "t");
		}
		if ((counterTransition / 190))
		{
			App->fonts->BlitText(358, 200, Font, "w");
		}
		if ((counterTransition / 200))
		{
			App->fonts->BlitText(376, 200, Font, "i");
		}
		if (counterTransition / 210)
		{
			App->fonts->BlitText(394, 200, Font, "t");
		}
		if ((counterTransition / 230))
		{
			App->fonts->BlitText(412, 200, Font, "h");
		}
		if ((counterTransition / 240))
		{
			App->fonts->BlitText(40, 300, Font, "s");
		}
		if ((counterTransition / 260))
		{
			App->fonts->BlitText(58, 300, Font, "u");
		}
		if ((counterTransition / 270))
		{
			App->fonts->BlitText(76, 300, Font, "r");
		}
		if ((counterTransition / 280))
		{
			App->fonts->BlitText(94, 300, Font, "f");
		}
		if ((counterTransition / 290))
		{
			App->fonts->BlitText(112, 300, Font, "a");
		}
		if ((counterTransition / 300))
		{
			App->fonts->BlitText(130, 300, Font, "c");
		}
		if ((counterTransition / 310))
		{
			App->fonts->BlitText(148, 300, Font, "e");
		}
		if ((counterTransition / 320))
		{
			App->fonts->BlitText(178, 300, Font, "f");
		}
		if ((counterTransition / 330))
		{
			App->fonts->BlitText(196, 300, Font, "o");
		}
		if ((counterTransition / 340))
		{
			App->fonts->BlitText(214, 300, Font, "r");
		}
		if ((counterTransition / 350))
		{
			App->fonts->BlitText(232, 300, Font, "c");
		}
		if ((counterTransition / 360))
		{
			App->fonts->BlitText(250, 300, Font, "e");
		}
		if ((counterTransition / 370))
		{
			App->fonts->BlitText(268, 300, Font, "s");
		}
		if (counterTransition / 380)
		{
			App->fonts->BlitText(298, 300, Font, "c");
		}
		if ((counterTransition / 390))
		{
			App->fonts->BlitText(316, 300, Font, "o");
		}
		if (counterTransition / 400)
		{
			App->fonts->BlitText(334, 300, Font, "n");
		}
		if (counterTransition / 410)
		{
			App->fonts->BlitText(352, 300, Font, "f");
		}
		if (counterTransition / 420)
		{
			App->fonts->BlitText(370, 300, Font, "i");
		}
		if (counterTransition / 430)
		{
			App->fonts->BlitText(388, 300, Font, "r");
		}
		if (counterTransition / 440)
		{
			App->fonts->BlitText(406, 300, Font, "m");
		}
		if (counterTransition / 450)
		{
			App->fonts->BlitText(424, 300, Font, "e");
		}
		if (counterTransition / 460)
		{
			App->fonts->BlitText(442, 300, Font, "d");
		}
		if (counterTransition / 470)
		{
			App->fonts->BlitText(100, 400, Font, "c");
		}
		if (counterTransition / 480)
		{
			App->fonts->BlitText(118, 400, Font, "o");
		}
		if (counterTransition / 490)
		{
			App->fonts->BlitText(136, 400, Font, "m");
		}
		if (counterTransition / 500)
		{
			App->fonts->BlitText(154, 400, Font, "m");
		}
		if (counterTransition / 510)
		{
			App->fonts->BlitText(172, 400, Font, "e");
		}
		if (counterTransition / 520)
		{
			App->fonts->BlitText(190, 400, Font, "n");
		}
		if (counterTransition / 530)
		{
			App->fonts->BlitText(208, 400, Font, "c");
		}
		if (counterTransition / 540)
		{
			App->fonts->BlitText(226, 400, Font, "i");
		}
		if (counterTransition / 550)
		{
			App->fonts->BlitText(244, 400, Font, "n");
		}
		if (counterTransition / 560)
		{
			App->fonts->BlitText(262, 400, Font, "g");
		}
		if (counterTransition / 570)
		{
			App->fonts->BlitText(292, 400, Font, "a");
		}
		if (counterTransition / 580)
		{
			App->fonts->BlitText(310, 400, Font, "t");
		}
		if (counterTransition / 590)
		{
			App->fonts->BlitText(328, 400, Font, "t");
		}
		if (counterTransition / 600)
		{
			App->fonts->BlitText(346, 400, Font, "a");
		}
		if (counterTransition / 610)
		{
			App->fonts->BlitText(364, 400, Font, "c");
		}
		if (counterTransition / 620)
		{
			App->fonts->BlitText(382, 400, Font, "k");
		}
		if (counterTransition / 700)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
		}
	}

	return UpdateResult::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// L10: DONE 2: Enable (and properly disable) the player module
	App->player->Disable();
	App->playerIntro->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->playerIntro->flipBack.Reset();
	App->playerIntro->flipForward.Reset();
	App->playerIntro->flipPlane.Reset();
	App->playerIntro->idleAnim.Reset();
	App->playerIntro->runWay.Reset();
	App->playerIntro->smallPlane.Reset();
	App->textures->Unload(bgTexture);
	App->textures->Unload(cloudTexture);

	return true;
}