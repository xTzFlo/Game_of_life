#include "game_of_life.h"

int main() {
	RenderWindow window(sf::VideoMode(400, 400), "Game of life");
	window.setFramerateLimit(60);
	game_of_life game(&window);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		game.draw();
		game.next_generation();
	}

	return 0;
}