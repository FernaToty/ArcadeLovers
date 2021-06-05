#ifndef __MODULEPLAYERANIM_H__
#define __MODULEPLAYERANIM_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Path.h"

struct SDL_Texture;
struct Collider;

class ModulePlayerAnim : public Module
{
public:
	// Constructor
	ModulePlayerAnim(bool startEnabled);

	// Destructor
	~ModulePlayerAnim();

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

	//Player life bar
	uint life = 10;

	//Player R dodge counter
	uint R = 4;


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
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	bool menuAnim = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[150] = { "\0" };

};

#endif // __MODULEPLAYERANIM_H__