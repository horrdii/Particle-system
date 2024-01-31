#pragma once

#include "particle.h"
#include <iostream>

using namespace std;


class particleControl
{
protected:
	vector<particle> particles;
	RenderWindow* window;

	float maxSpeed = 1.1f, minSpeed = -2.f;
	Vector2i mPos;
public:
	particleControl(RenderWindow *w, int particlesCount);

	void particlesMove();
	void checkBounces();

	void drawParticles();
};

