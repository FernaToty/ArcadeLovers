#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	UpdateResult Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	UpdateResult PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

	// Draws gamepad debug info in the screen
	void DebugDrawGamepadInfo();

	//Player life bar
	uint playerlife = 9;
	bool life = false;

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

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation rightAnim;
	Animation leftAnim;
	Animation dodgeForward;
	Animation dodgeBack;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool GodMode = false;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// Font score index
	uint score = 000;
	int Fonts = -1;
	int scoreFont = -1;
	int redScoreFont = 2;

	char scoreText[150] = { "\0" };
	char scoreFontText[150] = { "\0" };
	char redScoreFontText[16] = { "\0" };

	// Debugdraw for gamepad data
	bool debugGamepadInfo = false;
};

#endif // __MODULEPLAYER_H__