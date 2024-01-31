#include "particleControl.h"
#include <math.h>


particleControl::particleControl(RenderWindow *w, int particlesCount) {
	window = w;

	for (int i = 0; i < particlesCount; i++) {
		//particle p(w->getSize().x / 2, w->getSize().y / 2);
		particle p(i * 10 + 1, i * 5 + 1);
		particles.push_back(p);
	}
}


void particleControl::particlesMove() {
	for (auto &i : particles) {
		Vector2f pPos = i.getObj()->getPosition();
		if (Mouse::isButtonPressed(Mouse::Button::Left)) {
			mPos = Mouse::getPosition(*window);
			cout << i.speed << '\t' << pPos.x << '\t' << pPos.y << '\t' << i.isIntersect << endl;

			if (i.speed == 0) { i.speed = 0.01; continue; }
			else if (i.speed < maxSpeed && i.speed > 0) { i.speed *= 1.006; }
			else if (i.speed > maxSpeed) { i.speed /= 1.002; }
			else if (i.speed < 0 && i.speed > minSpeed) { i.speed /= 1.03; if (i.speed > -0.02) i.speed = 0.01; }
			else if (i.speed < minSpeed) { i.speed = minSpeed + 0.1; }

			i.getObj()->move((mPos.x - pPos.x) / 100 * i.speed, (mPos.y - pPos.y) / 100 * i.speed);
		}
		else if(i.speed > 0){
			if (i.speed <= 0.05) { i.speed = 0; }
			else { i.speed /= 1.001; }

			i.getObj()->move((mPos.x - pPos.x) / 300 * i.speed, (mPos.y - pPos.y) / 300 * i.speed);
		}

		
	}

}

void particleControl::checkBounces() {
	for (int i = 0; i < particles.size(); i++) {
		FloatRect f = particles[i].getObj()->getGlobalBounds();
		for (int j = i + 1; j < particles.size(); j++) {
			FloatRect s = particles[j].getObj()->getGlobalBounds();
			if (f.intersects(s) && !particles[j].isIntersect && !particles[i].isIntersect) {
				//cout << "enter" << endl;
				particles[j].isIntersect = true;
				particles[i].isIntersect = true;
				if (particles[i].speed > particles[j].speed) {
					auto fP = particles[i].getObj()->getPosition();
					auto sP = particles[j].getObj()->getPosition();
					particles[j].getObj()->move(Vector2f((mPos.x - sP.x) / (mPos.x - sP.x) * (fP.x > sP.x ? -1 : 1),
						(mPos.y - sP.y) / (mPos.y - sP.y) * (fP.y > sP.y ? -1 : 1)));

					particles[j].speed += particles[i	].speed / 2.;
					if(particles[i].speed > minSpeed)
						particles[i].speed -= particles[i].speed * 2;

				}
				else {
					auto fP = particles[j].getObj()->getPosition();
					auto sP = particles[i].getObj()->getPosition();
					particles[i].getObj()->move(Vector2f((mPos.x - sP.x) / (mPos.x - sP.x) * (fP.x > sP.x ? -1 : 1),
						(mPos.y - sP.y) / (mPos.y - sP.y) * (fP.y > sP.y ? -1 : 1)));

					particles[i].speed += particles[j].speed / 2.;
					if (particles[j].speed > minSpeed)
						particles[j].speed -= particles[j].speed * 2;

				}
			}
			else {
				//cout << "enter" << endl;
				particles[j].isIntersect = false;
				particles[i].isIntersect = false;
			}
		}
	}
}


void particleControl::drawParticles() {
	for (particle i : particles) {
		window->draw(*i.getObj());
	}
}