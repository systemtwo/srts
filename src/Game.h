#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "Ship.h"

class Game {
	public:
		Game();
		~Game();
		void init();
		void run();

	private:
		std::vector<Ship> playerShips;

		//sf::RenderWindow window;
};

#endif //GAME_H
