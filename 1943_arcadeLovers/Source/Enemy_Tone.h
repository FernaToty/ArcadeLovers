#ifndef __ENEMY_ENEMYTONE_H__
#define __ENEMY_ENEMYTONE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Tone : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Tone(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The enemy animation
	Animation tone;

	// The path that will define the position in the world
	Path path;
};

#endif 
