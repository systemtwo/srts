#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "MouseInput.h"
#include "World.h"
#include "Camera.h"
#include "Background.h"

#include "Factory.h"

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
		Background _background;

		Factory _factory;
		Factory _enemyFactory;
		bool _inShopMode;
		std::vector<sf::Vector2f> _motionPoints;

		enum PlayerState {NONE, WIN, LOSE} _playerState;
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
		void checkWinCondition();
};

#endif //GAME_H
