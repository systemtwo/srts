#include <iostream>

#include "Game.h"
#include "MouseInput.h"
#include "GeomUtil.h"
#include "DroneShip.h"

Game::Game() 
	: _window(sf::VideoMode(800,600), "SimpleRTS"),
	  _inputDevice(_window),
	  _running(true),
	  _isSelecting(false) {
	
	_window.setFramerateLimit(60);


	//Testing
	_playerShips.push_back(new DroneShip(200,100));
	_playerShips.push_back(new DroneShip(400,150));
	//_playerShips.push_back(new DroneShip(300,500));
	//_playerShips.push_back(new DroneShip(200,100));

	std::vector<sf::Vector2f> poly;
	poly.push_back(sf::Vector2f(50,50));
	poly.push_back(sf::Vector2f(50,150));
	poly.push_back(sf::Vector2f(150,150));
	poly.push_back(sf::Vector2f(150,50));

	if (GeomUtil::pointInPolygon(poly, 100, 100))
		std::cout << "Test 1 passed" << std::endl;
	else 
		std::cout << "Test 1 failed" << std::endl;

}

Game::~Game() {
}

void Game::run() {
	while (_running && _window.isOpen()) {
		pollForWindowEvent();
		update();
		draw();
	}
}

void Game::update() {
	auto dt = (double)_clock.restart().asMilliseconds() / 1000.0;
	for (auto ship : _playerShips) {
		ship->update(dt);
	}

	if (_inputDevice.isSelecting()) {
		_selectPoints.push_back(sf::Vector2f(_inputDevice.getX(), _inputDevice.getY()));
		_isSelecting = true;
	} else {
		if (_isSelecting) {
			//Was just selecting
			_selectedShips.clear();
			for (auto ship : _playerShips) {
				if (GeomUtil::pointInPolygon(_selectPoints, ship->getPosition().x, ship->getPosition().y)) {
					std::cout << "Ship " << ship->getName() << " selected." << std::endl;
					ship->setSelected(true);
					_selectedShips.push_back(ship);
				} else {
					ship->setSelected(false);
				}
			}
		}
		_selectPoints.clear();
		_isSelecting = false;
	}

	if (_inputDevice.isMoving()) {
		if (_selectedShips.size() == 0) {
			//Move camera
		}
		//Find center
		double cx = 0;
		double cy = 0;
		for (auto ship : _selectedShips) {
			cx += ship->getPosition().x;
			cy += ship->getPosition().y;
		}
		cx /= _selectedShips.size();
		cy /= _selectedShips.size();

		for (auto ship : _selectedShips) {
			//Get relative position
			double relX = ship->getPosition().x - cx;
			double relY = ship->getPosition().y - cy;

			ship->setMoveLocation(_inputDevice.getX() + relX, _inputDevice.getY() + relY);
		}

	}
}

void Game::draw() {
	//Mouse pointer graphic
	//_window.setMouseCursorVisible(false);
	//sf::RectangleShape rect;
	//rect.setSize(sf::Vector2f(10,10));
	//rect.setFillColor(sf::Color::Cyan);
	//rect.setPosition(_inputDevice.getX(), _inputDevice.getY());
	//_window.draw(rect);

	for (auto point : _selectPoints) {
		sf::RectangleShape r;
		r.setSize(sf::Vector2f(1,1));
		r.setFillColor(sf::Color::White);
		r.setPosition(point);
		_window.draw(r);
	}

	for (int i = 0; i < _playerShips.size(); i++) {
		_playerShips[i]->draw(_window);
	}

	_window.display();
	_window.clear();
}

void Game::pollForWindowEvent() {
	sf::Event e;
	while (_window.pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			_running = false;
			_window.close();
		}
	}
}
