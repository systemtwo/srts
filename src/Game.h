#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "MouseInput.h"

class Game {
	public:
		Game();
		~Game();
		void run();

	private:
		std::vector<sf::Vector2f> _selectPoints;
		std::vector<Ship> _playerShips;
		MouseInput _inputDevice;

		sf::RenderWindow _window;
		sf::Clock _clock;
		bool _running;

		void pollForWindowEvent();
		void update();
		void draw();
};

#endif //GAME_H
