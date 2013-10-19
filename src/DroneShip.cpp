#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "DroneShip.h"
#include "GeomUtil.h"
#include "ComponentNavigationNormal.h"

DroneShip::DroneShip(double x, double y, int team) 
	: _health(100),
	  _navigation(new ComponentNavigationNormal(x, y, 100.0, PI)),
	  _team(team) {
	
	_health.setSize(sf::Vector2f(20, 5));
	
}

void DroneShip::update(double dt, World* world) {
	_navigation->update(dt);
}

void DroneShip::draw(sf::RenderWindow& window) {
	//Draw Ship
	sf::RectangleShape rect;
	if (!_selected)
		rect.setFillColor(sf::Color::Red);
	else 
		rect.setFillColor(sf::Color::Yellow);

	rect.setPosition(_navigation->getPosition());
	rect.setSize(sf::Vector2f(10, 10));
	rect.setOrigin(sf::Vector2f(5,5));
	rect.setRotation(GeomUtil::radToDeg(_navigation->getAngle()));
	window.draw(rect);

	//Draw target location marker
	if (_selected) {
		sf::RectangleShape tmarker;
		tmarker.setFillColor(sf::Color::Cyan);
		tmarker.setPosition(_navigation->getTarget());
		tmarker.setSize(sf::Vector2f(2, 2));
		window.draw(tmarker);
	}

	//Draw Healthbar
	_health.draw(window, _navigation->getPosition().x - 10, _navigation->getPosition().y - 15);

}

sf::Vector2f DroneShip::getPosition() {
	return _navigation->getPosition();
}

std::string DroneShip::getName() {
	return std::string("Drone");
}

int DroneShip::getTeam() {
	return _team;
}

void DroneShip::setSelected(bool selected) {
	_selected = selected;
}

void DroneShip::setMoveLocation(double x, double y) {
	_navigation->setTarget(x, y);
}
