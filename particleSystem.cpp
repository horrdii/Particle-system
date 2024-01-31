#include "classes/particleControl.h"


const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 800;
RenderWindow window;

int main() {
	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RECCCCCCCCC");
	particleControl pc(&window, 2);

	Event event;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window.close();
				break;
			}
		}

		pc.particlesMove();
		pc.checkBounces();

		window.clear();

		pc.drawParticles();
		
		window.display();
	}
}
