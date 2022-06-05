#ifndef _GAME_OF_LIFE_H_
#define _GAME_OF_LIFE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class game_of_life {
private:
	static const unsigned int COLS = 40;
	static const unsigned int ROWS = 40;
	bool _generation[ROWS][COLS];
	bool _next_generation[ROWS][COLS];
	bool random_value();
	bool cell_taken(int i, int j);
	int number_neighbours(int i, int j);
	void drawing();

	RenderWindow* window;
	Clock clock;
	RectangleShape _grid[ROWS][COLS];
	bool have_drawn;

public:
	game_of_life(RenderWindow* window);
	void next_generation();
	void draw();
};

#endif


