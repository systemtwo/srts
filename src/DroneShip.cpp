#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "DroneShip.h"
#include "GeomUtil.h"

DroneShip::DroneShip(double x, double y) 
	: _x(x),
	  _y(y) {

	_targetX = x;
	_targetY = y;
	_angle = 1.57;
}

void DroneShip::update(double dt) {
	//Fix angle if needed
	if (_angle > (3.0 * PI))
		_angle -= 2.0 * PI;
	if (_angle < -PI) 
		_angle += 2.0 * PI;


	//Turn towards target
	double targetAngle = atan2(_targetY - _y, _targetX - _x);
	if (targetAngle < 0)
		targetAngle = (2.0 * PI) + targetAngle;

	//Cross product method
	double vecTargetX = _targetX - _x;
	double vecTargetY = _targetY - _y;

	double vecFacingX = cos(_angle);
	double vecFacingY = sin(_angle);


	std::cout <<"Cross product" << ((vecTargetX * vecFacingY) - (vecTargetY * vecFacingX)) << std::endl;
	if (((vecTargetX * vecFacingY) - (vecTargetY * vecFacingX)) > 0) 
		_angle -= TURNING_SPEED * dt;
	else
		_angle += TURNING_SPEED * dt;

	
	//Move with turning
	double xmove = SPEED * cos(_angle) * dt;
	double ymove = SPEED * sin(_angle) * dt;

	_x += xmove;
	_y += ymove;

	/*
	std::cout << "dt: " << dt << std::endl;
	std::cout << "Non-dt speeds: " << SPEED * cos(_angle) << ", " << SPEED * sin(_angle) << std::endl;
	std::cout << "Moving speed: " << xmove << ", " << ymove << std::endl;
	std::cout << "Current Angle: " << _angle << std::endl;
	std::cout << "Target Angle: " << targetAngle << std::endl;
	*/
}

void DroneShip::draw(sf::RenderWindow& window) {
	sf::RectangleShape rect;
	if (!_selected)
		rect.setFillColor(sf::Color::Red);
	else 
		rect.setFillColor(sf::Color::Yellow);

	rect.setPosition(sf::Vector2f(_x, _y));
	rect.setSize(sf::Vector2f(2, 2));
	rect.setRotation(_angle);
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
