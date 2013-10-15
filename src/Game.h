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
		std::vector<Ship*> _playerShips;
		MouseInput _inputDevice;
		bool _isSelecting;
		bool _running;

		sf::RenderWindow _window;
		sf::Clock _clock;

		void pollForWindowEvent();
		void update();
		void draw();
};

#endif //GAME_H
