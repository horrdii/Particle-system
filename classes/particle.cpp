#include "particle.h"


particle::particle(float posX, float posY) {
	/*Image img;
	img.loadFromFile("src/circle.png");

	t.loadFromImage(img);*/

	obj.setFillColor(Color::Red);
	obj.setRadius(radius);
	obj.setPosition(Vector2f(posX, posY));
}

CircleShape* particle::getObj() {
	return &obj;
}