#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "DroneShip.h"
#include "GeomUtil.h"

DroneShip::DroneShip(double x, double y) 
	: _health(100),
	  _navigation(x, y, 100.0, PI) {
}

void DroneShip::update(double dt) {
	_navigation.update(dt);
}

void DroneShip::draw(sf::RenderWindow& window) {
	sf::RectangleShape rect;
	if (!_selected)
		rect.setFillColor(sf::Color::Red);
	else 
		rect.setFillColor(sf::Color::Yellow);

	rect.setPosition(_navigation.getPosition());
	rect.setSize(sf::Vector2f(2, 2));
	rect.setRotation(_navigation.getAngle());
	window.draw(rect);

	//Draw target location marker
	
	if (_selected) {
		sf::RectangleShape tmarker;
		tmarker.setFillColor(sf::Color::Cyan);
		tmarker.setPosition(_navigation.getTarget());
		tmarker.setSize(sf::Vector2f(2, 2));
		window.draw(tmarker);
	}

}

sf::Vector2f DroneShip::getPosition() {
	return _navigation.getPosition();
}

std::string DroneShip::getName() {
	return std::string("Drone");
}

void DroneShip::setSelected(bool selected) {
	_selected = selected;
}

void DroneShip::setMoveLocation(double x, double y) {
	_navigation.setTarget(x, y);
}
