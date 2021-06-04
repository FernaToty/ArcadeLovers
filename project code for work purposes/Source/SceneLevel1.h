#ifndef __SCENELEVEL1_H__
#define __SCENELEVEL1_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	// Constructor
	SceneLevel1(bool startEnabled);

	// Destructor
	~SceneLevel1();

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

	uint Coin = 0;

private:

	int counter = 0;
};

#endif  // __SCENELEVEL1_H__