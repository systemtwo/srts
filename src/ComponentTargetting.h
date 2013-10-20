#ifndef COMPONENT_TARGETTING_H
#define COMPONENT_TARGETTING_H

#include <vector>

#include "Ship.h"

//Finds (or user sets) a target that it attempts to follow

//TODO - Add a enum or something that allows for different targetting techniques
class ComponentTargetting {
	public:
		ComponentTargetting(double x, double y, double scanRadius)
	       		: _x(x),
			  _y(y),
       			  _scanRadius(scanRadius),
       			  _targetShip(NULL) { }

		void setTarget(double x, double y) { _targetX = x; _targetY = y; }
		void setOrigin(double x, double y) { _x = x; _y = y; }
		void setScanRadius(double rad) { _scanRadius = rad; }

		sf::Vector2f getTargetPosition() { return sf::Vector2f(_targetX, _targetX); }
		Ship* getTargetShip() { return _targetShip; }
		sf::Vector2f getOrigin() { return sf::Vector2f(_x, _y); }
		double getScanRadius() { return _scanRadius; }


		void scan(std::vector<Ship*> ships) {
			//Target closest ship
			double minDist = _scanRadius;
			for (auto ship : ships) {
				double diffX = ship->getPosition().x - _x;
				double diffY = ship->getPosition().y - _y;
				if (hypot(diffX, diffY) < minDist) {
					minDist = hypot(diffX, diffY);
					_targetShip = ship;
					_targetX = ship->getPosition().x;
					_targetY = ship->getPosition().y;
					std::cout << "Got target... " << std::endl;
				}
			}
	       	}

	
	private: 
		Ship*  _targetShip;
		double _targetX;
		double _targetY;
		double _x; //Origin
		double _y;
		double _scanRadius;
};

#endif //COMPONENT_TARGETTING_H
