#include <iostream>

#include "Game.h"
#include "MouseInput.h"

Game::Game() 
	: _window(sf::VideoMode(800,600), "SimpleRTS"),
	  _running(true),
	  _inputDevice(_window) {
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
	auto dt = _clock.restart().asMilliseconds();
	for (auto ship : _playerShips) {
		ship.update(dt);
	}
	if (_inputDevice.isSelecting()) {
		_selectPoints.push_back(sf::Vector2f(_inputDevice.getX(), _inputDevice.getY()));
	}
}

void Game::draw() {
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(10,10));
	rect.setFillColor(sf::Color::Cyan);
	rect.setPosition(_inputDevice.getX(), _inputDevice.getY());
	std::cout << _inputDevice.getX() << ", " << _inputDevice.getY() << std::endl;
	_window.draw(rect);

	for (auto ship : _playerShips) {
		ship.draw(_window);
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
