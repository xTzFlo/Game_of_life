#include "game_of_life.h"

bool game_of_life::random_value()
{
	static int first = 0;
	if (!first)
	{
		srand(time(nullptr));
		first = 1;
	}

	int val = rand() % 4;

	return val == 0; // 25% chance of true
}


bool game_of_life::cell_taken(int i, int j)
{
	if (i >= 0 && j >= 0 && i < ROWS && j < COLS)
		return _generation[i][j];
	return false;
}

int game_of_life::number_neighbours(int i, int j)
{
	int sum = 0;

	if (cell_taken(i - 1, j - 1))
		sum++;

	if (cell_taken(i, j - 1))
		sum++;

	if (cell_taken(i + 1, j - 1))
		sum++;

	if (cell_taken(i - 1, j))
		sum++;

	if (cell_taken(i + 1, j))
		sum++;

	if (cell_taken(i - 1, j + 1))
		sum++;

	if (cell_taken(i, j + 1))
		sum++;

	if (cell_taken(i + 1, j + 1))
		sum++;

	return sum;
}


game_of_life::game_of_life(RenderWindow* window)
{
	this->window = window;
	this->clock = Clock();

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			_generation[i][j] = random_value();

			_grid[i][j] = RectangleShape(Vector2f(10, 10));
			_grid[i][j].setPosition(i * 10, j * 10);
		}
	}

	drawing();
}

void game_of_life::next_generation()
{
	if (have_drawn)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				int number = number_neighbours(i, j);
				if (cell_taken(i, j))
				{
					if (number == 2 || number == 3)
						_next_generation[i][j] = true;
					else
						_next_generation[i][j] = false;
				}
				else
				{
					if (number == 3)
						_next_generation[i][j] = true;
					else
						_next_generation[i][j] = false;
				}
			}
		}

		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				_generation[i][j] = _next_generation[i][j];
			}
		}

		have_drawn = false;
	}
}


void game_of_life::draw()
{
	Time t = clock.getElapsedTime();
	if (t.asMilliseconds() >= 2)
	{
		drawing();
	}
}

void game_of_life::drawing()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (cell_taken(i, j))
				_grid[i][j].setFillColor(Color(255, 255, 255));
			else
				_grid[i][j].setFillColor(Color(0, 0, 0));
			window->draw(_grid[i][j]);
		}
	}

	window->display();
	clock.restart();
	have_drawn = true;
}