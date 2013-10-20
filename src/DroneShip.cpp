#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "DroneShip.h"
#include "GeomUtil.h"
#include "ComponentNavigationNormal.h"

DroneShip::DroneShip(double x, double y, int team) 
	: _health(100),
	  _navigation(new ComponentNavigationNormal(x, y, 100.0, PI)),
	  _targetting(x, y, 100),
	  _team(team) {
	
	_health.setSize(sf::Vector2f(20, 5));
	
}

void DroneShip::update(double dt, World* world) {
	_navigation->update(dt);
	//Should be:
	//1) If move command is given discard any targetting and do not scan
	//2) If not moving + no move command, target an enemy
	//3) If we already have a target, keep following it unless 1)
	
	std::cout << "This is ship of team [" << _team << "]: ";
	//Move this into a switch() {case}?
	if (_state == MOVING && _navigation->atTargetLocation()) {
		//Ship arrived where player directed, so begin scanning to attack
		_state = SCANNING;
		_targetting.setOrigin(_navigation->getPosition());
	}

	if (_state == SCANNING) {
		if (_targetting.getTargetShip() == NULL) {
			//No Ship targetted
			std::cout << "No ship targetted...";
			_targetting.scan(world->getEnemyShips(_team));
			std::cout << world->getEnemyShips(_team).size() << "ships found" << std::endl;

		} else if (world->isShipDead(_targetting.getTargetShip())) {
			//Targetted ship is dead / does not exist
			_targetting.scan(world->getEnemyShips(_team));
			std::cout << "Ship is dead..." << std::endl;
		} else {
			//Ship has been found
			_state = ATTACKING;
		}
	}

	if (_state == ATTACKING) {
		_navigation->setTarget(_targetting.getTargetShip()->getPosition());
		std::cout << "Attacking! " << std::endl;
	}
}

void DroneShip::draw(sf::RenderWindow& window) {
	//Draw Ship
	sf::RectangleShape rect;
	switch (_team) {
		case 1:
			if (!_selected)
				rect.setFillColor(sf::Color::Red);
			else 
				rect.setFillColor(sf::Color::Yellow);
			break;
		case 2:
			rect.setFillColor(sf::Color::Magenta);
			break;
		default:
			break;

	}

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

//Controller MUST call this! (AI or Player)
void DroneShip::setMoveLocation(double x, double y) {
	_navigation->setTarget(x, y);
	_state = MOVING;
}
