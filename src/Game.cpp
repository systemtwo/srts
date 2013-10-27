#define ARENA_WIDTH 1600
#define ARENA_HEIGHT 1200

#include <iostream>
#include <algorithm>

#include "Game.h"
#include "MouseInput.h"
#include "GeomUtil.h"
#include "DroneShip.h"

Game::Game() 
	: _window(sf::VideoMode(800,600), "SimpleRTS"),
	  _inputDevice(_window),
	  _running(true),
	  _isSelecting(false),
	  _world(ARENA_WIDTH, ARENA_HEIGHT) {
	
	_window.setFramerateLimit(60);


	//Testing
	//_playerShips.push_back(new DroneShip(200,100,1));
	//_playerShips.push_back(new DroneShip(400,150,1));
	
	//_world.addShip(new DroneShip(200, 100, 1));
	_world.addShip(new DroneShip(400, 150, 1));
	_world.addShip(new DroneShip(400, 350, 2));

#ifdef WITH_TESTS
	std::vector<sf::Vector2f> poly;
	poly.push_back(sf::Vector2f(50,50));
	poly.push_back(sf::Vector2f(50,150));
	poly.push_back(sf::Vector2f(150,150));
	poly.push_back(sf::Vector2f(150,50));

	if (GeomUtil::pointInPolygon(poly, 100, 100))
		std::cout << "Test 1 passed" << std::endl;
	else 
		std::cout << "Test 1 failed" << std::endl;

#endif //WITH_TESTS
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

	_world.cleanProjectiles();
	_world.cleanShips();

	//TODO - Refactor _allShips to allShips (its not an instance/member var)
	auto _allShips = _world.getAllShips();
	for (auto ship : _allShips) {
		ship->update(dt, &_world);
	}

	auto allProjectiles = _world.getAllProjectiles();

	//Update all projectiles
	for (auto projectile : allProjectiles) {
		projectile->update(dt);
	}

	if (_inputDevice.isSelecting()) {
		//Define selection vertices
		_selectPoints.push_back(sf::Vector2f(_inputDevice.getX(), _inputDevice.getY()));
		_isSelecting = true;
	} else {
		if (_isSelecting) {
			//Was just selecting
			_selectedShips.clear();
			auto _friendlyShips = _world.getTeamShips(1);
			for (auto ship : _friendlyShips) {
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

	//Remove dead ships from selection
	std::vector<Ship*>::size_type i = 0;
	while (i < _selectedShips.size()) {
		auto ship = _selectedShips[i];
		if (_world.isShipDead(ship)) {
			_selectedShips.erase(_selectedShips.begin() + i);
		} else {
			i++;
		}
	}

	if (_inputDevice.isMoving()) {
		if (_selectedShips.size() == 0) {
			//Move camera
		} else {
			//Otherwise move ships
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


	auto allShips = _world.getAllShips();
	for (unsigned int i = 0; i < allShips.size(); i++) {
		allShips[i]->draw(_window);
	}

	auto allProjectiles = _world.getAllProjectiles();
	for (auto projectile : allProjectiles) {
		projectile->draw(_window);
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
