#pragma once

#ifndef __ENEMY_HORIZONTALPLANE_H__
#define __ENEMY_HORIZONTALPLANE__

#include "Enemy.h"
#include "Path.h"

class Enemy_HorizontalPlane : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_HorizontalPlane(int x, int y);

	// The enemy is going to perform a sinusoidal movement
	void Update() override;

private:
	// The position (as ratio) in the wave at a specific moment
	float waveRatio = 0.0f;

	// The speed at which the wave ratio is increased
	float waveRatioSpeed = 0.025f;

	// The original spawning position. The wave will be calculated from that
	int spawn_y = 0;

	// The total height of the wave
	int waveHeight = 50;

	// The enemy animation
	Animation flyAnim, flyFlip, flyFlip2, flyFlip3, flyBack;

	// The path that will define the position in the world
	Path path;

};

#endif // __ENEMY_GREENPLANE_H__