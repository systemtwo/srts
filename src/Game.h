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
		sf::RenderWindow _window;
		sf::Clock _clock;

		std::vector<sf::Vector2f> _selectPoints;
		std::vector<Ship*> _playerShips;
		std::vector<Ship*> _selectedShips;
		MouseInput _inputDevice;
		bool _running;
		bool _isSelecting;

		void pollForWindowEvent();
		void update();
		void draw();
};

#endif //GAME_H
