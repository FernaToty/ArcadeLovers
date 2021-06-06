#ifndef __ENEMY_MINITURRET_H__
#define __ENEMY_MINITURRET_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_ToneMiniTur : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_ToneMiniTur(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;

	// Enemy animations
	Animation front, back;

	// The enemy animation
	Animation angle[16];
	float degrees;
	int counter;
};

#endif // __ENEMY_MINITURRET_H__