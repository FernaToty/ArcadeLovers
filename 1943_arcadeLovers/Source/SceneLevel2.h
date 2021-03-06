#ifndef __SCENELEVEL2_H__
#define __SCENELEVEL2_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel2 : public Module
{
public:
	// Constructor
	SceneLevel2(bool startEnabled);

	// Destructor
	~SceneLevel2();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* cloudTexture = nullptr;
	SDL_Texture* UiTexture = nullptr;
	SDL_Texture* InsertCoinRevive = nullptr;
	SDL_Texture* healthBar1 = nullptr;
	SDL_Texture* healthBar2 = nullptr;
	SDL_Texture* healthBar3 = nullptr;
	SDL_Texture* healthBar4 = nullptr;
	SDL_Texture* healthBar5 = nullptr;
	SDL_Texture* healthBar6 = nullptr;
	SDL_Texture* healthBar7 = nullptr;
	SDL_Texture* healthBar8 = nullptr;
	SDL_Texture* healthBar9 = nullptr;

	SDL_Texture* Credit1 = nullptr;
	SDL_Texture* Credit2 = nullptr;
	SDL_Texture* Credit3 = nullptr;
	SDL_Texture* Credit4 = nullptr;
	SDL_Texture* Credit5 = nullptr;
	SDL_Texture* Credit6 = nullptr;
	SDL_Texture* Credit7 = nullptr;
	SDL_Texture* Credit8 = nullptr;
	SDL_Texture* Credit9 = nullptr;

	SDL_Texture* Ship = nullptr;
	SDL_Texture* ShipDestroyed = nullptr;

	SDL_Texture* BlackScreen = nullptr;

	//power up
	SDL_Texture* WAY = nullptr;
	SDL_Texture* AUTO = nullptr;

	uint Coin = 0;
	uint TypeWritter = 0;
	uint loopAudio = 0;
	uint lowHp = 0;

	//fonts for the story typing
	int Font = -1;
	char scoreText[150] = { "\0" };

private:
	bool anim = true;

	int countDown = 0;
	int counter = 0;

	int counterTransition = 0;
	bool counterTransHide = true;

	int counterFonts;
	bool counterFontsHide = true;

	bool lose2;
	bool win = false;

	bool ship = true;
	bool delayExpl = false;
	bool textType = false;
	bool introLoop = false;
};

#endif  // __SCENELEVEL2_H__