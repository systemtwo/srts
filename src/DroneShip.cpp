#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "DroneShip.h"

DroneShip::DroneShip(double x, double y) 
	: _x(x),
	  _y(y) {

	_targetX = x;
	_targetY = y;
}

void DroneShip::update(double dt) {
	//Move Drone
	double dist = hypot(_targetX - _x, _targetY - _y);

	//Hack for 0 dist 
	if (dist == 0) 
		dist = 0.0001;

	double ratio = SPEED/dist;
	
	double xspeed = (_targetX - _x) * ratio;
	double yspeed = (_targetY - _y) * ratio;

	_x += xspeed * dt;
	_y += yspeed * dt;
}

void DroneShip::draw(sf::RenderWindow& window) {
	sf::RectangleShape rect;
	if (!_selected)
		rect.setFillColor(sf::Color::Red);
	else 
		rect.setFillColor(sf::Color::Yellow);

	rect.setPosition(sf::Vector2f(_x, _y));
	rect.setSize(sf::Vector2f(2, 2));
	window.draw(rect);

	//Draw target location marker
	
	if (_selected) {
		sf::RectangleShape tmarker;
		tmarker.setFillColor(sf::Color::Cyan);
		tmarker.setPosition(sf::Vector2f(_targetX, _targetY));
		tmarker.setSize(sf::Vector2f(2, 2));
		window.draw(tmarker);
	}

}

sf::Vector2f DroneShip::getPosition() {
	return sf::Vector2f(_x, _y);
}

std::string DroneShip::getName() {
	return std::string("Drone");
}

void DroneShip::setSelected(bool selected) {
	_selected = selected;
}

void DroneShip::setMoveLocation(double x, double y) {
	_targetX = x;
	_targetY = y;
}
