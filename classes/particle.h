#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;


class particle
{
protected:
	CircleShape obj;
	Texture t;

	float radius = 5.;
public:
	float speed = 0.;
	bool isIntersect = false;

	particle(float posX, float posY);

	CircleShape* getObj();
};

