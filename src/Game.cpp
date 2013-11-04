#define ARENA_WIDTH 1600
#define ARENA_HEIGHT 1200

#include <iostream>
#include <algorithm>
#include <ctime>

#include "Game.h"
#include "MouseInput.h"
#include "GeomUtil.h"
#include "DroneShip.h"
#include "ShipBomber.h"
#include "ShipMothership.h"

Game::Game() 
	: _window(sf::VideoMode(800,600), "SimpleRTS"),
	  _inputDevice(_window),
	  _running(true),
	  _isSelecting(false),
	  _world(ARENA_WIDTH, ARENA_HEIGHT),
	  _camera(_window, 0, 0),
	  _factory(1),
	  _inShopMode(false),
	  _playerState(NONE) {
	
	_window.setFramerateLimit(60);
	srand(time(NULL));


	//Testing
	//_playerShips.push_back(new DroneShip(200,100,1));
	//_playerShips.push_back(new DroneShip(400,150,1));
	
	_world.addShip(new DroneShip(200, 100, 1));
	_world.addShip(new ShipBomber(200, 150, 1));
	_world.addShip(new DroneShip(400, 150, 1));
	_world.addShip(new DroneShip(400, 350, 2));
	_world.addShip(new ShipBomber(500, 350, 2));
	
	_world.addShip(new ShipMothership(50, 50, 1));
	_world.addShip(new ShipMothership(600, 550, 2));
	//_world.addShip(new DroneShip(450, 250, 1));
	//_world.addShip(new DroneShip(500, 250, 1));
	//_world.addShip(new DroneShip(550, 250, 1));
	//_world.addShip(new DroneShip(450, 300, 2));
	//_world.addShip(new DroneShip(500, 300, 2));
	//_world.addShip(new DroneShip(550, 300, 2));

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
	if (_playerState != NONE)
		return;

	checkWinCondition();

	/*if (rand() % 150 == 0) {
		_world.addShip(new DroneShip(rand()%500, rand()%500, 2));
		_world.addShip(new DroneShip(rand()%500, rand()%500, 1));
	} else if (rand() % 150 == 1) {
	}
	*/
	//} else if (rand() % 150 == 2) {
		//_world.addShip(new DroneShip(rand()%500, rand()%500, 1));
	//}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
		_factory.createShip(ShipType::DRONE);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
		_factory.createShip(ShipType::BOMBER);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
		_factory.createShip(ShipType::DESTROYER);
	}


	_factory.update(dt, &_world);

	_world.cleanProjectiles();
	_world.cleanShips();

	//TODO - Refactor _allShips to allShips (its not an instance/member var)
	auto _allShips = _world.getAllShips();
	for (auto ship : _allShips) {
		ship->updateComponents(dt, &_world);
		ship->update(dt, &_world);
	}

	auto allProjectiles = _world.getAllProjectiles();

	//Update all projectiles
	for (auto projectile : allProjectiles) {
		projectile->update(dt);
	}

	if (_inputDevice.isSelecting()) {
		//Define selection vertices
		_selectPoints.push_back(sf::Vector2f(_inputDevice.getX() + _camera.getPosition().x, _inputDevice.getY() + _camera.getPosition().y));
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
			if (_firstMove) {
				//Make sure we start movement using the coordinates 
				//of the first move "command"
				_lastX = _inputDevice.getX();
				_lastY = _inputDevice.getY();
				_firstMove = false;
			}
			//Move camera
			double currX = _inputDevice.getX();
			double currY = _inputDevice.getY();

			//Check to make sure we don't go past the edges
			_camera.move(_lastX - currX, _lastY - currY);
			_camera.update();

			_lastX = currX;
			_lastY = currY;

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

				ship->setMoveLocation(_inputDevice.getX() + relX + _camera.getPosition().x, _inputDevice.getY() + relY + _camera.getPosition().y);
			}

		}
	} else {
		//Also reset the camera firstmove
		_firstMove = true;
	}

	if (_inputDevice.isAction()) {
		if (_selectedShips.size() > 0) {
			//Set target of ships
			for (auto ship : _world.getEnemyShips(1)) {
				if (hypot(ship->getPosition().x - _inputDevice.getX() - _camera.getPosition().x, 
					  ship->getPosition().y - _inputDevice.getY() - _camera.getPosition().y) < 20) {

					//Set this ship as target for all selected ships
					for (auto sship : _selectedShips) {
						sship->setTargetShip(ship);
					}
				}
			}
		} else {
			//Shop menu
			_inShopMode = true;
		}
	}
	//Shop menu recording
	if (_inShopMode) {
		if (_motionPoints.size() < 60) {
			//We have less than 60 samples
			_motionPoints.push_back(sf::Vector2f(_inputDevice.getX(), _inputDevice.getY()));

		} else {
			_inShopMode = false;

			//Classify movement
			double sumX = 0;
			double sumY = 0;

			for (auto point : _motionPoints) {
				//Note: we want the positions relative to the starting point
				sumX += point.x - _motionPoints[0].x;
				sumY += point.y - _motionPoints[0].y;
			}

			if (fabs(sumX) > fabs(sumY)) {
				//Most likely in X direction
				if (sumX > 0) {
					//Most likely to the right
					std::cout << "Right" << std::endl;
					_factory.createShip(ShipType::DRONE);
				} else {
					//Most likely to the left
					std::cout << "Left" << std::endl;
					_factory.createShip(ShipType::DESTROYER);
				}
			} else {
				if (sumY > 0) {
					//Most likely to the bottom
					std::cout << "Bottom" << std::endl;
					_factory.createShip(ShipType::BOMBER);
				} else {
					//Most likely to the top
					std::cout << "Up" << std::endl;
					_factory.upgrade();
				}
			}
			_motionPoints.clear();
		}
	}
}

void Game::draw() {
	if (_playerState == WIN) {
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(ARENA_WIDTH, ARENA_HEIGHT));
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(0, 0);
		_window.draw(rect);
		return;
	} else if (_playerState == LOSE) {
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(ARENA_WIDTH, ARENA_HEIGHT));
		rect.setFillColor(sf::Color::Red);
		rect.setPosition(0, 0);
		_window.draw(rect);
		return;
	}


	//Mouse pointer graphic
	_window.setMouseCursorVisible(false);
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(2, 2));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(_inputDevice.getX() + _camera.getPosition().x, _inputDevice.getY() + _camera.getPosition().y);
	_window.draw(rect);

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

	if (_inShopMode) {
		//Draw helper pie prompt
	}

	//Testing?
	for (auto point : _motionPoints) {
		sf::RectangleShape r;
		r.setSize(sf::Vector2f(1,1));
		r.setFillColor(sf::Color::Cyan);
		r.setPosition(point);
		_window.draw(r);
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

void Game::checkWinCondition() {
	bool playerShipFound = false;
	int mothershipCount = 0;
	for (auto ship : _world.getAllShips()) {
		if (ship->getName().compare("Mothership") == 0) {
			++mothershipCount;
			if (ship->getTeam() == 1) {
				playerShipFound = true;
			}
		}
	}

	if (playerShipFound == false) {
		_playerState = LOSE;
	} else if (playerShipFound == true && mothershipCount == 1) {
		_playerState = WIN;
	}

	
}
