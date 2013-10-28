#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "MouseInput.h"
#include "World.h"
#include "Camera.h"

class Game {
	public:
		Game();
		~Game();
		void run();

	private:
		sf::RenderWindow _window;
		sf::Clock _clock;

		World _world;
		MouseInput _inputDevice;
		Camera _camera;

		bool _running;
		bool _isSelecting;
		bool _firstMove;
		std::vector<sf::Vector2f> _selectPoints;
		std::vector<Ship*> _selectedShips;

		double _lastX;
		double _lastY;


		void pollForWindowEvent();
		void update();
		void draw();
};

#endif //GAME_H
