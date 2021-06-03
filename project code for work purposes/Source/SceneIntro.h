#ifndef __SCENEINTRO_H__
#define __SCENEINTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:
	// Constructor
	SceneIntro(bool startEnabled);

	// Destructor
	~SceneIntro();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

	bool CleanUp();

	bool coin = true;
public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* menuTexture = nullptr;
	SDL_Texture* cloudTexture = nullptr;
	SDL_Texture* InsertCoin = nullptr;
	SDL_Texture* Credits = nullptr;
	SDL_Texture* Credit1 = nullptr;
	SDL_Texture* healthBar1 = nullptr;
	SDL_Texture* healthBar2 = nullptr;
	SDL_Texture* healthBar3 = nullptr;
	SDL_Texture* healthBar4 = nullptr;
	SDL_Texture* healthBar5 = nullptr;
	SDL_Texture* healthBar6 = nullptr;
	SDL_Texture* healthBar7 = nullptr;
	SDL_Texture* healthBar8 = nullptr;
	SDL_Texture* healthBar9 = nullptr;

private:

	int counter = 0;
};

#endif	// __SCENEINTRO_H__