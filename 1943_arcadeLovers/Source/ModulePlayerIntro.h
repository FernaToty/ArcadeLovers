#ifndef __MODULEPLAYERINTRO_H__
#define __MODULEPLAYERINTRO_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Path.h"

struct SDL_Texture;
struct Collider;

class ModulePlayerIntro : public Module
{
public:
	// Constructor
	ModulePlayerIntro(bool startEnabled);

	// Destructor
	~ModulePlayerIntro();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	UpdateResult Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	UpdateResult PostUpdate() override;

	bool CleanUp();

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;


public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// Countdown to handle shot spacing
	int shotMaxCountdown = 20;
	int shotCountdown = 0;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	//Path
	Path path;

	// A set of animations
	Animation smallPlane;
	Animation runWay;
	Animation idleAnim;
	Animation flipForward;
	Animation flipBack;
	Animation flipPlane;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

};

#endif // __MODULEPLAYERINTRO_H__